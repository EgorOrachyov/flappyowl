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

#include "callback_queue.hpp"

#include "debug/profiler.hpp"

namespace wmoge {

    CallbackQueue::CallbackQueue(std::size_t buffer_size) {
        m_memory_buffer.resize(buffer_size);
    }
    CallbackQueue::~CallbackQueue() {
        clear();
    }
    void CallbackQueue::flush() {
        WG_AUTO_PROFILE_CORE();

        std::lock_guard guard(m_mutex);
        std::size_t     offset = 0;
        while (m_allocated_callbacks > 0) {
            Callback* callback = reinterpret_cast<Callback*>(m_memory_buffer.data() + offset);
            offset += callback->size();
            callback->execute();
            callback->~Callback();
            m_allocated_callbacks -= 1;
        }

        m_allocated_bytes = 0;
    }
    void CallbackQueue::clear() {
        WG_AUTO_PROFILE_CORE();

        std::lock_guard guard(m_mutex);
        std::size_t     offset = 0;
        while (m_allocated_callbacks > 0) {
            Callback* callback = reinterpret_cast<Callback*>(m_memory_buffer.data() + offset);
            offset += callback->size();
            callback->~Callback();
            m_allocated_callbacks -= 1;
        }
        m_allocated_bytes = 0;
    }

}// namespace wmoge
