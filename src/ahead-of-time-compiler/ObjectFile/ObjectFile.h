#ifndef __EXECUTABLE_H__
#define __EXECUTABLE_H__

#include <llvm/ADT/APInt.h>
#include <llvm/ADT/StringRef.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/IRPrintingPasses.h>
#include <llvm/IR/InstrTypes.h>
#include <llvm/IR/Instruction.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Verifier.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/Support/Error.h>
#include <llvm/Support/MemoryBuffer.h>
#include <llvm/Support/SourceMgr.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Transforms/Utils/Cloning.h>

#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/PassManager.h"
#include "llvm/IR/Type.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Pass.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Target/TargetOptions.h"
#include "llvm/TargetParser/Host.h"
#include "llvm/Transforms/Scalar.h"
// ExecutionEngine
#include "llvm-c/Analysis.h"
#include "llvm-c/BitWriter.h"
#include "llvm-c/Core.h"
#include "llvm-c/TargetMachine.h"
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/ExecutionEngine/Interpreter.h>
#include <llvm/ExecutionEngine/MCJIT.h>
#include <llvm/ExecutionEngine/SectionMemoryManager.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IR/Module.h>
#include <llvm/Linker/Linker.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/SourceMgr.h>

#include "llvm//IR/Value.h"
#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/GenericValue.h"
#include "llvm/ExecutionEngine/Interpreter.h"
#include "llvm/ExecutionEngine/Orc/CompileUtils.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/PassManager.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/ManagedStatic.h"
#include "llvm/Support/Signals.h"
#include "llvm/Support/raw_ostream.h"
// JIT
#include "../../Common.h"
#include <llvm/ExecutionEngine/Orc/LLJIT.h>
#include <llvm/Support/raw_ostream.h>

using namespace llvm;
using namespace llvm::sys;

class ObjectFile {

public:
  ~ObjectFile() = default;

  void writeModuleToFile(Module &module, TargetMachine *targetMachine,
                         const std::string &fileName) {
    auto TargetTriple = module.getTargetTriple();

    std::string Error;
    auto Target = llvm::TargetRegistry::lookupTarget(TargetTriple, Error);

    if (Error.size() > 0) {
      errs() << "Error looking up target: " << Error;
      return;
    }

    llvm::sys::fs::create_directories(
        FLOWWING::IR::CONSTANTS::TEMP_OBJECT_FILES_DIR);

    llvm::sys::fs::create_directories(FLOWWING::IR::CONSTANTS::TEMP_BIN_DIR);

    const std::string destPath =
        FLOWWING::IR::CONSTANTS::TEMP_OBJECT_FILES_DIR + fileName + ".o";

    DEBUG_LOG("Writing object file to: " + destPath);

    std::error_code EC;
    raw_fd_ostream dest(destPath, EC, sys::fs::OF_None);

    if (EC) {
      errs() << "Could not open file: " << EC.message();
      return;
    }

    llvm::legacy::PassManager pass = legacy::PassManager();

    pass.add(createVerifierPass());
    pass.add(createCFGSimplificationPass());
    pass.add(createDeadCodeEliminationPass());

    auto FileType = CodeGenFileType::CGFT_ObjectFile;

    if (targetMachine->addPassesToEmitFile(pass, dest, nullptr, FileType)) {
      errs() << "TargetMachine can't emit a file of this type";
      return;
    }
    pass.run(module);
    dest.flush();
  }

  void writeModuleToFile(const Module *_module, const std::string &fileName) {

    LLVMModuleRef module = wrap(_module);

    char *errors = 0;
    LLVMTargetRef target;
    LLVMGetTargetFromTriple(LLVMGetDefaultTargetTriple(), &target, &errors);
    // printf("error: %s\n", errors);
    // LLVMPrintModuleToFile(module, "module.txt", &errors);
    // printf("error: %s\n", errors);
    LLVMDisposeMessage(errors);

    //  LLVMInitializeAllTargetInfos();
    //   LLVMInitializeAllTargets();
    //   LLVMInitializeAllTargetMCs();
    //   LLVMInitializeAllAsmParsers();
    //   LLVMInitializeAllAsmPrinters();

    LLVMGetTargetFromTriple(LLVMGetDefaultTargetTriple(), &target, &errors);

    if (errors) {
      errs() << "error: " << errors;
      LLVMDisposeMessage(errors);
      return;
    }

    LLVMDisposeMessage(errors);

    CODEGEN_DEBUG_LOG("Target Name: ", LLVMGetTargetName(target));

    CODEGEN_DEBUG_LOG("Target Description: ", LLVMGetTargetDescription(target));

    CODEGEN_DEBUG_LOG("Target Has JIT: ", LLVMTargetHasJIT(target));

    CODEGEN_DEBUG_LOG("Target Has Target Machine: ",
                      LLVMTargetHasTargetMachine(target));

    CODEGEN_DEBUG_LOG("Triple: ", LLVMGetDefaultTargetTriple());

    CODEGEN_DEBUG_LOG("Features: ", LLVMGetHostCPUFeatures());

    LLVMTargetMachineRef machine = LLVMCreateTargetMachine(
        target, LLVMGetDefaultTargetTriple(), LLVMGetHostCPUName(),
        LLVMGetHostCPUFeatures(), LLVMCodeGenLevelDefault,
        LLVMRelocMode::LLVMRelocPIC, LLVMCodeModel::LLVMCodeModelDefault);

    LLVMSetTarget(module, LLVMGetDefaultTargetTriple());
    LLVMTargetDataRef datalayout = LLVMCreateTargetDataLayout(machine);
    char *datalayout_str = LLVMCopyStringRepOfTargetData(datalayout);

    CODEGEN_DEBUG_LOG("datalayout: ", datalayout_str);

    LLVMSetDataLayout(module, datalayout_str);
    LLVMDisposeMessage(datalayout_str);

    llvm::sys::fs::create_directories(
        FLOWWING::IR::CONSTANTS::TEMP_OBJECT_FILES_DIR);

    llvm::sys::fs::create_directories(FLOWWING::IR::CONSTANTS::TEMP_BIN_DIR);

    std::string destPath =
        FLOWWING::IR::CONSTANTS::TEMP_OBJECT_FILES_DIR + fileName + ".o";

    CODEGEN_DEBUG_LOG("Writing object file to: " + destPath);

    LLVMTargetMachineEmitToFile(machine, module, (char *)destPath.c_str(),
                                LLVMObjectFile, &errors);

    LLVMDisposeMessage(errors);
  }
};

#endif