#!/bin/bash

# ==============================================================================
# Git pre-commit hook to automatically manage copyright headers for staged files.
# It uses the core logic from `license_tool.sh`.
# ==============================================================================

# Source the core licensing tool script.
# The path is relative from the .git/hooks directory to the project root.
source "$(dirname "$0")/../../license_tool.sh"

# Get a list of staged files that match our target patterns, excluding the external dir.
STAGED_FILES=$(git diff --cached --name-only --diff-filter=ACM -- "*.h" "*.cpp" "CMakeLists.txt" "*.cmake" | grep -v '^src/external/')

# If there are no matching files, exit early.
if [ -z "$STAGED_FILES" ]; then
    exit 0
fi

# Process each relevant staged file.
for file in $STAGED_FILES; do
    # Call the core function in "commit_mode" to enable `git add`
    process_file "$file" "commit_mode"
done

exit 0