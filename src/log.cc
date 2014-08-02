/* log.cc
 * vim: set tw=80:
 * Eryn Wells <eryn@erynwells.me>
 */

#include "log.hh"


namespace charles {
namespace log {

/** Useful predefined levels. */
namespace level {
    const unsigned int Error = 10;
    const unsigned int Warning = 20;
    const unsigned int Info = 30;
    const unsigned int Debug = 40;
    const unsigned int Trace = 50;
};


unsigned int Log::sLevel = 0;
std::ostream* Log::sOutput = nullptr;
Log::LoggerMap Log::sLoggers;


/* static */ void
Log::Init(const std::string& filename,
          unsigned int level)
{
    assert(sOutput == nullptr);
    sOutput = new std::ofstream(filename);
    sLevel = level;

    Log("ROOT", 1) << "Opening log file " << filename;
    Log("ROOT", 1) << "Log level set to " << sLevel;
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

    /* Write a log message leader: "<time with millis> - <name>:<level> - ". */
    auto now = system_clock::now();
    auto nowMillis =
        duration_cast<milliseconds>(now.time_since_epoch() % seconds(1));
    auto cNow = system_clock::to_time_t(now);
    *this << std::put_time(std::localtime(&cNow), "%F %T")
          << "." << std::left << std::setw(3) << nowMillis.count()
          << " - " << mName
          << ":" << std::left << std::setw(2) << mLevel << " - ";
}


Log::~Log()
{
    /* Add a newline at the end of this log message. */
    *this << "\n";
}


/* static */ Log::Logger&
Log::GetLogger(const std::string& name)
{
    /*
     * TODO: For now, output is always the same: sOutput. In the future, figure
     * out a way to set different outputs for different streams.
     */
    auto pair = sLoggers.emplace(name, sLevel);
    return pair.first->second;
}

#pragma mark Log::Logger

Log::Logger::Logger(unsigned int l)
    : level(l)
{ }


#pragma mark Tracer

Tracer::Tracer(const std::string& name,
               const std::string& function)
    : mName(name),
      mFunction(function)
{
    Log(mName, level::Trace) << "--> " << mFunction;
}


Tracer::~Tracer()
{
    Log(mName, level::Trace) << "<-- " << mFunction;
}

} /* namespace log */
} /* namespace charles */
