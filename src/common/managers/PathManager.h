#pragma once

#include <filesystem>

class PathManager {
public:
  auto static inline getClangPath() -> std::filesystem::path {
    std::filesystem::path CLANG_PATH = "";

#if defined(__linux__)
    CLANG_PATH = "/usr/bin/clang-17";
#elif defined(__APPLE__)
    CLANG_PATH = "/usr/bin/clang++";
#endif

    return CLANG_PATH;
  }

  auto static inline getLibPath() -> std::filesystem::path {
    std::filesystem::path LIB_PATH = "";

#if defined(AOT_TEST_MODE_RELEASE)
    LIB_PATH = "../../../lib/linux-x86_64/lib";
    return LIB_PATH;
#endif

#if defined(DEBUG) && defined(__linux__)
#if defined(__x86_64__)
    LIB_PATH = "../../../lib/linux-x86_64/lib";
#else
    LIB_PATH = "../../../lib/linux/lib";
#endif

#elif defined(DEBUG) && defined(__APPLE__)
    LIB_PATH = "/Users/apple/code/per/Flow-Wing/lib/mac-silicon/lib";
#elif defined(RELEASE) && defined(__linux__) && defined(AOT_TEST_MOD)
    LIB_PATH = "../../../lib/linux/lib";
#elif defined(RELEASE) && defined(__linux__)
    LIB_PATH = "../../../lib/linux/lib";
#elif defined(RELEASE) && defined(__APPLE__)
    LIB_PATH = "/opt/homebrew/opt/flowwing/lib/FlowWing/lib";
#endif

    return LIB_PATH;
  }

  auto static inline getModulesPath() -> std::filesystem::path {
    return getLibPath() / "modules";
  }
};