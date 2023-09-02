#ifndef JITCOMPILER_H
#define JITCOMPILER_H

#include "../evaluator/llvm/IRGenerator.h"
#include "../parser/Parser.h"
#include <fstream>
#include <iostream>

class JITCompiler {
public:
  JITCompiler();
  ~JITCompiler();
  void compile(std::vector<std::string> &text, std::ostream &outputStream);
};

#endif // JITCOMPILER_H