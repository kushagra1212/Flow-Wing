#!/bin/bash

# Define paths and variables
export SHARED_LIB_PATH="libbuilt_in_module.a"

# Compile the C++ code into a shared library
echo "Compiling C++ code into shared library..."
clang-cpp-17  -fPIC  libbuilt_in_module.ll -o $SHARED_LIB_PATH 

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


