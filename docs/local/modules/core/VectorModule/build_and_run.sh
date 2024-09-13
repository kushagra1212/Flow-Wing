#!/bin/bash

# Define paths and variables
export FLOW_WING_COMPILER_PATH="/Users/apple/code/per/Flow-Wing/targets/aot-compiler/aot-compiler-build/FlowWing"
export FLOW_WING_LIB_PATH="/opt/homebrew/lib/FlowWing/lib/"
export FLOW_WING_FILE="test.fg"
export SHARED_LIB_PATH=$FLOW_WING_LIB_PATH/"libflowwing_vector.so"
export OUTPUT_EXECUTABLE="build/bin/test"

# Compile the C++ code into a shared library
echo "Compiling C++ code into shared library..."
clang++ -std=c++20  -fPIC -shared  vector.cpp -o $SHARED_LIB_PATH   -I/opt/homebrew/include

# Check for errors in the C compilation step
if [ $? -ne 0 ]; then
    echo "Error: Failed to compile C code into shared library."
    exit 1
fi
export DYLD_LIBRARY_PATH=/Users/apple/code/per/Flow-Wing/lib/mac-silicon/lib:$DYLD_LIBRARY_PATH


# Check if the shared library was created successfully
if [ ! -f "$SHARED_LIB_PATH" ]; then
    echo "Error: Shared library not created."
    exit 1
fi


# Compile the Flow-Wing code
echo "Compiling Flow-Wing code..."
$FLOW_WING_COMPILER_PATH --F=$FLOW_WING_FILE -O3 

# Check if the executable was created successfully
if [ ! -f "$OUTPUT_EXECUTABLE" ]; then
    echo "Error: Executable not created."
    exit 1
fi

# Run the executable
echo "Executing the executable..."
$OUTPUT_EXECUTABLE
