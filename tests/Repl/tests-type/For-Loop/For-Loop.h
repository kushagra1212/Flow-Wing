#ifndef FOR_LOOP_TEST_H
#define FOR_LOOP_TEST_H
#include "../../../../src/REPL/Repl.h"
#include <gtest/gtest.h>
class ForLoopReplTest : public ::testing::Test {
protected:
  ForLoopReplTest();

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
#endif // FOR_LOOP_H