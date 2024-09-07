#!/bin/bash

# Define paths and variables
export FLOW_WING_COMPILER_PATH="/Users/apple/code/per/Flow-Wing/targets/aot-compiler/aot-compiler-build/FlowWing"
export FLOW_WING_LIB_PATH="/Users/apple/code/per/Flow-Wing/docs/local/modules/flow-wing-server"
export FLOW_WING_FILE="server.fg"
export SHARED_LIB_PATH="libwing.so"
export OUTPUT_EXECUTABLE="build/bin/server"

# Compile the C code into a shared library
echo "Compiling C code into shared library..."
clang -fPIC -shared -o $SHARED_LIB_PATH server.c -I/opt/homebrew/include -L/opt/homebrew/lib

# Check for errors in the C compilation step
if [ $? -ne 0 ]; then
    echo "Error: Failed to compile C code into shared library."
    exit 1
fi



# Check if the shared library was created successfully
if [ ! -f "$SHARED_LIB_PATH" ]; then
    echo "Error: Shared library not created."
    exit 1
fi


# Compile the Flow-Wing code
echo "Compiling Flow-Wing code..."
$FLOW_WING_COMPILER_PATH --F=$FLOW_WING_FILE -O3 -L=$FLOW_WING_LIB_PATH -l=wing

# Check if the executable was created successfully
if [ ! -f "$OUTPUT_EXECUTABLE" ]; then
    echo "Error: Executable not created."
    exit 1
fi

# Run the executable
echo "Running the server..."
$OUTPUT_EXECUTABLE
