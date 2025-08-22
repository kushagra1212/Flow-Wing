#!/bin/bash

# ==============================================================================
# One-off script to bring all existing project files into license compliance.
# It uses the core logic from `license_tool.sh`.
# ==============================================================================

# Source the core licensing tool script.
# `$(dirname "$0")` ensures it works no matter where you call it from.
source "$(dirname "$0")/license_tool.sh"

echo "Running full license scan..."

# Find all relevant files and process them one by one.
find . -type f \( -name "*.h" -o -name "*.cpp" -o -name "CMakeLists.txt" -o -name "*.cmake" \) \
-not -path "./build/*" \
-not -path "./.git/*" \
-not -path "./src/external/*" \
-not -path "./.fw_dependencies/*" \
-not -path "./.fw_dependencies_debug_bak/*" \
-not -path "./.fw_dependencies_release_bak/*" \
-print0 | while IFS= read -r -d $'\0' file; do
    process_file "$file"
done

echo "License update complete."