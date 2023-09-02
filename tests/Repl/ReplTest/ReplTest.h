#ifndef REPL_TEST_H
#define REPL_TEST_H
#include "../../../src/REPL/Repl.h"
#include <gtest/gtest.h>
#include <sstream>

class ReplTest : public ::testing::Test {
protected:
  ReplTest();

  void SetUp() override;
  void TearDown() override;
  void setInput(const std::string &input);
  std::string getOutput() const;
  void runEvaluator();

  // Common methods
  Repl *repl;
  std::stringstream input_stream;
  std::stringstream output_stream;
  std::streambuf *saved_cout_buf;
};

#endif // REPL_TEST_H