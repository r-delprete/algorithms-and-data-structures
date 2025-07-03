#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <string>

enum class LogLevel { INFO, WARNING, ERROR, DEBUG };

inline std::string logLevelToString(LogLevel level) {
  switch (level) {
    case LogLevel::INFO:
      return "INFO";
    case LogLevel::WARNING:
      return "WARNING";
    case LogLevel::ERROR:
      return "ERROR";
    case LogLevel::DEBUG:
      return "DEBUG";
    default:
      return "UNKNOWN";
  }
}

inline void log(const std::string& message, LogLevel level = LogLevel::INFO) {
  auto now = std::chrono::system_clock::now();
  std::time_t now_time = std::chrono::system_clock::to_time_t(now);

  std::cout << "[" << std::put_time(std::localtime(&now_time), "%Y-%m-%d %H:%M:%S") << "] "
            << "[" << logLevelToString(level) << "] " << message << std::endl;
}

#endif  // LOGGER_HPP
