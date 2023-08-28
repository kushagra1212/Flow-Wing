#ifndef IN_BUILT_FUNCTIONS_H
#define IN_BUILT_FUNCTIONS_H
#include "../../../../src/REPL/Repl.h"
#include <gtest/gtest.h>

class InBuiltFunction : public ::testing::Test {
protected:
  InBuiltFunction();

  void SetUp() override;

  void TearDown() override;

  // Common methods
  std::string runReplWithInput(const std::string &input);

  std::string runReplWithInputPrint(std::string input);

  std::unique_ptr<Repl> repl;
  std::stringstream captured_output;
  std::streambuf *cout_backup;
};

#endif // IN_BUILT_FUNCTIONS_H