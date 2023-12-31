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

#ifndef GAME_ENGINE_TUTORIAL_MAIN_HPP
#define GAME_ENGINE_TUTORIAL_MAIN_HPP

#include <chrono>
#include <iostream>
#include <memory>
#include <string>

namespace wmoge {

    /**
     * @class Main
     * @brief Control engine execution: initialization, runtime, and shutdown
     */
    class Main {
    public:
        explicit Main(class Application* application);
        ~Main();

        bool load_config(const std::string& config_path);
        bool initialize();
        bool iteration();
        bool shutdown();

    private:
        using clock      = std::chrono::steady_clock;
        using time_point = clock::time_point;
        using ns         = std::chrono::nanoseconds;

        std::size_t m_num_iterations = 0;
        time_point  m_time_point{};
        time_point  m_runtime_time{};

        std::unique_ptr<class CmdLine>          m_cmd_line;
        std::unique_ptr<class ConfigFile>       m_config_engine;
        std::unique_ptr<class CallbackQueue>    m_main_queue;
        std::unique_ptr<class FileSystem>       m_file_system;
        std::unique_ptr<class TaskManager>      m_task_manager;
        std::unique_ptr<class EventManager>     m_event_manager;
        std::unique_ptr<class ResourceManager>  m_resource_manager;
        std::unique_ptr<class AuxDrawManager>   m_aux_draw_manager;
        std::unique_ptr<class SceneManager>     m_scene_manager;
        std::unique_ptr<class ActionManager>    m_action_manager;
        std::unique_ptr<class GameTokenManager> m_game_token_manager;
        std::unique_ptr<class Profiler>         m_profiler;
        std::unique_ptr<class ShaderCache>      m_shader_cache;
        std::unique_ptr<class Console>          m_console;
        std::unique_ptr<class Canvas>           m_canvas_2d_debug;
        std::unique_ptr<class PfxManager>       m_pfx_manager;

        std::unique_ptr<class GlfwWindowManager> m_glfw_window_manager;
        std::unique_ptr<class VKDriver>          m_vk_driver;
        std::unique_ptr<class ALAudioEngine>     m_al_engine;
        std::unique_ptr<class DebugLayer>        m_dbg_layer;
        std::unique_ptr<class LuaScriptSystem>   m_lua_script_system;
    };

}// namespace wmoge

#endif//GAME_ENGINE_TUTORIAL_MAIN_HPP
