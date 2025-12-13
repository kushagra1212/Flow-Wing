/*
 * FlowWing Compiler
 * Copyright (C) 2023-2025 Kushagra Rathore
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
 */

#pragma once

#include <string>

namespace flow_wing {
namespace utils {

struct PathUtils {
  // Converts a relative file path to an absolute path based on the current
  // working directory.
  static std::string getAbsoluteFilePath(const std::string &relative_file_path);

  // Extracts the filename (including extension) from a full path.
  // Example: "/path/to/file.txt" -> "file.txt"
  static std::string getFileName(const std::string &file_path);

  // Extracts the filename without its extension.
  // Example: "/path/to/file.txt" -> "file"
  static std::string removeExtension(const std::string &file_path);

  // Extracts the extension from a file path, including the dot.
  // Example: "/path/to/file.txt" -> ".txt"
  static std::string getExtension(const std::string &file_path);
};

} // namespace utils
} // namespace flow_wing
