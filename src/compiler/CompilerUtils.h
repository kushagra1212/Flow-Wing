#include "../diagnostics/DiagnosticHandler/DiagnosticHandler.h"
#include "../utils/FlowWingConfig.h"
#include <cstdint>
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/IR/Module.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/Linker/Linker.h>
#include <llvm/Object/Archive.h>
#include <llvm/Object/Binary.h>
#include <llvm/Object/ObjectFile.h>
#include <llvm/Support/MemoryBuffer.h>
#include <llvm/Support/SourceMgr.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/TargetParser/Host.h>
#include <llvm/TargetParser/Triple.h>

namespace FlowWing {

namespace Compiler {

std::unique_ptr<llvm::MemoryBuffer>
getMemoryBuffer(const std::string &filePath,
                FlowWing::DiagnosticHandler *diagHandler);

std::vector<std::string>
getIRFilePaths(FlowWing::DiagnosticHandler *diagHandler,
               const std::string &directoryPath);

std::unique_ptr<llvm::Module>
createLLVMModuleFromCodeorIR(std::unique_ptr<llvm::LLVMContext> &TheContext,
                             FlowWing::DiagnosticHandler *diagHandler);

const int8_t isValidLLFile(const std::string &filePath);

std::unique_ptr<llvm::Module>
getLinkedModule(std::unique_ptr<llvm::LLVMContext> &TheContext,
                FlowWing::DiagnosticHandler *diagHandler);

//? Create Module

std::unique_ptr<llvm::Module>
createModuleFromIR(const std::string &filePath,
                   std::unique_ptr<llvm::LLVMContext> &TheContext,
                   FlowWing::DiagnosticHandler *diagHandler);

std::unique_ptr<llvm::Module>
createModuleFromBitcode(const std::string &filePath,
                        std::unique_ptr<llvm::LLVMContext> &TheContext,
                        FlowWing::DiagnosticHandler *diagHandler);

// Function to load the .a file into the ExecutionEngine
void loadArchiveIntoExecutionEngine(llvm::ExecutionEngine *executionEngine,
                                    const std::string &archivePath,
                                    FlowWing::DiagnosticHandler *diagHandler);

//? INLINE FUNCTIONS

// JSON LOG FILE for (AST/ERR)
void logNoErrorJSONIfAsked(const std::string &outputFilePath);

} // namespace Compiler
} // namespace FlowWing