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

#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>
#include <sys/stat.h>
#include <vector>

#if defined(__linux__) || defined(__APPLE__)
#include <cstdlib>
#include <unistd.h>
#elif defined(_WIN32)
#include <windows.h>
#endif

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

static inline std::vector<std::string>
getFiles(const std::string &directory_path, const std::string &extension,
         bool recursive = true) {
  std::vector<std::string> files = std::vector<std::string>();

  for (const auto &entry :
       std::filesystem::directory_iterator(directory_path)) {
    if (entry.path().extension() == extension) {
      files.push_back(entry.path().string());
    }

    if (entry.is_directory() && recursive) {
      std::vector<std::string> subFiles =
          getFiles(entry.path().string(), extension, recursive);
      files.insert(files.end(), subFiles.begin(), subFiles.end());
    }
  }

  return files;
}

static inline void removeFiles(const std::string &directory_path,
                               const std::string &extension) {
  std::vector<std::string> files = getFiles(directory_path, extension);
  for (const auto &file : files) {
    std::filesystem::remove(file);
  }
}

static inline std::string getTempDirectoryPath() {
#if defined(_WIN32)
  char tempPath[MAX_PATH];
  DWORD pathLen = GetTempPathA(MAX_PATH, tempPath);
  if (pathLen > 0 && pathLen < MAX_PATH) {
    return std::string(tempPath);
  }
  return "";
#else
  const char *tempDir = std::getenv("TMPDIR");
  if (!tempDir) {
    tempDir = "/tmp/";
  }
  return std::string(tempDir);
#endif
}

} // namespace io
} // namespace flow_wing
