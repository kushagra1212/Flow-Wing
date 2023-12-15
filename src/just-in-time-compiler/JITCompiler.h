#ifndef JITCOMPILER_H
#define JITCOMPILER_H

#include "../IR/IRGenerator.h"
#include "../IR/utils/fileSaver/ll-file/LLFileSaveStrategy.h"
#include "../parser/Parser.h"
#include "../utils/Utils.h"
#include <fstream>
#include <gtest/gtest.h>
#include <iostream>

class JITCompiler {
  std::string _filePath;
  std::unique_ptr<LLFileSaveStrategy> llFileSaveStrategy;

public:
  std::string executable_directory_string;
  JITCompiler(std::string filePath = "");
  ~JITCompiler();
  void compile(std::vector<std::string> &text, std::ostream &outputStream);
  void runTests(std::istream &inputStream, std::ostream &outputStream);
  void execute();
  std::vector<std::string> text = std::vector<std::string>();
};

#endif // JITCOMPILER_H