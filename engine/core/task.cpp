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

#include "core/task.hpp"
#include "core/engine.hpp"
#include "core/log.hpp"
#include "core/task_manager.hpp"
#include "debug/profiler.hpp"

namespace wmoge {

    Task::Task(TaskRunnable runnable) : Task(StringId(), std::move(runnable)) {
    }
    Task::Task(StringId name, TaskRunnable runnable) : m_runnable(std::move(runnable)), m_name(name) {
    }

    void Task::set_task_manager(class TaskManager* task_manager) {
        m_task_manager = task_manager;
    }
    void Task::set_to_wait_total(int deps_to_wait) {
        assert(deps_to_wait >= 0);
        if (deps_to_wait == 0) {
            run();
            return;
        }
        m_to_wait_total = deps_to_wait;
    }
    TaskAsync Task::run() {
        assert(m_ok.load() == m_to_wait_total);

        TaskManager* task_manager = m_task_manager ? m_task_manager : Engine::instance()->task_manager();
        task_manager->submit(ref_ptr<Task>(this));

        return TaskAsync(ref_ptr<Task>(this));
    }

    void Task::execute(TaskContext& context) {
        WG_AUTO_PROFILE_TASK(m_name.str());

        auto ret = m_runnable(context);

        if (ret) {
            set_failed();
            WG_LOG_ERROR("failed: " << m_name << " worker: " << context.thread_name());
        } else {
            set_result(0);
        }
    }

    void Task::notify(AsyncStatus status, AsyncStateBase* invoker) {
        AsyncStateBase::notify(status, invoker);

        assert(m_to_wait_total > 0);

        if (status == AsyncStatus::Ok) {
            int prev = m_ok.fetch_add(1);
            if (prev + 1 == m_to_wait_total) run();
            return;
        }
        if (status == AsyncStatus::Failed) {
            int prev = m_failed.fetch_add(1);
            if (prev == 0) {
                set_failed();
                WG_LOG_ERROR("failed: " << m_name << " dep failed");
            }
            return;
        }
    }
    void Task::wait_completed() {
        WG_AUTO_PROFILE_TASK(m_name.str());

        AsyncState::wait_completed();
    }

}// namespace wmoge
