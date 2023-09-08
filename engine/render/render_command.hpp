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

#ifndef GAME_ENGINE_TUTORIAL_RENDER_COMMAND_HPP
#define GAME_ENGINE_TUTORIAL_RENDER_COMMAND_HPP

#include "core/ref.hpp"
#include "core/string_id.hpp"

#include "gfx/gfx_driver.hpp"

#include "math/mat.hpp"
#include "math/vec.hpp"

#include <array>

namespace wmoge {

    /**
     * @class DrawParams
     * @brief Params to draw single object to pass to the shader
     */
    struct DrawParams {
        Mat4x4f      transform;
        Mat4x4f      transform_prev;
        Vec4f        tint;
        unsigned int object_id;
        unsigned int material_id;
        unsigned int flags;
    };

    /**
     * @class RenderCommand
     * @brief Base class for drawing anything to the screen as a single draw call
     */
    class RenderCommand : public RefCnt {
    public:
        ~RenderCommand() override = default;

        /** Called by rendering pipeline to execute draw call on gfx device */
        virtual bool execute(GfxDriver* driver) = 0;
        /** Called by pipeline no prepare command for rendering (if required) */
        virtual bool compile(GfxDriver* driver) = 0;
        /** @return Tag this command has to determine where to render it */
        virtual const StringId& get_tag() = 0;
        /** @return Debug name of the command */
        virtual const StringId& get_name() = 0;
        /** @return True if compiled, otherwise requires compilation */
        virtual bool is_compiled() = 0;
    };

}// namespace wmoge

#endif//GAME_ENGINE_TUTORIAL_RENDER_COMMAND_HPP
