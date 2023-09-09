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

#ifndef GAME_ENGINE_TUTORIAL_RENDER_VIEW_HPP
#define GAME_ENGINE_TUTORIAL_RENDER_VIEW_HPP

#include "core/ref.hpp"
#include "gfx/gfx_texture.hpp"
#include "platform/window.hpp"
#include "render/render_camera.hpp"
#include "render/render_command.hpp"
#include "render/render_pipeline.hpp"

#include <memory>
#include <vector>

namespace wmoge {

    /**
     * @class RenderView
     * @brief Reusable storage to capture all single frame objects to be drawn
     */
    class RenderView final : public RefCnt {
    public:
        ~RenderView() override = default;

        void set_target(ref_ptr<Window> target);
        void set_target(ref_ptr<GfxTexture> target);
        void set_camera(const RenderCamera& cam);
        void set_camera_prev(const RenderCamera& cam);

        void push_command(ref_ptr<RenderCommand> command);

    private:
        RenderCamera m_camera;
        RenderCamera m_camera_prev;

        ref_ptr<Window>     m_rt_window;
        ref_ptr<GfxTexture> m_rt_texture;

        std::vector<ref_ptr<RenderCommand>> m_cmd_shadows;
        std::vector<ref_ptr<RenderCommand>> m_cmd_opaque;
        std::vector<ref_ptr<RenderCommand>> m_cmd_ui;
        std::vector<ref_ptr<RenderCommand>> m_cmd_ui_dbg;
    };

}// namespace wmoge

#endif//GAME_ENGINE_TUTORIAL_RENDER_VIEW_HPP
