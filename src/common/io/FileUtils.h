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

#include <fstream>
#include <optional>
#include <sstream>
#include <string>
#include <vector>

namespace flow_wing {
namespace io {

struct FileUtils {
private:
  static inline std::vector<std::string>
  readLinesFromStream(std::istream &stream) {
    std::vector<std::string> lines;
    std::string line;
    // std::getline defaults to using '\n' as the delimiter, which is the
    // correct behavior for both reading from a file and a string stream.
    while (std::getline(stream, line)) {
      // Check for and remove carriage return ('\r') for Windows compatibility
      if (!line.empty() && line.back() == '\r') {
        line.pop_back();
      }
      lines.push_back(std::move(line));
    }
    return lines;
  }

public:
  static inline std::optional<std::vector<std::string>>
  readLines(const std::string &file_path) {
    std::ifstream file(file_path);
    if (!file.is_open()) {
      return std::nullopt; // Signal that the file could not be opened.
    }
    // file is closed by the destructor of the ifstream
    return readLinesFromStream(file);
  }

  static inline std::vector<std::string>
  readLinesFromString(const std::string &content) {
    std::stringstream ss(content);
    return readLinesFromStream(ss);
  }
};

} // namespace io
} // namespace flow_wing
