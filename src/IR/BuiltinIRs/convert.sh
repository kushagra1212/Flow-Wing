#!/bin/bash

# Check if the input file is provided as argument
if [ $# -ne 1 ]; then
    echo "Usage: $0 <input_file.ll>"
    exit 1
fi

# Assign input file name to a variable
input_file="$1"

# Check if the input file exists
if [ ! -f "$input_file" ]; then
    echo "Error: Input file '$input_file' does not exist."
    exit 1
fi

# Extract the filename without extension
filename=$(basename -- "$input_file")
filename_no_ext="${filename%.*}"

# Perform the conversion using llvm-as
llvm-as "$input_file" -o "$filename_no_ext.bc"

# Check if conversion was successful
if [ $? -ne 0 ]; then
    echo "Error: Conversion failed."
    exit 1
fi

echo "Conversion successful. Output file: $filename_no_ext.bc"