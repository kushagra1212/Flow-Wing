#ifndef __JIT__FUNCTION_TEST_H__
#define __JIT__FUNCTION_TEST_H__

#include "../../../JITCompilerTest/JITCompilerTest.h"
#include "../../../ReplTest/ReplTest.h"

class JITFunction : public ::testing::Test {
 protected:
  JITFunction();

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
#endif  // __JIT__FUNCTION_TEST_H__