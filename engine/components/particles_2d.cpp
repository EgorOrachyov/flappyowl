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

#include "particles_2d.hpp"

#include "core/engine.hpp"
#include "resource/resource_manager.hpp"

namespace wmoge {

    void Particles2d::create(const ref_ptr<PfxEffect>& effect) {
        assert(effect);
        m_emitter = effect->make_emitter();
    }
    void Particles2d::emit(int amount) {
        PfxSpawnParams params;
        params.amount = amount;
        params.pos2d  = get_pos_global();
        emit(params);
    }
    void Particles2d::emit(const PfxSpawnParams& params) {
        assert(m_emitter);
        assert(params.amount > 0);
        m_emitter->emit(params);
    }

    bool Particles2d::on_load_from_yaml(const YamlConstNodeRef& node) {
        if (!CanvasItem::on_load_from_yaml(node)) {
            return false;
        }

        auto res    = Yaml::read_sid(node["effect"]);
        auto effect = Engine::instance()->resource_manager()->load(res).cast<PfxEffect>();
        if (!effect) {
            WG_LOG_ERROR("failed to load effect " << res);
            return false;
        }

        create(effect);
        return true;
    }
    void Particles2d::advance_time(float delta_time) {
        if (m_emitter) m_emitter->advance_time(delta_time);
    }
    void Particles2d::on_draw(class Camera2d& camera, class Canvas& canvas) {
        if (m_emitter) m_emitter->render(camera, canvas);
    }
    void Particles2d::on_draw_begin(class Camera2d& camera, Canvas& canvas) {
        // nothing to do
    }
    void Particles2d::on_draw_end(class Camera2d& camera, Canvas& canvas) {
        // nothing to do
    }
    bool Particles2d::need_draw() {
        return CanvasItem::need_draw() && m_emitter;
    }

}// namespace wmoge
