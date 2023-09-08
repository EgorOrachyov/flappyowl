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

#ifndef GAME_ENGINE_TUTORIAL_SHADER_BUILDER_HPP
#define GAME_ENGINE_TUTORIAL_SHADER_BUILDER_HPP

#include "core/fast_vector.hpp"
#include "core/string_id.hpp"
#include "render/shader_variant.hpp"
#include "resource/mesh.hpp"
#include "resource/shader.hpp"

#include <sstream>
#include <string>
#include <vector>

namespace wmoge {

    /**
     * @class ShaderBuilder
     * @brief Builder of a particular shader variation
     */
    class ShaderBuilder {
    public:
        ShaderBuilder& set_shader(Shader* shader);
        ShaderBuilder& set_key(StringId key);
        ShaderBuilder& set_attribs(MeshAttribs mesh_attribs);
        ShaderBuilder& add_define(const std::string& define);
        ShaderBuilder& add_defines(const fast_vector<std::string>& defines);
        ShaderBuilder& add_vertex_module(const std::string& code);
        ShaderBuilder& add_fragment_module(const std::string& code);

        bool compile();

        ShaderVariant& get_variant();
        MeshAttribs    get_mesh_attribs();

    private:
        Shader*           m_shader;
        StringId          m_key;
        std::stringstream m_vertex;
        std::stringstream m_fragment;
        ShaderVariant     m_variant;
        MeshAttribs       m_mesh_attribs;
    };

}// namespace wmoge

#endif//GAME_ENGINE_TUTORIAL_SHADER_BUILDER_HPP
