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

#include "pfx_manager.hpp"

#include "core/engine.hpp"
#include "core/log.hpp"
#include "debug/profiler.hpp"
#include "pfx/features/pfx_feature_color.hpp"
#include "pfx/features/pfx_feature_lifetime.hpp"
#include "pfx/features/pfx_feature_movement.hpp"
#include "pfx/features/pfx_feature_size.hpp"
#include "pfx/features/pfx_feature_sprite.hpp"
#include "pfx/features/pfx_feature_velocity.hpp"
#include "resource/pfx_effect.hpp"

namespace wmoge {

    PfxManager::PfxManager() {
        register_feature(make_ref<PfxFeatureColor>());
        register_feature(make_ref<PfxFeatureLifetime>());
        register_feature(make_ref<PfxFeatureMovement2d>());
        register_feature(make_ref<PfxFeatureSize>());
        register_feature(make_ref<PfxFeatureSprite>());
        register_feature(make_ref<PfxFeatureVelocity2d>());
    }
    void PfxManager::update() {
        WG_AUTO_PROFILE_PFX();

        {
            std::lock_guard guard(m_mutex);

            for (auto emitter : m_emitters) {
                if (emitter->is_active()) {
                    auto task = make_ref<Task>(SID("update-" + emitter->get_effect()->get_name().str()), [e = ref_ptr<PfxEmitter>(emitter)](auto&) {
                        e->update();
                        return 0;
                    });
                    task->run();
                    m_update_tasks.push_back(task);
                }
            }
        }

        for (auto& task : m_update_tasks) {
            task->wait_completed();
        }

        m_update_tasks.clear();
    }
    void PfxManager::add_emitter(PfxEmitter* emitter) {
        std::lock_guard guard(m_mutex);

        assert(m_emitters.find(emitter) == m_emitters.end());
        m_emitters.emplace(emitter);
    }
    void PfxManager::remove_emitter(PfxEmitter* emitter) {
        std::lock_guard guard(m_mutex);

        assert(m_emitters.find(emitter) != m_emitters.end());
        m_emitters.erase(emitter);
    }
    bool PfxManager::has_feature(const StringId& name) {
        std::lock_guard guard(m_mutex);
        return m_features.find(name) != m_features.end();
    }
    void PfxManager::register_feature(ref_ptr<PfxFeature> feature) {
        std::lock_guard guard(m_mutex);

        assert(feature);
        assert(m_features.find(feature->get_feature_name()) == m_features.end());

        m_features[feature->get_feature_name()] = feature;
    }
    ref_ptr<PfxFeature> PfxManager::make_feature(const StringId& name) {
        std::lock_guard guard(m_mutex);

        auto query = m_features.find(name);

        if (query == m_features.end()) {
            WG_LOG_ERROR("no such feature registered to create " << name);
            return ref_ptr<PfxFeature>{};
        }

        return query->second->create();
    }

}// namespace wmoge