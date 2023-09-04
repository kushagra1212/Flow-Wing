
#include "Function.h"

Function::Function() {
#ifdef JIT_TEST_MODE
  _test = std::make_unique<JITCompilerTest>();
#endif

#ifdef REPL_TEST_MODE
  _test = std::make_unique<ReplTest>();
#endif
}

void Function::SetUp() { _test->SetUp(); }

void Function::TearDown() { _test->TearDown(); }

void Function::setInput(const std::string &input) { _test->setInput(input); }

std::string Function::getOutput() const { return _test->getOutput(); }

void Function::runEvaluator() { _test->runEvaluator(); }

// Function with no parameters

// Function with only return statement

// nthg is the return type and int str bool deci nthg are the return value

TEST_F(Function, NthgReturnTypeWithIntReturnValue) {
  std::string input = R"(fun main()-> nthg {
    return 2
}
print(main()))";

  setInput(input);
  runEvaluator();
  // Expected output should be in the of the output
  std::string lowerCaseOutput = getOutput();

  std::transform(lowerCaseOutput.begin(), lowerCaseOutput.end(),
                 lowerCaseOutput.begin(), ::tolower);

  std::string expected_output =
      R"(Function return type is Nothing, return expression is found)";
  std::transform(expected_output.begin(), expected_output.end(),
                 expected_output.begin(), ::tolower);

  EXPECT_TRUE(lowerCaseOutput.find(expected_output) != std::string::npos);
}
TEST_F(Function, NthgReturnTypeWithStringReturnValue) {
  std::string input = R"(fun main()-> nthg {
    return "Hello"
}
print(main()))";

  setInput(input);
  runEvaluator();
  // Expected output should be in the of the output
  std::string lowerCaseOutput = getOutput();

  std::transform(lowerCaseOutput.begin(), lowerCaseOutput.end(),
                 lowerCaseOutput.begin(), ::tolower);

  std::string expected_output =
      R"(Function return type is Nothing, return expression is found)";
  std::transform(expected_output.begin(), expected_output.end(),
                 expected_output.begin(), ::tolower);

  EXPECT_TRUE(lowerCaseOutput.find(expected_output) != std::string::npos);
}

TEST_F(Function, NthgReturnTypeWithBoolReturnValue) {
  std::string input = R"(fun main()-> nthg {
    return (true)
}
print(main()))";

  setInput(input);
  runEvaluator();
  // Expected output should be in the of the output
  std::string lowerCaseOutput = getOutput();

  std::transform(lowerCaseOutput.begin(), lowerCaseOutput.end(),
                 lowerCaseOutput.begin(), ::tolower);

  std::string expected_output =
      R"(Function return type is Nothing, return expression is found)";
  std::transform(expected_output.begin(), expected_output.end(),
                 expected_output.begin(), ::tolower);

  EXPECT_TRUE(lowerCaseOutput.find(expected_output) != std::string::npos);
}
TEST_F(Function, NthgReturnTypeWithDeciReturnValue) {
  std::string input = R"(fun main()-> nthg {
    return 2.2
}
print(main()))";

  setInput(input);
  runEvaluator();
  // Expected output should be in the of the output
  std::string lowerCaseOutput = getOutput();

  std::transform(lowerCaseOutput.begin(), lowerCaseOutput.end(),
                 lowerCaseOutput.begin(), ::tolower);

  std::string expected_output =
      R"(Function return type is Nothing, return expression is found)";
  std::transform(expected_output.begin(), expected_output.end(),
                 expected_output.begin(), ::tolower);

  EXPECT_TRUE(lowerCaseOutput.find(expected_output) != std::string::npos);
}

TEST_F(Function, NthgReturnTypeWithNthgReturnValue) {
  std::string input = R"(fun main()-> nthg {
    return:
}
print(main()))";

  setInput(input);
  runEvaluator();
  // Expected output should be in the of the output
  std::string lowerCaseOutput = getOutput();

  std::string expected_output = "";

  EXPECT_EQ(lowerCaseOutput, expected_output);
}
TEST_F(Function, NthgReturnTypeWithNoReturnValue) {
  std::string input = R"(fun main()-> nthg {
  
}
print(main()))";

  setInput(input);
  runEvaluator();
  // Expected output should be in the of the output
  std::string lowerCaseOutput = getOutput();

  std::string expected_output = "";

  EXPECT_EQ(lowerCaseOutput, expected_output);
}

// Int return type with int str bool deci nthg as return value

TEST_F(Function, IntReturnTypeWithNoReturnValue) {
  std::string input = R"(fun main()-> int {
    return 2+2
}
print(main()))";

  setInput(input);
  runEvaluator();
  // Expected output should be in the of the output
  std::string lowerCaseOutput = getOutput();

  std::string expected_output = "4";

  EXPECT_EQ(lowerCaseOutput, expected_output);
}

TEST_F(Function, IntReturnTypeWithNoReturnValueWithBrackets) {
  std::string input = R"(fun main()-> int {
    return (2+2)
}
print(main()))";

  setInput(input);
  runEvaluator();
  // Expected output should be in the of the output
  std::string lowerCaseOutput = getOutput();

  std::string expected_output = "4";

  EXPECT_EQ(lowerCaseOutput, expected_output);
}

TEST_F(Function, IntReturnTypeWithNthg) {
  std::string input = R"(
fun main()-> int {
    return:
}
print(main())
)";

  setInput(input);
  runEvaluator();
  // Expected output should be in the of the output
  std::string lowerCaseOutput = getOutput();

  std::transform(lowerCaseOutput.begin(), lowerCaseOutput.end(),
                 lowerCaseOutput.begin(), ::tolower);

  std::string expected_output =
      R"(Function return type is not Nothing, return expression is not found)";
  std::transform(expected_output.begin(), expected_output.end(),
                 expected_output.begin(), ::tolower);

  EXPECT_TRUE(lowerCaseOutput.find(expected_output) != std::string::npos);
}

TEST_F(Function, IntReturnTypeWithNoReturn) {
  std::string input = R"(
fun main()-> int {
}
print(main())
)";

  setInput(input);
  runEvaluator();
  // Expected output should be in the of the output
  std::string lowerCaseOutput = getOutput();

  std::transform(lowerCaseOutput.begin(), lowerCaseOutput.end(),
                 lowerCaseOutput.begin(), ::tolower);

  std::string expected_output =
      R"(Function return type is not Nothing, return  statement is not found)";
  std::transform(expected_output.begin(), expected_output.end(),
                 expected_output.begin(), ::tolower);

  EXPECT_TRUE(lowerCaseOutput.find(expected_output) != std::string::npos);
}

TEST_F(Function, IntReturnTypeWithStrReturnValue) {
  std::string input = R"(
fun main()-> int {
return "str"
}
print(main())
)";

  setInput(input);
  runEvaluator();
  // Expected output should be in the of the output
  std::string lowerCaseOutput = getOutput();

  std::transform(lowerCaseOutput.begin(), lowerCaseOutput.end(),
                 lowerCaseOutput.begin(), ::tolower);

  std::string expected_output =
      R"(Return Type Mismatch Integer is expected but String is found)";
  std::transform(expected_output.begin(), expected_output.end(),
                 expected_output.begin(), ::tolower);

  EXPECT_TRUE(lowerCaseOutput.find(expected_output) != std::string::npos);
}

TEST_F(Function, IntReturnTypeWithBoolReturnValue) {
  std::string input = R"(
fun main()-> int {
return true
}
print(main())
)";

  setInput(input);
  runEvaluator();
  // Expected output should be in the of the output
  std::string lowerCaseOutput = getOutput();

  std::transform(lowerCaseOutput.begin(), lowerCaseOutput.end(),
                 lowerCaseOutput.begin(), ::tolower);

  std::string expected_output =
      R"(Return Type Mismatch Integer is expected but Boolean is found)";
  std::transform(expected_output.begin(), expected_output.end(),
                 expected_output.begin(), ::tolower);

  EXPECT_TRUE(lowerCaseOutput.find(expected_output) != std::string::npos);
}

TEST_F(Function, IntReturnTypeWithBoolReturnValueFalse) {
  std::string input = R"(
fun main()-> int {
return false
}
print(main())
)";

  setInput(input);
  runEvaluator();
  // Expected output should be in the of the output
  std::string lowerCaseOutput = getOutput();

  std::transform(lowerCaseOutput.begin(), lowerCaseOutput.end(),
                 lowerCaseOutput.begin(), ::tolower);

  std::string expected_output =
      R"(Return Type Mismatch Integer is expected but Boolean is found)";
  std::transform(expected_output.begin(), expected_output.end(),
                 expected_output.begin(), ::tolower);

  EXPECT_TRUE(lowerCaseOutput.find(expected_output) != std::string::npos);
}
TEST_F(Function, IntReturnTypeWithDeciReturnValue) {
  std::string input = R"(
fun main()-> int {
return 1.2
}
print(main())
)";

  setInput(input);
  runEvaluator();
  // Expected output should be in the of the output
  std::string lowerCaseOutput = getOutput();

  std::transform(lowerCaseOutput.begin(), lowerCaseOutput.end(),
                 lowerCaseOutput.begin(), ::tolower);

  std::string expected_output =
      R"(Return Type Mismatch Integer is expected but Decimal is found)";
  std::transform(expected_output.begin(), expected_output.end(),
                 expected_output.begin(), ::tolower);

  EXPECT_TRUE(lowerCaseOutput.find(expected_output) != std::string::npos);
}

// Bool Return Type

TEST_F(Function, BoolReturnTypeWithIntReturnValue) {
  std::string input = R"(
fun main()-> bool {
return 1
}
print(main())
)";

  setInput(input);
  runEvaluator();
  // Expected output should be in the of the output
  std::string lowerCaseOutput = getOutput();

  std::transform(lowerCaseOutput.begin(), lowerCaseOutput.end(),
                 lowerCaseOutput.begin(), ::tolower);

  std::string expected_output =
      R"(Return Type Mismatch Boolean is expected but Integer is found)";
  std::transform(expected_output.begin(), expected_output.end(),
                 expected_output.begin(), ::tolower);

  EXPECT_TRUE(lowerCaseOutput.find(expected_output) != std::string::npos);
}

TEST_F(Function, BoolReturnTypeWithNthgReturnValue) {
  std::string input = R"(
fun main()-> bool {
return:
}
print(main())
)";

  setInput(input);
  runEvaluator();
  // Expected output should be in the of the output
  std::string lowerCaseOutput = getOutput();

  std::transform(lowerCaseOutput.begin(), lowerCaseOutput.end(),
                 lowerCaseOutput.begin(), ::tolower);

  std::string expected_output =
      R"(Function return type is not Nothing, return  statement is not found)";
  std::transform(expected_output.begin(), expected_output.end(),
                 expected_output.begin(), ::tolower);

  EXPECT_TRUE(lowerCaseOutput.find(expected_output) != std::string::npos);
}

TEST_F(Function, BoolReturnTypeWithNoReturn) {
  std::string input = R"(
fun main()-> bool {

}
print(main())
)";

  setInput(input);
  runEvaluator();
  // Expected output should be in the of the output
  std::string lowerCaseOutput = getOutput();

  std::transform(lowerCaseOutput.begin(), lowerCaseOutput.end(),
                 lowerCaseOutput.begin(), ::tolower);

  std::string expected_output =
      R"(Function return type is not Nothing, return  statement is not found)";
  std::transform(expected_output.begin(), expected_output.end(),
                 expected_output.begin(), ::tolower);

  EXPECT_TRUE(lowerCaseOutput.find(expected_output) != std::string::npos);
}

TEST_F(Function, BoolReturnTypeWithStringReturnValue) {
  std::string input = R"(
fun main()-> bool {
return "str"
}
print(main())
)";

  setInput(input);
  runEvaluator();
  // Expected output should be in the of the output
  std::string lowerCaseOutput = getOutput();

  std::transform(lowerCaseOutput.begin(), lowerCaseOutput.end(),
                 lowerCaseOutput.begin(), ::tolower);

  std::string expected_output =
      R"(Return Type Mismatch Boolean is expected but String is found)";
  std::transform(expected_output.begin(), expected_output.end(),
                 expected_output.begin(), ::tolower);

  EXPECT_TRUE(lowerCaseOutput.find(expected_output) != std::string::npos);
}

TEST_F(Function, BoolReturnTypeWithBoolReturnValueTrue) {
  std::string input = R"(
fun main()-> bool {
return true
}
print(main())
)";

  setInput(input);
  runEvaluator();
  // Expected output should be in the of the output
  std::string lowerCaseOutput = getOutput();

  std::string expected_output = R"(true)";

  EXPECT_EQ(lowerCaseOutput, expected_output);
}

TEST_F(Function, BoolReturnTypeWithBoolReturnValueFalse) {
  std::string input = R"(
fun main()-> bool {
return false
}
print(main())
)";

  setInput(input);
  runEvaluator();
  // Expected output should be in the of the output
  std::string lowerCaseOutput = getOutput();

  std::string expected_output = R"(false)";

  EXPECT_EQ(lowerCaseOutput, expected_output);
}

TEST_F(Function, BoolReturnTypeWithDeciReturnValue) {
  std::string input = R"(
fun main()-> bool {
return 1.2
}
print(main())
)";

  setInput(input);
  runEvaluator();
  // Expected output should be in the of the output
  std::string lowerCaseOutput = getOutput();

  std::transform(lowerCaseOutput.begin(), lowerCaseOutput.end(),
                 lowerCaseOutput.begin(), ::tolower);

  std::string expected_output =
      R"(Return Type Mismatch Boolean is expected but Decimal is found)";
  std::transform(expected_output.begin(), expected_output.end(),
                 expected_output.begin(), ::tolower);

  EXPECT_TRUE(lowerCaseOutput.find(expected_output) != std::string::npos);
}

// String Return Type

TEST_F(Function, StringReturnTypeWithIntReturnValue) {
  std::string input = R"(
fun main()-> str {
return 1
}
print(main())
)";

  setInput(input);
  runEvaluator();
  // Expected output should be in the of the output
  std::string lowerCaseOutput = getOutput();

  std::transform(lowerCaseOutput.begin(), lowerCaseOutput.end(),
                 lowerCaseOutput.begin(), ::tolower);

  std::string expected_output =
      R"(Return Type Mismatch String is expected but Integer is found)";
  std::transform(expected_output.begin(), expected_output.end(),
                 expected_output.begin(), ::tolower);

  EXPECT_TRUE(lowerCaseOutput.find(expected_output) != std::string::npos);
}

TEST_F(Function, StringReturnTypeWithNthgReturnValue) {
  std::string input = R"(
fun main()-> str {
return:
}
print(main())
)";

  setInput(input);
  runEvaluator();
  // Expected output should be in the of the output
  std::string lowerCaseOutput = getOutput();

  std::transform(lowerCaseOutput.begin(), lowerCaseOutput.end(),
                 lowerCaseOutput.begin(), ::tolower);

  std::string expected_output =
      R"(Function return type is not Nothing, return  statement is not found)";
  std::transform(expected_output.begin(), expected_output.end(),
                 expected_output.begin(), ::tolower);

  EXPECT_TRUE(lowerCaseOutput.find(expected_output) != std::string::npos);
}

TEST_F(Function, StringReturnTypeWithNoReturnValue) {
  std::string input = R"(
fun main()-> str {

}
print(main())
)";

  setInput(input);
  runEvaluator();
  // Expected output should be in the of the output
  std::string lowerCaseOutput = getOutput();

  std::transform(lowerCaseOutput.begin(), lowerCaseOutput.end(),
                 lowerCaseOutput.begin(), ::tolower);

  std::string expected_output =
      R"(Function return type is not Nothing, return  statement is not found)";
  std::transform(expected_output.begin(), expected_output.end(),
                 expected_output.begin(), ::tolower);

  EXPECT_TRUE(lowerCaseOutput.find(expected_output) != std::string::npos);
}

TEST_F(Function, StringReturnTypeWithBoolReturnValueTrue) {
  std::string input = R"(
fun main()-> str {
return true
}
print(main())
)";

  setInput(input);
  runEvaluator();
  // Expected output should be in the of the output
  std::string lowerCaseOutput = getOutput();

  std::transform(lowerCaseOutput.begin(), lowerCaseOutput.end(),
                 lowerCaseOutput.begin(), ::tolower);

  std::string expected_output =
      R"(Return Type Mismatch String is expected but Boolean is found)";
  std::transform(expected_output.begin(), expected_output.end(),
                 expected_output.begin(), ::tolower);

  EXPECT_TRUE(lowerCaseOutput.find(expected_output) != std::string::npos);
}

TEST_F(Function, StringReturnTypeWithBoolReturnValueFalse) {
  std::string input = R"(
fun main()-> str {
return (false)
}
print(main())
)";

  setInput(input);
  runEvaluator();
  // Expected output should be in the of the output
  std::string lowerCaseOutput = getOutput();

  std::transform(lowerCaseOutput.begin(), lowerCaseOutput.end(),
                 lowerCaseOutput.begin(), ::tolower);

  std::string expected_output =
      R"(Return Type Mismatch String is expected but Boolean is found)";
  std::transform(expected_output.begin(), expected_output.end(),
                 expected_output.begin(), ::tolower);

  EXPECT_TRUE(lowerCaseOutput.find(expected_output) != std::string::npos);
}

TEST_F(Function, StringReturnTypeWithDeciReturnValue) {
  std::string input = R"(
fun main()-> str {
return 1.2
}
print(main())
)";

  setInput(input);
  runEvaluator();
  // Expected output should be in the of the output
  std::string lowerCaseOutput = getOutput();

  std::transform(lowerCaseOutput.begin(), lowerCaseOutput.end(),
                 lowerCaseOutput.begin(), ::tolower);

  std::string expected_output =
      R"(Return Type Mismatch String is expected but Decimal is found)";
  std::transform(expected_output.begin(), expected_output.end(),
                 expected_output.begin(), ::tolower);

  EXPECT_TRUE(lowerCaseOutput.find(expected_output) != std::string::npos);
}

TEST_F(Function, StringReturnTypeWithStringReturnValue) {
  std::string input = R"(
fun main()-> str {
return "Hello" + " World"
}
print(main())
)";

  setInput(input);
  runEvaluator();
  // Expected output should be in the of the output
  std::string lowerCaseOutput = getOutput();

  std::string expected_output = R"(Hello World)";

  EXPECT_EQ(lowerCaseOutput, expected_output);
}