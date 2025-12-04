#pragma once

#include <iostream>
#include <string>

/*
 * Logger class.
 * Used for logging messages to the terminal.
 */
class Logger {
public:
  static inline bool isEnabled = true;

  // Base case function (non-recursive)
  static void log_impl() {
    // When all arguments have been processed, print a newline
    std::cout << std::endl;
  }

  // Recursive template function (packs the arguments)
  template <typename T, typename... Args>
  static void log_impl(const T &first, const Args &...rest) {
    std::cout << first;
    // Recursive call: process the rest of the arguments
    log_impl(rest...);
  }

  // Public interface function
  template <typename T, typename... Args>
  static void log(const T &first, const Args &...rest) {
    if (isEnabled) {
      log_impl(first, rest...);
    }
  }
};
