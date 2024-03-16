#ifndef __FLOW__WING__COMPILER__H__
#define __FLOW__WING__COMPILER__H__

#include <gtest/gtest.h>

#include <fstream>
#include <iostream>

#include "../IR/IRGenerator.h"
#include "../IR/utils/fileSaver/ll-file/LLFileSaveStrategy.h"
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

  virtual void execute() = 0;

  std::string _filePath;
  std::unique_ptr<LLFileSaveStrategy> llFileSaveStrategy;
  std::vector<std::string> text = std::vector<std::string>();
  std::string executable_directory_string;
  std::unique_ptr<FLowWing::DiagnosticHandler> _currentDiagnosticHandler;
  llvm::ExecutionEngine *executionEngine;
  std::filesystem::path _executable_path = std::filesystem::current_path();
};

#endif // __FLOW__WING__COMPILER__H__