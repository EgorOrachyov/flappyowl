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

#include "pfx_feature_sprite.hpp"

#include "core/engine.hpp"
#include "debug/profiler.hpp"
#include "pfx/pfx_component_runtime.hpp"
#include "render/canvas.hpp"
#include "resource/resource_manager.hpp"
#include "resource/sprite.hpp"

namespace wmoge {

    ref_ptr<PfxFeature> PfxFeatureSprite::create() const {
        return make_ref<PfxFeatureSprite>();
    }
    const StringId& PfxFeatureSprite::get_feature_name() const {
        static StringId name("Sprite");
        return name;
    }
    const StringId& PfxFeatureSprite::get_feature_family() const {
        static StringId family("Visual");
        return family;
    }
    bool PfxFeatureSprite::load_from_options(const YamlConstNodeRef& node) {
        StringId sprite;

        Yaml::read(node["sprite"], sprite);
        if (sprite.empty()) {
            WG_LOG_ERROR("empty sprite name for feature " << sprite);
            return false;
        }

        auto* resource_manager = Engine::instance()->resource_manager();

        m_sprite = resource_manager->load(sprite).cast<Sprite>();
        if (!m_sprite) {
            WG_LOG_ERROR("failed to load sprite " << sprite);
            return false;
        }

        node["animation"] >> m_animation;

        return true;
    }
    void PfxFeatureSprite::on_added(PfxAttributes& attributes) {
        attributes.set(PfxAttribute::Time);
        attributes.set(PfxAttribute::Pos2d);
        attributes.set(PfxAttribute::Size);
        attributes.set(PfxAttribute::Angle);
        attributes.set(PfxAttribute::Color);
    }
    void PfxFeatureSprite::on_render_2d(class PfxComponentRuntime& runtime, class Camera2d& camera, class Canvas& canvas) {
        WG_AUTO_PROFILE_PFX();

        if (m_animation == -1) return;

        auto* storage = runtime.get_storage();
        auto  view_t  = storage->get_time();
        auto  view_p  = storage->get_pos2d();
        auto  view_a  = storage->get_angle();
        auto  view_s  = storage->get_size();
        auto  view_c  = storage->get_color();

        const auto& texture       = m_sprite->get_animation_texture(m_animation);
        const float anim_speed    = m_sprite->get_animation_speed(m_animation);
        const int   anim_n_frames = m_sprite->get_animation_n_frames(m_animation);
        const bool  anim_loop     = m_sprite->get_animation_loop(m_animation);
        const auto  size          = m_sprite->get_size();
        const auto  pivot         = m_sprite->get_pivot();

        for (auto particle_id : runtime.get_update_range()) {
            const float t           = view_t[particle_id];
            const float frame_accum = t * anim_speed;
            const int   curr_frame  = int(Math::floor(frame_accum));
            const int   frame       = anim_loop ? curr_frame % anim_n_frames : Math::min(curr_frame, anim_n_frames - 1);

            assert(0 < anim_n_frames);
            assert(0 <= frame && frame < anim_n_frames);

            const auto& frame_uv = m_sprite->get_animation_frame(m_animation, frame);
            const float scale    = view_s[particle_id];

            canvas.push(view_p[particle_id], view_a[particle_id], Vec2f(scale, scale));
            canvas.set_tint_color(view_c[particle_id]);
            canvas.draw_texture(texture, -pivot, size, Vec2f(frame_uv.x(), frame_uv.y()), Vec2f(frame_uv.z(), frame_uv.w()));
            canvas.pop();
        }
    }

}// namespace wmoge