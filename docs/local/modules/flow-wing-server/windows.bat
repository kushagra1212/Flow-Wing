@echo off

:: Define paths and variables
set FLOW_WING_COMPILER_PATH="C:\\Users\\kusha\\Flow-Wing\\targets\\aot-compiler\\build\\FlowWing.exe"
set OTHER_LIB_PATH="C:\\Users\\kusha\\Flow-Wing\\lib\\win-x86_64\\lib"
set FLOW_WING_LIB_PATH="C:\\Users\\kusha\\Flow-Wing\\docs\\local\\modules\\core\\VectorModule"
set FLOW_WING_FILE="server.fg"
set SHARED_LIB_PATH="flowwing_vortex.dll"
set OUTPUT_EXECUTABLE="build\\bin\\server.exe"

:: Compile the C code into a shared library
echo Compiling C code into shared library...
clang++ -std=c++20 -shared -o %SHARED_LIB_PATH% server-windows.cpp -lws2_32

:: Check for errors in the C compilation step
if errorlevel 1 (
    echo Error: Failed to compile C code into shared library.
    exit /b 1
)

:: Check if the shared library was created successfully
if not exist %SHARED_LIB_PATH% (
    echo Error: Shared library not created.
    exit /b 1
)

:: Compile the Flow-Wing code
echo Compiling Flow-Wing code...
%FLOW_WING_COMPILER_PATH% --F=%FLOW_WING_FILE% -O=-O3 -L=%FLOW_WING_LIB_PATH% -l=flowwing_vortex 

:: Check if the executable was created successfully
if not exist %OUTPUT_EXECUTABLE% (
    echo Error: Executable not created.
    exit /b 1
)

:: Run the executable
echo Running the server...
%OUTPUT_EXECUTABLE%
