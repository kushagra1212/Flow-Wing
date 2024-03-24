#ifndef FOR_LOOP_TEST_H
#define FOR_LOOP_TEST_H

#include "../../Common.h"

class ForLoopReplTest : public ::testing::Test {
protected:
  ForLoopReplTest();

  void SetUp() override;
  void TearDown() override;
  void setInput(const std::string &input);
  std::string getOutput() const;
  void runEvaluator();

  std::unique_ptr<BaseTest> _test;
};
#endif // FOR_LOOP_H