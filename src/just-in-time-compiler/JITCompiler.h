#ifndef JITCOMPILER_H
#define JITCOMPILER_H

#include "../evaluator/llvm/IRGenerator.h"
#include "../parser/Parser.h"

#include <fstream>
#include <gtest/gtest.h>
#include <iostream>

class JITCompiler {
  std::string _filePath;

public:
  JITCompiler(std::string filePath = "");
  ~JITCompiler();
  void compile(std::vector<std::string> &text, std::ostream &outputStream);
  void runTests(std::istream &inputStream, std::ostream &outputStream);
  std::vector<std::string> text = std::vector<std::string>();
};

#endif // JITCOMPILER_H