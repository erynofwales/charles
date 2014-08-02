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
    unsigned int Error = 10;
    unsigned int Warning = 20;
    unsigned int Info = 30;
    unsigned int Debug = 40;
    unsigned int Trace = 50;
};


struct Log
{
    static void Init(const std::string& filename);
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

    static std::ostream* sOutput;
    static LoggerMap sLoggers;

    static Logger& GetLogger(const std::string& name);

    const std::string& mName;
    unsigned int mLevel;
    Logger& mOutput;
};


std::ostream* Log::sOutput = nullptr;
Log::LoggerMap Log::sLoggers;


/* static */ void
Log::Init(const std::string& filename)
{
    assert(sOutput == nullptr);
    sOutput = new std::ofstream(filename);

    Log("root", level::Error) << "Opening log file: " << filename;
}


/* static */ void
Log::Close()
{
    assert(sOutput != nullptr);
    delete sOutput;
    sOutput = nullptr;
}


/**
 * Construct a Log object.
 *
 * @param [in] name     The name of the log stream. If this name hasn't been
 *                      seen before, a new one will be created for you.
 * @param [in] level    The level. If this is higher than the level of the log
 *                      stream, nothing will be output.
 */
Log::Log(const std::string& name,
         unsigned int level)
    : mName(name),
      mLevel(level),
      mOutput(Log::GetLogger(name))
{
    using namespace std::chrono;

    /* Write a log message leader: "<time> - <name>:<level>: ". */
    auto now = system_clock::to_time_t(system_clock::now());
    *this << std::put_time(std::localtime(&now), "%F %T")
          << " - " << mName << ":" << mLevel << " - ";
}


Log::~Log()
{
    /* Add a newline at the end of this log message. */
    *this << "\n";
}


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


/* static */ Log::Logger&
Log::GetLogger(const std::string& name)
{
    /*
     * TODO: For now, output is always the same: sOutput. In the future, figure
     * out a way to set different outputs for different streams.
     */
    auto pair = sLoggers.emplace(name, level::Info);
    return pair.first->second;
}


Log::Logger::Logger(unsigned int l)
    : level(l)
{ }

} /* namespace log */
} /* namespace charles */

#endif /* __LOG_HH__ */
