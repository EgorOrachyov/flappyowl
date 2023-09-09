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

#include "canvas_text.hpp"

#include "core/engine.hpp"
#include "render/canvas.hpp"
#include "resource/resource_manager.hpp"

namespace wmoge {

    void CanvasText::create(std::string text, ref_ptr<Font> font, float font_size, const Color4f& font_color) {
        m_text       = std::move(text);
        m_font       = std::move(font);
        m_font_size  = font_size;
        m_font_color = font_color;
    }
    void CanvasText::set_font_color(const Color4f& color) {
        m_font_color = color;
    }
    void CanvasText::set_text(std::string text) {
        m_text = std::move(text);
    }
    void CanvasText::set_font(ref_ptr<Font> font) {
        m_font = std::move(font);
    }
    void CanvasText::set_font_size(float font_size) {
        m_font_size = font_size;
    }
    void CanvasText::set_centered() {
        m_centered = true;
    }
    const Color4f& CanvasText::get_font_color() {
        return m_font_color;
    }
    const std::string& CanvasText::get_text() {
        return m_text;
    }
    const ref_ptr<Font>& CanvasText::get_font() {
        return m_font;
    }
    float CanvasText::get_font_size() {
        return m_font_size;
    }

    bool CanvasText::on_load_from_yaml(const YamlConstNodeRef& node) {
        if (!CanvasItem::on_load_from_yaml(node)) {
            return false;
        }

        auto text       = Yaml::read_str(node["text"]);
        auto font_size  = Yaml::read_float(node["font_size"]);
        auto font_color = Yaml::read_vec4f(node["font_color"]);
        auto font_res   = Yaml::read_sid(node["font"]);
        auto font       = Engine::instance()->resource_manager()->load(font_res).cast<Font>();

        if (!font) {
            WG_LOG_ERROR("failed to load font " << font_res);
            return false;
        }

        create(std::move(text), std::move(font), font_size, font_color);

        if (node.has_child("centered")) {
            node["centered"] >> m_centered;
        }

        return true;
    }
    void CanvasText::on_draw(Camera2d& camera, Canvas& canvas) {
        if (m_font && !m_text.empty()) {
            auto pos_offset = m_centered ? m_font->get_string_size(m_text, m_font_size) * -0.5 : Vec2f();
            canvas.set_font(m_font);
            canvas.set_font_color(m_font_color);
            canvas.draw_text(m_text, pos_offset, m_font_size);
        }
    }

}// namespace wmoge
