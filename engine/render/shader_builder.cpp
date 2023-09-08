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

#include "shader_builder.hpp"

#include "core/engine.hpp"
#include "debug/profiler.hpp"
#include "gfx/gfx_driver.hpp"
#include "render/shader_cache.hpp"

namespace wmoge {

    ShaderBuilder& ShaderBuilder::set_shader(Shader* shader) {
        m_shader = shader;
        return *this;
    }
    ShaderBuilder& ShaderBuilder::set_key(StringId key) {
        m_key = std::move(key);
        return *this;
    }
    ShaderBuilder& ShaderBuilder::set_attribs(MeshAttribs mesh_attribs) {
        m_mesh_attribs = mesh_attribs;
        return *this;
    }
    ShaderBuilder& ShaderBuilder::add_define(const std::string& define) {
        m_vertex << "#define " << define << "\n";
        m_fragment << "#define " << define << "\n";
        return *this;
    }
    ShaderBuilder& ShaderBuilder::add_defines(const fast_vector<std::string>& defines) {
        for (const auto& d : defines) add_define(d);
        return *this;
    }
    ShaderBuilder& ShaderBuilder::add_vertex_module(const std::string& code) {
        m_vertex << code;
        return *this;
    }
    ShaderBuilder& ShaderBuilder::add_fragment_module(const std::string& code) {
        m_fragment << code;
        return *this;
    }
    bool ShaderBuilder::compile() {
        WG_AUTO_PROFILE_RENDER();

        ShaderCache* shader_cache = Engine::instance()->shader_cache();

        std::string        source = m_vertex.str() + m_fragment.str();
        ref_ptr<GfxShader> shader = shader_cache->find(source);

        if (!shader) {
            StringId gfx_name(m_shader->get_name().str() + ":" + m_key.str());
            shader = Engine::instance()->gfx_driver()->make_shader(m_vertex.str(), m_fragment.str(), gfx_name);
            shader_cache->cache(source, shader);
        }

        m_variant.m_owner      = m_shader;
        m_variant.m_key        = m_key;
        m_variant.m_hash       = std::hash<std::string>()(source);
        m_variant.m_gfx_shader = shader;
        return true;
    }
    ShaderVariant& ShaderBuilder::get_variant() {
        return m_variant;
    }
    MeshAttribs ShaderBuilder::get_mesh_attribs() {
        return m_mesh_attribs;
    }

}// namespace wmoge