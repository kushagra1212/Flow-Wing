#!/bin/bash

# ==============================================================================
# Script to refactor C++ #include paths in the FlowWing project.
# VERSION 3.2: Fixes the final logic error to ensure all new paths are
#              correctly prefixed with "src/".
#
# USAGE:
#   1. Dry Run (Recommended first):
#      ./refactor_includes.sh
#
#   2. Apply Changes:
#      ./refactor_includes.sh --apply
# ==============================================================================

# --- Configuration ---
SOURCE_ROOT="src"
SRC_FULL_PATH=$(realpath "$SOURCE_ROOT")

DRY_RUN=true
if [ "$1" == "--apply" ]; then
    DRY_RUN=false
    echo "--- APPLY MODE: Files will be modified. ---"
else
    echo "--- DRY RUN MODE: No files will be changed. Run with --apply to modify files. ---"
fi
echo ""

if ! command -v realpath &> /dev/null; then
    echo "ERROR: The 'realpath' command is not found. Please install it to continue."
    echo "(On macOS: brew install coreutils)"
    exit 1
fi

find "$SOURCE_ROOT" -type f \( -name "*.h" -o -name "*.cpp" \) \
-not -path "*/external/*" \
-print0 | while IFS= read -r -d $'\0' file_path; do

    include_lines=$(grep -E '^\s*#\s*include\s*"\.\./' "$file_path") || continue

    if [ -n "$include_lines" ]; then
        echo "============================================================"
        echo "Processing file: $file_path"
        echo "------------------------------------------------------------"

        sed_commands=()

        while IFS= read -r line; do
            tmp_path="${line#*\"}"
            relative_path="${tmp_path%\"*}"
            
            if [ -z "$relative_path" ]; then continue; fi

            file_dir=$(dirname "$file_path")
            target_header_full_path=$(realpath "$file_dir/$relative_path")
            
            if [[ "$target_header_full_path" == "$SRC_FULL_PATH"* ]]; then
                # Get the path relative to the inside of src/
                path_after_src=${target_header_full_path#$SRC_FULL_PATH/}

                # --- THE CRITICAL FIX IS HERE ---
                # Prepend "src/" to the path to make it relative to the project root.
                new_include_line="#include \"src/$path_after_src\""

                echo "--- OLD: $line"
                echo "+++ NEW: $new_include_line"
                echo ""
                
                sed_commands+=("-e" "s|$line|$new_include_line|g")
            fi
        done <<< "$include_lines"
        
        if [ "$DRY_RUN" == false ] && [ ${#sed_commands[@]} -gt 0 ]; then
            sed -i.bak "${sed_commands[@]}" "$file_path"
            echo "Applied ${#sed_commands[@]} changes to $file_path"
        fi
    fi
done

# --- Cleanup ---
if [ "$DRY_RUN" == false ]; then
    echo ""
    echo "Refactoring complete."
    BACKUP_FILES=$(find "$SOURCE_ROOT" -name "*.bak")
    if [ -n "$BACKUP_FILES" ]; then
        read -p "Do you want to delete all backup (.bak) files? (y/n) " -n 1 -r
        echo
        if [[ $REPLY =~ ^[Yy]$ ]]; then
            echo "Deleting backup files..."
            find "$SOURCE_ROOT" -name "*.bak" -delete
            echo "Done."
        fi
    fi
fi

echo "Script finished."