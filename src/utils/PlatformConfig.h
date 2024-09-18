#pragma once

// Define macros for build mode, platform, and architecture combinations

// Debug mode on Linux for x86_64 architecture
#if defined(DEBUG) && defined(__linux__) && defined(__x86_64__)
#define DEBUG_LINUX_X86_64 1
#else
#define DEBUG_LINUX_X86_64 0
#endif

// Debug mode on Linux for other architectures (e.g., ARM)
#if defined(DEBUG) && defined(__linux__) && !defined(__x86_64__)
#define DEBUG_LINUX_OTHER_ARCH 1
#else
#define DEBUG_LINUX_OTHER_ARCH 0
#endif

// Debug mode on macOS for Apple Silicon (M1, M2, etc.)
#if defined(DEBUG) && defined(__APPLE__) && defined(__arm64__)
#define DEBUG_MACOS_ARM64 1
#else
#define DEBUG_MACOS_ARM64 0
#endif

// Debug mode on macOS for Intel
#if defined(DEBUG) && defined(__APPLE__) && defined(__x86_64__)
#define DEBUG_MACOS_X86_64 1
#else
#define DEBUG_MACOS_X86_64 0
#endif

// Release mode on Linux for x86_64 architecture
#if defined(RELEASE) && defined(__linux__) && defined(__x86_64__)
#define RELEASE_LINUX_X86_64 1
#else
#define RELEASE_LINUX_X86_64 0
#endif

// Release mode on Linux for other architectures
#if defined(RELEASE) && defined(__linux__) && !defined(__x86_64__)
#define RELEASE_LINUX_OTHER_ARCH 1
#else
#define RELEASE_LINUX_OTHER_ARCH 0
#endif

// Release mode on macOS for Apple Silicon (M1, M2, etc.)
#if defined(RELEASE) && defined(__APPLE__) && defined(__arm64__)
#define RELEASE_MACOS_ARM64 1
#else
#define RELEASE_MACOS_ARM64 0
#endif

// Release mode on macOS for Intel
#if defined(RELEASE) && defined(__APPLE__) && defined(__x86_64__)
#define RELEASE_MACOS_X86_64 1
#else
#define RELEASE_MACOS_X86_64 0
#endif

// AOT Test Mode Release Macros
#if defined(AOT_TEST_MODE) && defined(RELEASE_LINUX_X86_64)
#define AOT_TEST_MODE_RELEASE_LINUX_X86_64 1
#else
#define AOT_TEST_MODE_RELEASE_LINUX_X86_64 0
#endif

#if defined(AOT_TEST_MODE) && defined(RELEASE_LINUX_OTHER_ARCH)
#define AOT_TEST_MODE_RELEASE_LINUX_OTHER_ARCH 1
#else
#define AOT_TEST_MODE_RELEASE_LINUX_OTHER_ARCH 0
#endif

#if defined(AOT_TEST_MODE) && defined(RELEASE_MACOS_X86_64)
#define AOT_TEST_MODE_RELEASE_MACOS_X86_64 1
#else
#define AOT_TEST_MODE_RELEASE_MACOS_X86_64 0
#endif

#if defined(AOT_TEST_MODE) && defined(RELEASE_MACOS_ARM64)
#define AOT_TEST_MODE_RELEASE_MACOS_ARM64 1
#else
#define AOT_TEST_MODE_RELEASE_MACOS_ARM64 0
#endif

// AOT Mode Release Macros
#if defined(AOT_MODE) && defined(RELEASE_LINUX_X86_64)
#define AOT_MODE_RELEASE_LINUX_X86_64 1
#else
#define AOT_MODE_RELEASE_LINUX_X86_64 0
#endif

#if defined(AOT_MODE) && defined(RELEASE_LINUX_OTHER_ARCH)
#define AOT_MODE_RELEASE_LINUX_OTHER_ARCH 1
#else
#define AOT_MODE_RELEASE_LINUX_OTHER_ARCH 0
#endif

#if defined(AOT_MODE) && defined(RELEASE_MACOS_X86_64)
#define AOT_MODE_RELEASE_MACOS_X86_64 1
#else
#define AOT_MODE_RELEASE_MACOS_X86_64 0
#endif

#if defined(AOT_MODE) && defined(RELEASE_MACOS_ARM64)
#define AOT_MODE_RELEASE_MACOS_ARM64 1
#else
#define AOT_MODE_RELEASE_MACOS_ARM64 0
#endif

// AOT Mode Debug Macros
#if defined(AOT_MODE) && defined(DEBUG_LINUX_X86_64)
#define AOT_MODE_DEBUG_LINUX_X86_64 1
#else
#define AOT_MODE_DEBUG_LINUX_X86_64 0
#endif

#if defined(AOT_MODE) && defined(DEBUG_LINUX_OTHER_ARCH)
#define AOT_MODE_DEBUG_LINUX_OTHER_ARCH 1
#else
#define AOT_MODE_DEBUG_LINUX_OTHER_ARCH 0
#endif

#if defined(AOT_MODE) && defined(DEBUG_MACOS_X86_64)
#define AOT_MODE_DEBUG_MACOS_X86_64 1
#else
#define AOT_MODE_DEBUG_MACOS_X86_64 0
#endif

#if defined(AOT_MODE) && defined(DEBUG_MACOS_ARM64)
#define AOT_MODE_DEBUG_MACOS_ARM64 1
#else
#define AOT_MODE_DEBUG_MACOS_ARM64 0
#endif
