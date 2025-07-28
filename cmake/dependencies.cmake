# =============================================================================
# Dependency Management
#
# Finds and configures all external dependencies required by the project,
# such as LLVM, Threads, and GTest.
# =============================================================================

# --- LLVM ---
find_package(LLVM 17 REQUIRED CONFIG)
message(STATUS "Found LLVM ${LLVM_VERSION} for static linking.")

# --- Threads ---
find_package(Threads REQUIRED)
message(STATUS "Found Threads for threading support.")

# --- AOT Linker (Conditional) ---
if(BUILD_AOT)
    find_program(AOT_LINKER_PATH
        NAMES clang-17 clang++ clang
        REQUIRED
        DOC "Path to the clang compiler for AOT linking.")
    message(STATUS "AOT linker for user code: ${AOT_LINKER_PATH}")
endif()

# --- GTest (Conditional) ---
if(TESTS_ENABLED)
    find_package(GTest REQUIRED)
endif()