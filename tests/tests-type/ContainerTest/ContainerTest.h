#ifndef __CONTAINER_TEST_H__
#define __CONTAINER_TEST_H__
#include <gtest/gtest.h>

#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>

#include "../../../src/REPL/Repl.h"
#include "../../BaseTest/BaseTest.h"
#include "../../JITCompilerTest/JITCompilerTest.h"
#include "../../ReplTest/ReplTest.h"
class ContainerTest : public ::testing::Test {
 protected:
  ContainerTest();

  void SetUp() override;
  void TearDown() override;
  void setInput(const std::string &input);
  std::string getOutput() const;
  void runEvaluator();

  std::unique_ptr<BaseTest> _test;
};
#endif  // __CONTAINER_TEST_H__