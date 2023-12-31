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

#ifndef GAME_ENGINE_TUTORIAL_VK_PIPELINE_HPP
#define GAME_ENGINE_TUTORIAL_VK_PIPELINE_HPP

#include "gfx/gfx_pipeline.hpp"
#include "gfx/vulkan/vk_defs.hpp"
#include "gfx/vulkan/vk_render_pass.hpp"
#include "gfx/vulkan/vk_resource.hpp"
#include "gfx/vulkan/vk_shader.hpp"

namespace wmoge {

    /**
     * @class VKPipeline
     * @brief Vulkan pipeline implementation
     */
    class VKPipeline final : public VKResource<GfxPipeline> {
    public:
        VKPipeline(const GfxPipelineState& state, const StringId& name, class VKDriver& driver);
        ~VKPipeline() override;

        bool validate();

        GfxPipelineStatus       status() const override;
        std::string             message() const override;
        const GfxPipelineState& state() const override;
        VkPipeline              pipeline() const { return m_pipeline; }
        VkPipelineLayout        layout() const { return m_layout; }

    private:
        void compile(const ref_ptr<VKRenderPassHnd>& render_pass);
        void release();

    private:
        GfxPipelineState               m_state;
        ref_ptr<VKRenderPass>          m_render_pass;
        std::atomic<GfxPipelineStatus> m_status{GfxPipelineStatus::Default};
        std::string                    m_message;
        VkPipeline                     m_pipeline = VK_NULL_HANDLE;
        VkPipelineLayout               m_layout   = VK_NULL_HANDLE;
        int                            m_version  = -1;
    };

}// namespace wmoge

#endif//GAME_ENGINE_TUTORIAL_VK_PIPELINE_HPP
