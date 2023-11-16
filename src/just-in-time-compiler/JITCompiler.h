#ifndef JITCOMPILER_H
#define JITCOMPILER_H

#include "../IR/IRGenerator.h"
#include "../parser/Parser.h"
#include "../utils/Utils.h"
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
  void execute();
  std::vector<std::string> text = std::vector<std::string>();
};

#endif // JITCOMPILER_H