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



// Platform-specific includes and functions for enabling colors on Windows
#if defined(_WIN32)
#include <windows.h>
#endif

// A helper function to enable ANSI virtual terminal processing on Windows.
// Returns true on success, false on failure.
// On non-Windows platforms, this function does nothing and returns true.
bool enableVirtualTerminalProcessing() {
#if defined(_WIN32)
  // Get the handle to the standard output stream (the console)
  HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
  if (hOut == INVALID_HANDLE_VALUE) {
    return false; // Failed to get handle
  }

  // Get the current console mode
  DWORD dwMode = 0;
  if (!GetConsoleMode(hOut, &dwMode)) {
    return false; // Failed to get console mode
  }

  // Add the ENABLE_VIRTUAL_TERMINAL_PROCESSING flag to the current mode.
  // This is the magic flag that enables ANSI escape code support.
  dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;

  // Set the new console mode.
  if (!SetConsoleMode(hOut, dwMode)) {
    return false; // Failed to set console mode
  }
#endif
  return true; // Success (or not on Windows, so we don't need to do anything)
}