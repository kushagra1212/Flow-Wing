#ifndef __FLOW_WING__BC__FILE__SAVE__STRATEGY__H__
#define __FLOW_WING__BC__FILE__SAVE__STRATEGY__H__

#include "../../../logger/LLVMLogger.h"
#include "../FileSaveStrategy.h"
#include <llvm/Bitcode/BitcodeWriter.h>
#include <llvm/IR/Module.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/raw_ostream.h>

class BCFileSaveStrategy
    : public FileSaveStrategy<llvm::Module *, LLVMLogger *> {
public:
  BCFileSaveStrategy(LLVMLogger *llvmLogger);
  bool saveToFile(const std::string &path, llvm::Module *module) const override;
};

#endif // __FLOW_WING__BC__FILE__SAVE__STRATEGY__H__