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

#ifndef GAME_ENGINE_TUTORIAL_PFX_EMITTER_HPP
#define GAME_ENGINE_TUTORIAL_PFX_EMITTER_HPP

#include "core/task.hpp"
#include "math/color.hpp"
#include "pfx/pfx_component.hpp"
#include "pfx/pfx_component_runtime.hpp"
#include "pfx/pfx_feature.hpp"
#include "pfx/pfx_storage.hpp"

namespace wmoge {

    /**
     * @class PfxSpawnParams
     * @brief Spawn params used to manually or automatically spawn particles
     */
    struct PfxSpawnParams {
        Color4f color = Color::WHITE4f;
        Vec2f   pos2d;
        Vec2f   vel2d;
        float   angle    = 0.0f;
        float   size     = 1.0f;
        float   lifetime = 1.0f;
        int     amount   = 0;
    };

    /**
     * @class PfxEmitter
     * @brief Runtime representation of a spawned active pfx effect
     */
    class PfxEmitter final : public RefCnt {
    public:
        explicit PfxEmitter(ref_ptr<class PfxEffect> effect);
        ~PfxEmitter() override;

        void emit(const PfxSpawnParams& params);
        void render(class Camera2d& camera, class Canvas& canvas);

        void advance_time(float delta_time);
        void update();

        const PfxComponentRuntime&   get_runtime(int id) const;
        const ref_ptr<PfxComponent>& get_component(int id) const;
        const ref_ptr<PfxEffect>&    get_effect() const;
        float                        get_time() const;
        float                        get_delta_time() const;
        bool                         is_active() const;

    private:
        fast_vector<PfxComponentRuntime> m_runtime[2];
        fast_vector<PfxSpawnParams>      m_emit_queue;
        ref_ptr<class PfxEffect>         m_effect;
        int                              m_runtime_index      = 0;
        int                              m_runtime_prev_index = 1;
        float                            m_time               = 0.0f;
        float                            m_delta_time         = 0.0f;
        bool                             m_is_active          = true;
    };

}// namespace wmoge

#endif//GAME_ENGINE_TUTORIAL_PFX_EMITTER_HPP
