#!/bin/bash

# Define paths and variables
export SHARED_LIB_PATH="libflowwing_vector.so"

# Compile the C++ code into a shared library
echo "Compiling C++ code into shared library..."
clang-17 -std=c++20  -fPIC -shared  vector.cpp -o $SHARED_LIB_PATH 

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


