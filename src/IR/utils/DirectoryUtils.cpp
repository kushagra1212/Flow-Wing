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



#include "DirectoryUtils.h"

namespace FLOWWING::IR::UTILS {

int8_t createFreshTempDirectory(const std::string &tempDir,
                                LLVMLogger *logger) {
  std::error_code RemoveEC = llvm::sys::fs::remove_directories(tempDir);

  if (RemoveEC && RemoveEC != std::errc::no_such_file_or_directory) {
    logger->LogError("Failed to remove directory '" + tempDir +
                     "': " + RemoveEC.message());

    return EXIT_FAILURE;
  }

  std::error_code CreateEC = llvm::sys::fs::create_directories(tempDir);

  if (CreateEC) {
    logger->LogError("Failed to create directory '" + tempDir +
                     +"': " + CreateEC.message());

    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

int8_t createTempDirectories(LLVMLogger *logger) {
  int8_t result = EXIT_SUCCESS;

#if defined(JIT_MODE) || defined(JIT_TEST_MODE)
  result = createFreshTempDirectory(
      Utils::getTempDir() + FLOWWING::IR::CONSTANTS::TEMP_BC_FILES_DIR, logger);
#endif

#if defined(AOT_MODE) || defined(AOT_TEST_MODE)
  result = createFreshTempDirectory(
      FLOWWING::IR::CONSTANTS::TEMP_OBJECT_FILES_DIR, logger);

  result |=
      createFreshTempDirectory(FLOWWING::IR::CONSTANTS::TEMP_BIN_DIR, logger);

#endif

  return result;
}

} // namespace FLOWWING::IR::UTILS