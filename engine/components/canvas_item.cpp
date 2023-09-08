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

#include "canvas_item.hpp"

#include "components/camera_2d.hpp"
#include "components/canvas_layer.hpp"
#include "components/spatial_2d.hpp"
#include "render/canvas.hpp"
#include "scene/scene_object.hpp"

namespace wmoge {

    bool CanvasItem::on_load_from_yaml(const YamlConstNodeRef& node) {
        if (!SceneComponent::on_load_from_yaml(node)) {
            return false;
        }

        if (node.has_child("tint")) {
            m_tint = Yaml::read_vec4f(node["tint"]);
        }

        if (node.has_child("is_visible")) {
            node["is_visible"] >> m_is_visible;
        }

        return true;
    }
    void CanvasItem::on_scene_enter() {
        SceneComponent::on_scene_enter();

        SceneObject* parent = get_scene_object();
        while (parent) {
            if (CanvasLayer* layer = parent->get<CanvasLayer>()) {
                m_layer_id = layer->get_id();
                break;
            }
            parent = parent->get_parent();
        }

        on_transform_updated();
    }
    void CanvasItem::on_transform_updated() {
        SceneComponent::on_transform_updated();
        m_matr_global     = get_scene_object()->get_or_create<Spatial2d>()->get_matr_global();
        m_matr_global_inv = get_scene_object()->get_or_create<Spatial2d>()->get_matr_global_inv();
    }

    bool CanvasItem::need_draw() {
        return m_is_visible;
    }
    void CanvasItem::on_draw_begin(class Camera2d& camera, Canvas& canvas) {
        canvas.push(m_matr_global);
        canvas.set_tint_color(m_tint);
    }
    void CanvasItem::on_draw_end(class Camera2d& camera, Canvas& canvas) {
        canvas.pop();
    }

    void CanvasItem::hide() {
        m_is_visible = false;
    }
    void CanvasItem::show() {
        m_is_visible = true;
    }
    void CanvasItem::set_layer_id(int id) {
        m_layer_id = id;
    }
    void CanvasItem::set_tint(const Color4f& color) {
        m_tint = color;
    }
    Vec2f CanvasItem::get_pos_global() const {
        return Math2d::transform(m_matr_global, Vec2f());
    }
    const Mat3x3f& CanvasItem::get_matr_global() const {
        return m_matr_global;
    }
    const Mat3x3f& CanvasItem::get_matr_global_inv() const {
        return m_matr_global_inv;
    }
    const Color4f& CanvasItem::get_tint() const {
        return m_tint;
    }
    int CanvasItem::get_layer_id() const {
        return m_layer_id;
    }
    bool CanvasItem::is_visible() const {
        return m_is_visible;
    }

}// namespace wmoge