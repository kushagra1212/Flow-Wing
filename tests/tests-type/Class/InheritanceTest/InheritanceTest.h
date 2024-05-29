#ifndef __INHERITANCE_TEST_H__
#define __INHERITANCE_TEST_H__

#include "../../../Common.h"

class InheritanceTest : public ::testing::Test {
protected:
  InheritanceTest();

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
#endif // __INHERITANCE_TEST_H__