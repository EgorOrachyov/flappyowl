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

#include "material.hpp"

#include "core/class.hpp"
#include "core/engine.hpp"
#include "debug/profiler.hpp"
#include "gfx/gfx_driver.hpp"
#include "resource/resource_manager.hpp"

#include <cstring>
#include <magic_enum.hpp>
#include <sstream>

namespace wmoge {

    void Material::create(ref_ptr<MaterialShader> shader) {
        assert(shader);

        m_shader = std::move(shader);
        m_textures.resize(m_shader->get_textures_count());
        m_parameters.resize(m_shader->get_parameters_size());
        m_gfx_parameters = Engine::instance()->gfx_driver()->make_uniform_buffer(int(m_parameters.size()), GfxMemUsage::GpuLocal, get_name());

        for (const auto& entry : m_shader->get_parameters()) {
            auto&         param = entry.second;
            std::uint8_t* mem   = m_parameters.data() + param.offset;
            set_parameter_from_string(param.type, param.value, mem);
        }

        // todo: default textures
    }

    bool Material::load_from_import_options(const YamlTree& tree) {
        WG_AUTO_PROFILE_RESOURCE();

        if (!Resource::load_from_import_options(tree)) return false;

        auto params  = tree["params"];
        auto res_man = Engine::instance()->resource_manager();

        std::string shader;
        params["shader"] >> shader;
        if (shader.empty()) {
            WG_LOG_ERROR("passed empty shader for " << get_name());
            return false;
        }

        auto material_shader = res_man->find(SID(shader)).cast<MaterialShader>();
        if (!material_shader) {
            WG_LOG_ERROR("not loaded shader " << shader << ". shader must be loaded");
            return false;
        }

        create(material_shader);

        auto parameters = params["parameters"];
        for (auto it = parameters.first_child(); it.valid(); it = it.next_sibling()) {
            std::string name;
            std::string value;

            it["name"] >> name;
            it["value"] >> value;

            auto param = m_shader->get_parameters().find(SID(name));
            if (param == m_shader->get_parameters().end()) {
                WG_LOG_ERROR("no such param in shader " << name);
                continue;
            }

            set_parameter_from_string(param->second.type, value, m_parameters.data() + param->second.offset);
        }

        auto textures = params["textures"];
        for (auto it = textures.first_child(); it.valid(); it = it.next_sibling()) {
            std::string name;
            std::string value;

            it["name"] >> name;
            it["value"] >> value;

            auto texture = res_man->find(SID(value)).cast<Texture>();
            if (!texture) {
                WG_LOG_ERROR("not loaded texture " << value);
                continue;
            }

            set_texture(SID(name), texture);
        }

        return true;
    }
    void Material::copy_to(Resource& copy) {
        Resource::copy_to(copy);
        auto material              = dynamic_cast<Material*>(&copy);
        material->m_shader         = m_shader;
        material->m_gfx_parameters = Engine::instance()->gfx_driver()->make_uniform_buffer(int(m_parameters.size()), GfxMemUsage::GpuLocal, get_name());
        material->m_parameters     = m_parameters;
        material->m_textures       = m_textures;
    }

    const ref_ptr<MaterialShader>& Material::get_shader() {
        return m_shader;
    }
    const fast_vector<std::uint8_t>& Material::get_parameters() {
        return m_parameters;
    }
    const fast_vector<ref_ptr<Texture>>& Material::get_textures() {
        return m_textures;
    }
    const ref_ptr<GfxUniformBuffer>& Material::get_gfx_parameters() {
        if (m_dirty && !m_parameters.empty()) {
            auto* gfx  = Engine::instance()->gfx_driver();
            auto  data = make_ref<Data>(m_parameters.data(), m_parameters.size());
            gfx->update_uniform_buffer(m_gfx_parameters, 0, int(m_parameters.size()), data);
            m_dirty = false;
        }
        return m_gfx_parameters;
    }

    void Material::set_int(const StringId& name, int value) {
        assert(m_shader);

        const auto  type   = ShaderParamType::Int;
        const auto& params = m_shader->get_parameters();
        const auto  param  = params.find(name);

        if (param == params.end() || param->second.type != type) {
            WG_LOG_ERROR("no such param " << name << " of type " << magic_enum::enum_name(type));
            return;
        }

        std::memcpy(m_parameters.data() + param->second.offset, &value, param->second.size);
        m_dirty = true;
    }
    void Material::set_float(const StringId& name, float value) {
        assert(m_shader);

        const auto  type   = ShaderParamType::Float;
        const auto& params = m_shader->get_parameters();
        const auto  param  = params.find(name);

        if (param == params.end() || param->second.type != type) {
            WG_LOG_ERROR("no such param " << name << " of type " << magic_enum::enum_name(type));
            return;
        }

        std::memcpy(m_parameters.data() + param->second.offset, &value, param->second.size);
        m_dirty = true;
    }
    void Material::set_vec2(const StringId& name, const Vec2f& value) {
        assert(m_shader);

        const auto  type   = ShaderParamType::Vec2;
        const auto& params = m_shader->get_parameters();
        const auto  param  = params.find(name);

        if (param == params.end() || param->second.type != type) {
            WG_LOG_ERROR("no such param " << name << " of type " << magic_enum::enum_name(type));
            return;
        }

        std::memcpy(m_parameters.data() + param->second.offset, &value, param->second.size);
        m_dirty = true;
    }
    void Material::set_vec3(const StringId& name, const Vec3f& value) {
        assert(m_shader);

        const auto  type   = ShaderParamType::Vec3;
        const auto& params = m_shader->get_parameters();
        const auto  param  = params.find(name);

        if (param == params.end() || param->second.type != type) {
            WG_LOG_ERROR("no such param " << name << " of type " << magic_enum::enum_name(type));
            return;
        }

        std::memcpy(m_parameters.data() + param->second.offset, &value, param->second.size);
        m_dirty = true;
    }
    void Material::set_vec4(const StringId& name, const Vec4f& value) {
        assert(m_shader);

        const auto  type   = ShaderParamType::Vec4;
        const auto& params = m_shader->get_parameters();
        const auto  param  = params.find(name);

        if (param == params.end() || param->second.type != type) {
            WG_LOG_ERROR("no such param " << name << " of type " << magic_enum::enum_name(type));
            return;
        }

        std::memcpy(m_parameters.data() + param->second.offset, &value, param->second.size);
        m_dirty = true;
    }
    void Material::set_texture(const StringId& name, const ref_ptr<Texture>& texture) {
        assert(m_shader);

        if (!texture) {
            WG_LOG_ERROR("an attempt to set null " << name << " texture");
            return;
        }

        const auto& textures      = m_shader->get_textures();
        const auto  texture_param = textures.find(name);

        if (texture_param == textures.end() || texture_param->second.type != texture->get_tex_type()) {
            WG_LOG_ERROR("no such param " << name << " of type " << magic_enum::enum_name(texture->get_tex_type()));
            return;
        }

        m_textures[texture_param->second.id] = texture;
    }
    void Material::set_parameter_from_string(ShaderParamType type, const std::string& str_value, void* mem) {
        std::stringstream value(str_value);

        switch (type) {
            case ShaderParamType::Int:
                value >> *(reinterpret_cast<int*>(mem));
                break;
            case ShaderParamType::Float:
                value >> *(reinterpret_cast<float*>(mem));
                break;
            case ShaderParamType::Vec2:
                value >> *(reinterpret_cast<float*>(mem) + 0);
                value >> *(reinterpret_cast<float*>(mem) + 1);
                break;
            case ShaderParamType::Vec3:
                value >> *(reinterpret_cast<float*>(mem) + 0);
                value >> *(reinterpret_cast<float*>(mem) + 1);
                value >> *(reinterpret_cast<float*>(mem) + 2);
                break;
            case ShaderParamType::Vec4:
                value >> *(reinterpret_cast<float*>(mem) + 0);
                value >> *(reinterpret_cast<float*>(mem) + 1);
                value >> *(reinterpret_cast<float*>(mem) + 2);
                value >> *(reinterpret_cast<float*>(mem) + 3);
                break;
            default:
                WG_LOG_ERROR("invalid shader parameter type");
                return;
        }
    }

    void Material::register_class() {
        auto* cls = Class::register_class<Material>();
    }

}// namespace wmoge