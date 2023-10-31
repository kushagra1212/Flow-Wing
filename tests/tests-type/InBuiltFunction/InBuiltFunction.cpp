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

// Conversions

// To Bool

TEST_F(InBuiltFunction, BasicIntToBoolFalse) {
  std::string input = R"(print(Bool(0)))";

  std::string expected_output = "false";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(InBuiltFunction, BasicIntToBoolTrue) {
  std::string input = R"(print(Bool(1)))";

  std::string expected_output = "true";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(InBuiltFunction, BasicDoubleToBoolFalse) {
  std::string input = R"(print(Bool(0.0)))";

  std::string expected_output = "false";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(InBuiltFunction, BasicDoubleToBoolTrue) {
  std::string input = R"(print(Bool(1.3)))";

  std::string expected_output = "true";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(InBuiltFunction, BasicStringToBoolFalse) {
  std::string input = R"(print(Bool("")))";

  std::string expected_output = "false";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(InBuiltFunction, BasicStringToBoolTrue) {
  std::string input = R"(print(Bool("sssg")))";

  std::string expected_output = "true";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(InBuiltFunction, BasicBoolToBoolFalse) {
  std::string input = R"(print(Bool(false)))";

  std::string expected_output = "false";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(InBuiltFunction, BasicBoolToBoolTrue) {
  std::string input = R"(print(Bool(true)))";

  std::string expected_output = "true";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

// To String

TEST_F(InBuiltFunction, BasicIntToString) {
  std::string input = R"(print(String(123)))";

  std::string expected_output = "123";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(InBuiltFunction, BasicDoubleToString) {
  std::string input = R"(print(String(123.33)))";

  std::string expected_output = "123.330000";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}
TEST_F(InBuiltFunction, BasicBoolToStringTrue) {
  std::string input = R"(print(String(true)))";

  std::string expected_output = "true";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(InBuiltFunction, BasicBoolToStringFalse) {
  std::string input = R"(print(String(false)))";

  std::string expected_output = "false";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(InBuiltFunction, BasicStringToString) {
  std::string input = R"(print(String("Hello")))";

  std::string expected_output = "Hello";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

// To Int32

TEST_F(InBuiltFunction, BasicIntToInt32) {
  std::string input = R"(print(Int32(123)))";

  std::string expected_output = "123";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(InBuiltFunction, BasicDoubleToInt32) {
  std::string input = R"(print(Int32(123.33)))";

  std::string expected_output = "123";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(InBuiltFunction, BasicBoolToInt32True) {
  std::string input = R"(print(Int32(true)))";

  std::string expected_output = "1";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(InBuiltFunction, BasicBoolToInt32False) {
  std::string input = R"(print(Int32(false)))";

  std::string expected_output = "0";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(InBuiltFunction, BasicStringToInt32) {
  std::string input = R"(print(Int32("123")))";

  std::string expected_output = "123";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(InBuiltFunction, BasicStringToInt32UndefinedBehaviour) {
  std::string input = R"(print(Int32("sss")))";

  std::string expected_output = "0";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

// To Double

TEST_F(InBuiltFunction, BasicIntToDouble) {
  std::string input = R"(print(Decimal(123)))";

  std::string expected_output = "123.000000";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(InBuiltFunction, BasicDoubleToDouble) {
  std::string input = R"(print(Decimal(123.33)))";

  std::string expected_output = "123.330000";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(InBuiltFunction, BasicBoolToDoubleTrue) {
  std::string input = R"(print(Decimal(true)))";

  std::string expected_output = "1.000000";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(InBuiltFunction, BasicBoolToDoubleFalse) {
  std::string input = R"(print(Decimal(false)))";

  std::string expected_output = "0.000000";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

#ifndef JIT_TEST_MODE

TEST_F(InBuiltFunction, BasicStringToDoubleWithInt) {
  std::string input = R"(print(Decimal("123")))";

  std::string expected_output = "123.000000";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(InBuiltFunction, BasicStringToDouble) {
  std::string input = R"(print(Decimal("123.33")))";

  std::string expected_output = "123.330000";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(InBuiltFunction, BasicStringToDoubleUndefinedBehaviour) {
  std::string input = R"(print(Decimal("wwws")))";

  std::string expected_output = "0.000000";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}
#endif

// input function
#ifdef REPL_TEST_MODE

TEST_F(InBuiltFunction, BasicInputFunction) {
  std::string input = R"(print(input()))";

  std::string expected_output = "123";

  setInput(input);
  _test->setInput("123");
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(InBuiltFunction, BasicInputFunctionWithPrompt) {
  std::string input = R"(print(input("Enter a number: ")))";

  std::string expected_output = "123";

  setInput(input);
  _test->setInput("123");
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

#endif