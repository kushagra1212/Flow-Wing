#include "BCFileSaveStrategy.h"

BCFileSaveStrategy::BCFileSaveStrategy(LLVMLogger *llvmLogger) {
  logger = llvmLogger;
}

bool BCFileSaveStrategy::saveToFile(
    const std::string &path,
    llvm::Module *module) const { // Create an output stream for the .bc file
  std::error_code EC;
  llvm::raw_fd_ostream OS(path, EC, llvm::sys::fs::OF_None);

  // llvm::legacy::PassManager pass = llvm::legacy::PassManager();
  // pass.add(llvm::createVerifierPass());
  // pass.add(llvm::createCFGSimplificationPass());
  // pass.add(llvm::createDeadCodeEliminationPass());
  // pass.run(*module);

  if (!EC) {
    // Write the LLVM module to the .bc file
    llvm::WriteBitcodeToFile(*module, OS);
    OS.flush();
    return true;
  } else {

    const std::string errorString = "Error opening " +
                                    Utils::getFileName(path) +
                                    " for writing: " + EC.message();
    if (logger == nullptr) {
      std::cerr << errorString;
    } else {
      logger->LogError(errorString);
    }

    return false;
  }
}