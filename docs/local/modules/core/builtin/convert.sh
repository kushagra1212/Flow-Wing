#!/bin/bash
# Filename: convert_c_to_a.sh

llvm_bin_path="../../../../../.fw_dependencies/install/bin"
sdk_path="/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk"

# Check if the input file is provided as argument
if [ $# -ne 1 ]; then
    echo "Usage: $0 <input_file.c>"
    exit 1
fi

input_file="$1"

# Check if the input file exists
if [ ! -f "$input_file" ]; then
    echo "Error: Input file '$input_file' does not exist."
    exit 1
fi

# Extract the filename without extension
filename=$(basename -- "$input_file")
filename_no_ext="${filename%.*}"

rm -f "$filename_no_ext.a"


# Step 1: Compile .c file to an object file .o using clang++
echo "Compiling $input_file with clang++..."
$llvm_bin_path/clang --sysroot=$sdk_path -c -o "$filename_no_ext.o" "$input_file"

# Check if compilation was successful
if [ $? -ne 0 ]; then
    echo "Error: C to Object File compilation failed."
    exit 1
fi

# Step 2: Create an archive file using llvm-ar
echo "Archiving $filename_no_ext.o into $filename_no_ext.a..."
$llvm_bin_path/llvm-ar rcs "$filename_no_ext.a" "$filename_no_ext.o"

# Check if archive creation was successful
if [ $? -ne 0 ]; then
    echo "Error: Archive creation failed."
    exit 1
fi

echo "Compilation and archive creation successful. Output file: $filename_no_ext.a"