#include "InBuiltFunction.h"

InBuiltFunction::InBuiltFunction() { repl = std::make_unique<Repl>(true); }

void InBuiltFunction::SetUp() {
  cout_backup = std::cout.rdbuf();
  std::cout.rdbuf(captured_output.rdbuf());
}

void InBuiltFunction::TearDown() { std::cout.rdbuf(cout_backup); }

std::string InBuiltFunction::runReplWithInput(const std::string &input) {

  repl->addTextString(input);
  repl->runForTest(std::cin, std::cout);

  return captured_output.str();
}
std::string InBuiltFunction::runReplWithInputPrint(std::string input) {

  testing::internal::CaptureStdout();

  repl->addTextString(input);
  repl->runForTest(std::cin, std::cout);

  return testing::internal::GetCapturedStdout();
}

/*                                                              PRINT FUNCTION
 */

TEST_F(InBuiltFunction, BasicPrintFunctionNumber) {
  std::string input = "print(2)";

  std::string expected_output = "2";

  std::string capturedOutput = runReplWithInputPrint(input);

  EXPECT_EQ(capturedOutput, expected_output);
}

TEST_F(InBuiltFunction, BasicPrintFunctionNumberInsideScope) {
  std::string input = "{ print(2) }";

  std::string expected_output = "2";

  std::string capturedOutput = runReplWithInputPrint(input);

  EXPECT_EQ(capturedOutput, expected_output);
}

TEST_F(InBuiltFunction, BasicPrintFunctionString) {
  std::string input = "{ print(\"Hello\") }";

  std::string expected_output = "Hello";

  std::string capturedOutput = runReplWithInputPrint(input);

  EXPECT_EQ(capturedOutput, expected_output);
}

TEST_F(InBuiltFunction, BasicPrintFunctionStringBasicOperation) {
  std::string input = R"({ print("Hello" + " " + "World") })";

  std::string expected_output = "Hello World";

  std::string capturedOutput = runReplWithInputPrint(input);

  EXPECT_EQ(capturedOutput, expected_output);
}

TEST_F(InBuiltFunction, BasicPrintFunctionComparisionBasicOperation) {
  std::string input = R"({ print(2 < 3) })";

  std::string expected_output = "true";

  std::string capturedOutput = runReplWithInputPrint(input);

  EXPECT_EQ(capturedOutput, expected_output);
}