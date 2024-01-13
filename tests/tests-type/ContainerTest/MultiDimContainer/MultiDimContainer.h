#ifndef __MULTIDIM__CONTAINER_TEST_H__
#define __MULTIDIM__CONTAINER_TEST_H__

#include "../../../JITCompilerTest/JITCompilerTest.h"
#include "../../../ReplTest/ReplTest.h"

class MultiDimContainer : public ::testing::Test {
 protected:
  MultiDimContainer();

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
#endif  // __MULTIDIM__CONTAINER_TEST_H__