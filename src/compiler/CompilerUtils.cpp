#include "CompilerUtils.h"
#include <cstdlib>
#include <stdexcept>

namespace FlowWing {

namespace Compiler {

std::unique_ptr<llvm::MemoryBuffer>
getMemoryBuffer(const std::string &filePath,
                FlowWing::DiagnosticHandler *diagHandler) {
  if (auto bufferOrErr = llvm::MemoryBuffer::getFile(filePath)) {
    return std::move(*bufferOrErr);
  } else {
    diagHandler->printDiagnostic(
        std::cerr, Diagnostic("Error reading bitcode file: " + filePath + " " +
                                  bufferOrErr.getError().message(),
                              DiagnosticUtils::DiagnosticLevel::Error,
                              DiagnosticUtils::DiagnosticType::Linker,
                              DiagnosticUtils::SourceLocation()));
    throw std::runtime_error("Error reading bitcode file: " + filePath);
    return nullptr;
  }
}

std::vector<std::string>
getIRFilePaths(FlowWing::DiagnosticHandler *diagHandler,
               const std::string &directoryPath) {
  std::vector<std::string> irFilesPath = {};

#ifdef DEBUG
  irFilesPath =
      Utils::getAllFilesInDirectoryWithExtension(directoryPath, ".ll", false);
#else
  irFilesPath =
      Utils::getAllFilesInDirectoryWithExtension(directoryPath, ".bc", false);
#endif

  if (irFilesPath.size() == 0) {
    diagHandler->printDiagnostic(
        std::cerr,
        Diagnostic("No user defined IR files found. in " + directoryPath,
                   DiagnosticUtils::DiagnosticLevel::Error,
                   DiagnosticUtils::DiagnosticType::Linker,
                   DiagnosticUtils::SourceLocation(0, 0, 0, "")));
    return {};
  }

  return irFilesPath;
}

std::unique_ptr<llvm::Module>
createLLVMModuleFromCodeorIR(std::unique_ptr<llvm::LLVMContext> &TheContext,
                             FlowWing::DiagnosticHandler *diagHandler) {

  const std::string &filePath = LIB_BUILT_IN_MODULE_PATH;

#if defined(RELEASE)

  std::unique_ptr<llvm::Module> TheModule =
      std::move(createModuleFromBitcode(filePath, TheContext, diagHandler));
#else
  std::unique_ptr<llvm::Module> TheModule =
      isValidLLFile(filePath) == EXIT_SUCCESS
          ? std::move(createModuleFromIR(filePath, TheContext, diagHandler))
          : std::move(
                createModuleFromBitcode(filePath, TheContext, diagHandler));
#endif

  llvm::InitializeNativeTarget();
  llvm::InitializeNativeTargetAsmPrinter();
  llvm::InitializeNativeTargetAsmParser();

#if defined(__APPLE__)
  TheModule->setTargetTriple(llvm::sys::getDefaultTargetTriple());
#elif defined(__linux__)
  TheModule->setTargetTriple(
      llvm::Triple::normalize(llvm::sys::getDefaultTargetTriple()));
#endif

  return TheModule;
}

const int8_t isValidLLFile(const std::string &filePath) {
  if (filePath.length() <= 3) {
    throw std::runtime_error(filePath + " is not an valid file path");
    return EXIT_FAILURE;
  }

  if (Utils::hasFileExtenstion(filePath, "ll") == EXIT_SUCCESS) {
    return EXIT_SUCCESS;
  }

  if (Utils::hasFileExtenstion(filePath, "bc") == EXIT_SUCCESS) {
    return EXIT_FAILURE;
  }

  throw std::runtime_error(filePath + " is not an valid file path");
  return EXIT_FAILURE;
}

std::unique_ptr<llvm::Module>
getLinkedModule(std::unique_ptr<llvm::LLVMContext> &TheContext,
                FlowWing::DiagnosticHandler *diagHandler) {

  std::unique_ptr<llvm::Module> TheModule =
      std::move(FlowWing::Compiler::createLLVMModuleFromCodeorIR(TheContext,
                                                                 diagHandler));

  std::vector<std::string> filesPath = FlowWing::Compiler::getIRFilePaths(
      diagHandler, FLOWWING::IR::CONSTANTS::TEMP_BC_FILES_DIR);

//! Need to Include the built in .bc files for both DEBUG and Release
#if defined(RELEASE) && defined(JIT_MODE)

#endif

  for (const std::string &path : filesPath) {
    llvm::SMDiagnostic err;

    CODEGEN_DEBUG_LOG(" [INFO]: Linking " + path);

    bool LinkResult = llvm::Linker::linkModules(
        *TheModule.get(), llvm::parseIRFile(path, err, *TheContext.get()),
        llvm::Linker::Flags::OverrideFromSrc);
    if (LinkResult) {
      diagHandler->printDiagnostic(
          std::cerr,
          Diagnostic("Error linking " + path,
                     DiagnosticUtils::DiagnosticLevel::Error,
                     DiagnosticUtils::DiagnosticType::Linker,
                     DiagnosticUtils::SourceLocation(0, 0, 0, path)));
      return nullptr;
    }
  }

  CODEGEN_DEBUG_LOG(" [INFO]: Finished linking modules Done. ");

  return TheModule;
}

std::unique_ptr<llvm::Module>
createModuleFromIR(const std::string &filePath,
                   std::unique_ptr<llvm::LLVMContext> &TheContext,
                   FlowWing::DiagnosticHandler *diagHandler) {
  llvm::SMDiagnostic Err;
  std::unique_ptr<llvm::Module> TheModule =
      llvm::parseIRFile(filePath, Err, *TheContext);

  if (!TheModule) {
    diagHandler->printDiagnostic(
        std::cerr, Diagnostic("Error reading IR file: " + filePath,
                              DiagnosticUtils::DiagnosticLevel::Error,
                              DiagnosticUtils::DiagnosticType::Linker,
                              DiagnosticUtils::SourceLocation(0, 0, 0, "")));
    return nullptr;
  }

  return TheModule;
}

std::unique_ptr<llvm::Module>
createModuleFromBitcode(const std::string &filePath,
                        std::unique_ptr<llvm::LLVMContext> &TheContext,
                        FlowWing::DiagnosticHandler *diagHandler) {

  std::unique_ptr<llvm::MemoryBuffer> buffer =
      std::move(getMemoryBuffer(filePath, diagHandler));

  if (auto moduleOrErr =
          llvm::parseBitcodeFile(buffer->getMemBufferRef(), *TheContext)) {
    return std::move(*moduleOrErr);
  } else {
    diagHandler->printDiagnostic(
        std::cerr, Diagnostic("Error reading bitcode file: " + filePath,
                              DiagnosticUtils::DiagnosticLevel::Error,
                              DiagnosticUtils::DiagnosticType::Linker,
                              DiagnosticUtils::SourceLocation(0, 0, 0, "")));
    return nullptr;
  }
}

auto logNoErrorJSONIfAsked(const std::string &outputFilePath) -> void {
  if (Utils::getExtension(outputFilePath) == ".json") {
    JSON jsonObj = {{"error", false}};
    Utils::logJSON(jsonObj,
                   outputFilePath.substr(0, outputFilePath.find_last_of(".")) +
                       ".err.json");
  }
}

} // namespace Compiler

} // namespace FlowWing