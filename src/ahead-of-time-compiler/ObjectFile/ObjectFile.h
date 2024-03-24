#ifndef __EXECUTABLE_H__
#define __EXECUTABLE_H__

#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/Module.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Target/TargetOptions.h"
#include "llvm/TargetParser/Host.h"

using namespace llvm;
using namespace llvm::sys;

class ObjectFile {
  std::string _fileName;

public:
  ObjectFile(std::string fileName) : _fileName(fileName) {}
  ~ObjectFile() = default;

  void writeModuleToFile(Module *module) {
    auto TargetTriple = getDefaultTargetTriple();

    std::string Error;
    auto Target = llvm::TargetRegistry::lookupTarget(TargetTriple, Error);
    auto CPU = "generic";
    auto Features = "";

    TargetOptions opt;

    auto TargetMachine = Target->createTargetMachine(
        TargetTriple, CPU, Features, opt, std::optional<Reloc::Model>());

    module->setDataLayout(TargetMachine->createDataLayout());
    module->setTargetTriple(TargetTriple);

    std::error_code EC;
    raw_fd_ostream dest(_fileName + ".o", EC, sys::fs::OF_None);

    legacy::PassManager pass;
    auto FileType = CGFT_ObjectFile;

    if (TargetMachine->addPassesToEmitFile(pass, dest, nullptr, FileType)) {
      errs() << "TargetMachine can't emit a file of this type";
      return;
    }
    pass.run(*module);
    dest.flush();
  }
};

#endif