#ifndef __MDC_FUNCTION_TEST_H__
#define __MDC_FUNCTION_TEST_H__
#include "../../../../../src/REPL/Repl.h"
#include "../../../../BaseTest/BaseTest.h"
#include "../../../../JITCompilerTest/JITCompilerTest.h"
#include "../../../../ReplTest/ReplTest.h"

class MDCInFunction : public ::testing::Test {
protected:
  MDCInFunction();

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
#endif // __MDC_FUNCTION_TEST_H__