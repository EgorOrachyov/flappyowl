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

#ifndef GAME_ENGINE_TUTORIAL_GFX_DRIVER_HPP
#define GAME_ENGINE_TUTORIAL_GFX_DRIVER_HPP

#include <array>
#include <string>
#include <thread>

#include "core/callback_queue.hpp"
#include "core/data.hpp"
#include "math/mat.hpp"
#include "math/vec.hpp"
#include "platform/window.hpp"

#include "gfx/gfx_buffers.hpp"
#include "gfx/gfx_defs.hpp"
#include "gfx/gfx_pipeline.hpp"
#include "gfx/gfx_render_pass.hpp"
#include "gfx/gfx_resource.hpp"
#include "gfx/gfx_sampler.hpp"
#include "gfx/gfx_shader.hpp"
#include "gfx/gfx_texture.hpp"
#include "gfx/gfx_vert_format.hpp"

namespace wmoge {

    /**
     * @class GfxDriver
     * @brief Gfx driver interface
     *
     * Driver exposes gfx device object creation and rendering API.
     *
     * Device provided objects can be safely created from any thread.
     * Created objects references are immediately returned from `make_*` functions.
     * Actual object creation will be deferred and executed on a gfx thread only.
     *
     * From user side, created objects can be safely and immediately used in the drawing and update API.
     */
    class GfxDriver {
    public:
        virtual ~GfxDriver() = default;

        // Default textures;
        ref_ptr<GfxTexture> texture_2d_white;
        ref_ptr<GfxTexture> texture_2d_black;

        // Create object API (thread-safe)
        virtual ref_ptr<GfxVertFormat>    make_vert_format(const GfxVertElements& elements, const StringId& name = StringId())                                                                                = 0;
        virtual ref_ptr<GfxVertBuffer>    make_vert_buffer(int size, GfxMemUsage usage, const StringId& name = StringId())                                                                                    = 0;
        virtual ref_ptr<GfxIndexBuffer>   make_index_buffer(int size, GfxMemUsage usage, const StringId& name = StringId())                                                                                   = 0;
        virtual ref_ptr<GfxUniformBuffer> make_uniform_buffer(int size, GfxMemUsage usage, const StringId& name = StringId())                                                                                 = 0;
        virtual ref_ptr<GfxStorageBuffer> make_storage_buffer(int size, GfxMemUsage usage, const StringId& name = StringId())                                                                                 = 0;
        virtual ref_ptr<GfxShader>        make_shader(std::string vertex, std::string fragment, const StringId& name = StringId())                                                                            = 0;
        virtual ref_ptr<GfxShader>        make_shader(ref_ptr<Data> code, const StringId& name = StringId())                                                                                                  = 0;
        virtual ref_ptr<GfxTexture>       make_texture_2d(int width, int height, int mips, GfxFormat format, GfxTexUsages usages, GfxMemUsage mem_usage, const StringId& name = StringId())                   = 0;
        virtual ref_ptr<GfxTexture>       make_texture_2d_array(int width, int height, int mips, int slices, GfxFormat format, GfxTexUsages usages, GfxMemUsage mem_usage, const StringId& name = StringId()) = 0;
        virtual ref_ptr<GfxTexture>       make_texture_cube(int width, int height, int mips, GfxFormat format, GfxTexUsages usages, GfxMemUsage mem_usage, const StringId& name = StringId())                 = 0;
        virtual ref_ptr<GfxSampler>       make_sampler(const GfxSamplerDesc& desc, const StringId& name = StringId())                                                                                         = 0;
        virtual ref_ptr<GfxRenderPass>    make_render_pass(GfxRenderPassType pass_type, const StringId& name = StringId())                                                                                    = 0;
        virtual ref_ptr<GfxPipeline>      make_pipeline(const GfxPipelineState& state, const StringId& name = StringId())                                                                                     = 0;

        // Update API (thread-safe)
        virtual void update_vert_buffer(const ref_ptr<GfxVertBuffer>& buffer, int offset, int range, const ref_ptr<Data>& data)                = 0;
        virtual void update_index_buffer(const ref_ptr<GfxIndexBuffer>& buffer, int offset, int range, const ref_ptr<Data>& data)              = 0;
        virtual void update_uniform_buffer(const ref_ptr<GfxUniformBuffer>& buffer, int offset, int range, const ref_ptr<Data>& data)          = 0;
        virtual void update_storage_buffer(const ref_ptr<GfxStorageBuffer>& buffer, int offset, int range, const ref_ptr<Data>& data)          = 0;
        virtual void update_texture_2d(const ref_ptr<GfxTexture>& texture, int mip, Rect2i region, const ref_ptr<Data>& data)                  = 0;
        virtual void update_texture_2d_array(const ref_ptr<GfxTexture>& texture, int mip, int slice, Rect2i region, const ref_ptr<Data>& data) = 0;
        virtual void update_texture_cube(const ref_ptr<GfxTexture>& texture, int mip, int face, Rect2i region, const ref_ptr<Data>& data)      = 0;

        // Mapping write-only API (gfx-thread-only)
        virtual void* map_vert_buffer(const ref_ptr<GfxVertBuffer>& buffer)         = 0;
        virtual void* map_index_buffer(const ref_ptr<GfxIndexBuffer>& buffer)       = 0;
        virtual void* map_uniform_buffer(const ref_ptr<GfxUniformBuffer>& buffer)   = 0;
        virtual void* map_storage_buffer(const ref_ptr<GfxStorageBuffer>& buffer)   = 0;
        virtual void  unmap_vert_buffer(const ref_ptr<GfxVertBuffer>& buffer)       = 0;
        virtual void  unmap_index_buffer(const ref_ptr<GfxIndexBuffer>& buffer)     = 0;
        virtual void  unmap_uniform_buffer(const ref_ptr<GfxUniformBuffer>& buffer) = 0;
        virtual void  unmap_storage_buffer(const ref_ptr<GfxStorageBuffer>& buffer) = 0;

        // Drawing API (gfx-thread-only)
        virtual void begin_render_pass(const ref_ptr<GfxRenderPass>& pass)                                                                         = 0;
        virtual void bind_target(const ref_ptr<Window>& window)                                                                                    = 0;
        virtual void bind_color_target(const ref_ptr<GfxTexture>& texture, int target, int mip, int slice)                                         = 0;
        virtual void bind_depth_target(const ref_ptr<GfxTexture>& texture, int mip, int slice)                                                     = 0;
        virtual void viewport(const Rect2i& viewport)                                                                                              = 0;
        virtual void clear(int target, const Vec4f& color)                                                                                         = 0;
        virtual void clear(float depth, int stencil)                                                                                               = 0;
        virtual bool bind_pipeline(const ref_ptr<GfxPipeline>& pipeline)                                                                           = 0;
        virtual void bind_vert_buffer(const ref_ptr<GfxVertBuffer>& buffer, int index, int offset = 0)                                             = 0;
        virtual void bind_index_buffer(const ref_ptr<GfxIndexBuffer>& buffer, GfxIndexType index_type, int offset = 0)                             = 0;
        virtual void bind_texture(const StringId& name, int array_element, const ref_ptr<GfxTexture>& texture, const ref_ptr<GfxSampler>& sampler) = 0;
        virtual void bind_uniform_buffer(const StringId& name, int offset, int range, const ref_ptr<GfxUniformBuffer>& buffer)                     = 0;
        virtual void bind_storage_buffer(const StringId& name, int offset, int range, const ref_ptr<GfxStorageBuffer>& buffer)                     = 0;
        virtual void draw(int vertex_count, int base_vertex, int instance_count)                                                                   = 0;
        virtual void draw_indexed(int index_count, int base_vertex, int instance_count)                                                            = 0;
        virtual void end_render_pass()                                                                                                             = 0;

        // Driver misc API (thread-safe)
        CallbackQueue*         queue() { return &m_callback_queue; }
        const GfxDeviceCaps&   device_caps() const { return m_device_caps; }
        const StringId&        driver_name() const { return m_driver_name; }
        const std::string&     shader_cache_path() const { return m_shader_cache_path; }
        const std::string&     pipeline_cache_path() const { return m_pipeline_cache_path; }
        const std::thread::id& thread_id() const { return m_thread_id; }
        const Mat4x4f&         clip_matrix() const { return m_clip_matrix; }
        std::size_t            frame_number() const { return m_frame_number.load(); }
        bool                   on_gfx_thread() const { return m_thread_id == std::this_thread::get_id(); }

        // System level API (gfx-thread-only)
        virtual void shutdown()                                    = 0;
        virtual void begin_frame()                                 = 0;
        virtual void flush()                                       = 0;
        virtual void end_frame()                                   = 0;
        virtual void prepare_window(const ref_ptr<Window>& window) = 0;
        virtual void swap_buffers(const ref_ptr<Window>& window)   = 0;

    protected:
        CallbackQueue      m_callback_queue;
        GfxDeviceCaps      m_device_caps;
        StringId           m_driver_name = SID("unknown");
        std::thread::id    m_thread_id   = std::this_thread::get_id();
        Mat4x4f            m_clip_matrix;
        std::atomic_size_t m_frame_number{0};
        std::string        m_shader_cache_path;
        std::string        m_pipeline_cache_path;
    };

}// namespace wmoge

#endif//GAME_ENGINE_TUTORIAL_GFX_DRIVER_HPP
