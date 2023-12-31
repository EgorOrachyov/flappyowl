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

#ifndef GAME_ENGINE_TUTORIAL_CANVAS_HPP
#define GAME_ENGINE_TUTORIAL_CANVAS_HPP

#include "core/fast_vector.hpp"

#include "gfx/gfx_buffers.hpp"
#include "gfx/gfx_pipeline.hpp"
#include "gfx/gfx_sampler.hpp"
#include "gfx/gfx_texture.hpp"

#include "platform/window.hpp"
#include "resource/font.hpp"
#include "resource/shader.hpp"
#include "resource/texture.hpp"

#include "math/color.hpp"
#include "math/mat.hpp"
#include "math/quat.hpp"
#include "math/transform.hpp"
#include "math/vec.hpp"

#include <stack>
#include <vector>

namespace wmoge {

    /**
     * @class Canvas
     * @brief 2d drawing canvas for a vector graphics, text and image rendering
     *
     * Canvas allows to paint a virtual surface from a back to front using
     * standard primitives, such as lines, curves, rectangles, text and
     * textures for image drawing.
     *
     * @note Canvas supports transformation stack (in a old OpenCL 1.0 fashion).
     *       It allows to stack transformations and graw primitives without
     *       2d math complexity.
     *
     * @note Canvas supports alpha blending automatically. User can draw any
     *       primitives. They automatically overlay one on top of the another
     *       following the order of the drawing.
     *
     * @note The rendering of the elements is optimized using batching. Consecutive
     *       elements with the same type and texture are rendered at once as a
     *       group. Thy to avoid mixing of primitives in your code in order to
     *       get maximum performance of the rendering.
     */
    class Canvas final {
    public:
        Canvas();

        void           push(const Vec2f& translate, float rotate_rad, const Vec2f& scale);
        void           push(const Vec2f& translate, float rotate_rad);
        void           push(const Transform2d& transform);
        void           push(const Mat3x3f& matr);
        void           pop();
        const Mat3x3f& peek();

        void set_line_color(const Color4f& color);
        void set_fill_color(const Color4f& color);
        void set_font_color(const Color4f& color);
        void set_tint_color(const Color4f& color);
        void set_font(ref_ptr<Font> font);

        void draw_line(const Vec2f& from, const Vec2f& to, float width);
        void draw_triangle(const Vec2f& p0, const Vec2f& p1, const Vec2f& p2, float border);
        void draw_rect(const Vec2f& pos, const Vec2f& size, float border);
        void draw_filled_triangle(const Vec2f& p0, const Vec2f& p1, const Vec2f& p2);
        void draw_filled_rect(const Vec2f& pos, const Vec2f& size);
        void draw_texture(const ref_ptr<Texture2d>& texture, const Vec2f& pos, const Vec2f& size, const Vec2f& uv_base, const Vec2f& uv_size);
        void draw_text(const std::string& text, const Vec2f& pos, float size);

        void set_window(const ref_ptr<Window>& window);
        void set_viewport(const Rect2i& viewport);
        void set_screen_size(const Vec2f& size);

        Rect2i get_viewport() { return m_viewport; }
        Vec2f  get_screen_size() { return m_screen_size; }

        void render();

    private:
        struct CanvasTriangle {
            Vec2f               p[3];
            Vec2f               t[3];
            Color4f             color;
            ref_ptr<GfxTexture> texture;
            ref_ptr<GfxSampler> sampler;
            bool                is_text = false;
        };

        void add_triangle(const Vec2f& p0, const Vec2f& p1, const Vec2f& p2, const Color4f& color);
        void add_rect(const Vec2f& pos, const Vec2f& size, const Color4f& color);

    private:
        fast_vector<Mat3x3f> m_transform_stack;
        Color4f              m_color_line;
        Color4f              m_color_fill;
        Color4f              m_color_font;
        Color4f              m_color_tint;
        ref_ptr<Font>        m_font;

        ref_ptr<GfxVertBuffer>      m_gfx_triangles;
        std::vector<CanvasTriangle> m_triangles;

        ref_ptr<Shader>           m_shader;
        ref_ptr<GfxRenderPass>    m_render_pass;
        ref_ptr<GfxPipeline>      m_pipeline_triangle;
        ref_ptr<GfxPipeline>      m_pipeline_text;
        ref_ptr<GfxUniformBuffer> m_constants;
        ref_ptr<GfxTexture>       m_default_texture;
        ref_ptr<GfxSampler>       m_default_sampler;

        ref_ptr<Window> m_window;
        Rect2i          m_viewport;
        Vec2f           m_screen_size;

        int m_gfx_capacity_triangles = 0;
    };

}// namespace wmoge

#endif//GAME_ENGINE_TUTORIAL_CANVAS_HPP
