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

#ifndef GAME_ENGINE_TUTORIAL_PARTICLES_2D_HPP
#define GAME_ENGINE_TUTORIAL_PARTICLES_2D_HPP

#include "components/canvas_item.hpp"
#include "pfx/pfx_emitter.hpp"
#include "resource/pfx_effect.hpp"

namespace wmoge {

    /**
     * @class Particles2d
     * @brief Cpu-based 2d particles component for creating effects
     *
     * Particles component allows to instantiate a 2d pfx effect in a form of
     * emitter, placed some where in a scene. Component plays effect as it is
     * defined. Also, it provides additional methods for tweaking, allows to
     * spaw extra particles in a configurable fashion.
     *
     * @see PfxEffect
     * @see PfxEmitter
     * @see PfxSpawnParams
     */
    class Particles2d : public CanvasItem {
    public:
        WG_OBJECT(Particles2d, CanvasItem)

        void create(const ref_ptr<PfxEffect>& effect);
        void emit(int amount = 1);
        void emit(const PfxSpawnParams& params);

        bool on_load_from_yaml(const YamlConstNodeRef& node) override;
        void advance_time(float delta_time);
        void on_draw(class Camera2d& camera, Canvas& canvas) override;
        void on_draw_begin(class Camera2d& camera, Canvas& canvas) override;
        void on_draw_end(class Camera2d& camera, Canvas& canvas) override;
        bool need_draw() override;

    private:
        ref_ptr<PfxEmitter> m_emitter;
    };

}// namespace wmoge

#endif//GAME_ENGINE_TUTORIAL_PARTICLES_2D_HPP
