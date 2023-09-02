#ifndef IF_OR_IF_ELSE_H
#define IF_OR_IF_ELSE_H

#include "../../../src/REPL/Repl.h"
#include "../../BaseTest/BaseTest.h"
#include "../../JITCompilerTest/JITCompilerTest.h"
#include "../../ReplTest/ReplTest.h"
class IfORIFELSEReplTest : public ::testing::Test {
protected:
  IfORIFELSEReplTest();

  void SetUp() override;
  void TearDown() override;
  void setInput(const std::string &input);
  std::string getOutput() const;
  void runEvaluator();

  std::unique_ptr<BaseTest> _test;
};

#endif // VARIABLE_DECLARATION_H