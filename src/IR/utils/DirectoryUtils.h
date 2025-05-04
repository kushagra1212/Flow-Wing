#ifndef DIRECTORY_UTILS_H
#define DIRECTORY_UTILS_H

#include "../../IR/logger/LLVMLogger.h"
#include "../../utils/Utils.h"
#include <llvm/Support/FileSystem.h>
namespace FLOWWING::IR::UTILS {

int8_t createFreshTempDirectory(const std::string &tempDir, LLVMLogger *logger);

int8_t createTempDirectories(LLVMLogger *logger);

} // namespace FLOWWING::IR::UTILS
#endif
