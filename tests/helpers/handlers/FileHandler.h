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

#include "src/common/constants/FlowWingUtilsConstants.h"
#include "src/utils/FlowWingConfig.h"
#include "src/utils/LogConfig.h"
#include <filesystem>
#include <fstream>
#include <iostream>

class FileHandler {

public:
  FileHandler() {

#if defined(AOT_TEST_MODE)
    compilerType = "aot";
#endif
  }

  void createDirectory(const std::string &path) {

    if (!std::filesystem::exists(path)) {
      if (!std::filesystem::create_directory(path)) {
        std::cerr << "Failed to create directory: " << path << std::endl;
        return;
      }
    }
  }

  void removeDirectory(const std::string &path) {

    // Check if directory exists and remove it
    if (std::filesystem::exists(path)) {
      if (!std::filesystem::remove_all(path)) {
        std::cerr << "Failed to delete directory: " << path << std::endl;
        return; // Return an error code
      }
    }
  }

  std::string getCodeFilePath(const std::string &fileName) {
    return std::filesystem::path(TEST_SDK_PATH) / fileName;
  }

  void writeFile(const std::string &filename, const std::string &code) {
    std::ofstream exportFile(getCodeFilePath(filename));
    exportFile << code;
    exportFile.close();
  }

  std::string createBuildAndRunCmd(const std::string &fileName) {

    const std::string codeFilePath = getCodeFilePath(fileName);

    std::string runCMD = "cd " + std::filesystem::path(PROJECT_DIR).string() +
                         " && make run-" + compilerType +
                         "-release SILENT=1 -s FILE=" + codeFilePath;

    return runCMD;
  }

private:
  std::string compilerType = "jit";
  std::filesystem::path currentPath = std::filesystem::current_path();
};