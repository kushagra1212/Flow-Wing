#ifndef __MISCELLANEOUSTEST_H__
#define __MISCELLANEOUSTEST_H__

#include "../Common.h"

class MiscellaneousTest : public ::testing::Test {
protected:
  MiscellaneousTest();

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
#endif // __MISCELLANEOUSTEST_H__