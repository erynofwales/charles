/* logModule.hh
 * vim: set tw=80:
 * Eryn Wells <eryn@erynwells.me>
 */
/**
 * Defines some helper macros for logging that simplify the ones defined in
 * log.hh.
 */

#ifndef __LOGMODULE_HH__
#define __LOGMODULE_HH__

#if !defined(LOG_NAME)
#warning "Log stream name undefined. Using ROOT log stream."
#define LOG_NAME "ROOT"
#endif

#define LOG_LEVEL(level) LOG_NAME_LEVEL(LOG_NAME, level)
#define LOG_ERROR LOG_ERROR_NAME(LOG_NAME)
#define LOG_WARN LOG_WARN_NAME(LOG_NAME)
#define LOG_INFO LOG_INFO_NAME(LOG_NAME)
#define LOG_DEBUG LOG_DEBUG_NAME(LOG_NAME)
#define LOG_TRACE LOG_TRACE_NAME(LOG_NAME)

#define TRACE_FUNC TRACE_FUNC_NAME(LOG_NAME)

#endif /* __LOGMODULE_HH__ */
