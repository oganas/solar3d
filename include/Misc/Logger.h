#pragma once

#include <iostream>
#include <string>

/*
 * Logger class.
 * Used for logging messages to the terminal.
 *
 * !!! This was generated using AI. !!!
 */
class Logger {
public:
  static inline bool isEnabled = true;

  static void log_impl() {
    std::cout << std::endl;
  }

  template <typename T, typename... Args>
  static void log_impl(const T &first, const Args &...rest) {
    std::cout << first;
    log_impl(rest...);
  }

  template <typename T, typename... Args>
  static void log(const T &first, const Args &...rest) {
    if (isEnabled) {
      log_impl(first, rest...);
    }
  }
};
