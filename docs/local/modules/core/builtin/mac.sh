#!/bin/bash

# Define paths and variables
export SHARED_LIB_NAME="libbuilt_in_module"

# Compile the C++ code into a shared library
echo "Compiling C++ code into shared library..."
llc -filetype=obj  $SHARED_LIB_NAME.ll -o $SHARED_LIB_NAME.o

echo "Linking shared library..."
ar rcs $SHARED_LIB_NAME.a $SHARED_LIB_NAME.o

# Check for errors in the C compilation step
if [ $? -ne 0 ]; then
    echo "Error: Failed to compile C code into shared library."
    exit 1
fi



# Check if the shared library was created successfully
if [ ! -f "$SHARED_LIB_NAME.a" ]; then
    echo "Error: Shared library not created."
    exit 1
fi


