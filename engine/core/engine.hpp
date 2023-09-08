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

#ifndef GAME_ENGINE_TUTORIAL_ENGINE_HPP
#define GAME_ENGINE_TUTORIAL_ENGINE_HPP

#include <atomic>
#include <ctime>
#include <filesystem>
#include <memory>
#include <vector>

namespace wmoge {

    /**
     * @class Engine
     * @brief Global engine state responsible for other systems management
     *
     * Engine is a singleton class, which is responsible for engine start-up,
     * sub-systems initialization and de-initialization, and per frame update.
     *
     * Engine provides a single point for accessing global systems, allows to
     * push additional user layers to get updated, provides mechanism to query
     * global, update and game time.
     */
    class Engine {
    public:
        void push_layer(class Layer* layer);

        void request_close();
        bool close_requested() const;

        class Application*      application();
        class CmdLine*          cmd_line();
        class ConfigFile*       config_engine();
        class CallbackQueue*    main_queue();
        class FileSystem*       file_system();
        class TaskManager*      task_manager();
        class EventManager*     event_manager();
        class ResourceManager*  resource_manager();
        class WindowManager*    window_manager();
        class Input*            input();
        class GfxDriver*        gfx_driver();
        class AuxDrawManager*   aux_draw_manager();
        class SceneManager*     scene_manager();
        class ActionManager*    action_manager();
        class GameTokenManager* game_token_manager();
        class Profiler*         profiler();
        class ShaderCache*      shader_cache();
        class Console*          console();
        class Canvas*           canvas_2d_debug();
        class ScriptSystem*     script_system();
        class PfxManager*       pfx_manager();
        class AudioEngine*      audio_engine();

        std::chrono::steady_clock::time_point get_start();
        std::time_t                           get_time();
        std::tm                               get_tm(std::time_t time);
        std::string                           get_time_formatted(const char* format, std::time_t time);
        std::size_t                           get_iteration();
        float                                 get_time() const;
        float                                 get_delta_time() const;
        float                                 get_delta_time_game() const;

        static Engine* instance();

    private:
        friend class Main;

        std::size_t                           m_iteration = 0;
        std::atomic_bool                      m_close_requested{false};
        std::chrono::steady_clock::time_point m_start = std::chrono::steady_clock::now();

        class CmdLine*            m_cmd_line;
        class ConfigFile*         m_config_engine;
        class CallbackQueue*      m_main_queue;
        class FileSystem*         m_file_system;
        class TaskManager*        m_task_manager;
        class EventManager*       m_event_manager;
        class ResourceManager*    m_resource_manager;
        class WindowManager*      m_window_manager;
        class Input*              m_input;
        class GfxDriver*          m_gfx_driver;
        class AuxDrawManager*     m_aux_draw_manager;
        class SceneManager*       m_scene_manager;
        class ActionManager*      m_action_manager;
        class GameTokenManager*   m_game_token_manager;
        class Profiler*           m_profiler;
        class ShaderCache*        m_shader_cache;
        class Console*            m_console;
        class Canvas*             m_canvas_2d;
        class Canvas*             m_canvas_2d_debug;
        class ScriptSystem*       m_script_system;
        class PfxManager*         m_pfx_manager;
        class AudioEngine*        m_audio_engine;
        std::vector<class Layer*> m_layers;

        float              m_time;
        float              m_current_delta;
        float              m_current_delta_game;
        class Application* m_application = nullptr;
    };

}// namespace wmoge

#endif//GAME_ENGINE_TUTORIAL_ENGINE_HPP
