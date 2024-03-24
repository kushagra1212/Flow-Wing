#ifndef COMMENT_TEST_H
#define COMMENT_TEST_H

#include "../../Common.h"

class CommentTest : public ::testing::Test {
protected:
  CommentTest();

  void SetUp() override;
  void TearDown() override;
  void setInput(const std::string &input);
  std::string getOutput() const;
  void runEvaluator();

  std::unique_ptr<BaseTest> _test;
};
#endif // FOR_LOOP_H