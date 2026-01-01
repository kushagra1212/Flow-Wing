#pragma once

#include "src/utils/FlowWingConfig.h"
#include <filesystem>
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

namespace flow_wing {
namespace io {
class PathUtils {
public:
  // Returns the full path to the currently running executable.
  static std::filesystem::path getExecutablePath() {
#if defined(_WIN32)
    wchar_t path[MAX_PATH] = {0};
    GetModuleFileNameW(NULL, path, MAX_PATH);
    return std::filesystem::path(path);
#elif defined(__linux__)
    char result[PATH_MAX];
    ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
    size_t string_size = static_cast<size_t>((count > 0) ? count : 0);

    return std::filesystem::path(std::string(result, string_size));
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

  // Gets the path to the fg modules (.fg files).
  static std::filesystem::path getModulesPath() {
    auto exePath = getExecutablePath();
#if defined(__APPLE__)
    if (exePath.string().find(".app/Contents/MacOS") != std::string::npos) {
      return exePath.parent_path().parent_path() / "Resources/modules";
    }
#endif
    // For standard installs (and SDK), it's relative to the 'bin' dir.
    return exePath.parent_path().parent_path() / "lib/modules";
  }

  // Gets the path to the pre-built libraries (.so, .bc, etc).
  static std::filesystem::path getLibrariesPath() {
    auto exePath = getExecutablePath();

    if (std::string(TEST_SDK_PATH) != "") {
      return std::filesystem::path(TEST_SDK_PATH) / FLOWWING_PLATFORM_LIB_DIR;
    }

#if defined(__APPLE__)
    if (exePath.string().find(".app/Contents/MacOS") != std::string::npos) {
      return exePath.parent_path().parent_path() / "Resources";
    }
#endif
    // In our SDK, this will resolve to 'build/sdk/bin/../lib/Darwin-arm64'
    return exePath.parent_path().parent_path() / FLOWWING_PLATFORM_LIB_DIR;
  }

  // Gets the path to the AOT linker.(Clang)
  static std::string getAOTLinkerPath() { return AOT_LINKER_PATH; }
};

} // namespace io
} // namespace flow_wing