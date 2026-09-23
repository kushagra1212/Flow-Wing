# The Flow-Wing front end (lexer, parser, semantic analysis) built for the
# browser with Emscripten. Built by scripts/wasm/build-frontend.sh.
#
# It is the compiler's own command line with everything from IR generation on
# left out (FLOWWING_FRONTEND_ONLY), so it prints exactly the tokens, trees and
# errors the full compiler does, without LLVM. A page runs it as
#
#   createFlowWingFrontend() -> FS.writeFile("/main.fg", source)
#                            -> callMain(["/main.fg", "--emit=sem", ...])
#
# and reads the JSON it writes. The source lists mirror cmake/targets.cmake,
# minus IRGen, the linker and the passes that need LLVM.

cmake_minimum_required(VERSION 3.20)
project(flowwing_frontend CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

get_filename_component(ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../../.." ABSOLUTE)
set(SRC "${ROOT}/src")

file(GLOB_RECURSE FRONTEND_SOURCES
    "${SRC}/SourceTokenizer/*.cpp"
    "${SRC}/ASTBuilder/*.cpp"
    "${SRC}/ASTVisitor/*.cpp"
    "${SRC}/SemanticAnalyzer/*.cpp"
    "${SRC}/syntax/*.cpp"
    "${SRC}/common/*.cpp"
    "${SRC}/compiler/Serialization/*.cpp"
    "${SRC}/compiler/formatter/*.cpp"
    "${SRC}/compiler/diagnostics/*.cpp"
    "${SRC}/compiler/CompilerOptions/*.cpp"
    "${SRC}/compiler/BuildProgress/*.cpp"
    "${SRC}/compiler/pipeline/*.cpp")
list(FILTER FRONTEND_SOURCES EXCLUDE REGEX
    "/pipeline/(backends|passes/(IRGenerationPass|IrDumperPass|JITCompilerPass|OptimizationPass|ObjectEmissionPass|LinkerPass|WasmEmissionPass|WasmLinkPass))/")
list(APPEND FRONTEND_SOURCES "${SRC}/compiler/main.cpp")

# version.h, as cmake/version.cmake writes it for the full compiler. Written
# only when it changes, so a reconfigure does not recompile its users.
file(READ "${ROOT}/VERSION.txt" FLOWWING_VERSION)
string(STRIP "${FLOWWING_VERSION}" FLOWWING_VERSION)
file(CONFIGURE OUTPUT "${CMAKE_BINARY_DIR}/src/common/version.h"
    CONTENT "#pragma once\n#define VERSION_INFO \"${FLOWWING_VERSION}\"\n")

# The standard modules, flat, as an SDK installs them in lib/modules.
file(GLOB_RECURSE FG_MODULE_FILES "${ROOT}/fw-modules/*.fg")
file(REMOVE_RECURSE "${CMAKE_BINARY_DIR}/modules")
file(COPY ${FG_MODULE_FILES} DESTINATION "${CMAKE_BINARY_DIR}/modules")

add_executable(flowwing-frontend ${FRONTEND_SOURCES})
target_include_directories(flowwing-frontend PRIVATE "${CMAKE_BINARY_DIR}" "${ROOT}")
target_compile_definitions(flowwing-frontend PRIVATE
    FLOWWING_FRONTEND_ONLY
    AOT_MODE
    FLOWWING_PLATFORM_LIB_DIR="lib/wasm32"
    TEST_SDK_PATH="")
target_compile_options(flowwing-frontend PRIVATE -O2 -fexceptions)

target_link_options(flowwing-frontend PRIVATE
    -O2
    -fexceptions
    # A factory, not a program that runs on load: the page calls main itself,
    # once per analysis, on a fresh instance.
    -sMODULARIZE=1
    -sEXPORT_NAME=createFlowWingFrontend
    -sINVOKE_RUN=0
    -sEXIT_RUNTIME=1
    -sEXPORTED_RUNTIME_METHODS=FS,ENV,callMain
    -sFORCE_FILESYSTEM=1
    -sALLOW_MEMORY_GROWTH=1
    -sSTACK_SIZE=8388608
    -sENVIRONMENT=web,worker,node
    # NODEFS, so tests/wasm_frontend_parity.mjs can mount the real disk and
    # analyse fixtures, and the files they bring, at their real paths.
    -lnodefs.js
    # The standard modules, so `bring vec` and friends resolve: the compiler
    # finds them through FLOWWING_MODULES_PATH, which the page sets to
    # /lib/modules.
    "--embed-file=${CMAKE_BINARY_DIR}/modules@/lib/modules")
# --embed-file is not a dependency CMake sees: relink when a module changes.
set_target_properties(flowwing-frontend PROPERTIES
    SUFFIX ".js"
    LINK_DEPENDS "${FG_MODULE_FILES}")
