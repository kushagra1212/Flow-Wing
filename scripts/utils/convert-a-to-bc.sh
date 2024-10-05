#!/bin/bash

# Check if input .a file is provided
if [ $# -ne 1 ]; then
    echo "Usage: $0 <input_library.a>"
    exit 1
fi

input_library="$1"



# Extract object files from the archive
llvm-ar x "$input_library" 

for obj_file in *.o; do
    file "$obj_file"
done

# Link all .bc files into one final bitcode file
llvm-link *.bc -o final_output.bc

# Move the final bitcode file to the current directory



echo "Conversion successful. Output: final_output.bc"
