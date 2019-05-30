///
/// The log manager
/// 

#ifndef __LOG_MANAGER_H__
#define __LOG_MANAGER_H__

// System includes.
#include <stdio.h>
#include <map>

// Engine includes.
#include "Manager.h"
#include "utility.h"

// Two-letter acronym for easier access to manager.
#define LM df::LogManager::getInstance()

namespace df {

/// Default Dragonfly cofiguration file.
/// Override with DRAGONFLY_LOG environment variable.
const std::string LOGFILE_DEFAULT = "dragonfly.log";

class LogManager : public Manager {

 private:
  LogManager();                     ///< Private since a singleton.
  LogManager(LogManager const&);    ///< Don't allow copy.
  void operator=(LogManager const&);///< Don't allow assignment.
  bool m_do_flush;                  ///< True if flush to disk after write.
  int m_log_level;                  ///< Logging level.
  bool m_log_time_string;	    ///< True if prepend time.
  bool m_log_step_count;	    ///< True if prepend step count.
  FILE *m_p_f;                      ///< Pointer to main logfile.
  std::map <std::string, FILE *> m_file_list; ///< List of custom logfiles.

 public:
  /// If logfile is open, close it.
  ~LogManager();

  /// Get the one and only instance of the LogManager.
  static LogManager &getInstance();

  /// Start up LogManager (open main logfile, usually "dragonfly.log").
  /// Return 0 if ok, else -1.
  int startUp();

  /// Shut down LogManager (close all logfiles).
  void shutDown();

  /// Write to logfile.
  /// Supports printf() formatting of strings.
  /// Return number of bytes written (excluding prepends), -1 if error.
  int writeLog(const char *fmt, ...) const;

  /// Write to logfile.
  /// Only write if indicated log level >= LogManager log level.
  /// Supports printf() formatting of strings.
  /// Return number of bytes written (excluding prepends), -1 if error.
  int writeLog(int log_level, const char *fmt, ...) const;

  /// Write to custom logfile, identified by filename.
  /// Supports printf() formatting of strings.
  /// Return number of bytes written (excluding prepends), -1 if error.
  int writeMyLog(std::string filename, const char *fmt, ...);
  
  /// Write to custom logfile, identified by filename.
  /// Only write if indicated log level >= LogManager log level.
  /// Supports printf() formatting of strings.
  /// Return number of bytes written (excluding prepends), -1 if error.
  int writeMyLog(std::string filename, int log_level, const char *fmt, ...);

  /// Set logging level.
  void setLogLevel(int new_log_level);

  /// Get logging level.
  int getLogLevel() const;
  
  /// Set flush of logfile after each write.
  void setFlush(bool do_flush=true);
  
  /// Set prepend time string to log messages.
  void setLogTimeString(bool log_time_string=true);
  
  /// Set prepend step count to log messages.
  void setLogStepCount(bool log_step_count=true);
};

} // end of namespace df
#endif // __LOG_MANAGER_H__
