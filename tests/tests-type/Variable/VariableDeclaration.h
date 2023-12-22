#ifndef VARIABLE_DECLARATION_H
#define VARIABLE_DECLARATION_H
#include "../../../src/REPL/Repl.h"
#include "../../BaseTest/BaseTest.h"
#include "../../JITCompilerTest/JITCompilerTest.h"
#include "../../ReplTest/ReplTest.h"

class VariableDeclaration : public ::testing::Test {
protected:
  VariableDeclaration();
  void SetUp() override;
  void TearDown() override;
  void setInput(const std::string &input);
  std::string getOutput() const;
  void runEvaluator();

  std::unique_ptr<BaseTest> _test;
};
#endif // VARIABLE_DECLARATION_H