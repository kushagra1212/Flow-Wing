#ifndef REPL_TEST_H
#define REPL_TEST_H
#include "../../../src/REPL/Repl.h"
#include <gtest/gtest.h>
#include <sstream>

class ReplTest : public ::testing::Test {
protected:
  void SetUp() override;

  void TearDown() override;

  // Common methods
  std::string runReplWithInput(const std::string &input);

  std::unique_ptr<Repl> repl;
};

#endif // REPL_TEST_H