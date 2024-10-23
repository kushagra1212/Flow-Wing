#include "LLFileSaveStrategy.h"

LLFileSaveStrategy::LLFileSaveStrategy(LLVMLogger *llvmLogger) {
  logger = llvmLogger;
}

bool LLFileSaveStrategy::saveToFile(const std::string &path,
                                    llvm::Module *module) const {

  llvm::sys::fs::create_directories(Utils::getTempDir() +
                                    FLOWWING::IR::CONSTANTS::TEMP_BC_FILES_DIR);

  // Create an output stream for the .ll file
  std::error_code EC;
  llvm::raw_fd_ostream OS(path, EC, llvm::sys::fs::OF_None);

  if (!EC) {
    // Write the LLVM module to the .ll file
    module->print(OS, nullptr);
    OS.flush();
    return true;
  } else {
    if (logger == nullptr) {
      std::cerr << "Error opening " + Utils::getFileName(path) +
                       " for writing: " + EC.message();
    } else {
      logger->LogError("Error opening " + Utils::getFileName(path) +
                       " for writing: " + EC.message());
    }

    return false;
  }
}