#ifndef __FLOW_WING__O__FILE__SAVE__STRATEGY__H__
#define __FLOW_WING__O__FILE__SAVE__STRATEGY__H__

#include "../../../logger/LLVMLogger.h"
#include "../FileSaveStrategy.h"
#include <llvm/CodeGen/CommandFlags.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IR/Module.h>
#include <llvm/MC/TargetRegistry.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/ToolOutputFile.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/Transforms/IPO.h>

class OFileSaveStrategy
    : public FileSaveStrategy<llvm::Module *, LLVMLogger *> {
public:
  OFileSaveStrategy(LLVMLogger *llvmLogger);
  bool saveToFile(const std::string &path, llvm::Module *module) const override;
};

#endif // __FLOW_WING__O__FILE__SAVE__STRATEGY__H__