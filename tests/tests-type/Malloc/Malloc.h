#ifndef __MALLOC_TEST_H__
#define __MALLOC_TEST_H__

#include "../../Common.h"

class Malloc : public ::testing::Test {
protected:
  Malloc();

  void SetUp() override;
  void TearDown() override;
  void setInput(const std::string &input);
  std::string getOutput() const;
  void runEvaluator();

  inline auto I(const std::string input) -> void {
    setInput(input);
    runEvaluator();
  }

  inline auto O(const std::string EXPECTED) -> void {
    EXPECT_EQ(getOutput(), EXPECTED);
  }

  std::unique_ptr<BaseTest> _test;
};
#endif // __MALLOC_TEST_H__