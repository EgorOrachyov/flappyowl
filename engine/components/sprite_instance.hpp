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

#ifndef GAME_ENGINE_TUTORIAL_SPRITE_INSTANCE_HPP
#define GAME_ENGINE_TUTORIAL_SPRITE_INSTANCE_HPP

#include "components/canvas_item.hpp"
#include "resource/sprite.hpp"

namespace wmoge {

    /**
     * @class SpriteInstance
     * @brief Contains sprites with multiple textures for animation
     *
     * Use this component to render animated sprite texture on a scene.
     * Rendered sprite will use 2d transform of the object on a scene.
     * Call `play_animation` and `stop_animation` to control sprite.
     */
    class SpriteInstance final : public CanvasItem {
    public:
        WG_OBJECT(SpriteInstance, CanvasItem);

        /**
         * @brief Creates new sprite instance from sprite
         *
         * By default it will show default 0 animation with 0 frame with no play.
         * Call `play_animation` to play an animation on this instance.
         *
         * @param sprite Sprite with animations
         */
        void create(ref_ptr<Sprite> sprite);
        /** @brief Starts playing animation by its name */
        void play_animation(const StringId& animation);
        /** @brief Starts playing animation by its identification */
        void play_animation(int animation_id);
        /** @brief Stop playing animation */
        void stop_animation();
        /** @brief Set addition uv offset to a frame when sprite is rendered */
        void set_uv_offset(const Vec2f& offset);
        /** @return Sprite resource of this instance  */
        const ref_ptr<Sprite>& get_sprite();

        bool on_load_from_yaml(const YamlConstNodeRef& node) override;
        void on_animate(float delta);
        void on_draw(class Camera2d& camera, class Canvas& canvas) override;

    private:
        ref_ptr<Sprite> m_sprite;
        Vec2f           m_uv_offset;
        int             m_animation   = -1;
        int             m_frame       = -1;
        float           m_speed_scale = 1.0f;
        float           m_frame_accum = 0.0f;
        bool            m_playing     = false;
    };

}// namespace wmoge

#endif//GAME_ENGINE_TUTORIAL_SPRITE_INSTANCE_HPP
