#include "InBuiltFunction.h"

InBuiltFunction::InBuiltFunction() {
#ifdef JIT_TEST_MODE
  _test = std::make_unique<JITCompilerTest>();
#endif

#ifdef REPL_TEST_MODE
  _test = std::make_unique<ReplTest>();
#endif
}

void InBuiltFunction::SetUp() { _test->SetUp(); }

void InBuiltFunction::TearDown() { _test->TearDown(); }

void InBuiltFunction::setInput(const std::string &input) {
  _test->setInput(input);
}

std::string InBuiltFunction::getOutput() const { return _test->getOutput(); }

void InBuiltFunction::runEvaluator() { _test->runEvaluator(); }

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