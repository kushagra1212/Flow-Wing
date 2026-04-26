/*
 * FlowWing Compiler
 * Copyright (C) 2023-2026 Kushagra Rathore
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#pragma once

#include "src/common/cli/CliColors.h"
#include <iostream>
#include <sstream>
#include <string>
// [NEW] Required for printing LLVM Values/Types

// clang-format off
#include "src/compiler/diagnostics/DiagnosticPush.hpp"
#include <llvm/Support/raw_ostream.h>
#include "src/compiler/diagnostics/DiagnosticPop.hpp"
// clang-format on

#define AOT_TEST_MODE_RELEASE_IN_LINUX                                         \
  defined(AOT_TEST_MODE) && defined(RELEASE) && defined(__linux__)

#if defined(ENABLE_LOGGING)


// ==========================================
// Container & LLVM-Aware Printing Logic
// ==========================================

// 1. Helper to check if T is a container
template <typename T, typename = void> struct is_container : std::false_type {};

template <typename T>
struct is_container<T, std::void_t<decltype(std::begin(std::declval<T>())),
                                   decltype(std::end(std::declval<T>()))>>
    : std::true_type {};

// 2. Helper to check if T is a string
template <typename T> struct is_string : std::false_type {};
template <> struct is_string<std::string> : std::true_type {};
template <> struct is_string<const char *> : std::true_type {};
template <> struct is_string<char *> : std::true_type {};

// 3. Helper to check if T can be streamed to std::ostream standardly
template <typename T, typename = void>
struct is_streamable : std::false_type {};
template <typename T>
struct is_streamable<T, std::void_t<decltype(std::declval<std::ostream &>()
                                             << std::declval<T>())>>
    : std::true_type {};

// 4. Helper to check if T has an LLVM-style print method:
// .print(llvm::raw_ostream &)
template <typename T, typename = void>
struct has_llvm_print : std::false_type {};
template <typename T>
struct has_llvm_print<T, std::void_t<decltype(std::declval<T>().print(
                             std::declval<llvm::raw_ostream &>()))>>
    : std::true_type {};

// Forward declaration
template <typename T> void print_arg(std::stringstream &ss, const T &arg);

// 5. Helper to print a single element (Handles: Values, Pointers, LLVM Objects)
template <typename T> void print_element(std::stringstream &ss, const T &val) {
  using BaseType = std::decay_t<T>;

  // CASE A: It is a pointer (and not a C-string)
  if constexpr (std::is_pointer_v<BaseType> && !is_string<BaseType>::value) {
    if (val) {
      // Dereference the pointer to check the underlying type
      using PointedType = std::remove_pointer_t<BaseType>;

      // 1. If the underlying type is streamable (e.g. int*, string*), print it
      if constexpr (is_streamable<PointedType>::value) {
        ss << *val;
      }
      // 2. If the underlying type has .print() (e.g. llvm::Value, llvm::Type),
      // use it
      else if constexpr (has_llvm_print<PointedType>::value) {
        std::string buffer;
        llvm::raw_string_ostream os(buffer);
        val->print(os); // Call LLVM print
        ss << buffer;   // Stream the result
      }
      // 3. Fallback: Print the memory address
      else {
        ss << val;
      }
    } else {
      ss << "nullptr";
    }
  }
  // CASE B: It is not a pointer (Value types)
  else {
    ss << val;
  }
}

// 6. The main print function (Handles Containers)
template <typename T> void print_arg(std::stringstream &ss, const T &arg) {
  using BaseType = std::decay_t<T>;

  // If container, iterate and print
  if constexpr (is_container<BaseType>::value && !is_string<BaseType>::value &&
                !std::is_same_v<BaseType, char>) {
    ss << "[";
    bool first = true;
    for (const auto &item : arg) {
      if (!first)
        ss << ", ";
      print_element(ss, item);
      first = false;
    }
    ss << "]";
  } else {
    // Single item
    print_element(ss, arg);
  }
}

template <typename... Args>
void DEBUG_LOG_IMPL(const std::string &type, const std::string &file, int line,
                    const std::string &func, const std::string &format,
                    Args &&...args) {

  std::stringstream ss;
  ((ss << " => ", print_arg(ss, std::forward<Args>(args))), ...);

  std::string only_file_name = " " +
                               (file.substr(file.find_last_of("/") + 1))
                                   .substr(0, file.find_last_of(".")) +
                               " ";

  std::cout << BOLD_TEXT << "[DEBUG]" << BLUE_TEXT
            << (type.empty() ? "" : " [" + type + "]") << only_file_name
            << GREEN_TEXT << " => " << format << HIGHLIGHT_TEXT << ss.str()
            << " \n"
            << GRAY_TEXT << file << ":" << line << " in " << func << "\n "
            << RESET << std::endl;
}

// Macro to expand the variadic arguments correctly

#define DEBUG_LOG(format, ...)                                                 \
  DEBUG_LOG_IMPL("", __FILE__, __LINE__, __PRETTY_FUNCTION__, format,          \
                 __VA_ARGS__)

#define CLI_PARSER_DEBUG_LOG(format, ...)                                      \
  DEBUG_LOG_IMPL("[CLI PARSER]", __FILE__, __LINE__, __PRETTY_FUNCTION__,      \
                 format, __VA_ARGS__)

#define SOURCE_LOADER_DEBUG_LOG(format, ...)                                   \
  DEBUG_LOG_IMPL("[SOURCE LOADER]", __FILE__, __LINE__, __PRETTY_FUNCTION__,   \
                 format, __VA_ARGS__)

// Macro for general info logs
#define INFO_DEBUG_LOG(format, ...)                                            \
  DEBUG_LOG_IMPL("[INFO]", __FILE__, __LINE__, __PRETTY_FUNCTION__, format,    \
                 __VA_ARGS__)

// Macro for lexer logs
#define LEXER_DEBUG_LOG(format, ...)                                           \
  DEBUG_LOG_IMPL("[LEXER]", __FILE__, __LINE__, __PRETTY_FUNCTION__, format,   \
                 __VA_ARGS__)

// Macro for parser logs
#define PARSER_DEBUG_LOG(format, ...)                                          \
  DEBUG_LOG_IMPL("[PARSER]", __FILE__, __LINE__, __PRETTY_FUNCTION__, format,  \
                 __VA_ARGS__)

// Macro for binder logs
#define BINDER_DEBUG_LOG(format, ...)                                          \
  DEBUG_LOG_IMPL("[BINDER]", __FILE__, __LINE__, __PRETTY_FUNCTION__, format,  \
                 __VA_ARGS__)

// Macro for code generation logs
#define CODEGEN_DEBUG_LOG(format, ...)                                         \
  DEBUG_LOG_IMPL("[CODEGEN]", __FILE__, __LINE__, __PRETTY_FUNCTION__, format, \
                 __VA_ARGS__)
// Macro for code generation logs
#define LINKING_DEBUG_LOG(format, ...)                                         \
  DEBUG_LOG_IMPL("[LINKING]", __FILE__, __LINE__, __PRETTY_FUNCTION__, format, \
                 __VA_ARGS__)
#else
#define DEBUG_LOG(format, ...) // No-op in release builds
#define CLI_PARSER_DEBUG_LOG(format, ...)
#define SOURCE_LOADER_DEBUG_LOG(format, ...)
#define INFO_DEBUG_LOG(format, ...)
#define LEXER_DEBUG_LOG(format, ...)
#define PARSER_DEBUG_LOG(format, ...)
#define BINDER_DEBUG_LOG(format, ...)
#define CODEGEN_DEBUG_LOG(format, ...)
#define LINKING_DEBUG_LOG(format, ...)
#endif
