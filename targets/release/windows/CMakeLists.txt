cmake_minimum_required(VERSION 3.0)
project(FlowWingInstaller)

# Specify the location of your binaries and libraries
set(FLOWWING_BINARIES
    "${CMAKE_SOURCE_DIR}/bin/FlowWing.exe"
    "${CMAKE_SOURCE_DIR}/bin/FlowWing-jit.exe"
    "${CMAKE_SOURCE_DIR}/bin/lld-link.exe"
)

set(FLOWWING_LIBS
    "${CMAKE_SOURCE_DIR}/lib/built_in_module.lib"
    "${CMAKE_SOURCE_DIR}/lib/flowwing_string.lib"
    "${CMAKE_SOURCE_DIR}/lib/flowwing_map.dll"
    "${CMAKE_SOURCE_DIR}/lib/flowwing_map.exp"
    "${CMAKE_SOURCE_DIR}/lib/flowwing_map.lib"
    "${CMAKE_SOURCE_DIR}/lib/flowwing_vector.lib"
    "${CMAKE_SOURCE_DIR}/lib/flowwing_vector.exp"
    "${CMAKE_SOURCE_DIR}/lib/flowwing_vector.dll"
    "${CMAKE_SOURCE_DIR}/lib/flowwing_vortex.dll"
    "${CMAKE_SOURCE_DIR}/lib/flowwing_vortex.lib"
    "${CMAKE_SOURCE_DIR}/lib/flowwing_vortex.exp"
    "${CMAKE_SOURCE_DIR}/lib/gc.dll"
    "${CMAKE_SOURCE_DIR}/lib/gc.lib"
)

# Specify modules folder path
set(FLOWWING_MODULES_DIR "${CMAKE_SOURCE_DIR}/lib/modules")
add_custom_target(FlowWingInstaller
    COMMENT "Building FlowWing Installer"
)
# Define installer target
install(CODE "execute_process(COMMAND cmake -E make_directory \"\$ENV{PROGRAMFILES}/FlowWing\")")
install(FILES ${FLOWWING_BINARIES} DESTINATION "${CMAKE_INSTALL_PREFIX}/bin")
install(FILES ${FLOWWING_LIBS} DESTINATION "${CMAKE_INSTALL_PREFIX}/lib")
install(DIRECTORY ${FLOWWING_MODULES_DIR} DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/modules")

find_program(NSIS_EXECUTABLE makensis PATHS "C:/Program Files (x86)/NSIS" REQUIRED)


# Add NSIS target
add_custom_command(TARGET FlowWingInstaller
    POST_BUILD
    COMMAND ${NSIS_EXECUTABLE} "${CMAKE_BINARY_DIR}/../FlowWingInstaller.nsi"
    COMMENT "Running NSIS to create installer"
)