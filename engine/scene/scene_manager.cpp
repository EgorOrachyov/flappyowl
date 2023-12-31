/**********************************************************************************/
/* Flappyowl game                                                                 */
/* Available at github https://github.com/EgorOrachyov/flappyowl                  */
/**********************************************************************************/
/* MIT License                                                                    */
/*                                                                                */
/* Copyright (c) 2023 Egor Orachyov                                               */
/*                                                                                */
/* Permission is hereby granted, free of charge, to any person obtaining a copy   */
/* of this software and associated documentation files (the "Software"), to deal  */
/* in the Software without restriction, including without limitation the rights   */
/* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell      */
/* copies of the Software, and to permit persons to whom the Software is          */
/* furnished to do so, subject to the following conditions:                       */
/*                                                                                */
/* The above copyright notice and this permission notice shall be included in all */
/* copies or substantial portions of the Software.                                */
/*                                                                                */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR     */
/* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,       */
/* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE    */
/* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER         */
/* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,  */
/* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE  */
/* SOFTWARE.                                                                      */
/**********************************************************************************/

#include "scene_manager.hpp"

#include "core/engine.hpp"
#include "debug/profiler.hpp"
#include "scene/scene_container.hpp"
#include "scene/scene_object.hpp"

#include "components/audio_listener_2d.hpp"
#include "components/audio_source_2d.hpp"
#include "components/camera_2d.hpp"
#include "components/canvas_item.hpp"
#include "components/canvas_layer.hpp"
#include "components/canvas_text.hpp"
#include "components/particles_2d.hpp"
#include "components/script_component.hpp"
#include "components/spatial_2d.hpp"
#include "components/sprite_instance.hpp"
#include "components/tag.hpp"

namespace wmoge {

    SceneManager::SceneManager() {
        register_container(std::make_unique<TSceneContainerMem<SceneObject>>());
        register_container(std::make_unique<TSceneContainerMem<SceneComponent>>());
        register_container(std::make_unique<TSceneContainerMem<Spatial2d>>());
        register_container(std::make_unique<TSceneContainerMem<Camera2d>>());
        register_container(std::make_unique<TSceneContainerMem<CanvasItem>>());
        register_container(std::make_unique<TSceneContainerMem<CanvasLayer>>());
        register_container(std::make_unique<TSceneContainerMem<CanvasText>>());
        register_container(std::make_unique<TSceneContainerMem<ScriptComponent>>());
        register_container(std::make_unique<TSceneContainerMem<SpriteInstance>>());
        register_container(std::make_unique<TSceneContainerMem<Particles2d>>());
        register_container(std::make_unique<TSceneContainerMem<AudioSource2d>>());
        register_container(std::make_unique<TSceneContainerMem<AudioListener2d>>());

        WG_LOG_INFO("init scene manager");
    }
    SceneManager::~SceneManager() {
        shutdown();
    }

    void SceneManager::shutdown() {
        WG_AUTO_PROFILE_SCENE();

        m_running.reset();
        m_next_running.reset();

        for (auto& scene : m_scenes) {
            scene->shutdown();
        }

        m_scenes.clear();
        m_to_shutdown.clear();

        WG_LOG_INFO("shutdown scene manager");
    }
    void SceneManager::next_running(ref_ptr<Scene> scene) {
        std::lock_guard guard(m_mutex);

        assert(scene);
        assert(m_scenes.find(scene) != m_scenes.end());

        m_next_running = scene;
    }
    void SceneManager::shutdown_scene(ref_ptr<Scene> scene) {
        std::lock_guard guard(m_mutex);

        assert(scene);
        assert(m_scenes.find(scene) != m_scenes.end());

        m_to_shutdown.insert(scene);
    }
    void SceneManager::register_container(std::unique_ptr<SceneContainerMem> mem) {
        std::lock_guard guard(m_mutex);

        auto* cls         = mem->get_class();
        m_containers[cls] = std::move(mem);
    }
    ref_ptr<Scene> SceneManager::get_running_scene() {
        return m_running;
    }
    ref_ptr<Scene> SceneManager::make_scene(const StringId& name) {
        auto scene    = make_ref<Scene>();
        scene->m_name = name;
        scene->init();

        std::lock_guard guard(m_mutex);
        m_scenes.insert(scene);

        return scene;
    }
    ref_ptr<SceneObject> SceneManager::make_object(StringId name) {
        auto* cls       = SceneObject::class_ptr_static();
        auto* container = get_container(cls);

        ref_ptr<SceneObject> object(reinterpret_cast<SceneObject*>(container->create()));
        object->m_name = name;
        return object;
    }
    SceneContainerMem* SceneManager::get_container(const Class* cls) {
        std::lock_guard guard(m_mutex);

        auto query = m_containers.find(cls);
        return query != m_containers.end() ? query->second.get() : nullptr;
    }
    void SceneManager::on_start_frame() {
        WG_AUTO_PROFILE_SCENE();
    }
    void SceneManager::on_update() {
        WG_AUTO_PROFILE_SCENE();

        std::lock_guard guard(m_mutex);

        if (!m_running && !m_next_running) {
            WG_LOG_ERROR("no active scene to process");
            return;
        }
        if (!m_running) {
            // Ok, since have next to run in the next frame
            return;
        }

        auto* system_render_2d = m_running->get_system_render_2d();
        system_render_2d->process();

        auto* system_script = m_running->get_system_script();
        system_script->process();
    }
    void SceneManager::on_debug_draw() {
        WG_AUTO_PROFILE_SCENE();
    }
    void SceneManager::on_end_frame() {
        WG_AUTO_PROFILE_SCENE();

        std::lock_guard guard(m_mutex);

        // do switch at the end of the frame in case if
        // scene has some resources which are still not loaded

        if (m_next_running) {
            m_running = std::move(m_next_running);
        }

        if (m_to_shutdown.find(m_running) != m_to_shutdown.end()) {
            m_running.reset();
        }

        for (auto& scene : m_to_shutdown) {
            scene->shutdown();
            m_scenes.erase(scene);
        }

        m_to_shutdown.clear();
    }

}// namespace wmoge