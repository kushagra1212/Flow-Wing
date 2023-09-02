#ifndef IN_BUILT_FUNCTIONS_H
#define IN_BUILT_FUNCTIONS_H
#include "../../../src/REPL/Repl.h"
#include <gtest/gtest.h>

class InBuiltFunction : public ::testing::Test {
protected:
  InBuiltFunction();

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

#endif // IN_BUILT_FUNCTIONS_H