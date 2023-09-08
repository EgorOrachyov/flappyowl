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

#include "sprite_instance.hpp"

#include "components/camera_2d.hpp"
#include "core/engine.hpp"
#include "render/canvas.hpp"
#include "resource/resource_manager.hpp"
#include "scene/scene.hpp"
#include "scene/scene_object.hpp"

namespace wmoge {

    void SpriteInstance::create(ref_ptr<Sprite> sprite) {
        assert(sprite);

        m_sprite    = sprite;
        m_animation = 0;
        m_frame     = 0;
    }
    void SpriteInstance::play_animation(const StringId& animation) {
        int id = m_sprite->get_animation_id(animation);

        if (id < 0) {
            WG_LOG_ERROR("failed to find animation " << animation);
            return;
        }

        play_animation(id);
    }
    void SpriteInstance::play_animation(int animation_id) {
        m_animation   = animation_id;
        m_frame       = 0;
        m_frame_accum = 0.0f;
        m_playing     = true;
    }
    void SpriteInstance::stop_animation() {
        m_playing = false;
    }
    void SpriteInstance::set_uv_offset(const Vec2f& offset) {
        m_uv_offset = offset;
    }

    const ref_ptr<Sprite>& SpriteInstance::get_sprite() {
        return m_sprite;
    }

    bool SpriteInstance::on_load_from_yaml(const YamlConstNodeRef& node) {
        if (!CanvasItem::on_load_from_yaml(node)) {
            return false;
        }

        auto res    = Yaml::read_sid(node["sprite"]);
        auto sprite = Engine::instance()->resource_manager()->load(res).cast<Sprite>();

        if (!sprite) {
            WG_LOG_ERROR("failed to load sprite " << res);
            return false;
        }

        create(std::move(sprite));
        return true;
    }
    void SpriteInstance::on_animate(float delta) {
        if (!m_playing || m_animation == -1) return;

        const float anim_speed    = m_sprite->get_animation_speed(m_animation);
        const int   anim_n_frames = m_sprite->get_animation_n_frames(m_animation);
        const bool  anim_loop     = m_sprite->get_animation_loop(m_animation);

        if (m_frame_accum < anim_n_frames) {
            m_frame_accum += m_speed_scale * anim_speed * delta;
        }

        const float curr_frame = Math::floor(m_frame_accum);

        if (!anim_loop) {
            m_frame = Math::min(int(curr_frame), anim_n_frames - 1);
        } else {
            m_frame       = int(curr_frame) % anim_n_frames;
            m_frame_accum = m_frame_accum - curr_frame + m_frame;
        }

        assert(0 < anim_n_frames);
        assert(0 <= m_frame && m_frame < anim_n_frames);
        assert(0 <= m_frame_accum);
    }
    void SpriteInstance::on_draw(Camera2d& camera, Canvas& canvas) {
        if (m_animation == -1) return;

        const auto& texture = m_sprite->get_animation_texture(m_animation);
        const auto  frame   = m_sprite->get_animation_frame(m_animation, m_frame);
        const auto  size    = m_sprite->get_size();
        canvas.draw_texture(texture, -m_sprite->get_pivot(), size, Vec2f(frame.x(), frame.y()) + m_uv_offset, Vec2f(frame.z(), frame.w()));
    }

}// namespace wmoge