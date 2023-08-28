#ifndef WHILE_LOOP_H
#define WHILE_LOOP_H
#include "../../../../src/REPL/Repl.h"
#include <gtest/gtest.h>

class WhileLoop : public ::testing::Test {
protected:
  WhileLoop();

  void SetUp() override;

  void TearDown() override;

  // Common methods
  std::string runReplWithInput(const std::string &input);

  std::string runReplWithInputPrint(std::string input);

  std::unique_ptr<Repl> repl;
  std::stringstream captured_output;
  std::streambuf *cout_backup;
};
#endif // VARIABLE_DECLARATION_H