#ifndef IF_OR_IF_ELSE_H
#define IF_OR_IF_ELSE_H

#include "../../../../src/REPL/Repl.h"
#include <gtest/gtest.h>

class IfORIFELSEReplTest : public ::testing::Test {
protected:
  IfORIFELSEReplTest();

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
};

#endif // VARIABLE_DECLARATION_H