#include "InBuiltFunction.h"

InBuiltFunction::InBuiltFunction() { repl = std::make_unique<Repl>(); }

void InBuiltFunction::SetUp() {
  saved_cout_buf = std::cout.rdbuf(output_stream.rdbuf());
}
void InBuiltFunction::TearDown() { std::cout.rdbuf(saved_cout_buf); }

void InBuiltFunction::setInput(const std::string &input) {
  input_stream.str(input);
}

std::string InBuiltFunction::getOutput() const { return output_stream.str(); }

void InBuiltFunction::runEvaluator() {

  repl->runTests(input_stream, output_stream);
}

// TESTS

/*                                                              PRINT
FUNCTION
 */

TEST_F(InBuiltFunction, BasicPrintFunctionNumber) {
  std::string input = "print(2)";

  std::string expected_output = "2";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(InBuiltFunction, BasicPrintFunctionNumberInsideScope) {
  std::string input = "{ print(2) }";

  std::string expected_output = "2";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(InBuiltFunction, BasicPrintFunctionString) {
  std::string input = "{ print(\"Hello\") }";

  std::string expected_output = "Hello";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(InBuiltFunction, BasicPrintFunctionStringBasicOperation) {
  std::string input = R"({ print("Hello" + " " + "World") })";

  std::string expected_output = "Hello World";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(InBuiltFunction, BasicPrintFunctionComparisionBasicOperation) {
  std::string input = R"({ print(2 < 3) })";

  std::string expected_output = "true";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}