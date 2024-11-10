#include "JITCompiler.h"
#include "../../common/version.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/IR/AssemblyAnnotationWriter.h"
#include "llvm/IR/Verifier.h"
#include <cstdint>
#include <iostream>
#include <string>

JITCompiler::JITCompiler(std::string filePath) : Compiler(filePath) {}

void JITCompiler::execute() {
  std::unique_ptr<llvm::LLVMContext> TheContext =
      std::make_unique<llvm::LLVMContext>();
  std::unique_ptr<llvm::IRBuilder<>> Builder =
      std::make_unique<llvm::IRBuilder<>>(*TheContext);

  std::unique_ptr<llvm::Module> TheModule =
      std::move(FlowWing::Compiler::getLinkedModule(
          TheContext, _currentDiagnosticHandler.get()));

  DEBUG_LOG("Finished getting linked module");

  DEBUG_LOG("Getting main function: ", FLOWWING_GLOBAL_ENTRY_POINT);
  llvm::Function *mainFunction =
      TheModule->getFunction(FLOWWING_GLOBAL_ENTRY_POINT);
  DEBUG_LOG("Finished getting main function");

  TheModule->print(llvm::outs(), nullptr);
  std::string errorMessage;
#if defined(DEBUG)
  char **_out_message = nullptr;
  LLVMVerifyModule(wrap(TheModule.get()),
                   LLVMVerifierFailureAction::LLVMPrintMessageAction,
                   _out_message);

  if (_out_message) {
    _currentDiagnosticHandler->printDiagnostic(
        std::cout,
        Diagnostic("[FATAL]: Corrupted Module: " + std::string(*_out_message),
                   DiagnosticUtils::DiagnosticLevel::Error,
                   DiagnosticUtils::DiagnosticType::Linker,
                   DiagnosticUtils::SourceLocation(0, 0, 0, "")));
    return;
  }
#endif

  DEBUG_LOG("Creating Execution Engine");

  executionEngine = llvm::EngineBuilder(std::move(TheModule))
                        .setErrorStr(&errorMessage)
                        .setEngineKind(llvm::EngineKind::Kind::JIT)
                        .setOptLevel(llvm::CodeGenOpt::Less)
                        .create();

  DEBUG_LOG("Finished creating Execution Engine");
  //! TODO: add support for linking libraries
  // const auto allArchivesFiles = Utils::getAllFilesInDirectoryWithExtension(
  //     (FLOWWING_LIB_PATH), ".a", false);

  // for (const auto &archivePath : allArchivesFiles) {
  //   FlowWing::Compiler::loadArchiveIntoExecutionEngine(
  //       executionEngine, archivePath, _currentDiagnosticHandler.get());
  // }
  if (!executionEngine) {
    _currentDiagnosticHandler->printDiagnostic(
        std::cout,
        Diagnostic("Failed to create Execution Engine: " + errorMessage,
                   DiagnosticUtils::DiagnosticLevel::Error,
                   DiagnosticUtils::DiagnosticType::Linker,
                   DiagnosticUtils::SourceLocation(0, 0, 0, "")));
    return;
  }

  if (!mainFunction) {
    _currentDiagnosticHandler->printDiagnostic(
        std::cout, Diagnostic("Function not found in module.",
                              DiagnosticUtils::DiagnosticLevel::Error,
                              DiagnosticUtils::DiagnosticType::Linker,
                              DiagnosticUtils::SourceLocation(0, 0, 0, "")));
    return;
  }

  DEBUG_LOG("Getting return type");
  llvm::Type *returnType = mainFunction->getReturnType();
  llvm::GenericValue resultValue = llvm::GenericValue();

  DEBUG_LOG("Running function");
  int8_t hasError = 1;
  try {
    resultValue = executionEngine->runFunction(mainFunction, {});
    DEBUG_LOG("Finished running function");
    if (returnType->isIntegerTy()) {
      hasError = (resultValue.IntVal != 0) ? 1 : 0;
    }
  } catch (const std::exception &e) {
    std::cerr << e.what();
    _currentDiagnosticHandler->printDiagnostic(
        std::cout, Diagnostic("Error executing function.",
                              DiagnosticUtils::DiagnosticLevel::Error,
                              DiagnosticUtils::DiagnosticType::Linker,
                              DiagnosticUtils::SourceLocation(
                                  0, 0, 0, FLOWWING_GLOBAL_ENTRY_POINT)));
  }
}

#if defined(JIT_MODE) || defined(JIT_TEST_MODE)

void signalHandler(int signal) {
  // Output information about the signal:

  std::cerr << RED_TEXT << "Signal " << signal << " (" << strsignal(signal)
            << ") received." << RESET << std::endl;

  exit(1); // Exit with a non-zero status to indicate an error.
}

#endif

#ifdef JIT_TEST_MODE

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  signal(SIGSEGV, signalHandler);
  return RUN_ALL_TESTS();
}

#elif JIT_MODE

int main(int argc, char *argv[]) {
  Utils::enableAnsiCodes();
  signal(SIGSEGV, signalHandler);

  argh::parser _cmdl(argv);

  FlowWing::Cli::cmdl = &(_cmdl);

  auto basicArgStatus = FlowWing::Cli::handleBasicArgs();

  if (basicArgStatus == FlowWing::Cli::STATUS::DONE) {
    return EXIT_SUCCESS;
  }

  if (basicArgStatus == FlowWing::Cli::STATUS::FAILURE) {
    return EXIT_FAILURE;
  }

  std::vector<std::string> text = {};

  std::string filePath = "";

  auto status = FlowWing::Cli::handleFileArgs(text, filePath, argv);

  if (status == FlowWing::Cli::STATUS::DONE) {
    return EXIT_SUCCESS;
  }

  if (status == FlowWing::Cli::STATUS::FAILURE) {
    return EXIT_FAILURE;
  }

  std::unique_ptr<JITCompiler> jitCompiler =
      std::make_unique<JITCompiler>(filePath);

  jitCompiler->_executable_path = std::filesystem::path(argv[0]);
  jitCompiler->compile(text, std::cout);

  return EXIT_SUCCESS;
}

#endif
