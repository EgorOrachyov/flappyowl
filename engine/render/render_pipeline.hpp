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

#ifndef GAME_ENGINE_TUTORIAL_RENDER_PIPELINE_HPP
#define GAME_ENGINE_TUTORIAL_RENDER_PIPELINE_HPP

#include "gfx/gfx_buffers.hpp"
#include "gfx/gfx_defs.hpp"
#include "gfx/gfx_texture.hpp"

#include "render/render_view.hpp"

#include <memory>
#include <vector>

namespace wmoge {

    /**
     * @class RenderPipelineResources
     * @brief Resources shared across stages of a single render pipeline
     */
    class RenderPipelineResources final {
    public:
        ref_ptr<GfxTexture> rt_gbuffer_pos;
        ref_ptr<GfxTexture> rt_gbuffer_norm;
        ref_ptr<GfxTexture> rt_gbuffer_color;
        ref_ptr<GfxTexture> rt_gbuffer_velocity;
        ref_ptr<GfxTexture> rt_gbuffer_params;
        ref_ptr<GfxTexture> rt_gbuffer_aux;

        ref_ptr<GfxTexture> rt_ssao_gen;
        ref_ptr<GfxTexture> rt_ssao_final;

        ref_ptr<GfxTexture> rt_bloom_mips;
        ref_ptr<GfxTexture> rt_bloom_final;

        ref_ptr<GfxTexture> rt_light_shafts_mask;
        ref_ptr<GfxTexture> rt_light_shafts_radial;
        ref_ptr<GfxTexture> rt_light_shafts_final;

        ref_ptr<GfxTexture> rt_ui;
        ref_ptr<GfxTexture> rt_ui_dbg;
    };

    /**
     * @class RenderPipelineStage
     * @brief Single stage performing some work in a rendering pipeline
     */
    class RenderPipelineStage {
    public:
        RenderPipelineStage(class RenderPipeline* pipeline);
        virtual ~RenderPipelineStage();

        virtual void init() {}
        virtual void execute() {}
        virtual void resize(int new_width, int new_height) {}
        virtual void finalize() {}

        const StringId&                get_name() const;
        class RenderPipeline*          get_pipeline();
        class RenderPipelineResources* get_resources();

    protected:
        StringId              m_name;
        class RenderPipeline* m_pipeline;
    };

    /**
     * @class RenderPipeline
     * @brief Set of sequential stages executed in order to draw single render view frame
     */
    class RenderPipeline : public RefCnt {
    public:
        virtual ~RenderPipeline();

        virtual void init() {}
        virtual void execute(class RenderView* view) { m_view = view; }
        virtual void resize(int new_width, int new_height) {}
        virtual void finalize() {}

        const StringId&                get_name() const;
        class RenderView*              get_view();
        class RenderPipelineResources* get_resources();

    protected:
        StringId          m_name;
        class RenderView* m_view = nullptr;

        std::vector<std::unique_ptr<RenderPipelineStage>> m_stages;
        std::unique_ptr<RenderPipelineResources>          m_resources;
    };

}// namespace wmoge

#endif//GAME_ENGINE_TUTORIAL_RENDER_PIPELINE_HPP
