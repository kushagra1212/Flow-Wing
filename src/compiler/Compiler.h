#ifndef COMPILER_H
#define COMPILER_H

#include "../Common.h"
#include "../evaluator/Evaluator.h"
#include "../parser/Parser.h"
#include "../utils/Utils.h"

class Compiler {
private:
  std::vector<std::string> _text = std::vector<std::string>();

public:
  Compiler();

  void compile(const std::vector<std::string> &text);
  ~Compiler();
};

#endif // COMPILER_H