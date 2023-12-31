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

#ifndef GAME_ENGINE_TUTORIAL_LUA_BINDINGS_EVENT_HPP
#define GAME_ENGINE_TUTORIAL_LUA_BINDINGS_EVENT_HPP

#include "scripting/lua_bindings/lua_bindings.hpp"
#include "scripting/lua_bindings/lua_bindings_core.hpp"

#include "core/engine.hpp"
#include "event/event.hpp"
#include "event/event_action.hpp"
#include "event/event_input.hpp"
#include "event/event_listener.hpp"
#include "event/event_manager.hpp"
#include "event/event_resource.hpp"
#include "event/event_token.hpp"
#include "event/event_window.hpp"

namespace wmoge {

    struct LuaEvent : public LuaObject {
        const StringId& type() const {
            return cast_unsafe<Event>()->type();
        }
    };

    struct LuaEventListener : public LuaRefCnt {
        void unsubscribe() {
            cast_unsafe<EventListener>()->unsubscribe();
        }
        void pause() {
            cast_unsafe<EventListener>()->pause();
        }
        void resume() {
            cast_unsafe<EventListener>()->resume();
        }
    };

    struct LuaEventWindow : public LuaEvent {
        int notification() const {
            return static_cast<int>(cast_unsafe<EventWindow>()->notification);
        }
    };

    struct LuaEventInput : public LuaEvent {
    };

    struct LuaEventMouse : public LuaEventInput {
    };

    struct LuaEventKeyboard : public LuaEventInput {
        int action() const {
            return static_cast<int>(cast_unsafe<EventKeyboard>()->action);
        }
        int key() const {
            return static_cast<int>(cast_unsafe<EventKeyboard>()->key);
        }
        std::string text() const {
            return cast_unsafe<EventKeyboard>()->text;
        }
    };

    struct LuaEventJoystick : public LuaEventInput {
    };

    struct LuaEventDrop : public LuaEventInput {
    };

    struct LuaEventAction : public LuaEvent {
        const StringId& name() const {
            return cast_unsafe<EventAction>()->name;
        }
        float strength() const {
            return cast_unsafe<EventAction>()->strength;
        }
    };

    struct LuaEventToken : public LuaEvent {
        const StringId& token() const {
            return cast_unsafe<EventToken>()->token;
        }
        TokenNotification notification() const {
            return cast_unsafe<EventToken>()->notification;
        }
    };

}// namespace wmoge

#endif//GAME_ENGINE_TUTORIAL_LUA_BINDINGS_EVENT_HPP
