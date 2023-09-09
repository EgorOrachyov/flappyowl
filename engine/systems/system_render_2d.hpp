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

#ifndef GAME_ENGINE_TUTORIAL_SYSTEM_RENDER_2D_HPP
#define GAME_ENGINE_TUTORIAL_SYSTEM_RENDER_2D_HPP

#include "components/camera_2d.hpp"
#include "components/canvas_item.hpp"
#include "components/canvas_layer.hpp"
#include "render/canvas.hpp"
#include "scene/scene_system.hpp"

#include <memory>
#include <vector>

namespace wmoge {

    /**
     * @class Render2d
     * @brief Scene render 2d class responsible for 2d rendering
     */
    class SystemRender2d : public SceneSystem {
    public:
        SystemRender2d(class Scene* scene);
        ~SystemRender2d() override = default;

        void process() override;

    private:
        std::unique_ptr<Canvas> m_canvas;
    };

}// namespace wmoge

#endif//GAME_ENGINE_TUTORIAL_SYSTEM_RENDER_2D_HPP
