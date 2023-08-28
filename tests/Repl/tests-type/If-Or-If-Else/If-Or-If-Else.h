#ifndef IF_OR_IF_ELSE_H
#define IF_OR_IF_ELSE_H

#include "../../../../src/REPL/Repl.h"
#include <gtest/gtest.h>

class IfORIFELSEReplTest : public ::testing::Test {
protected:
  IfORIFELSEReplTest();

  void SetUp() override;

  void TearDown() override;

  // Common methods
  std::string runReplWithInput(const std::string &input);

  std::string runReplWithInputPrint(std::string input);

  std::unique_ptr<Repl> repl;
  std::stringstream captured_output;
  std::streambuf *cout_backup;
};

#endif // VARIABLE_DECLARATION_H