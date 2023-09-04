#ifndef USER_FUNCTIONS_H
#define USER_FUNCTIONS_H
#include "../../../src/REPL/Repl.h"
#include "../../BaseTest/BaseTest.h"
#include "../../JITCompilerTest/JITCompilerTest.h"
#include "../../ReplTest/ReplTest.h"
#include <cstdio>
#include <gtest/gtest.h>
#include <iostream>
#include <sstream>
#include <string>
class Function : public ::testing::Test {
protected:
  Function();

  void SetUp() override;
  void TearDown() override;
  void setInput(const std::string &input);
  std::string getOutput() const;
  void runEvaluator();

  std::unique_ptr<BaseTest> _test;
};

#endif // IN_BUILT_FUNCTIONS_H