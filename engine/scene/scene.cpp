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

#include "scene.hpp"

#include "core/class.hpp"
#include "core/engine.hpp"
#include "debug/profiler.hpp"
#include "scene/scene_manager.hpp"

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

    void Scene::init() {
        m_root                  = Engine::instance()->scene_manager()->make_object(SID("root"));
        m_root->m_scene         = this;
        m_root->m_is_in_scene   = true;
        m_root->m_name_absolute = m_root->m_name;

        m_registry = std::make_unique<SceneRegistry>();
        m_registry->register_type<SceneObject>();
        m_registry->register_type<SceneComponent>();
        m_registry->register_type<Spatial2d>();
        m_registry->register_type<Camera2d>();
        m_registry->register_type<CanvasItem>();
        m_registry->register_type<CanvasLayer>();
        m_registry->register_type<CanvasText>();
        m_registry->register_type<ScriptComponent>();
        m_registry->register_type<SpriteInstance>();
        m_registry->register_type<Particles2d>();
        m_registry->register_type<AudioSource2d>();
        m_registry->register_type<AudioListener2d>();

        m_system_render_2d = std::make_unique<SystemRender2d>(this);
        m_system_script    = std::make_unique<SystemScript>(this);
    }

    void Scene::shutdown() {
        WG_AUTO_PROFILE_SCENE();

        m_root->shutdown();
    }

    void Scene::add_child(ref_ptr<SceneObject> object) {
        m_root->add_child(object);
    }
    SceneObject* Scene::get_child(int idx) {
        return m_root->get_child(idx);
    }
    SceneObject* Scene::find_child(const StringId& name) {
        WG_AUTO_PROFILE_SCENE();

        if (m_root->get_name() == name) {
            return m_root.get();
        }

        return m_root->find_child(name);
    }

    const StringId& Scene::get_name() {
        return m_name;
    }
    SceneRegistry* Scene::get_registry() {
        return m_registry.get();
    }
    SystemRender2d* Scene::get_system_render_2d() {
        return m_system_render_2d.get();
    }
    SystemScript* Scene::get_system_script() {
        return m_system_script.get();
    }
    void Scene::register_class() {
        auto* cls = Class::register_class<Scene>();
        cls->add_property(Property(VarType::StringId, SID("name"), SID("get_name")));
        cls->add_method(Method(VarType::StringId, SID("get_name"), {}), &Scene::get_name, {});
    }

}// namespace wmoge