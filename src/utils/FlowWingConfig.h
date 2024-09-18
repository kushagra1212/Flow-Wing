#pragma once

#define PLATFORM_LINUX_X86_64 1
#define PLATFORM_LINUX_OTHER 2
#define PLATFORM_MACOS_ARM64 3
#define PLATFORM_MACOS_X86_64 4

// Platform and architecture checks
#if defined(__linux__)
#if defined(__x86_64__)
#define PLATFORM_ARCH PLATFORM_LINUX_X86_64
#else
#define PLATFORM_ARCH PLATFORM_LINUX_OTHER
#endif
#elif defined(__APPLE__)
#if defined(__arm64__)
#define PLATFORM_ARCH PLATFORM_MACOS_ARM64
#elif defined(__x86_64__)
#define PLATFORM_ARCH PLATFORM_MACOS_X86_64
#endif
#endif

// Define the library path based on the configuration
#if PLATFORM_ARCH == PLATFORM_LINUX_X86_64 && defined(DEBUG) &&                \
    defined(AOT_MODE)
#define FLOWWING_LIB_PATH "../../../lib/linux-x86_64/lib"
#elif PLATFORM_ARCH == PLATFORM_LINUX_X86_64 && defined(RELEASE) &&            \
    defined(AOT_TEST_MODE)
#define FLOWWING_LIB_PATH "../../../lib/linux-x86_64/lib"
#elif PLATFORM_ARCH == PLATFORM_LINUX_OTHER && defined(DEBUG) &&               \
    defined(AOT_MODE)
#define FLOWWING_LIB_PATH "../../../lib/linux/lib"
#elif PLATFORM_ARCH == PLATFORM_LINUX_OTHER && defined(RELEASE) &&             \
    defined(AOT_TEST_MODE)
#define FLOWWING_LIB_PATH "../../../lib/linux/lib"
#elif PLATFORM_ARCH == PLATFORM_MACOS_ARM64 && defined(DEBUG) &&               \
    defined(AOT_MODE)
#define FLOWWING_LIB_PATH "../../../lib/mac-silicon/lib"
#elif PLATFORM_ARCH == PLATFORM_MACOS_ARM64 && defined(RELEASE) &&             \
    defined(AOT_TEST_MODE)
#define FLOWWING_LIB_PATH "../../../lib/mac-silicon/lib"
#elif PLATFORM_ARCH == PLATFORM_MACOS_ARM64 && defined(RELEASE) &&             \
    defined(AOT_MODE)
#define FLOWWING_LIB_PATH "/opt/homebrew/opt/flowwing/lib/FlowWing/lib"
#elif PLATFORM_ARCH == PLATFORM_MACOS_X86_64 && defined(RELEASE) &&            \
    defined(AOT_MODE)
#define FLOWWING_LIB_PATH "/opt/homebrew/opt/flowwing/lib/FlowWing/lib"
#elif PLATFORM_ARCH == PLATFORM_MACOS_ARM64
#define FLOWWING_LIB_PATH "../../../lib/mac-silicon/lib"
#elif PLATFORM_ARCH == PLATFORM_LINUX_X86_64
#define FLOWWING_LIB_PATH "../../../lib/linux-x86_64/lib"
#endif

// Define the module path based on the library path
#ifdef FLOWWING_LIB_PATH
#define FLOWWING_MODULE_PATH FLOWWING_LIB_PATH "/modules"
#endif

// Define the Clang path based on the platform
#if defined(__linux__)
#define FLOWWING_CLANG_PATH "/usr/bin/clang-17"
#elif defined(__APPLE__)
#define FLOWWING_CLANG_PATH "/usr/bin/clang++"
#endif

// #define FLOWWING_LIB_PATH "../../../lib/linux-x86_64/lib"
// #define FLOWWING_MODULE_PATH FLOWWING_LIB_PATH "/modules"
// #define FLOWWING_CLANG_PATH "/usr/bin/clang-17"

//! For JIT Config

#if defined(DEBUG) && defined(__linux__)
#define LIB_BUILT_IN_MODULE_PATH                                               \
  "../../../lib/linux-x86_64/libbuilt_in_module.bc"
#elif defined(DEBUG) && defined(__APPLE__)
#define LIB_BUILT_IN_MODULE_PATH                                               \
  "../../../lib/mac-silicon/libbuilt_in_module.bc"
#elif defined(RELEASE) && defined(__linux__)
#define LIB_BUILT_IN_MODULE_PATH                                               \
  "../../../lib/linux-x86_64/libbuilt_in_module.bc"
#elif defined(RELEASE) && defined(__APPLE__)
#define LIB_BUILT_IN_MODULE_PATH                                               \
  "/opt/homebrew/opt/flowwing/lib/FlowWing/lib/libbuilt_in_module.bc"
#endif