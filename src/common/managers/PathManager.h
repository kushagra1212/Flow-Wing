#pragma once

#include <filesystem>

class PathManager {

public:
  auto static inline getClangPath() -> std::filesystem::path {
    std::filesystem::path CLANG_PATH = "";

#if defined(__linux__)
    CLANG_PATH = "/usr/bin/clang-17";
#elif defined(__APPLE__)
    CLANG_PATH = "/usr/bin/clang";
#endif

    return CLANG_PATH;
  }

  auto static inline getLibPath() -> std::filesystem::path {
    std::filesystem::path LIB_PATH = "";

#if defined(__linux__)
    LIB_PATH = "/usr/local/lib/FlowWing";
#elif defined(__APPLE__)
    LIB_PATH = "/Users/apple/code/per/Flow-Wing/lib/mac-silicon/lib";
#endif

    return LIB_PATH;
  }
};