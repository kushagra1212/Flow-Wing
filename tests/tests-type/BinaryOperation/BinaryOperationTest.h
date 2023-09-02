#ifndef BINARY_OPERATION_TESTS_H
#define BINARY_OPERATION_TESTS_H

#include "../../../src/REPL/Repl.h"
#include <gtest/gtest.h>
class BinaryOperationTest : public ::testing::Test {
protected:
  void SetUp() override;
  void TearDown() override;
  void setInput(const std::string &input);
  std::string getOutput() const;
  void runEvaluator();

  // Common methods
  std::stringstream input_stream;
  std::stringstream output_stream;
  std::streambuf *saved_cout_buf;
};
#endif // BINARY_OPERATION_H