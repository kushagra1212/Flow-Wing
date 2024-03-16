#ifndef __OBJECT_GLOBAL_TEST_H__
#define __OBJECT_GLOBAL_TEST_H__

#include "../../../Common.h"

class ObjectGlobalTest : public ::testing::Test {
protected:
  ObjectGlobalTest();

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
#endif // __OBJECT_GLOBAL_TEST_H__