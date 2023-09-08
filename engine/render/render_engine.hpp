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

#ifndef GAME_ENGINE_TUTORIAL_RENDER_ENGINE_HPP
#define GAME_ENGINE_TUTORIAL_RENDER_ENGINE_HPP

#include "core/callback_queue.hpp"

#include "render/render_camera.hpp"
#include "render/render_pipeline.hpp"
#include "render/render_view.hpp"

#include <mutex>
#include <unordered_map>
#include <vector>

namespace wmoge {

    /**
     * @class RenderEngine
     * @brief Engine is responsible for drawing all scene objects into the screen
     */
    class RenderEngine {
    public:
        void render(ref_ptr<RenderPipeline> pipeline, ref_ptr<RenderView> view);

        ref_ptr<RenderPipeline> make_standard_pipeline();
        ref_ptr<RenderView>     make_view();

        class BufferManager*   buffer_manager();
        class MaterialManager* material_manager();
        class TextureManager*  texture_manager();
        class GeometryManager* geometry_manager();

        CallbackQueue* queue_render();
        CallbackQueue* queue_gfx();

    private:
        std::unique_ptr<class BufferManager>   m_buffer_manager;
        std::unique_ptr<class MaterialManager> m_material_manager;
        std::unique_ptr<class TextureManager>  m_texture_manager;
        std::unique_ptr<class GeometryManager> m_geometry_manager;

        CallbackQueue m_queue_render;// thread to interact with render
        CallbackQueue m_queue_gfx;   // thread to interact with gfx and process views

        std::mutex m_mutex;
    };

}// namespace wmoge

#endif//GAME_ENGINE_TUTORIAL_RENDER_ENGINE_HPP
