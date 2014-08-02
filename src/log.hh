/* log.hh
 * vim: set tw=80:
 * Eryn Wells <eryn@erynwells.me>
 */

#ifndef __LOG_HH__
#define __LOG_HH__

#include <cassert>
#include <cstddef>

#include <chrono>
#include <iomanip>
#include <map>
#include <fstream>
#include <string>


namespace charles {
namespace log {

/** Useful predefined levels. */
namespace level {
    extern const unsigned int Error;
    extern const unsigned int Warning;
    extern const unsigned int Info;
    extern const unsigned int Debug;
    extern const unsigned int Trace;
};


struct Log
{
    static void Init(const std::string& filename,
                     unsigned int level = level::Info);
    static void Close();

    Log(const std::string& name = "root", unsigned int level = level::Info);
    ~Log();

    template<typename T> Log& operator<<(const T& item);

private:
    struct Logger
    {
        Logger(unsigned int level = level::Info);

        unsigned int level;
    };

    typedef std::map<std::string, Logger> LoggerMap;

    static unsigned int sLevel;
    static std::ostream* sOutput;
    static LoggerMap sLoggers;

    static Logger& GetLogger(const std::string& name);

    const std::string& mName;
    unsigned int mLevel;
    Logger& mOutput;
};


struct Tracer
{
    Tracer(const std::string& name,
           const std::string& function);
    ~Tracer();

private:
    const std::string& mName;
    const std::string& mFunction;
};


template<typename T>
Log&
Log::operator<<(const T& item)
{
    if (mLevel <= mOutput.level) {
        assert(sOutput != nullptr);
        *sOutput << item;
    }
    return *this;
}


} /* namespace log */
} /* namespace charles */


#define LOG_NAME_LEVEL(name, level) charles::log::Log((name), (level))
#define LOG_ERROR_NAME(name) LOG_NAME_LEVEL(name, charles::log::level::Error)
#define LOG_WARN_NAME(name) LOG_NAME_LEVEL(name, charles::log::level::Warning)
#define LOG_INFO_NAME(name) LOG_NAME_LEVEL(name, charles::log::level::Info)
#define LOG_DEBUG_NAME(name) LOG_NAME_LEVEL(name, charles::log::level::Debug)
#define LOG_TRACE_NAME(name) LOG_NAME_LEVEL(name, charles::log::level::Trace)

#define TRACE_FUNC_NAME(name) \
    auto __tracer = charles::log::Tracer((name), __PRETTY_FUNCTION__)

#endif /* __LOG_HH__ */
