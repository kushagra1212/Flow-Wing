#include "OFileSaveStrategy.h"

OFileSaveStrategy::OFileSaveStrategy(LLVMLogger *llvmLogger) {
  logger = llvmLogger;
}

bool OFileSaveStrategy::saveToFile(const std::string &path,
                                   llvm::Module *module) const {

#if defined(REPL) || defined(REPL_TEST_MODE)
  return true;
#endif

  //  LLVMInitializeAArch64TargetInfo();
  std::string targetTriple =
      module->getTargetTriple(); // TODO: "x86_64-pc-windows-msvc
  module->setTargetTriple(targetTriple);

  std::string error;
  const llvm::Target *target =
      llvm::TargetRegistry::lookupTarget(targetTriple, error);

  if (!target) {
    logger->LogError(error);
    return false;
  }

  std::string cpu = "generic";
  std::string features = "";
  llvm::TargetOptions opt;
  std::optional<llvm::Reloc::Model> rm = std::nullopt;
  std::unique_ptr<llvm::TargetMachine> targetMachine(
      target->createTargetMachine(targetTriple, cpu, features, opt, rm));

  module->setDataLayout(targetMachine->createDataLayout());

  std::error_code EC;
  llvm::raw_fd_ostream dest(path, EC, llvm::sys::fs::OF_None);

  if (EC) {
    logger->LogError("Could not open file: " + EC.message());
    return false;
  }

  llvm::legacy::PassManager passManager;

  auto fileType = llvm::CGFT_ObjectFile;

  if (targetMachine->addPassesToEmitFile(passManager, dest, nullptr,
                                         fileType)) {
    logger->LogError("TargetMachine can't emit a file of this type");
    return false;
  }

  passManager.run(*module);
  dest.flush();

  return true;
}