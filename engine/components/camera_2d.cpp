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

#include "camera_2d.hpp"

#include "core/engine.hpp"
#include "event/event_manager.hpp"
#include "event/event_window.hpp"
#include "platform/window_manager.hpp"

namespace wmoge {

    void Camera2d::set_viewport(const Rect2i& viewport) {
        m_viewport = viewport;
    }
    void Camera2d::set_screen_size(const Vec2f& screen_size) {
        m_screen_size = screen_size;
    }
    const ref_ptr<Window>& Camera2d::get_window() const {
        return m_window;
    }
    const Rect2i& Camera2d::get_viewport() const {
        return m_viewport;
    }
    const Vec2f& Camera2d::get_screen_size() const {
        return m_screen_size;
    }

    bool Camera2d::on_load_from_yaml(const YamlConstNodeRef& node) {
        if (!SceneComponent::on_load_from_yaml(node)) {
            return false;
        }

        if (node.has_child("screen_size")) {
            m_screen_size = Yaml::read_vec2f(node["screen_size"]);
        }

        return true;
    }
    void Camera2d::on_scene_enter() {
        CanvasItem::on_scene_enter();

        auto engine = Engine::instance();

        m_window        = engine->window_manager()->primary_window();
        m_viewport      = Rect2i{0, 0, m_window->fbo_width(), m_window->fbo_height()};
        m_window_update = make_listener<EventWindow>([this](const EventWindow& event) {
            if (event.window == m_window && event.notification == WindowNotification::FramebufferResized) {
                m_viewport = Rect2i{0, 0, m_window->fbo_width(), m_window->fbo_height()};
            }
            return false;
        });

        engine->event_manager()->subscribe(m_window_update);
    }
    void Camera2d::on_scene_exit() {
        CanvasItem::on_scene_exit();

        auto engine = Engine::instance();
        engine->event_manager()->unsubscribe(m_window_update);
    }
    void Camera2d::on_transform_updated() {
        CanvasItem::on_transform_updated();
    }

}// namespace wmoge