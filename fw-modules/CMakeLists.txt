# =============================================================================
# FlowWing | Modules Entry Point
#
# This file serves as the entry point for the fw-modules directory.
# It includes the individual CMakeLists.txt files for each module,
# which in turn define the library targets for the SDK.
# =============================================================================

add_subdirectory(built_in_module)
add_subdirectory(dynamic)
add_subdirectory(map_module)
add_subdirectory(text_module)
add_subdirectory(vec_module)
add_subdirectory(file_module)  
add_subdirectory(io_module) 
add_subdirectory(vortex_module)
add_subdirectory(raylib_module)

