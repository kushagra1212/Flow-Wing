#ifndef WHILE_LOOP_H
#define WHILE_LOOP_H

#include "../../JITCompilerTest/JITCompilerTest.h"
#include "../../ReplTest/ReplTest.h"

class WhileLoop : public ::testing::Test {
 protected:
  WhileLoop();

  void SetUp() override;
  void TearDown() override;
  void setInput(const std::string &input);
  std::string getOutput() const;
  void runEvaluator();

  std::unique_ptr<BaseTest> _test;
};
#endif  // VARIABLE_DECLARATION_H