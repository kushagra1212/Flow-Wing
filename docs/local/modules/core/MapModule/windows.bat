@echo off
REM Define paths and variables
set FLOW_WING_COMPILER_PATH="C:\\Users\\kusha\\Flow-Wing\\targets\\aot-compiler\\build\\FlowWing.exe"
set FLOW_WING_LIB_PATH="C:\\Users\\kusha\\Flow-Wing\\docs\\local\\modules\\core\\MapModule"
set FLOW_WING_FILE="test.fg"
set SHARED_LIB_PATH="flowwing_map.dll"
set SHARED_LIB_PATH_O="flowwing_map.o"
set OUTPUT_EXECUTABLE="build\\bin\\test.exe"
set OTHER_LIB_PATH="C:\\Users\\kusha\\Flow-Wing\\lib\\win-x86_64\\lib"

REM Compile the C++ code into a shared library
echo Compiling C++ code into shared library...
clang++ -std=c++20 -shared map.cpp -o %SHARED_LIB_PATH%

REM Check for errors in the C compilation step
if %ERRORLEVEL% neq 0 (
    echo Error: Failed to compile C++ code into shared library.
    exit /b 1
)

REM Check if the shared library was created successfully
if not exist "%SHARED_LIB_PATH%" (
    echo Error: Shared library not created.
    exit /b 1
)

REM Compile the Flow-Wing code
echo Compiling Flow-Wing code...

call %FLOW_WING_COMPILER_PATH% --F=%FLOW_WING_FILE% -O3 -L=%OTHER_LIB_PATH% -l=built_in_module -l=flowwing_vector  -l=flowwing_string -l=gc -l=flowwing_map

REM Check if the executable was created successfully
if not exist "%OUTPUT_EXECUTABLE%" (
    echo Error: Executable not created.
    exit /b 1
)

REM Run the executable
echo Executing the executable...
%OUTPUT_EXECUTABLE%
