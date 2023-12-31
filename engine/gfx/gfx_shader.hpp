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

#ifndef GAME_ENGINE_TUTORIAL_GFX_SHADER_HPP
#define GAME_ENGINE_TUTORIAL_GFX_SHADER_HPP

#include "core/data.hpp"
#include "core/fast_map.hpp"
#include "core/string_id.hpp"
#include "gfx/gfx_resource.hpp"
#include "io/archive.hpp"

#include <array>

namespace wmoge {

    /**
     * @class GfxShaderReflection
     * @brief Reflection data of the shader
     */
    class GfxShaderReflection {
    public:
        struct Texture {
            StringId name;
            int      set        = -1;
            int      binding    = -1;
            int      array_size = -1;
            GfxTex   tex;

            friend Archive& operator<<(Archive& archive, const Texture& texture);
            friend Archive& operator>>(Archive& archive, Texture& texture);
        };
        struct Buffer {
            StringId name;
            int      set     = -1;
            int      binding = -1;
            int      size    = -1;

            friend Archive& operator<<(Archive& archive, const Buffer& buffer);
            friend Archive& operator>>(Archive& archive, Buffer& buffer);
        };
        fast_map<StringId, Texture>               textures;
        fast_map<StringId, Buffer>                ub_buffers;
        fast_map<StringId, Buffer>                sb_buffers;
        std::array<int, GfxLimits::MAX_DESC_SETS> textures_per_desc{};
        std::array<int, GfxLimits::MAX_DESC_SETS> ub_buffers_per_desc{};
        std::array<int, GfxLimits::MAX_DESC_SETS> sb_buffers_per_desc{};

        friend Archive& operator<<(Archive& archive, const GfxShaderReflection& reflection);
        friend Archive& operator>>(Archive& archive, GfxShaderReflection& reflection);
    };

    /**
     * @class GfxShader
     * @brief Complete gpu program (shader with complete set of stages) for the execution
     *
     * Shaders consists of a number of stages for execution.
     * Shader can be created from any engine thread. Shader compilation
     * is asynchronous and done in the background. As soon as shader compiled,
     * it will be used in the rendering pipeline.
     *
     * Possible shader stages sets:
     *  - vertex and fragment for classic rendering
     *  - compute for computational pipeline
     */
    class GfxShader : public GfxResource {
    public:
        ~GfxShader() override                                 = default;
        virtual GfxShaderStatus            status() const     = 0;
        virtual std::string                message() const    = 0;
        virtual const GfxShaderReflection* reflection() const = 0;
        virtual ref_ptr<Data>              byte_code() const  = 0;
    };

}// namespace wmoge

#endif//GAME_ENGINE_TUTORIAL_GFX_SHADER_HPP
