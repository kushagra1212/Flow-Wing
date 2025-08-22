/*
 * FlowWing Compiler
 * Copyright (C) 2023-2025 Kushagra Rathore
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

#include "Colors.h"
#include <iostream>
#include <sstream>
#include <string>



 #define AOT_TEST_MODE_RELEASE_IN_LINUX                                         \
  defined(AOT_TEST_MODE) && defined(RELEASE) && defined(__linux__)


#ifdef ENABLE_LOGGING 
// Implementation function
// Implementation of the debug log function
template <typename... Args>
void DEBUG_LOG_IMPL(const std::string &type, const std::string &file, int line,
                    const std::string &func, const std::string &format,
                    Args &&...args) {
  std::stringstream ss;
  ((ss << std::forward<Args>(args)), ...);

  std::cout << BOLD << "[DEBUG]" << BLUE_TEXT
            << (type.empty() ? "" : "[" + type + "]") << GREY_TEXT << " ("
            << file << ":" << line << " in " << func << "):\n " << GREEN_TEXT
            << format << YELLOW_TEXT << ss.str() << RESET << std::endl;
}


// Macro to expand the variadic arguments correctly

#define DEBUG_LOG(format, ...)                                                 \
  DEBUG_LOG_IMPL("", __FILE__, __LINE__, __func__, format, __VA_ARGS__)

// Macro for general info logs
#define INFO_DEBUG_LOG(format, ...)                                            \
  DEBUG_LOG_IMPL("[INFO]", __FILE__, __LINE__, __func__, format, __VA_ARGS__)

// Macro for lexer logs
#define LEXER_DEBUG_LOG(format, ...)                                           \
  DEBUG_LOG_IMPL("[LEXER]", __FILE__, __LINE__, __func__, format, __VA_ARGS__)

// Macro for parser logs
#define PARSER_DEBUG_LOG(format, ...)                                          \
  DEBUG_LOG_IMPL("[PARSER]", __FILE__, __LINE__, __func__, format, __VA_ARGS__)

// Macro for binder logs
#define BINDER_DEBUG_LOG(format, ...)                                          \
  DEBUG_LOG_IMPL("[BINDER]", __FILE__, __LINE__, __func__, format, __VA_ARGS__)

// Macro for code generation logs
#define CODEGEN_DEBUG_LOG(format, ...)                                         \
  DEBUG_LOG_IMPL("[CODEGEN]", __FILE__, __LINE__, __func__, format, __VA_ARGS__)
// Macro for code generation logs
#define LINKING_DEBUG_LOG(format, ...)                                         \
  DEBUG_LOG_IMPL("[LINKING]", __FILE__, __LINE__, __func__, format, __VA_ARGS__)
#else
#define DEBUG_LOG(format, ...) // No-op in release builds
#define INFO_DEBUG_LOG(format, ...)
#define LEXER_DEBUG_LOG(format, ...)
#define PARSER_DEBUG_LOG(format, ...)
#define BINDER_DEBUG_LOG(format, ...)
#define CODEGEN_DEBUG_LOG(format, ...)
#define LINKING_DEBUG_LOG(format, ...)
#endif

