#ifndef FOR_LOOP_TEST_H
#define FOR_LOOP_TEST_H
#include "../../../../src/REPL/Repl.h"
#include <gtest/gtest.h>
class ForLoopReplTest : public ::testing::Test {
protected:
  ForLoopReplTest();

  void SetUp() override;

  void TearDown() override;

  // Common methods
  std::string runReplWithInput(const std::string &input);

  std::string runReplWithInputPrint(std::string input);
  std::unique_ptr<Repl> repl;
  std::stringstream captured_output;
  std::streambuf *cout_backup;
};
#endif // FOR_LOOP_H