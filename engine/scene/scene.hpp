/**********************************************************************************/
/* Game engine tutorial                                                           */
/* Available at github https://github.com/EgorOrachyov/game-engine-tutorial       */
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

#ifndef GAME_ENGINE_TUTORIAL_SCENE_HPP
#define GAME_ENGINE_TUTORIAL_SCENE_HPP

#include "core/class.hpp"
#include "core/fast_vector.hpp"
#include "platform/window.hpp"
#include "render/render_engine.hpp"
#include "scene/scene_component.hpp"
#include "scene/scene_object.hpp"
#include "scene/scene_registry.hpp"
#include "systems/system_render_2d.hpp"
#include "systems/system_script.hpp"

namespace wmoge {

    /**
     * @class Scene
     * @brief Scene objects container representing virtual logical game scene
     */
    class Scene final : public Object {
    public:
        WG_OBJECT(Scene, Object);

        void init();
        void shutdown();

        void               add_child(ref_ptr<SceneObject> object);
        class SceneObject* get_child(int idx);
        class SceneObject* find_child(const StringId& name);
        const StringId&    get_name();
        SceneRegistry*     get_registry();
        SystemRender2d*    get_system_render_2d();
        SystemScript*      get_system_script();

    private:
        friend class ScenePacked;
        friend class SceneManager;

        std::unique_ptr<SceneRegistry>  m_registry;
        std::unique_ptr<SystemRender2d> m_system_render_2d;
        std::unique_ptr<SystemScript>   m_system_script;
        ref_ptr<SceneObject>            m_root;
        StringId                        m_name;
    };

}// namespace wmoge

#endif//GAME_ENGINE_TUTORIAL_SCENE_HPP
