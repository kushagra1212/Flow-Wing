
#include "Function.h"

void Tests::FlowWing::Function::SetUp() { _test->SetUp(); }

void Tests::FlowWing::Function::TearDown() { _test->TearDown(); }

// Function with no parameters

// Function with only return statement

// nthg is the return type and int str bool deci nthg are the return value

#ifdef REPL_TEST_MODE

TEST_F(Function, NthgReturnTypeWithIntReturnValue) {
  std::string input = R"(
fun mainTest()-> nthg {
    return 2
}
print(mainTest())
)";

  setInput(input);
  runEvaluator();
  // Expected output should be in the of the output
  std::string lowerCaseOutput = getOutput();

  std::transform(lowerCaseOutput.begin(), lowerCaseOutput.end(),
                 lowerCaseOutput.begin(), ::tolower);

  std::string expected_output =
      "Function return type is Nothing, return expression is found";
  std::transform(expected_output.begin(), expected_output.end(),
                 expected_output.begin(), ::tolower);

// check expected output is substring of the output or not
#if defined(JIT_TEST_MODE) || defined(AOT_TEST_MODE)
  EXPECT_TRUE(Utils::isSubstring(lowerCaseOutput, expected_output));
#elif REPL_TEST_MODE
  EXPECT_TRUE(lowerCaseOutput.find(expected_output) != std::string::npos);
#endif
}
TEST_F(Function, NthgReturnTypeWithStringReturnValue) {
  std::string input = R"(
    fun mainTest()-> nthg {
      return "Hello"
    }
    print(mainTest())
  )";

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
#if defined(JIT_TEST_MODE) || defined(AOT_TEST_MODE)
  EXPECT_TRUE(Utils::isSubstring(lowerCaseOutput, expected_output));
#elif REPL_TEST_MODE
  EXPECT_TRUE(lowerCaseOutput.find(expected_output) != std::string::npos);
#endif
}

TEST_F(Function, NthgReturnTypeWithBoolReturnValue) {
  std::string input = R"(fun mainTest()-> nthg {
    return (true)
}
print(mainTest()))";

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
#if defined(JIT_TEST_MODE) || defined(AOT_TEST_MODE)
  EXPECT_TRUE(Utils::isSubstring(lowerCaseOutput, expected_output));
#elif REPL_TEST_MODE
  EXPECT_TRUE(lowerCaseOutput.find(expected_output) != std::string::npos);
#endif
}
TEST_F(Function, NthgReturnTypeWithDeciReturnValue) {
  std::string input = R"(fun mainTest()-> nthg {
    return 2.2
}
print(mainTest()))";

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
#if defined(JIT_TEST_MODE) || defined(AOT_TEST_MODE)
  EXPECT_TRUE(Utils::isSubstring(lowerCaseOutput, expected_output));
#elif REPL_TEST_MODE
  EXPECT_TRUE(lowerCaseOutput.find(expected_output) != std::string::npos);
#endif
}

// Int return type with int str bool deci nthg as return value

TEST_F(Function, IntReturnTypeWithNoReturnValue) {
  std::string input = R"(fun mainTest()-> int {
    return 2+2
}
print(mainTest()))";

  setInput(input);
  runEvaluator();
  // Expected output should be in the of the output
  std::string lowerCaseOutput = getOutput();

  std::string expected_output = "4";

  EXPECT_EQ(lowerCaseOutput, expected_output);
}

TEST_F(Function, IntReturnTypeWithNoReturnValueWithBrackets) {
  std::string input = R"(fun mainTest()-> int {
    return (2+2)
}
print(mainTest()))";

  setInput(input);
  runEvaluator();
  // Expected output should be in the of the output
  std::string lowerCaseOutput = getOutput();

  std::string expected_output = "4";

  EXPECT_EQ(lowerCaseOutput, expected_output);
}

TEST_F(Function, IntReturnTypeWithNthg) {
  std::string input = R"(
fun mainTest()-> int {
    return:
}
print(mainTest())
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
#if defined(JIT_TEST_MODE) || defined(AOT_TEST_MODE)
  EXPECT_TRUE(Utils::isSubstring(lowerCaseOutput, expected_output));
#elif REPL_TEST_MODE
  EXPECT_TRUE(lowerCaseOutput.find(expected_output) != std::string::npos);
#endif
}
TEST_F(Function, IntReturnTypeWithNoReturn) {
  std::string input = R"(fun main2()-> int {
}print(main2()))";

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
#if defined(JIT_TEST_MODE) || defined(AOT_TEST_MODE)
  EXPECT_TRUE(Utils::isSubstring(lowerCaseOutput, expected_output));
#elif REPL_TEST_MODE
  EXPECT_TRUE(lowerCaseOutput.find(expected_output) != std::string::npos);
#endif
}

TEST_F(Function, IntReturnTypeWithStrReturnValue) {
  std::string input = R"(
fun mainTest()-> int {
return "str"
}
print(mainTest())
)";

  setInput(input);
  runEvaluator();
  // Expected output should be in the of the output
  std::string lowerCaseOutput = getOutput();

  std::transform(lowerCaseOutput.begin(), lowerCaseOutput.end(),
                 lowerCaseOutput.begin(), ::tolower);

  std::string expected_output =
      R"(Return Type Mismatch Int32 is expected but String is found)";
  std::transform(expected_output.begin(), expected_output.end(),
                 expected_output.begin(), ::tolower);
#if defined(JIT_TEST_MODE) || defined(AOT_TEST_MODE)
  EXPECT_TRUE(Utils::isSubstring(lowerCaseOutput, expected_output));
#elif REPL_TEST_MODE
  EXPECT_TRUE(lowerCaseOutput.find(expected_output) != std::string::npos);
#endif
}

TEST_F(Function, IntReturnTypeWithBoolReturnValue) {
  std::string input = R"(
fun mainTest()-> int {
return true
}
print(mainTest())
)";

  setInput(input);
  runEvaluator();
  // Expected output should be in the of the output
  std::string lowerCaseOutput = getOutput();

  std::transform(lowerCaseOutput.begin(), lowerCaseOutput.end(),
                 lowerCaseOutput.begin(), ::tolower);

  std::string expected_output =
      R"(Return Type Mismatch Int32 is expected but Bool is found)";
  std::transform(expected_output.begin(), expected_output.end(),
                 expected_output.begin(), ::tolower);

#if defined(JIT_TEST_MODE) || defined(AOT_TEST_MODE)
  EXPECT_TRUE(Utils::isSubstring(lowerCaseOutput, expected_output));
#elif REPL_TEST_MODE
  EXPECT_TRUE(lowerCaseOutput.find(expected_output) != std::string::npos);
#endif
}

TEST_F(Function, IntReturnTypeWithBoolReturnValueFalse) {
  std::string input = R"(
fun mainTest()-> int {
return false
}
print(mainTest())
)";

  setInput(input);
  runEvaluator();
  // Expected output should be in the of the output
  std::string lowerCaseOutput = getOutput();

  std::transform(lowerCaseOutput.begin(), lowerCaseOutput.end(),
                 lowerCaseOutput.begin(), ::tolower);

  std::string expected_output =
      R"(Return Type Mismatch Int32 is expected but Bool is found)";
  std::transform(expected_output.begin(), expected_output.end(),
                 expected_output.begin(), ::tolower);
#if defined(JIT_TEST_MODE) || defined(AOT_TEST_MODE)
  EXPECT_TRUE(Utils::isSubstring(lowerCaseOutput, expected_output));
#elif REPL_TEST_MODE
  EXPECT_TRUE(lowerCaseOutput.find(expected_output) != std::string::npos);
#endif
}
TEST_F(Function, IntReturnTypeWithDeciReturnValue) {
  std::string input = R"(
fun mainTest()-> int {
return 1.2
}
print(mainTest())
)";

  setInput(input);
  runEvaluator();
  // Expected output should be in the of the output
  std::string lowerCaseOutput = getOutput();

  std::transform(lowerCaseOutput.begin(), lowerCaseOutput.end(),
                 lowerCaseOutput.begin(), ::tolower);

  std::string expected_output =
      R"(Return Type Mismatch Int32 is expected but Decimal is found)";
  std::transform(expected_output.begin(), expected_output.end(),
                 expected_output.begin(), ::tolower);
#if defined(JIT_TEST_MODE) || defined(AOT_TEST_MODE)
  EXPECT_TRUE(Utils::isSubstring(lowerCaseOutput, expected_output));
#elif REPL_TEST_MODE
  EXPECT_TRUE(lowerCaseOutput.find(expected_output) != std::string::npos);
#endif
}

// Bool Return Type

TEST_F(Function, BoolReturnTypeWithIntReturnValue) {
  std::string input = R"(
fun mainTest()-> bool {
return 1
}
print(mainTest())
)";

  setInput(input);
  runEvaluator();
  // Expected output should be in the of the output
  std::string lowerCaseOutput = getOutput();

  std::transform(lowerCaseOutput.begin(), lowerCaseOutput.end(),
                 lowerCaseOutput.begin(), ::tolower);

  std::string expected_output =
      R"(Return Type Mismatch Bool is expected but Int32 is found)";
  std::transform(expected_output.begin(), expected_output.end(),
                 expected_output.begin(), ::tolower);
#if defined(JIT_TEST_MODE) || defined(AOT_TEST_MODE)
  EXPECT_TRUE(Utils::isSubstring(lowerCaseOutput, expected_output));
#elif REPL_TEST_MODE
  EXPECT_TRUE(lowerCaseOutput.find(expected_output) != std::string::npos);
#endif
}

TEST_F(Function, BoolReturnTypeWithNthgReturnValue) {
  std::string input = R"(
fun mainTest()-> bool {
return:
}
print(mainTest())
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
#if defined(JIT_TEST_MODE) || defined(AOT_TEST_MODE)
  EXPECT_TRUE(Utils::isSubstring(lowerCaseOutput, expected_output));
#elif REPL_TEST_MODE
  EXPECT_TRUE(lowerCaseOutput.find(expected_output) != std::string::npos);
#endif
}

TEST_F(Function, BoolReturnTypeWithNoReturn) {
  std::string input = R"(
fun mainTest()-> bool {

}
print(mainTest())
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
#if defined(JIT_TEST_MODE) || defined(AOT_TEST_MODE)
  EXPECT_TRUE(Utils::isSubstring(lowerCaseOutput, expected_output));
#elif REPL_TEST_MODE
  EXPECT_TRUE(lowerCaseOutput.find(expected_output) != std::string::npos);
#endif
}

TEST_F(Function, BoolReturnTypeWithStringReturnValue) {
  std::string input = R"(
fun mainTest()-> bool {
return "str"
}
print(mainTest())
)";

  setInput(input);
  runEvaluator();
  // Expected output should be in the of the output
  std::string lowerCaseOutput = getOutput();

  std::transform(lowerCaseOutput.begin(), lowerCaseOutput.end(),
                 lowerCaseOutput.begin(), ::tolower);

  std::string expected_output =
      R"(Return Type Mismatch Bool is expected but String is found)";
  std::transform(expected_output.begin(), expected_output.end(),
                 expected_output.begin(), ::tolower);
#if defined(JIT_TEST_MODE) || defined(AOT_TEST_MODE)
  EXPECT_TRUE(Utils::isSubstring(lowerCaseOutput, expected_output));
#elif REPL_TEST_MODE
  EXPECT_TRUE(lowerCaseOutput.find(expected_output) != std::string::npos);
#endif
}

TEST_F(Function, BoolReturnTypeWithBoolReturnValueTrue) {
  std::string input = R"(
fun mainTest()-> bool {
return true
}
print(mainTest())
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
fun mainTest()-> bool {
return false
}
print(mainTest())
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
fun mainTest()-> bool {
return 1.2
}
print(mainTest())
)";

  setInput(input);
  runEvaluator();
  // Expected output should be in the of the output
  std::string lowerCaseOutput = getOutput();

  std::transform(lowerCaseOutput.begin(), lowerCaseOutput.end(),
                 lowerCaseOutput.begin(), ::tolower);

  std::string expected_output =
      R"(Return Type Mismatch Bool is expected but Decimal is found)";
  std::transform(expected_output.begin(), expected_output.end(),
                 expected_output.begin(), ::tolower);
#if defined(JIT_TEST_MODE) || defined(AOT_TEST_MODE)
  EXPECT_TRUE(Utils::isSubstring(lowerCaseOutput, expected_output));
#elif REPL_TEST_MODE
  EXPECT_TRUE(lowerCaseOutput.find(expected_output) != std::string::npos);
#endif
}

// String Return Type

TEST_F(Function, StringReturnTypeWithIntReturnValue) {
  std::string input = R"(
fun mainTest()-> str {
return 1
}
print(mainTest())
)";

  setInput(input);
  runEvaluator();
  // Expected output should be in the of the output
  std::string lowerCaseOutput = getOutput();

  std::transform(lowerCaseOutput.begin(), lowerCaseOutput.end(),
                 lowerCaseOutput.begin(), ::tolower);

  std::string expected_output =
      R"(Return Type Mismatch String is expected but Int32 is found)";
  std::transform(expected_output.begin(), expected_output.end(),
                 expected_output.begin(), ::tolower);
#if defined(JIT_TEST_MODE) || defined(AOT_TEST_MODE)
  EXPECT_TRUE(Utils::isSubstring(lowerCaseOutput, expected_output));
#elif REPL_TEST_MODE
  EXPECT_TRUE(lowerCaseOutput.find(expected_output) != std::string::npos);
#endif
}

TEST_F(Function, StringReturnTypeWithNthgReturnValue) {
  std::string input = R"(
fun mainTest()-> str {
return:
}
print(mainTest())
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
#if defined(JIT_TEST_MODE) || defined(AOT_TEST_MODE)
  EXPECT_TRUE(Utils::isSubstring(lowerCaseOutput, expected_output));
#elif REPL_TEST_MODE
  EXPECT_TRUE(lowerCaseOutput.find(expected_output) != std::string::npos);
#endif
}

TEST_F(Function, StringReturnTypeWithNoReturnValue) {
  std::string input = R"(
fun mainTest()-> str {

}
print(mainTest())
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
#if defined(JIT_TEST_MODE) || defined(AOT_TEST_MODE)
  EXPECT_TRUE(Utils::isSubstring(lowerCaseOutput, expected_output));
#elif REPL_TEST_MODE
  EXPECT_TRUE(lowerCaseOutput.find(expected_output) != std::string::npos);
#endif
}

TEST_F(Function, StringReturnTypeWithBoolReturnValueTrue) {
  std::string input = R"(
fun mainTest()-> str {
return true
}
print(mainTest())
)";

  setInput(input);
  runEvaluator();
  // Expected output should be in the of the output
  std::string lowerCaseOutput = getOutput();

  std::transform(lowerCaseOutput.begin(), lowerCaseOutput.end(),
                 lowerCaseOutput.begin(), ::tolower);

  std::string expected_output =
      R"(Return Type Mismatch String is expected but Bool is found)";
  std::transform(expected_output.begin(), expected_output.end(),
                 expected_output.begin(), ::tolower);
#if defined(JIT_TEST_MODE) || defined(AOT_TEST_MODE)
  EXPECT_TRUE(Utils::isSubstring(lowerCaseOutput, expected_output));
#elif REPL_TEST_MODE
  EXPECT_TRUE(lowerCaseOutput.find(expected_output) != std::string::npos);
#endif
}

TEST_F(Function, StringReturnTypeWithBoolReturnValueFalse) {
  std::string input = R"(
fun mainTest()-> str {
return (false)
}
print(mainTest())
)";

  setInput(input);
  runEvaluator();
  // Expected output should be in the of the output
  std::string lowerCaseOutput = getOutput();

  std::transform(lowerCaseOutput.begin(), lowerCaseOutput.end(),
                 lowerCaseOutput.begin(), ::tolower);

  std::string expected_output =
      R"(Return Type Mismatch String is expected but Bool is found)";
  std::transform(expected_output.begin(), expected_output.end(),
                 expected_output.begin(), ::tolower);
#if defined(JIT_TEST_MODE) || defined(AOT_TEST_MODE)
  EXPECT_TRUE(Utils::isSubstring(lowerCaseOutput, expected_output));
#elif REPL_TEST_MODE
  EXPECT_TRUE(lowerCaseOutput.find(expected_output) != std::string::npos);
#endif
}

TEST_F(Function, StringReturnTypeWithDeciReturnValue) {
  std::string input = R"(
fun mainTest()-> str {
return 1.2
}
print(mainTest())
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
#if defined(JIT_TEST_MODE) || defined(AOT_TEST_MODE)
  EXPECT_TRUE(Utils::isSubstring(lowerCaseOutput, expected_output));
#elif REPL_TEST_MODE
  EXPECT_TRUE(lowerCaseOutput.find(expected_output) != std::string::npos);
#endif
}

TEST_F(Function, NthgReturnTypeWithNthgReturnValue) {
  std::string input = R"(
fun mainTest()-> nthg {
    return:
}
mainTest()
)";

  setInput(input);
  runEvaluator();
  // Expected output should be in the of the output
  std::string lowerCaseOutput = getOutput();
  std::string expected_output;
#if defined(JIT_TEST_MODE) || defined(AOT_TEST_MODE)
  expected_output = "";
#elif REPL_TEST_MODE
  expected_output = "";
#endif

  EXPECT_EQ(lowerCaseOutput, expected_output);
}
TEST_F(Function, NthgReturnTypeWithNoReturnValue) {
  std::string input = R"(fun mainTest()-> nthg {
  
}
mainTest())";

  setInput(input);
  runEvaluator();
  // Expected output should be in the of the output
  std::string lowerCaseOutput = getOutput();

  std::string expected_output;
#if defined(JIT_TEST_MODE) || defined(AOT_TEST_MODE)
  expected_output = "";
#elif REPL_TEST_MODE
  expected_output = "";
#endif

  EXPECT_EQ(lowerCaseOutput, expected_output);
}

TEST_F(Function, StringReturnTypeWithStringReturnValue) {
  std::string input = R"(
fun mainTest()-> str {
return "Hello" + " World"
}
print(mainTest())
)";

  setInput(input);
  runEvaluator();
  // Expected output should be in the of the output
  std::string lowerCaseOutput = getOutput();

  std::string expected_output = R"(Hello World)";

  EXPECT_EQ(lowerCaseOutput, expected_output);
}

// sum of n numbers using recursion

TEST_F(Function, SumOfNNumbersUsingRecursion) {
  std::string input = R"(
fun sum(n) -> int {
  if (n == 0) {
    return 0
  }
  return n + sum(n - 1)
}
print(sum(10))
)";
  setInput(input);
  runEvaluator();
  std::string lowerCaseOutput = getOutput();
  std::string expected_output = "55";
  EXPECT_EQ(lowerCaseOutput, expected_output);
}

// sum of n numbers using loop

TEST_F(Function, SumOfNNumbersUsingLoop) {
  std::string input = R"(
fun sum(n) -> int {
  var sum = 0
  for (var i = 0 to n : 1) {
    sum = sum + i
  }
  return sum
}
print(sum(10))
)";
  setInput(input);
  runEvaluator();
  std::string lowerCaseOutput = getOutput();
  std::string expected_output = "55";
  EXPECT_EQ(lowerCaseOutput, expected_output);
}

// write a function to find the factorial of a number

TEST_F(Function, FactorialOfANumberUsingRecursion) {
  std::string input = R"(
fun factorial(n) -> int {
  if (n == 0) {
    return 1
  }
  return n * factorial(n - 1)
}
print(factorial(5))
)";
  setInput(input);
  runEvaluator();
  std::string lowerCaseOutput = getOutput();
  std::string expected_output = "120";
  EXPECT_EQ(lowerCaseOutput, expected_output);
}

// write a function to find the factorial of a number using loop

TEST_F(Function, FactorialOfANumberUsingLoop) {
  std::string input = R"(
fun factorial(n) -> int {
  var fact = 1
  for (var i = 1 to n : 1) {
    fact = fact * i
  }
  return fact
}
print(factorial(5))
)";
  setInput(input);
  runEvaluator();
  std::string lowerCaseOutput = getOutput();
  std::string expected_output = "120";
  EXPECT_EQ(lowerCaseOutput, expected_output);
}

// write a function to find the fibonacci of a number

TEST_F(Function, FibonacciOfANumberUsingRecursion) {
  std::string input = R"(
fun fibonacci(n) -> int {
  if (n == 0) {
    return 0
  }
  if (n == 1) {
    return 1
  }
  return fibonacci(n - 1) + fibonacci(n - 2)
}
print(fibonacci(10))
)";
  setInput(input);
  runEvaluator();
  std::string lowerCaseOutput = getOutput();
  std::string expected_output = "55";
  EXPECT_EQ(lowerCaseOutput, expected_output);
}

// write a function to find the fibonacci of a number using loop

TEST_F(Function, FibonacciOfANumberUsingLoop) {
  std::string input = R"(
fun fibonacci(n) -> int {
  var a = 0
  var b = 1
  var c = 0
  for (var i = 2 to n : 1) {
    c = a + b
    a = b
    b = c
  }
  return c
}
print(fibonacci(10))
)";
  setInput(input);
  runEvaluator();
  std::string lowerCaseOutput = getOutput();
  std::string expected_output = "55";
  EXPECT_EQ(lowerCaseOutput, expected_output);
}

// write a function to find the gcd of two numbers

TEST_F(Function, GCDOfTwoNumbersUsingRecuhrsion) {
  std::string input = R"(
fun gcd(a, b) -> int {
  if (b == 0) {
    return a
  }
  return gcd(b, a % b)
}
print(gcd(10, 15))
)";
  setInput(input);
  runEvaluator();
  std::string lowerCaseOutput = getOutput();
  std::string expected_output = "5";
  EXPECT_EQ(lowerCaseOutput, expected_output);
}

// write a function to find the gcd of two numbers using loop

TEST_F(Function, GCDOfTwoNumbersUsingLoop) {
  std::string input = R"(
fun gcd(a, b) -> int {
  while (b != 0) {
    var temp = b
    b = a % b
    a = temp
  }
  return a
}
print(gcd(10, 15))
)";
  setInput(input);
  runEvaluator();
  std::string lowerCaseOutput = getOutput();
  std::string expected_output = "5";
  EXPECT_EQ(lowerCaseOutput, expected_output);
}

// write a function to find the lcm of two numbers

TEST_F(Function, LCMOfTwoNumbersUsingRecursion) {
  std::string input = R"(
fun gcd(a, b) -> int {
  if (b == 0) {
    return a
  }
  return gcd(b, a % b)
}
fun lcm(a, b) -> int {
  return ((a * b) // gcd(a, b))
}
print(lcm(10, 15))
)";
  setInput(input);
  runEvaluator();
  std::string lowerCaseOutput = getOutput();
  std::string expected_output = "30";
  EXPECT_EQ(lowerCaseOutput, expected_output);
}

// write a function to find the lcm of two numbers using loop

TEST_F(Function, LCMOfTwoNumbersUsingLoop) {
  std::string input = R"(
fun gcd(a, b) -> int {
  while (b != 0) {
    var temp = b
    b = a % b
    a = temp
  }
  return a
}

fun lcm(a, b) -> int {
  return ((a * b) // gcd(a, b))
}

print(lcm(10, 15))
)";
  setInput(input);
  runEvaluator();
  std::string lowerCaseOutput = getOutput();
  std::string expected_output = "30";
  EXPECT_EQ(lowerCaseOutput, expected_output);
}

// write a function to find the power of a number

TEST_F(Function, PowerOfANumberUsingRecursion) {
  std::string input = R"(
fun power(base, exp) -> int {
  if (exp == 0) {
    return 1
  }
  return base * power(base, exp - 1)
}

print(power(2, 3))
)";
  setInput(input);
  runEvaluator();
  std::string lowerCaseOutput = getOutput();
  std::string expected_output = "8";
  EXPECT_EQ(lowerCaseOutput, expected_output);
}

// write a function to find the power of a number using loop

TEST_F(Function, PowerOfANumberUsingLoop) {
  std::string input = R"(
fun power(base, exp) -> int {
  var result = 1
  for (var i = 0 to exp - 1: 1) {
    result = result * base
  }
  return result
}

print(power(2, 3))
)";
  setInput(input);
  runEvaluator();
  std::string lowerCaseOutput = getOutput();
  std::string expected_output = "8";
  EXPECT_EQ(lowerCaseOutput, expected_output);
}

// write a function to find the sum of digits of a number

TEST_F(Function, SumOfDigitsOfANumberUsingRecursion) {
  std::string input = R"(

fun sumOfDigits(n) -> int {
  if (n == 0) {
    return 0
  }
  return ((n % 10) + sumOfDigits(n // 10))
}

print(sumOfDigits(123))
)";
  setInput(input);
  runEvaluator();
  std::string lowerCaseOutput = getOutput();
  std::string expected_output = "6";
  EXPECT_EQ(lowerCaseOutput, expected_output);
}

// write a function to find the sum of digits of a number using loop

TEST_F(Function, SumOfDigitsOfANumberUsingLoop) {
  std::string input = R"(
fun sumOfDigits(n) -> int {
  var sum = 0
  while (n != 0) {
    sum = sum + (n % 10)
    n = n // 10
  }
  return sum
}

print(sumOfDigits(123))
)";
  setInput(input);
  runEvaluator();
  std::string lowerCaseOutput = getOutput();
  std::string expected_output = "6";
  EXPECT_EQ(lowerCaseOutput, expected_output);
}
// Also use the Inbuti function like Decimal() Int32() String() Bool()

// write a function to find the sum of digits of a number using loop

TEST_F(Function, SumOfDigitsOfANumberUsingLoopWhile) {
  std::string input = R"(
fun sumOfDigits(n) -> int {
  var sum = 0
  while (n != 0) {
    sum = sum + (n % 10)
    n = n // 10
  }
  return sum
}

print(sumOfDigits(123))
)";
  setInput(input);
  runEvaluator();
  std::string lowerCaseOutput = getOutput();
  std::string expected_output = "6";
  EXPECT_EQ(lowerCaseOutput, expected_output);
}

#endif // NOT_JIT_TEST_MODE
