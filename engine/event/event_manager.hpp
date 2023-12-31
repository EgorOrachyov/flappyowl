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

#ifndef GAME_ENGINE_TUTORIAL_EVENT_MANAGER_HPP
#define GAME_ENGINE_TUTORIAL_EVENT_MANAGER_HPP

#include "core/fast_map.hpp"
#include "core/fast_vector.hpp"
#include "event/event.hpp"
#include "event/event_listener.hpp"

#include <functional>
#include <list>
#include <mutex>

namespace wmoge {

    /**
     * @class EventManager
     * @brief Event manager is responsible for engine events
     *
     *  Use this class to:
     *  - Subscribe listeners to events
     *  - Dispatch events and notify listeners
     */
    class EventManager {
    public:
        void update();
        void shutdown();

        void subscribe(const ref_ptr<EventListener>& listener);
        void unsubscribe(const ref_ptr<EventListener>& listener);
        void dispatch(const ref_ptr<Event>& event);

    private:
        using ListenersList = std::list<ref_ptr<EventListener>>;

        fast_map<EventType, ListenersList>  m_listeners;
        fast_vector<ref_ptr<EventListener>> m_pending_add;
        fast_vector<ref_ptr<EventListener>> m_pending_remove;
        fast_vector<ref_ptr<Event>>         m_events;

        mutable std::mutex m_mutex;
    };

}// namespace wmoge

#endif//GAME_ENGINE_TUTORIAL_EVENT_MANAGER_HPP
