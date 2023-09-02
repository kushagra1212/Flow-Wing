#ifndef WHILE_LOOP_H
#define WHILE_LOOP_H
#include "../../../../src/REPL/Repl.h"
#include <gtest/gtest.h>

class WhileLoop : public ::testing::Test {
protected:
  WhileLoop();

  void SetUp() override;
  void TearDown() override;
  void setInput(const std::string &input);
  std::string getOutput() const;
  void runEvaluator();

  // Common methods
  Repl *repl;
  std::stringstream input_stream;
  std::stringstream output_stream;
  std::streambuf *saved_cout_buf;
  std::stringstream captured_output;
  std::streambuf *cout_backup;
};
#endif // VARIABLE_DECLARATION_H