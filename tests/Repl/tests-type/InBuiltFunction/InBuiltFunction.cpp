#include "InBuiltFunction.h"

/*                                                              PRINT FUNCTION
 */

TEST_F(ReplTest, BasicPrintFunctionNumber) {
  std::string input = "print(2)";

  std::string expected_output = "2\n";
  expected_output += "\n";
  std::string capturedOutput = runReplWithInputPrint(input);

  EXPECT_EQ(capturedOutput, expected_output);
}

TEST_F(ReplTest, BasicPrintFunctionNumberInsideScope) {
  std::string input = "{ print(2) }";

  std::string expected_output = "2\n";
  expected_output += "\n";
  std::string capturedOutput = runReplWithInputPrint(input);

  EXPECT_EQ(capturedOutput, expected_output);
}

TEST_F(ReplTest, BasicPrintFunctionString) {
  std::string input = "{ print(\"Hello\") }";

  std::string expected_output = "Hello\n";
  expected_output += "\n";
  std::string capturedOutput = runReplWithInputPrint(input);

  EXPECT_EQ(capturedOutput, expected_output);
}

TEST_F(ReplTest, BasicPrintFunctionStringBasicOperation) {
  std::string input = R"({ print("Hello" + " " + "World") })";

  std::string expected_output = "Hello World\n";
  expected_output += "\n";
  std::string capturedOutput = runReplWithInputPrint(input);

  EXPECT_EQ(capturedOutput, expected_output);
}

TEST_F(ReplTest, BasicPrintFunctionComparisionBasicOperation) {
  std::string input = R"({ print(2 < 3) })";

  std::string expected_output = "true\n";
  expected_output += "\n";
  std::string capturedOutput = runReplWithInputPrint(input);

  EXPECT_EQ(capturedOutput, expected_output);
}