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

#include "profiler.hpp"

#include "core/engine.hpp"
#include "core/log.hpp"
#include "platform/file_system.hpp"

namespace wmoge {

    ProfilerMark::ProfilerMark(StringId    in_function,
                               StringId    in_function_sig,
                               StringId    in_file,
                               StringId    in_category,
                               std::size_t in_line)
        : function(std::move(in_function)),
          function_sig(std::move(in_function_sig)),
          file(std::move(in_file)),
          category(std::move(in_category)),
          line(in_line),
          profiler(Engine::instance()->profiler()) {

        std::string to_replace = "__cdecl ";

        pretty_name = function_sig.str();
        auto pos    = pretty_name.find(to_replace);
        if (pos != std::string::npos) {
            pretty_name.replace(pos, to_replace.length(), "");
        }
    }

    ProfilerTimeEvent::ProfilerTimeEvent(ProfilerMark* mark, std::string desc)
        : m_mark(mark), m_desc(std::move(desc)) {
        m_timer.start();
    }
    ProfilerTimeEvent::~ProfilerTimeEvent() {
        m_timer.stop();

        if (m_mark->profiler->is_collecting()) {
            ProfilerEntry entry;
            entry.tid   = std::this_thread::get_id();
            entry.start = m_timer.get_start();
            entry.stop  = m_timer.get_end();
            entry.mark  = m_mark;
            entry.desc  = std::move(m_desc);
            m_mark->profiler->add_entry(std::move(entry));
        }
    }

    void ProfilerCapture::set_name(StringId name) {
        m_name = std::move(name);
    }
    void ProfilerCapture::set_file(std::string file) {
        m_file = std::move(file);
    }
    void ProfilerCapture::add_entry(ProfilerEntry&& entry) {
        m_entries.push_back(std::move(entry));
    }
    void ProfilerCapture::save_to_json() {
        using namespace std::chrono;

        Engine*     engine      = Engine::instance();
        FileSystem* file_system = engine->file_system();
        Profiler*   profiler    = engine->profiler();

        std::fstream file_stream;

        if (!file_system->open_file(m_file, file_stream, std::ios_base::out | std::ios::binary)) {
            WG_LOG_ERROR("failed to open capture file " << m_file);
            return;
        }

        auto start     = engine->get_start();
        auto tid_names = profiler->get_tid_names();

        file_stream << "{\"otherData\":{}, \"traceEvents\":[";

        bool first = true;
        for (const auto& entry : m_entries) {
            auto entry_start = duration_cast<microseconds>(entry.start - start).count();
            auto entry_dur   = duration_cast<microseconds>(entry.stop - entry.start).count();

            if (!first) file_stream << ",";

            file_stream << "{";
            file_stream << "\"pid\":0,";
            file_stream << "\"tid\":\"" << tid_names[entry.tid] << "\",";
            file_stream << "\"cat\":\"" << entry.mark->category.str() << "\",";
            file_stream << "\"name\":\"" << entry.mark->pretty_name << "\",";
            file_stream << "\"ph\":\"X\",";
            file_stream << "\"ts\":" << entry_start << ",";
            file_stream << "\"dur\":" << entry_dur << ",";
            file_stream << "\"args\":";
            file_stream << "{\"description\":\"" << entry.desc << "\"}";
            file_stream << "}";

            first = false;
        }

        file_stream << "]}";
        file_stream.close();
    }

    Profiler::Profiler() {
        add_tid(std::this_thread::get_id(), SID("main"));
    }
    void Profiler::set_enabled(bool value) {
        m_is_enabled.store(value);
        WG_LOG_INFO("time profiler active is " << value);
    }
    void Profiler::start_capture(std::shared_ptr<ProfilerCapture> capture) {
        if (!is_enabled()) return;
        std::lock_guard guard(m_mutex);
        m_capture = std::move(capture);
        m_is_collecting.store(true);
    }
    void Profiler::end_capture() {
        std::lock_guard guard(m_mutex);
        m_is_collecting.store(false);
        m_capture.reset();
    }
    void Profiler::add_entry(ProfilerEntry&& entry) {
        std::lock_guard guard(m_mutex);
        if (m_capture) m_capture->add_entry(std::move(entry));
    }
    void Profiler::add_tid(std::thread::id id, wmoge::StringId name) {
        std::lock_guard guard(m_mutex);
        m_tid_names[id] = std::move(name);
    }
    bool Profiler::is_enabled() {
        return m_is_enabled;
    }
    bool Profiler::is_collecting() {
        return m_is_collecting.load();
    }
    std::unordered_map<std::thread::id, StringId> Profiler::get_tid_names() const {
        return m_tid_names;
    }

}// namespace wmoge
