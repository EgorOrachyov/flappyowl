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

#ifndef GAME_ENGINE_TUTORIAL_PFX_FEATURE_SIZE_HPP
#define GAME_ENGINE_TUTORIAL_PFX_FEATURE_SIZE_HPP

#include "pfx/pfx_feature.hpp"

namespace wmoge {

    class PfxFeatureSize final : public PfxFeature {
    public:
        ~PfxFeatureSize() override = default;
        ref_ptr<PfxFeature> create() const override;
        const StringId&     get_feature_name() const override;
        const StringId&     get_feature_family() const override;
        bool                load_from_options(const YamlConstNodeRef& node) override;
        void                on_added(PfxAttributes& attributes) override;
        void                on_spawn(class PfxComponentRuntime& runtime, const struct PfxSpawnParams& params) override;
        void                on_update(class PfxComponentRuntime& runtime, float dt) override;
        void                on_render_2d(class PfxComponentRuntime& runtime, class Camera2d& camera, class Canvas& canvas) override {}

    private:
        float m_start_size = 1.0f;
        float m_end_size   = 1.0f;
    };

}// namespace wmoge

#endif//GAME_ENGINE_TUTORIAL_PFX_FEATURE_SIZE_HPP
