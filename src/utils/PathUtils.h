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