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

#include "render_view.hpp"

namespace wmoge {

    void RenderView::set_target(ref_ptr<Window> target) {
        m_rt_window = std::move(target);
    }
    void RenderView::set_target(ref_ptr<GfxTexture> target) {
        m_rt_texture = std::move(target);
    }
    void RenderView::set_camera(const RenderCamera& cam) {
        m_camera = cam;
    }
    void RenderView::set_camera_prev(const RenderCamera& cam) {
        m_camera_prev = cam;
    }
    void RenderView::push_command(ref_ptr<RenderCommand> command) {
        static StringId TAG_SHADOW = SID("shadow");
        static StringId TAG_OPAQUE = SID("opaque");
        static StringId TAG_UI     = SID("ui");
        static StringId TAG_UI_DBG = SID("dbg");

        assert(command);

        if (command->get_tag() == TAG_OPAQUE)
            m_cmd_opaque.push_back(std::move(command));
        if (command->get_tag() == TAG_SHADOW)
            m_cmd_shadows.push_back(std::move(command));
        if (command->get_tag() == TAG_UI)
            m_cmd_ui.push_back(std::move(command));
        if (command->get_tag() == TAG_UI_DBG)
            m_cmd_ui_dbg.push_back(std::move(command));

        WG_LOG_ERROR("unknown command type " << command->get_tag());
    }
}// namespace wmoge
