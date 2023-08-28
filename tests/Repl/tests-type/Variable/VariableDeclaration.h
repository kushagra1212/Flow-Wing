#ifndef VARIABLE_DECLARATION_H
#define VARIABLE_DECLARATION_H
#include "../../../../src/REPL/Repl.h"
#include <algorithm> // For std::remove_if
#include <cctype>    // For std::isspace
#include <gtest/gtest.h>

class VariableDeclaration : public ::testing::Test {
protected:
  VariableDeclaration();

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