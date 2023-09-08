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

#ifndef GAME_ENGINE_TUTORIAL_PFX_FEATURE_HPP
#define GAME_ENGINE_TUTORIAL_PFX_FEATURE_HPP

#include "core/ref.hpp"
#include "core/string_id.hpp"
#include "io/yaml.hpp"
#include "pfx/pfx_storage.hpp"

namespace wmoge {

    /**
     * @class PfxFeature
     * @brief Pfx reusable feature which controls single aspect of particles
     *
     * Feature is a setting which can be added to particle component. Single
     * feature controls single aspect of the particle components, such as
     * particles movement, rotation, color, rendering, collision, life time, etc.
     *
     * Features have unique type and unique settings. Each feature process its
     * own portion of the data.
     *
     * Combine different features with different settings to get new particles effects.
     */
    class PfxFeature : public RefCnt {
    public:
        ~PfxFeature() override = default;

        virtual ref_ptr<PfxFeature> create() const                                                                                 = 0;
        virtual const StringId&     get_feature_name() const                                                                       = 0;
        virtual const StringId&     get_feature_family() const                                                                     = 0;
        virtual bool                load_from_options(const YamlConstNodeRef& node)                                                = 0;
        virtual void                on_added(PfxAttributes& attributes)                                                            = 0;
        virtual void                on_spawn(class PfxComponentRuntime& runtime, const struct PfxSpawnParams& params)              = 0;
        virtual void                on_update(class PfxComponentRuntime& runtime, float dt)                                        = 0;
        virtual void                on_render_2d(class PfxComponentRuntime& runtime, class Camera2d& camera, class Canvas& canvas) = 0;
    };

}// namespace wmoge

#endif//GAME_ENGINE_TUTORIAL_PFX_FEATURE_HPP
