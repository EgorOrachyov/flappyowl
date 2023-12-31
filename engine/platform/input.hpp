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

#ifndef GAME_ENGINE_TUTORIAL_INPUT_HPP
#define GAME_ENGINE_TUTORIAL_INPUT_HPP

#include "core/string_id.hpp"
#include "platform/input_defs.hpp"
#include "platform/input_devices.hpp"

#include <unordered_map>

namespace wmoge {

    /**
     * @class Input
     * @brief Interface for OS-specific input layer to get user input
     */
    class Input {
    public:
        virtual ~Input()                                                    = default;
        virtual ref_ptr<Mouse>    mouse()                                   = 0;
        virtual ref_ptr<Keyboard> keyboard()                                = 0;
        virtual ref_ptr<Joystick> joystick(int id)                          = 0;
        virtual int               joystick_mapping(const StringId& mapping) = 0;
    };

}// namespace wmoge

#endif//GAME_ENGINE_TUTORIAL_INPUT_HPP
