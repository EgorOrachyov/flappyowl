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

#ifndef GAME_ENGINE_TUTORIAL_MATERIAL_HPP
#define GAME_ENGINE_TUTORIAL_MATERIAL_HPP

#include "core/fast_map.hpp"
#include "core/fast_vector.hpp"
#include "gfx/gfx_buffers.hpp"
#include "math/vec.hpp"
#include "resource/material_shader.hpp"
#include "resource/texture.hpp"

namespace wmoge {

    /**
     * @class Material
     * @brief Controls the rendering of the mesh geometry
     *
     * Material is composed of the shader object and a set of material params.
     * Material shader object defines the set of available params for rendering
     * settings. Material params provide user the ability to easily set params
     * to tweak rendering of the concrete object. User can apply shader to a
     * given mesh geometry and issuer rendering on a GPU.
     *
     * @note Particular shader variation depends on a mesh properties and other settings,
     *       thus huge number of materials with different settings may cause a significant
     *       increase of shader variations count.
     *
     * @see MaterialShader
     */
    class Material : public Resource {
    public:
        WG_OBJECT(Material, Resource);

        /**
         * @brief Create material using specified shader
         *
         * This method initialized material with specified shader, allocates
         * params storage with default values, setups default textures and
         * prepares material for the rendering.
         *
         * @param shader Valid shader to use for this material
         */
        void create(ref_ptr<MaterialShader> shader);

        /** @brief Set material int parameter value by name */
        void set_int(const StringId& name, int value);
        /** @brief Set material float parameter value by name */
        void set_float(const StringId& name, float value);
        /** @brief Set material vec2 parameter value by name */
        void set_vec2(const StringId& name, const Vec2f& value);
        /** @brief Set material vec3 parameter value by name */
        void set_vec3(const StringId& name, const Vec3f& value);
        /** @brief Set material vec4 parameter value by name */
        void set_vec4(const StringId& name, const Vec4f& value);
        /** @brief Set material texture parameter value by name */
        void set_texture(const StringId& name, const ref_ptr<Texture>& texture);

        bool load_from_import_options(const YamlTree& tree) override;
        void copy_to(Resource& copy) override;

        const ref_ptr<MaterialShader>&       get_shader();
        const fast_vector<std::uint8_t>&     get_parameters();
        const fast_vector<ref_ptr<Texture>>& get_textures();
        const ref_ptr<GfxUniformBuffer>&     get_gfx_parameters();

    private:
        void set_parameter_from_string(ShaderParamType type, const std::string& value, void* mem);

    private:
        ref_ptr<MaterialShader>       m_shader;
        ref_ptr<GfxUniformBuffer>     m_gfx_parameters;
        fast_vector<std::uint8_t>     m_parameters;
        fast_vector<ref_ptr<Texture>> m_textures;
        bool                          m_dirty = true;
    };

}// namespace wmoge

#endif//GAME_ENGINE_TUTORIAL_MATERIAL_HPP
