#ifndef USER_FUNCTIONS_H
#define USER_FUNCTIONS_H

#include "../../Common.h"

namespace FlowWing {
class Function : public ::testing::Test {
protected:
  Function();

  void SetUp() override;
  void TearDown() override;
  void setInput(const std::string &input);
  std::string getOutput() const;
  void runEvaluator();

  std::unique_ptr<BaseTest> _test;
};
} // namespace FlowWing

#endif // IN_BUILT_FUNCTIONS_H