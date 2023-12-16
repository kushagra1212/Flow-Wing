#ifndef LLFILESAVESTRATEGY_H
#define LLFILESAVESTRATEGY_H

#include "../../../logger/LLVMLogger.h"
#include "../FileSaveStrategy.h"
#include <llvm/IR/Module.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/raw_ostream.h>

class LLFileSaveStrategy
    : public FileSaveStrategy<llvm::Module *, LLVMLogger *> {
public:
  LLFileSaveStrategy(LLVMLogger *llvmLogger);
  bool saveToFile(const std::string &path, llvm::Module *module) const override;
};

#endif // LLFILESAVESTRATEGY_H