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

#ifndef GAME_ENGINE_TUTORIAL_LUA_SCRIPT_INSTANCE_HPP
#define GAME_ENGINE_TUTORIAL_LUA_SCRIPT_INSTANCE_HPP

#include "resource/script.hpp"
#include "scripting/lua/lua_defs.hpp"
#include "scripting/lua/lua_script_system.hpp"
#include "scripting/script_instance.hpp"

namespace wmoge {
    /**
     * @class LuaScriptInstance
     * @brief Lua script instance holding attached to an object script
     */
    class LuaScriptInstance final : public ScriptInstance {
    public:
        LuaScriptInstance(luabridge::LuaRef script_object, ref_ptr<class LuaScript> script, Object* object, lua_State* state);
        ~LuaScriptInstance() override;

        ScriptFunctionsMask get_mask() override;
        Script*             get_script() override;
        Object*             get_owner() override;

        void on_create() override;
        void on_scene_enter() override;
        void on_scene_exit() override;
        void on_transform_updated() override;
        void on_update(float delta_time) override;
        void on_signal(const StringId& signal) override;
        void on_input_mouse(const ref_ptr<EventMouse>& event) override;
        void on_input_keyboard(const ref_ptr<EventKeyboard>& event) override;
        void on_input_joystick(const ref_ptr<EventJoystick>& event) override;
        void on_input_drop(const ref_ptr<EventDrop>& event) override;
        void on_action(const ref_ptr<EventAction>& action) override;
        void on_token(const ref_ptr<EventToken>& token) override;

        int set(const StringId& property, const Var& value) override;
        int get(const StringId& property, Var& value) override;
        int call(const StringId& method, int argc, const Var* argv, Var& ret) override;

        luabridge::LuaRef& get_script_object() { return m_script_object; }

    private:
        luabridge::LuaRef        m_script_object;
        ref_ptr<class LuaScript> m_script;
        Object*                  m_object = nullptr;
        LuaScriptSystem*         m_system = nullptr;
        lua_State*               m_state  = nullptr;
        ScriptFunctionsMask      m_mask;
        ScriptFunctionsMask      m_mask_failed;
    };

}// namespace wmoge

#endif//GAME_ENGINE_TUTORIAL_LUA_SCRIPT_INSTANCE_HPP
