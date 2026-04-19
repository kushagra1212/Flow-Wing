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

/*
 * FlowWing Compiler - IO FFI
 * Cross-Platform: Compiles on Windows, macOS, and Linux
 */

#include <cstring>
#include <gc/gc.h>
#include <iostream>
#include <string>

extern "C" {

// Stores the last io error code
// 0 = OK, 1 = EOF/FAILED
static thread_local int32_t last_io_error = 0;

int32_t io_last_error() { return last_io_error; }

// Helper: Allocate a GC-tracked string to return to FlowWing.
// Declared as static to prevent linker conflicts with other FFI modules (like
// file_ffi)
static const char *alloc_gc_string_io(const std::string &str) {
  char *cstr = (char *)GC_MALLOC_ATOMIC(str.length() + 1);
  if (cstr) {
    std::memcpy(cstr, str.c_str(), str.length());
    cstr[str.length()] = '\0';
  }
  return cstr;
}

// Helper to map semantic color names to actual C++ ANSI literals
static const char *get_ansi_code(const char *color) {
  if (!color)
    return "";
  if (std::strcmp(color, "dim") == 0)
    return "\x1b[2m";
  if (std::strcmp(color, "cyan") == 0)
    return "\x1b[36m";
  if (std::strcmp(color, "green") == 0)
    return "\x1b[32m";
  if (std::strcmp(color, "yellow") == 0)
    return "\x1b[33m";
  if (std::strcmp(color, "red") == 0)
    return "\x1b[31m";

  // Fallback: If Flow-Wing's lexer gets updated later to support \x1b natively,
  // this ensures raw ANSI codes still pass through safely.
  if (color[0] == '\x1b')
    return color;

  return "";
}

// --- Standard Output ---

void io_print_log(const char *text, const char *color) {
  const char *ansi = get_ansi_code(color);
  if (std::strlen(ansi) > 0) {
    std::cout << ansi << text << "\x1b[0m"; // Reset color after printing
  } else {
    std::cout << text;
  }
}

void io_print_log_ln(const char *text, const char *color) {
  const char *ansi = get_ansi_code(color);
  if (std::strlen(ansi) > 0) {
    std::cout << ansi << text << "\x1b[0m\n"; // Reset color after printing
  } else {
    std::cout << text << "\n";
  }
}

void io_print_error_log(const char *text, const char *color) {
  const char *ansi = get_ansi_code(color);
  if (std::strlen(ansi) > 0) {
    std::cerr << ansi << text << "\x1b[0m"; // Reset color after printing
  } else {
    std::cerr << text;
  }
}

void io_print_error_log_ln(const char *text, const char *color) {
  const char *ansi = get_ansi_code(color);
  if (std::strlen(ansi) > 0) {
    std::cerr << ansi << text << "\x1b[0m\n"; // Reset color after printing
  } else {
    std::cerr << text << "\n";
  }
}

void io_flush() { std::cout.flush(); }

// --- Standard Input ---

const char *io_read_line() {
  std::string line;
  std::cin.clear();
  // std::getline reads up to the newline character
  if (std::getline(std::cin, line)) {
    last_io_error = 0;
    // Handle cross-platform CRLF by stripping trailing '\r' (e.g., when reading
    // piped files on Windows)
    if (!line.empty() && line.back() == '\r') {
      line.pop_back();
    }
    return alloc_gc_string_io(line);
  }

  last_io_error = 1; // EOF or stream failure
  return alloc_gc_string_io("");
}
}