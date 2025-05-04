
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