@echo off
setlocal

:: Define paths and variables
set FLOW_WING_COMPILER_PATH="C:\\Users\\kusha\\Flow-Wing\\targets\\aot-compiler\\build\\FlowWing.exe"
set FLOW_WING_LIB_PATH="C:\\Users\\kusha\\Flow-Wing\\docs\\local\\modules\\core\\stringModule"
set FLOW_WING_FILE="test.fg"
set SHARED_LIB_PATH="libflowwing_string.lib"  
set OUTPUT_EXECUTABLE="build\\bin\\test.exe"

:: Compile the C code into a static library
echo Compiling C code into object file...
clang -c -O3 -o "libflowwing_string.obj" libflowwing_string.c
if errorlevel 1 (
    echo Error: Failed to compile C code into object file.
    exit /b 1
)

:: Create the static library from the object file
llvm-lib /out:%SHARED_LIB_PATH% libflowwing_string.obj
if errorlevel 1 (
    echo Error: Failed to create static library.
    exit /b 1
)

:: Check if the static library was created successfully
if not exist %SHARED_LIB_PATH% (
    echo Error: Static library not created.
    exit /b 1
)

:: Compile the Flow-Wing code
echo Compiling Flow-Wing code...
%FLOW_WING_COMPILER_PATH% --F=%FLOW_WING_FILE% -O3 -L=%FLOW_WING_LIB_PATH% -l=flowwing_string
if not exist %OUTPUT_EXECUTABLE% (
    echo Error: Executable not created.
    exit /b 1
)

:: Run the executable
echo Build Complete...
%OUTPUT_EXECUTABLE%

endlocal
