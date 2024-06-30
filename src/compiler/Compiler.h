#ifndef __FLOW__WING__COMPILER__H__
#define __FLOW__WING__COMPILER__H__

#include <gtest/gtest.h>

#include <fstream>
#include <iostream>

#include "../IR/IRGenerator.h"
#include "../IR/utils/fileSaver/ll-file/LLFileSaveStrategy.h"
#include "../cli/commandLineOptions/commandLineOptions.h"
#include "../parser/Parser.h"
#include "../utils/Utils.h"
class Compiler {
public:
  Compiler(std::string filePath = "");

  void compile(std::vector<std::string> &text, std::ostream &outputStream);
  void runTests(std::istream &inputStream, std::ostream &outputStream);

  const std::string getBuiltInModulePath() const;
  std::unique_ptr<llvm::MemoryBuffer> getMemoryBuffer(std::string filePath);
  std::vector<std::string> getIRFilePaths() const;

  std::unique_ptr<llvm::Module>
  getLinkedModule(std::unique_ptr<llvm::LLVMContext> &TheContext);

  std::unique_ptr<llvm::Module>
  createModuleFromBitcode(const std::string &filePath,
                          std::unique_ptr<llvm::LLVMContext> &TheContext);

  std::unique_ptr<llvm::Module>
  createModuleFromIR(const std::string &filePath,
                     std::unique_ptr<llvm::LLVMContext> &TheContext);

  inline auto setOutputFilePath(const std::string &outputFilePath) {
    _outputFilePath = outputFilePath;
  }
  void link();
  virtual void execute() = 0;

  auto inline getClangFilePath() -> std::filesystem::path {
    std::filesystem::path CLANG_PATH = "";

#if defined(__linux__)
    CLANG_PATH = "/usr/bin/clang-17";
#elif defined(__APPLE__)
    CLANG_PATH = "/usr/bin/clang";
#endif

    return CLANG_PATH;
  }

  auto inline getLibPath() -> std::filesystem::path {
    std::filesystem::path LIB_PATH = "";

#if defined(__linux__)
    LIB_PATH = "/usr/local/lib/FlowWing";
#elif defined(__APPLE__)
    LIB_PATH = "/Users/apple/code/per/Flow-Wing/lib/mac-silicon/lib";
#endif

    return LIB_PATH;
  }

  auto inline getObjectFilesJoinedAsString() -> std::string {

    std::vector<std::string> objectFiles =
        Utils::getAllFilesInDirectoryWithExtension(
            FLOWWING::IR::CONSTANTS::TEMP_OBJECT_FILES_DIR, ".o", false);
    std::string joined = "";
    for (const auto &objectFile : objectFiles) {
      joined += objectFile + " ";
    }
    return joined;
  }

  auto inline deleteObjectFiles() -> void {
    std::vector<std::string> objectFiles =
        Utils::getAllFilesInDirectoryWithExtension(
            FLOWWING::IR::CONSTANTS::TEMP_OBJECT_FILES_DIR, ".o", false);
    for (const auto &objectFile : objectFiles) {
      std::filesystem::remove(objectFile);
    }
  }

  std::string _filePath;
  std::string _outputFilePath;
  std::unique_ptr<LLFileSaveStrategy> llFileSaveStrategy;
  std::vector<std::string> text = std::vector<std::string>();
  std::string executable_directory_string;
  std::unique_ptr<FLowWing::DiagnosticHandler> _currentDiagnosticHandler;
  llvm::ExecutionEngine *executionEngine;
  std::filesystem::path _executable_path = std::filesystem::current_path();

  //! Version
  FlowWingCliOptions::Option<bool> Version;
  FlowWingCliOptions::Option<bool> ShortVersion;

  //! File
  FlowWingCliOptions::Option<std::string> File;
  FlowWingCliOptions::Option<std::string> ShortFile;

  //! Format
  FlowWingCliOptions::Option<bool> Format;
  FlowWingCliOptions::Option<bool> ShortFormat;

  //! Format Print
  FlowWingCliOptions::Option<bool> FormatPrint;
  FlowWingCliOptions::Option<bool> ShortFormatPrint;
};

#endif // __FLOW__WING__COMPILER__H__