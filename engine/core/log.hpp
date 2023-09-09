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

#ifndef GAME_ENGINE_TUTORIAL_LOG_HPP
#define GAME_ENGINE_TUTORIAL_LOG_HPP

#include <cstddef>
#include <fstream>
#include <mutex>
#include <sstream>
#include <string>
#include <vector>

namespace wmoge {

    /**
     * @class LogLevel
     * @brief Level of a logged message
     */
    enum class LogLevel {
        Info    = 0,
        Warning = 1,
        Error   = 2,
        Never   = 4
    };

    /**
     * @class LogEntry
     * @brief Structure holding info about a single logged message
     */
    struct LogEntry {
        std::string message;
        std::string file;
        std::string function;
        std::size_t line;
        LogLevel    level;
    };

    /**
     * @class LogListener
     * @brief Listener interface which can be attached to a log
     */
    class LogListener {
    public:
        virtual ~LogListener()                         = default;
        virtual void on_message(const LogEntry& entry) = 0;
    };

    /**
     * @class Log
     * @brief Engine global logger
     */
    class Log {
    public:
        void listen(const std::shared_ptr<LogListener>& listener);
        void remove(const std::shared_ptr<LogListener>& listener);
        void log(LogLevel level, std::string message, std::string file, std::string function, std::size_t line);

        static Log* instance();

    private:
        std::vector<std::shared_ptr<LogListener>> m_listeners;
        std::recursive_mutex                      m_mutex;
    };

    /**
     * @class LogListenerStdout
     * @brief Log listener which dumps messages to out console
     */
    class LogListenerStdout final : public LogListener {
    public:
        LogListenerStdout(std::string name, LogLevel level);
        ~LogListenerStdout() override = default;
        void on_message(const LogEntry& entry) override;

    private:
        std::string m_name;
        LogLevel    m_level;
    };

    /**
     * @class LogListenerStream
     * @brief Log listener which dumps messages to a file stream
     */
    class LogListenerStream final : public LogListener {
    public:
        LogListenerStream(std::string name, LogLevel level);
        ~LogListenerStream() override = default;
        void on_message(const LogEntry& entry) override;

    private:
        std::fstream m_stream;
        std::string  m_name;
        LogLevel     m_level;
    };

    /**
     * @class LogListenerConsole
     * @brief Console log listener
     */
    class LogListenerConsole : public LogListener {
    public:
        LogListenerConsole(class Console* console, LogLevel level);
        ~LogListenerConsole() override = default;
        void on_message(const LogEntry& entry) override;

    private:
        class Console* m_console;
        LogLevel       m_level;
    };

}// namespace wmoge

#define WG_LOG_MESSAGE(level, message)                                                                                \
    do {                                                                                                              \
        std::stringstream __ss;                                                                                       \
        __ss << message;                                                                                              \
        ::wmoge::Log::instance()->log(level, __ss.str(), __FILE__, __FUNCTION__, static_cast<std::size_t>(__LINE__)); \
    } while (false)

#define WG_LOG_INFO(message)    WG_LOG_MESSAGE(::wmoge::LogLevel::Info, message)
#define WG_LOG_WARNING(message) WG_LOG_MESSAGE(::wmoge::LogLevel::Warning, message)
#define WG_LOG_ERROR(message)   WG_LOG_MESSAGE(::wmoge::LogLevel::Error, message)

#endif//GAME_ENGINE_TUTORIAL_LOG_HPP