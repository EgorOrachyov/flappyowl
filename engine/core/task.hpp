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

#ifndef GAME_ENGINE_TUTORIAL_TASK_HPP
#define GAME_ENGINE_TUTORIAL_TASK_HPP

#include "core/async.hpp"
#include "core/ref.hpp"
#include "core/string_id.hpp"

#include <atomic>
#include <functional>

namespace wmoge {

    /**
     * @class TaskContext
     * @brief Context passed in a time of task execution
     */
    class TaskContext {
    public:
        const StringId& thread_name() const { return m_thread_name; }
        int             thread_id() const { return m_thread_id; }
        class Task*     task() const { return m_task; }

    private:
        friend class TaskManager;

        class Task* m_task = nullptr;
        StringId    m_thread_name;
        int         m_thread_id = -1;
    };

    /**
     * @class TaskRunnable
     * @brief Function which used to make task
     */
    using TaskRunnable = std::function<int(TaskContext&)>;

    /**
     * @class TaskAsync
     * @brief Handle to submitted task
     */
    using TaskAsync = Async<int>;

    /**
     * @class Task
     * @brief Shared task state
     *
     * Typical use cases:
     *  - Async execution of different tasks
     *  - Background tasks using worker threads for a heavy job
     *  - Main thread to execute thread-sensitive work affecting scene or game objects
     *
     *  How to use:
     *  - Instantiate task object
     *  - Set optional abortion callback
     *  - Set mode of execution (main/background)
     *  - Optionally set manager where you want to exec task
     *  - a) Call run on task
     *  - b) Or specify how many deps to wait on and task will be started automatically when all satisfied
     */
    class Task : public AsyncState<int> {
    public:
        explicit Task(StringId name, TaskRunnable runnable);
        explicit Task(TaskRunnable runnable);

        ~Task() override = default;

        /**
         * @brief Set task manager for execution of this task
         *
         * @param task_manager Manager for task execution; if null will be used default
         */
        void set_task_manager(class TaskManager* task_manager);

        /**
         * @brief Set number for deps to wait for before this task can start
         *
         * When all deps are completed successfully (not failed), then task can start
         *
         * @param deps_to_wait Number of deps to wait; if 0 task starts immediately
         */
        void set_to_wait_total(int deps_to_wait);

        /**
         * @brief Kick off task for execution
         *
         * If set main, then will be executed on a main engine thread.
         * If set background, then will be executed in one of background threads.
         *
         * @return Async to track task execution
         */
        TaskAsync run();

        TaskRunnable&      runnable() { return m_runnable; }
        const StringId&    name() const { return m_name; }
        class TaskManager* task_manager() const { return m_task_manager; }

        void notify(AsyncStatus status, AsyncStateBase* invoker) override;
        void wait_completed() override;

    protected:
        friend class TaskManager;
        void execute(TaskContext& context);

    private:
        TaskRunnable       m_runnable;
        StringId           m_name;
        class TaskManager* m_task_manager = nullptr;
        int                m_to_wait_total{0};
        std::atomic_int    m_ok{0};
        std::atomic_int    m_failed{0};
    };

}// namespace wmoge

#endif//GAME_ENGINE_TUTORIAL_TASK_HPP
