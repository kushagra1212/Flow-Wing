#ifndef __BRINGTEST_H__
#define __BRINGTEST_H__

#include "../Common.h"

class BringTest : public ::testing::Test {
protected:
  BringTest();

  void SetUp() override;
  void TearDown() override;
  void setInput(const std::string &input);
  std::string getOutput() const;
  void runEvaluator();
  void writeFile(const std::string &filename, const std::string &code);
  std::string createBuildAndRunCmd(const std::string &fileName);

  inline auto I(const std::string input) -> void {
    setInput(input);
    runEvaluator();
  }

  inline auto O(const std::string EXPECTED) -> void {
    EXPECT_EQ(getOutput(), EXPECTED);
  }

  std::unique_ptr<BaseTest> _test;
  std::filesystem::path currentPath = std::filesystem::current_path();
};
#endif // __BRINGTEST_H__