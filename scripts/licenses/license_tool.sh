#!/bin/bash

# ==============================================================================
# CORE SCRIPT for managing copyright headers in the FlowWing project.
# This script is not meant to be run directly. It should be sourced by other
# scripts like `update_licenses.sh` or the `pre-commit` hook.
# ==============================================================================

# --- Configuration ---
COPYRIGHT_OWNER="Kushagra Rathore"
START_YEAR="2023"
CURRENT_YEAR=$(date +"%Y")

if [ "$START_YEAR" == "$CURRENT_YEAR" ]; then
  COPYRIGHT_LINE_RAW="Copyright (C) $CURRENT_YEAR $COPYRIGHT_OWNER"
else
  COPYRIGHT_LINE_RAW="Copyright (C) $START_YEAR-$CURRENT_YEAR $COPYRIGHT_OWNER"
fi

# --- Header Templates ---
LICENSE_HEADER_CPP="/*
 * FlowWing Compiler
 * $COPYRIGHT_LINE_RAW
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */\n\n\n"

LICENSE_HEADER_HASH="#
# FlowWing Compiler
# $COPYRIGHT_LINE_RAW
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License along
# with this program; if not, write to the Free Software Foundation, Inc.,
# 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
#\n\n\n"


# --- Core Function ---
# Processes a single file to add or update its license header.
#
# Arguments:
#   $1: The path to the file to process.
#   $2: (Optional) A mode flag. If set to "commit_mode", the file will be re-staged with `git add`.
#
process_file() {
    local file_path="$1"
    local commit_mode="$2"

    # Determine which style to use based on filename
    case "$file_path" in
        *.h|*.cpp)
            HEADER_TO_USE="$LICENSE_HEADER_CPP"
            COPYRIGHT_LINE_FORMATTED=" * $COPYRIGHT_LINE_RAW"
            ;;
        CMakeLists.txt|*.cmake)
            HEADER_TO_USE="$LICENSE_HEADER_HASH\n\n"
            COPYRIGHT_LINE_FORMATTED="# $COPYRIGHT_LINE_RAW"
            ;;
        *)
            # Skip files we don't recognize
            return
            ;;
    esac

    # Check if the file is newly added (for commit hook) or just doesn't have a header
    is_new=false
    if [ "$commit_mode" == "commit_mode" ] && git diff --cached --name-only --diff-filter=A | grep -q "^${file_path}$"; then
        is_new=true
    fi

    # If the file has a copyright line, update it. Otherwise, add a new header.
    if grep -q "Copyright (C)" "$file_path"; then
        # Only update if it's a modified file (not a new one with a copied header)
        if ! $is_new; then
            sed -i.bak "s/^.*Copyright (C).*$/$COPYRIGHT_LINE_FORMATTED/" "$file_path"
            rm "${file_path}.bak"
            echo "Updated license in: $file_path"
            [ "$commit_mode" == "commit_mode" ] && git add "$file_path"
        fi
    else
        echo "Adding license to: $file_path"
        echo -e "$HEADER_TO_USE$(cat "$file_path")" > "$file_path.tmp" && mv "$file_path.tmp" "$file_path"
        [ "$commit_mode" == "commit_mode" ] && git add "$file_path"
    fi
}