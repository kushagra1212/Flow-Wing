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

#include "AotCompilerUtils.h"
#include "src/IR/constants/FlowWingIRConstants.h"

namespace FlowWing {

namespace AOT {

//? LOGS

void LINKING_FAIL_ERROR(int status, std::string &fileNameWithOutExtension,
                        std::string version) {
  Utils::printErrors(
      {(std::string)YELLOW_TEXT + "FlowWing " + (version) + ": " +
       std::string(RED_TEXT) +
       " failed with non zero status: " + std::to_string(status)},
      std::cerr, false);
  Utils::printErrors({"Failed to link: " + fileNameWithOutExtension}, std::cerr,
                     false);
}

void RUN_ON_DEBUG_GENERATE_BC_FROM_LL() {
#if (defined(DEBUG) && defined(JIT_MODE)) ||                                   \
    (defined(DEBUG) && defined(AOT_MODE))
  std::vector<std::string> llFiles = Utils::getAllFilesInDirectoryWithExtension(
      std::filesystem::current_path().string(), ".ll", false);

  for (auto llFile : llFiles) {

    const std::string space = " ";

    std::string cmd = (FlowWing::PathUtils::getAOTLinkerPath()) + space +
                      llFile + " -emit-llvm -c " + " -o " +
                      llFile.substr(0, llFile.length() - 3) + ".bc";
    CODEGEN_DEBUG_LOG("Compiling: ", llFile);

    CODEGEN_DEBUG_LOG("Emit LLVM IR as BC file: ", cmd);

    const int status = std::system(cmd.c_str());

    if (status != 0) {

      std::cerr << Utils::CE("Failed to compile: ") << llFile << std::endl;
      return;
    }
  }

#endif
}

auto getFileNameWithoutExtension(FlowWing::DiagnosticHandler *diagHandler)
    -> std::string {

#if defined(AOT_TEST_MODE)
  return FLOWWING::IR::CONSTANTS::FLOWWING_GLOBAL_ENTRY_POINT;
#endif

  return Utils::removeExtensionFromString(
      Utils::getFileName(diagHandler->getAbsoluteFilePath()));
}

auto deleteObjectFiles() -> void {
  std::vector<std::string> objectFiles =
      Utils::getAllFilesInDirectoryWithExtension(
          FLOWWING::IR::CONSTANTS::TEMP_OBJECT_FILES_DIR, FLOWWING::IR::CONSTANTS::OBJECT_FILE_EXTENSION, false);
  for (const auto &objectFile : objectFiles) {
    LINKING_DEBUG_LOG("Deleting object file: ", objectFile);
    std::filesystem::remove(objectFile);
  }
}

auto deleteBcFiles() -> void {
  std::vector<std::string> objectFiles =
      Utils::getAllFilesInDirectoryWithExtension(
          Utils::getTempDir() + FLOWWING::IR::CONSTANTS::TEMP_BC_FILES_DIR,
          ".bc", false);
  for (const auto &objectFile : objectFiles) {
    std::filesystem::remove(objectFile);
  }
}

} // namespace AOT

} // namespace FlowWing