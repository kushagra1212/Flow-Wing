#ifndef BINARY_OPERATION_TESTS_H
#define BINARY_OPERATION_TESTS_H

#include "../../../src/REPL/Repl.h"
#include "../../BaseTest/BaseTest.h"
#include "../../JITCompilerTest/JITCompilerTest.h"
#include "../../ReplTest/ReplTest.h"

class BinaryOperationTest : public ::testing::Test {
 protected:
  BinaryOperationTest();
  void SetUp() override;
  void TearDown() override;
  void setInput(const std::string &input);
  void runEvaluator();
  std::string getOutput() const;

  std::unique_ptr<BaseTest> _test;
};
#endif  // BINARY_OPERATION_H