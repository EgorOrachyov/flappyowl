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

#ifndef GAME_ENGINE_TUTORIAL_CANVAS_ITEM_HPP
#define GAME_ENGINE_TUTORIAL_CANVAS_ITEM_HPP

#include "render/canvas.hpp"
#include "scene/scene_component.hpp"

namespace wmoge {

    /**
     * @class CanvasItem
     * @brief Base class for any item which wants to draw in 2d on screen
     *
     * Canvas item is an object which can be rendered on a scene using 2d
     * camera and 2d rendering canvas.
     *
     * Items are collected by 2d render manager. When scene is rendered,
     * specialized draw method gets called on all items. Inherit from this
     * component to create your custom 2d visible objects.
     */
    class CanvasItem : public SceneComponent {
    public:
        WG_OBJECT(CanvasItem, SceneComponent);

        virtual bool   need_draw();
        virtual void   on_draw(class Camera2d& camera, Canvas& canvas){};
        virtual void   on_draw_begin(class Camera2d& camera, Canvas& canvas);
        virtual void   on_draw_end(class Camera2d& camera, Canvas& canvas);
        void           hide();
        void           show();
        void           set_layer_id(int id);
        void           set_tint(const Color4f& tint);
        Vec2f          get_pos_global() const;
        const Mat3x3f& get_matr_global() const;
        const Mat3x3f& get_matr_global_inv() const;
        const Color4f& get_tint() const;
        int            get_layer_id() const;
        bool           is_visible() const;

        bool on_load_from_yaml(const YamlConstNodeRef& node) override;
        void on_scene_enter() override;
        void on_transform_updated() override;

    private:
        Mat3x3f m_matr_global;
        Mat3x3f m_matr_global_inv;
        Color4f m_tint       = Color::WHITE4f;
        int     m_layer_id   = 0;
        bool    m_is_visible = true;
    };

}// namespace wmoge

#endif//GAME_ENGINE_TUTORIAL_CANVAS_ITEM_HPP
