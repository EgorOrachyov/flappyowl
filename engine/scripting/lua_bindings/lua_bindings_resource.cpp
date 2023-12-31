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

#include "lua_bindings_resource.hpp"

#include "scripting/lua/lua_type_traits.hpp"

namespace wmoge {

    static int lua_ResourceManager_load(lua_State* state) {
        auto resource_id = WG_LUA_ARG(state, 0);

        auto* resource_manager = Engine::instance()->resource_manager();
        auto  resource         = resource_manager->load(LuaTypeTraits::to_sid(resource_id));
        LuaTypeTraits::from_object(state, resource.get()).push();

        return 1;
    }

    static int lua_ResourceManager_find(lua_State* state) {
        auto resource_id = WG_LUA_ARG(state, 0);

        auto* resource_manager = Engine::instance()->resource_manager();
        auto  resource         = resource_manager->find(LuaTypeTraits::to_sid(resource_id));
        LuaTypeTraits::from_object(state, resource.get()).push();

        return 1;
    }

    void LuaBindings::bind_resource(luabridge::Namespace& ns, fast_map<const Class*, LuaConvCppToLua>& mapping) {
        WG_LUA_MAP_CLASS(mapping, Resource);
        ns = ns.deriveClass<LuaResource, LuaObject>("Resource")
                     .addFunction("duplicate", &LuaResource::duplicate)
                     .addFunction("get_name", &LuaResource::get_name)
                     .endClass();

        WG_LUA_MAP_CLASS(mapping, AudioStream);
        ns = ns.deriveClass<LuaAudioStream, LuaResource>("AudioStream")
                     .addFunction("get_length", &LuaAudioStream::get_length)
                     .addFunction("get_samples_rate", &LuaAudioStream::get_samples_rate)
                     .addFunction("get_bits_per_sample", &LuaAudioStream::get_bits_per_sample)
                     .addFunction("get_num_samples", &LuaAudioStream::get_num_samples)
                     .addFunction("get_num_channels", &LuaAudioStream::get_num_channels)
                     .addFunction("is_stereo", &LuaAudioStream::is_stereo)
                     .addFunction("is_mono", &LuaAudioStream::is_mono)
                     .endClass();

        WG_LUA_MAP_CLASS(mapping, ConfigFile);
        ns = ns.deriveClass<LuaConfigFile, LuaResource>("ConfigFile")
                     .addFunction("get_bool", &LuaConfigFile::get_bool)
                     .addFunction("get_int", &LuaConfigFile::get_int)
                     .addFunction("get_float", &LuaConfigFile::get_float)
                     .addFunction("get_string", &LuaConfigFile::get_string)
                     .endClass();

        WG_LUA_MAP_CLASS(mapping, Texture);
        ns = ns.deriveClass<LuaTexture, LuaResource>("Texture")
                     .addFunction("get_width", &LuaTexture::get_width)
                     .addFunction("get_height", &LuaTexture::get_height)
                     .addFunction("get_depth", &LuaTexture::get_depth)
                     .addFunction("get_array_slices", &LuaTexture::get_array_slices)
                     .addFunction("get_mips", &LuaTexture::get_mips)
                     .addFunction("get_srgb", &LuaTexture::get_srgb)
                     .addFunction("get_compression", &LuaTexture::get_compression)
                     .endClass();

        WG_LUA_MAP_CLASS(mapping, Sprite);
        ns = ns.deriveClass<LuaSprite, LuaResource>("Sprite")
                     .addFunction("get_animation_texture", &LuaSprite::_c_get_animation_texture)
                     .addFunction("get_animation_frame", &LuaSprite::get_animation_frame)
                     .addFunction("get_animation_n_frames", &LuaSprite::get_animation_n_frames)
                     .addFunction("get_animation_speed", &LuaSprite::get_animation_speed)
                     .addFunction("get_animation_loop", &LuaSprite::get_animation_loop)
                     .addFunction("get_animation_id", &LuaSprite::get_animation_id)
                     .addFunction("get_n_animations", &LuaSprite::get_n_animations)
                     .addFunction("get_size", &LuaSprite::get_size)
                     .addFunction("get_pivot", &LuaSprite::get_pivot)
                     .endClass();

        WG_LUA_MAP_CLASS(mapping, PfxEffect);
        ns = ns.deriveClass<LuaPfxEffect, LuaResource>("PfxEffect")
                     .addFunction("get_components_count", &LuaPfxEffect::get_components_count)
                     .addFunction("get_type", &LuaPfxEffect::get_type)
                     .endClass();

        ns = ns.beginNamespace("ResourceManager")
                     .addCFunction("load", lua_ResourceManager_load)
                     .addCFunction("find", lua_ResourceManager_find)
                     .endNamespace();
    }

}// namespace wmoge