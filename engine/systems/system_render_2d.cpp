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

#include "system_render_2d.hpp"

#include "components/camera_2d.hpp"
#include "components/canvas_item.hpp"
#include "components/canvas_text.hpp"
#include "components/particles_2d.hpp"
#include "components/sprite_instance.hpp"
#include "core/engine.hpp"
#include "core/log.hpp"
#include "debug/profiler.hpp"
#include "render/canvas.hpp"
#include "scene/scene.hpp"

namespace wmoge {

    SystemRender2d::SystemRender2d(class Scene* scene) : SceneSystem(scene) {
        m_canvas = std::make_unique<Canvas>();
    }

    void SystemRender2d::process() {
        WG_AUTO_PROFILE_RENDER();

        auto* engine   = Engine::instance();
        auto* registry = m_scene->get_registry();

        // find any camera to draw
        std::optional<Camera2d*> active_camera = registry->first_matching<Camera2d>([](auto&) { return true; });

        if (!active_camera.has_value()) {
            WG_LOG_ERROR("no active camera set for 2d rendering");
            return;
        }

        float dt = float(engine->get_delta_time_game());

        // animate sprites
        registry->for_each<SpriteInstance>([dt](SpriteInstance& instance) {
            instance.on_animate(dt);
        });

        // advance time of particles for simulation
        registry->for_each<Particles2d>([dt](Particles2d& particles2d) {
            particles2d.advance_time(dt);
        });

        // collect and sort layers
        std::vector<std::pair<int, CanvasLayer*>> layers;

        registry->for_each<CanvasLayer>([&](CanvasLayer& layer) {
            layers.emplace_back(layer.get_id(), &layer);
        });

        std::sort(layers.begin(), layers.end(), [](const auto& a, const auto& b) { return a.first > b.first; });

        // draw items per layers
        auto* camera = active_camera.value();

        m_canvas->set_window(camera->get_window());
        m_canvas->set_viewport(camera->get_viewport());
        m_canvas->set_screen_size(camera->get_screen_size());

        m_canvas->set_fill_color(Color::BLACK4f);
        m_canvas->draw_filled_rect(Vec2f{}, camera->get_screen_size());

        m_canvas->push(camera->get_matr_global_inv());
        m_canvas->push(camera->get_screen_size() * 0.5, 0.0f);

        for (const auto& it : layers) {
            int          id    = it.first;
            CanvasLayer* layer = it.second;

            m_canvas->push(layer->get_offset(), layer->get_rotation());

            registry->for_each<CanvasItem>([&](CanvasItem& item) {
                if (item.get_layer_id() == id && item.need_draw()) {
                    item.on_draw_begin(*camera, *m_canvas);
                    item.on_draw(*camera, *m_canvas);
                    item.on_draw_end(*camera, *m_canvas);
                }
            });

            m_canvas->pop();
        }

        m_canvas->pop();
        m_canvas->pop();
        m_canvas->render();
    }

}// namespace wmoge