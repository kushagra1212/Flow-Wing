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


#include "PathUtils.h"

namespace FlowWing {

namespace PathUtils {
// Returns the full path to the currently running executable.
std::filesystem::path getExecutablePath() {
#if defined(_WIN32)
  wchar_t path[MAX_PATH] = {0};
  GetModuleFileNameW(NULL, path, MAX_PATH);
  return std::filesystem::path(path);
#elif defined(__linux__)
  char result[PATH_MAX];
  ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
  return std::filesystem::path(std::string(result, (count > 0) ? count : 0));
#elif defined(__APPLE__)
  char path[PATH_MAX];
  uint32_t size = sizeof(path);
  if (_NSGetExecutablePath(path, &size) == 0) {
    char *real_path = realpath(path, NULL);
    std::filesystem::path result(real_path);
    free(real_path);
    return result;
  }
  // Handle case where buffer was too small
  std::string resized_path(size, '\0');
  _NSGetExecutablePath(&resized_path[0], &size);
  char *real_path = realpath(resized_path.c_str(), NULL);
  std::filesystem::path result(real_path);
  free(real_path);
  return result;
#else
  // Fallback for other/unsupported OS
  return std::filesystem::path();
#endif
}
// Gets the path to the language modules (.fg files).
std::filesystem::path getModulesPath() {

#if defined(DEV_MODE_PATH)
  // Developer Mode: Use the dev path macro.
  return std::filesystem::path(DEV_MODE_PATH) / DEV_MODULES_PATH;

#endif

  // Installed Mode: Use the install path macro.
#if defined(__APPLE__)
  if (getExecutablePath().string().find(".app/Contents/MacOS") !=
      std::string::npos) {
    // For .app bundles, paths are relative to Contents directory
    return getExecutablePath().parent_path().parent_path() /
           INSTALL_MODULES_PATH;
  }
#endif
  // For standard FHS installs, paths are relative to the installation root.
  return getExecutablePath().parent_path().parent_path() / INSTALL_MODULES_PATH;
}

// Gets the path to the pre-built libraries (.so, .bc, etc).
std::filesystem::path getLibrariesPath() {

  DEBUG_LOG("DEV_MODE_PATH", DEV_MODE_PATH);
  DEBUG_LOG("DEV_LIBS_PATH", DEV_LIBS_PATH);

#if defined(DEV_MODE_PATH)
  // Developer Mode: Use the dev path macro.
  return std::filesystem::path(DEV_MODE_PATH) / DEV_LIBS_PATH;

#endif

// Installed Mode: Use the install path macro.
#if defined(__APPLE__)
  if (getExecutablePath().string().find(".app/Contents/MacOS") !=
      std::string::npos) {
    return getExecutablePath().parent_path().parent_path() / INSTALL_LIBS_PATH;
  }
#endif
  return getExecutablePath().parent_path().parent_path() / INSTALL_LIBS_PATH;
}

// Helper to get the full path to the crucial built-in bitcode file.
std::filesystem::path getBuiltInBCPath() {
  return getLibrariesPath() / "libbuilt_in_module.bc";
}

std::string getAOTLinkerPath() { return AOT_LINKER_PATH; }

} // namespace PathUtils
} // namespace FlowWing