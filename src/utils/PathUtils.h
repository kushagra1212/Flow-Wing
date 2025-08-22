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

#include "Macros.h"
#include <filesystem> // C++17 standard for path manipulation
#include <string>

#include <cstdlib> // For getEnv

// --- Platform-specific headers ---
#if defined(_WIN32)
#include <windows.h>
#elif defined(__APPLE__)
#include <limits.h>
#include <mach-o/dyld.h>
#elif defined(__linux__)
#include <limits.h>
#include <unistd.h>
#endif

namespace FlowWing {

namespace PathUtils {

// Returns the full path to the currently running executable.
std::filesystem::path getExecutablePath();

// Gets the path to the language modules (.fg files).
std::filesystem::path getModulesPath();

// Gets the path to the pre-built libraries (.so, .bc, etc).
std::filesystem::path getLibrariesPath();

// Helper to get the full path to the crucial built-in bitcode file.
std::filesystem::path getBuiltInBCPath();

// Gets the path to the AOT linker.(Clang)
std::string getAOTLinkerPath();

} // namespace PathUtils
} // namespace FlowWing