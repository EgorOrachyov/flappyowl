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

#ifndef GAME_ENGINE_TUTORIAL_PFX_SYSTEM_HPP
#define GAME_ENGINE_TUTORIAL_PFX_SYSTEM_HPP

#include "core/fast_map.hpp"
#include "core/fast_set.hpp"
#include "core/fast_vector.hpp"
#include "core/task.hpp"
#include "pfx/pfx_component.hpp"
#include "pfx/pfx_emitter.hpp"
#include "pfx/pfx_feature.hpp"

#include <mutex>

namespace wmoge {

    /**
     * @class PfxManager
     * @brief Engine manager for pfx features and effects
     */
    class PfxManager {
    public:
        PfxManager();

        void                update();
        void                add_emitter(PfxEmitter* emitter);
        void                remove_emitter(PfxEmitter* emitter);
        bool                has_feature(const StringId& name);
        void                register_feature(ref_ptr<PfxFeature> feature);
        ref_ptr<PfxFeature> make_feature(const StringId& name);

    private:
        fast_map<StringId, ref_ptr<PfxFeature>> m_features;
        fast_set<PfxEmitter*>                   m_emitters;
        fast_vector<ref_ptr<Task>>              m_update_tasks;
        std::mutex                              m_mutex;
    };

}// namespace wmoge

#endif//GAME_ENGINE_TUTORIAL_PFX_SYSTEM_HPP
