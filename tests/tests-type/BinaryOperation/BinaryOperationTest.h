#ifndef BINARY_OPERATION_TESTS_H
#define BINARY_OPERATION_TESTS_H

#include "../../../src/just-in-time-compiler/JITCompiler.h"

#include "../../../src/REPL/Repl.h"
#include <gtest/gtest.h>
class BinaryOperationTest : public ::testing::Test {
protected:
  BinaryOperationTest();
  void SetUp() override;
  void TearDown() override;
  void setInput(const std::string &input);
  void runEvaluator();
  std::string getOutput() const;
  // Common methods

  std::unique_ptr<Repl> repl;

  std::stringstream input_stream;
  std::stringstream output_stream;
  std::streambuf *saved_cout_buf;
};
#endif // BINARY_OPERATION_H