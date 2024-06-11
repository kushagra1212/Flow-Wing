#include "JITFunction.h"

JITFunction::JITFunction() { _test = std::move(Tests::FlowWing::getTest()); }

void JITFunction::SetUp() { _test->SetUp(); }

void JITFunction::TearDown() { _test->TearDown(); }

void JITFunction::setInput(const std::string &input) { _test->setInput(input); }

std::string JITFunction::getOutput() const { return _test->getOutput(); }

void JITFunction::runEvaluator() { _test->runEvaluator(); }

#if defined(JIT_TEST_MODE)

TEST_F(JITFunction, NthgReturnTypeWithIntReturnValue2) {
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
  EXPECT_TRUE(Utils::isSubstring(lowerCaseOutput, expected_output));
}
TEST_F(JITFunction, NthgReturnTypeWithStringReturnValue2) {
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
      R"(JITFunction return type is Nothing, return expression is found)";
  std::transform(expected_output.begin(), expected_output.end(),
                 expected_output.begin(), ::tolower);
#if defined(JIT_TEST_MODE) || defined(AOT_TEST_MODE)
  EXPECT_TRUE(Utils::isSubstring(lowerCaseOutput, expected_output));
#elif REPL_TEST_MODE
  EXPECT_TRUE(lowerCaseOutput.find(expected_output) != std::string::npos);
#endif
}

TEST_F(JITFunction, NthgReturnTypeWithBoolReturnValue2) {
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
      R"(JITFunction return type is Nothing, return expression is found)";
  std::transform(expected_output.begin(), expected_output.end(),
                 expected_output.begin(), ::tolower);
#if defined(JIT_TEST_MODE) || defined(AOT_TEST_MODE)
  EXPECT_TRUE(Utils::isSubstring(lowerCaseOutput, expected_output));
#elif REPL_TEST_MODE
  EXPECT_TRUE(lowerCaseOutput.find(expected_output) != std::string::npos);
#endif
}
TEST_F(JITFunction, NthgReturnTypeWithDeciReturnValue2) {
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
      R"(JITFunction return type is Nothing, return expression is found)";
  std::transform(expected_output.begin(), expected_output.end(),
                 expected_output.begin(), ::tolower);
#if defined(JIT_TEST_MODE) || defined(AOT_TEST_MODE)
  EXPECT_TRUE(Utils::isSubstring(lowerCaseOutput, expected_output));
#elif REPL_TEST_MODE
  EXPECT_TRUE(lowerCaseOutput.find(expected_output) != std::string::npos);
#endif
}

// Int return type with int str bool deci nthg as return value

TEST_F(JITFunction, IntReturnTypeWithNoReturnValue2) {
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

TEST_F(JITFunction, IntReturnTypeWithNoReturnValueWithBrackets2) {
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

TEST_F(JITFunction, IntReturnTypeWithNthg2) {
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
      R"(JITFunction return type is not Nothing, return expression is not found)";
  std::transform(expected_output.begin(), expected_output.end(),
                 expected_output.begin(), ::tolower);
#if defined(JIT_TEST_MODE) || defined(AOT_TEST_MODE)
  EXPECT_TRUE(Utils::isSubstring(lowerCaseOutput, expected_output));
#elif REPL_TEST_MODE
  EXPECT_TRUE(lowerCaseOutput.find(expected_output) != std::string::npos);
#endif
}
TEST_F(JITFunction, IntReturnTypeWithNoReturn2) {
  std::string input = R"(fun main2()-> int {
}print(main2()))";

  setInput(input);
  runEvaluator();
  // Expected output should be in the of the output
  std::string lowerCaseOutput = getOutput();

  std::transform(lowerCaseOutput.begin(), lowerCaseOutput.end(),
                 lowerCaseOutput.begin(), ::tolower);

  std::string expected_output =
      R"(JITFunction return type is not Nothing, return expression is not found)";
  std::transform(expected_output.begin(), expected_output.end(),
                 expected_output.begin(), ::tolower);
#if defined(JIT_TEST_MODE) || defined(AOT_TEST_MODE)
  EXPECT_TRUE(Utils::isSubstring(lowerCaseOutput, expected_output));
#elif REPL_TEST_MODE
  EXPECT_TRUE(lowerCaseOutput.find(expected_output) != std::string::npos);
#endif
}

TEST_F(JITFunction, IntReturnTypeWithStrReturnValue2) {
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
      R"(Return Type Mismatch Integer is expected but String is found)";
  std::transform(expected_output.begin(), expected_output.end(),
                 expected_output.begin(), ::tolower);
#if defined(JIT_TEST_MODE) || defined(AOT_TEST_MODE)
  EXPECT_TRUE(Utils::isSubstring(lowerCaseOutput, expected_output));
#elif REPL_TEST_MODE
  EXPECT_TRUE(lowerCaseOutput.find(expected_output) != std::string::npos);
#endif
}

TEST_F(JITFunction, IntReturnTypeWithBoolReturnValue2) {
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
      R"(Return Type Mismatch Integer is expected but Boolean is found)";
  std::transform(expected_output.begin(), expected_output.end(),
                 expected_output.begin(), ::tolower);

#if defined(JIT_TEST_MODE) || defined(AOT_TEST_MODE)
  EXPECT_TRUE(Utils::isSubstring(lowerCaseOutput, expected_output));
#elif REPL_TEST_MODE
  EXPECT_TRUE(lowerCaseOutput.find(expected_output) != std::string::npos);
#endif
}

TEST_F(JITFunction, IntReturnTypeWithBoolReturnValueFalse2) {
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
      R"(Return Type Mismatch Integer is expected but Boolean is found)";
  std::transform(expected_output.begin(), expected_output.end(),
                 expected_output.begin(), ::tolower);
#if defined(JIT_TEST_MODE) || defined(AOT_TEST_MODE)
  EXPECT_TRUE(Utils::isSubstring(lowerCaseOutput, expected_output));
#elif REPL_TEST_MODE
  EXPECT_TRUE(lowerCaseOutput.find(expected_output) != std::string::npos);
#endif
}
TEST_F(JITFunction, IntReturnTypeWithDeciReturnValue2) {
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
      R"(Return Type Mismatch Integer is expected but Decimal is found)";
  std::transform(expected_output.begin(), expected_output.end(),
                 expected_output.begin(), ::tolower);
#if defined(JIT_TEST_MODE) || defined(AOT_TEST_MODE)
  EXPECT_TRUE(Utils::isSubstring(lowerCaseOutput, expected_output));
#elif REPL_TEST_MODE
  EXPECT_TRUE(lowerCaseOutput.find(expected_output) != std::string::npos);
#endif
}

// Bool Return Type

TEST_F(JITFunction, BoolReturnTypeWithIntReturnValue2) {
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
      R"(Return Type Mismatch Boolean is expected but Integer is found)";
  std::transform(expected_output.begin(), expected_output.end(),
                 expected_output.begin(), ::tolower);
#if defined(JIT_TEST_MODE) || defined(AOT_TEST_MODE)
  EXPECT_TRUE(Utils::isSubstring(lowerCaseOutput, expected_output));
#elif REPL_TEST_MODE
  EXPECT_TRUE(lowerCaseOutput.find(expected_output) != std::string::npos);
#endif
}

TEST_F(JITFunction, BoolReturnTypeWithNthgReturnValue2) {
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
      R"(JITFunction return type is not Nothing, return expression is not found)";
  std::transform(expected_output.begin(), expected_output.end(),
                 expected_output.begin(), ::tolower);
#if defined(JIT_TEST_MODE) || defined(AOT_TEST_MODE)
  EXPECT_TRUE(Utils::isSubstring(lowerCaseOutput, expected_output));
#elif REPL_TEST_MODE
  EXPECT_TRUE(lowerCaseOutput.find(expected_output) != std::string::npos);
#endif
}

TEST_F(JITFunction, BoolReturnTypeWithNoReturn2) {
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
      R"(JITFunction return type is not Nothing, return expression is not found)";
  std::transform(expected_output.begin(), expected_output.end(),
                 expected_output.begin(), ::tolower);
#if defined(JIT_TEST_MODE) || defined(AOT_TEST_MODE)
  EXPECT_TRUE(Utils::isSubstring(lowerCaseOutput, expected_output));
#elif REPL_TEST_MODE
  EXPECT_TRUE(lowerCaseOutput.find(expected_output) != std::string::npos);
#endif
}

TEST_F(JITFunction, BoolReturnTypeWithStringReturnValue2) {
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
      R"(Return Type Mismatch Boolean is expected but String is found)";
  std::transform(expected_output.begin(), expected_output.end(),
                 expected_output.begin(), ::tolower);
#if defined(JIT_TEST_MODE) || defined(AOT_TEST_MODE)
  EXPECT_TRUE(Utils::isSubstring(lowerCaseOutput, expected_output));
#elif REPL_TEST_MODE
  EXPECT_TRUE(lowerCaseOutput.find(expected_output) != std::string::npos);
#endif
}

TEST_F(JITFunction, BoolReturnTypeWithBoolReturnValueTrue2) {
  I(R"(
fun mainTest()-> bool {
return true
}
print(mainTest())
)");

  O(R"(true)");
}

TEST_F(JITFunction, BoolReturnTypeWithBoolReturnValueFalse2) {
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

TEST_F(JITFunction, BoolReturnTypeWithDeciReturnValue2) {
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
      R"(Return Type Mismatch Boolean is expected but Decimal is found)";
  std::transform(expected_output.begin(), expected_output.end(),
                 expected_output.begin(), ::tolower);
#if defined(JIT_TEST_MODE) || defined(AOT_TEST_MODE)
  EXPECT_TRUE(Utils::isSubstring(lowerCaseOutput, expected_output));
#elif REPL_TEST_MODE
  EXPECT_TRUE(lowerCaseOutput.find(expected_output) != std::string::npos);
#endif
}

// String Return Type

TEST_F(JITFunction, StringReturnTypeWithIntReturnValue2) {
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
      R"(Return Type Mismatch String is expected but Integer is found)";
  std::transform(expected_output.begin(), expected_output.end(),
                 expected_output.begin(), ::tolower);
#if defined(JIT_TEST_MODE) || defined(AOT_TEST_MODE)
  EXPECT_TRUE(Utils::isSubstring(lowerCaseOutput, expected_output));
#elif REPL_TEST_MODE
  EXPECT_TRUE(lowerCaseOutput.find(expected_output) != std::string::npos);
#endif
}

TEST_F(JITFunction, StringReturnTypeWithNthgReturnValue2) {
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
      R"(JITFunction return type is not Nothing, return expression is not found)";
  std::transform(expected_output.begin(), expected_output.end(),
                 expected_output.begin(), ::tolower);
#if defined(JIT_TEST_MODE) || defined(AOT_TEST_MODE)
  EXPECT_TRUE(Utils::isSubstring(lowerCaseOutput, expected_output));
#elif REPL_TEST_MODE
  EXPECT_TRUE(lowerCaseOutput.find(expected_output) != std::string::npos);
#endif
}

TEST_F(JITFunction, StringReturnTypeWithNoReturnValue2) {
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
      R"(JITFunction return type is not Nothing, return expression is not found)";
  std::transform(expected_output.begin(), expected_output.end(),
                 expected_output.begin(), ::tolower);
#if defined(JIT_TEST_MODE) || defined(AOT_TEST_MODE)
  EXPECT_TRUE(Utils::isSubstring(lowerCaseOutput, expected_output));
#elif REPL_TEST_MODE
  EXPECT_TRUE(lowerCaseOutput.find(expected_output) != std::string::npos);
#endif
}

TEST_F(JITFunction, StringReturnTypeWithBoolReturnValueTrue2) {
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
      R"(Return Type Mismatch String is expected but Boolean is found)";
  std::transform(expected_output.begin(), expected_output.end(),
                 expected_output.begin(), ::tolower);
#if defined(JIT_TEST_MODE) || defined(AOT_TEST_MODE)
  EXPECT_TRUE(Utils::isSubstring(lowerCaseOutput, expected_output));
#elif REPL_TEST_MODE
  EXPECT_TRUE(lowerCaseOutput.find(expected_output) != std::string::npos);
#endif
}

TEST_F(JITFunction, StringReturnTypeWithBoolReturnValueFalse2) {
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
      R"(Return Type Mismatch String is expected but Boolean is found)";
  std::transform(expected_output.begin(), expected_output.end(),
                 expected_output.begin(), ::tolower);
#if defined(JIT_TEST_MODE) || defined(AOT_TEST_MODE)
  EXPECT_TRUE(Utils::isSubstring(lowerCaseOutput, expected_output));
#elif REPL_TEST_MODE
  EXPECT_TRUE(lowerCaseOutput.find(expected_output) != std::string::npos);
#endif
}

TEST_F(JITFunction, StringReturnTypeWithDeciReturnValue2) {
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

TEST_F(JITFunction, NthgReturnTypeWithNthgReturnValue2) {
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
TEST_F(JITFunction, NthgReturnTypeWithNoReturnValue2) {
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

#endif

#if defined(JIT_TEST_MODE) || defined(AOT_TEST_MODE)

TEST_F(JITFunction, StringReturnTypeWithStringReturnValue2) {
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

TEST_F(JITFunction, SumOfNNumbersUsingRecursion2) {
  I(R"(
fun sum(n:int) -> int {
  if (n == 0) {
    return 0
  }
  return n + sum(n - 1)
}
print(sum(10))
)");
  O(R"(55)");
}

// sum of n numbers using loop

TEST_F(JITFunction, SumOfNNumbersUsingLoop2) {
  std::string input = R"(
fun sum(n:int) -> int {
  var sum:int = 0
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

TEST_F(JITFunction, FactorialOfANumberUsingRecursion2) {
  std::string input = R"(
fun factorial(n:int) -> int {
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

TEST_F(JITFunction, FactorialOfANumberUsingLoop2) {
  std::string input = R"(
fun factorial(n:int) -> int {
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

TEST_F(JITFunction, FibonacciOfANumberUsingRecursion2) {
  std::string input = R"(
fun fibonacci(n:int) -> int {
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

TEST_F(JITFunction, FibonacciOfANumberUsingLoop2) {
  std::string input = R"(
fun fibonacci(n:int) -> int {
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

TEST_F(JITFunction, GCDOfTwoNumbersUsingRecuhrsion2) {
  std::string input = R"(
fun gcd(a:int, b:int) -> int {
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

TEST_F(JITFunction, GCDOfTwoNumbersUsingLoop2) {
  std::string input = R"(
fun gcd(a:int, b:int) -> int {
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

TEST_F(JITFunction, LCMOfTwoNumbersUsingRecursion2) {
  std::string input = R"(
fun gcd(a:int, b:int) -> int {
  if (b == 0) {
    return a
  }
  return gcd(b, a % b)
}
fun lcm(a:int, b:int) -> int {
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

TEST_F(JITFunction, LCMOfTwoNumbersUsingLoop2) {
  std::string input = R"(
fun gcd(a:int, b:int) -> int {
  while (b != 0) {
    var temp = b
    b = a % b
    a = temp
  }
  return a
}

fun lcm(a:int, b:int) -> int {
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

TEST_F(JITFunction, PowerOfANumberUsingRecursion2) {
  std::string input = R"(
fun power(base:int, exp:int) -> int {
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

TEST_F(JITFunction, PowerOfANumberUsingLoop2) {
  std::string input = R"(
fun power(base:int, exp:int) -> int {
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

TEST_F(JITFunction, SumOfDigitsOfANumberUsingRecursion2) {
  std::string input = R"(

fun sumOfDigits(n:int) -> int {
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

TEST_F(JITFunction, SumOfDigitsOfANumberUsingLoop2) {
  std::string input = R"(
fun sumOfDigits(n:int) -> int {
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

TEST_F(JITFunction, SumOfDigitsOfANumberUsingLoopWhile2) {
  std::string input = R"(
fun sumOfDigits(n:int) -> int {
  var sum:int = 0
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

TEST_F(JITFunction, FunctionStringTest) {
  std::string input = R"(

fun getConactString(b:str,a:str)-> str {

    return a + b
}

print(getConactString("Hello","World"))
)";
  setInput(input);
  runEvaluator();
  std::string lowerCaseOutput = getOutput();
  std::string expected_output = "WorldHello";
  EXPECT_EQ(lowerCaseOutput, expected_output);
}

TEST_F(JITFunction, FunctionIntTest) {
  std::string input = R"(
fun getSum(a:int,b:int)-> int {
    return a + b
}

print(getSum(2,3))
)";
  setInput(input);
  runEvaluator();
  std::string lowerCaseOutput = getOutput();
  std::string expected_output = "5";
  EXPECT_EQ(lowerCaseOutput, expected_output);
}

TEST_F(JITFunction, FunctionBoolTest) {
  std::string input = R"(
fun getBool(a:bool,b:bool)-> bool {
    return a && b
}

print(getBool(true,false))
)";
  setInput(input);
  runEvaluator();
  std::string lowerCaseOutput = getOutput();
  std::string expected_output = "false";
  EXPECT_EQ(lowerCaseOutput, expected_output);
}

TEST_F(JITFunction, FunctionDeciTest) {
  std::string input = R"(

fun getSum(a:deci,b:deci)-> deci {
    return a + b
}

print(getSum(2.2,3.3))
)";
  setInput(input);
  runEvaluator();
  std::string lowerCaseOutput = getOutput();
  std::string expected_output = "5.50000000000000";
  EXPECT_EQ(lowerCaseOutput, expected_output);
}

// TODO: Nthg Tests are Pending

// TEST_F(JITFunction, FunctionNthgTest) {
//   std::string input = R"(
// fun getNthg(a:nthg,b:nthg)-> nthg {
//     return:
// }

// print(getNthg(2,null))
// )";
//   setInput(input);
//   runEvaluator();
//   std::string lowerCaseOutput = getOutput();
//   std::string expected_output = "";
//   EXPECT_EQ(lowerCaseOutput, expected_output);
// }

TEST_F(JITFunction, FunctionIntWithDeciTest) {
  std::string input = R"(
fun getSum(a:int,b:deci)-> deci {
    return a + b

}

print(getSum(2,3.3))
)";
  setInput(input);
  runEvaluator();
  std::string lowerCaseOutput = getOutput();
  std::string expected_output = "5.30000000000000";
  EXPECT_EQ(lowerCaseOutput, expected_output);
}

TEST_F(JITFunction, FunctionIntWithBoolTest) {
  std::string input = R"(
fun getSum(a:int,b:bool)-> int {
    return a + b

}

print(getSum(2,true))
)";
  setInput(input);
  runEvaluator();
  std::string lowerCaseOutput = getOutput();
  std::string expected_output = "3";
  EXPECT_EQ(lowerCaseOutput, expected_output);
}

TEST_F(JITFunction, FunctionIntWithStringTest) {
  std::string input = R"(
fun getSum(a:int,b:str)-> str {
    return a + b

}

print(getSum(2,"Hello"))
)";
  setInput(input);
  runEvaluator();
  std::string lowerCaseOutput = getOutput();
  std::string expected_output = "2Hello";
  EXPECT_EQ(lowerCaseOutput, expected_output);
}

// TEST_F(JITFunction, FunctionIntWithNthgTest) {
//   std::string input = R"(

// fun getSum(a:int,b:nthg)-> int {
//     return a + b

// }

// print(getSum(2,3))
// )";
//   setInput(input);
//   runEvaluator();
//   std::string lowerCaseOutput = getOutput();
//   std::string expected_output = "5";
//   EXPECT_EQ(lowerCaseOutput, expected_output);
// }

TEST_F(JITFunction, FunctionDeciWithIntTest) {
  std::string input = R"(
fun getSum(a:deci,b:int)-> deci {
    return a + b

}

print(getSum(2.2,3))
)";
  setInput(input);
  runEvaluator();
  std::string lowerCaseOutput = getOutput();
  std::string expected_output = "5.20000000000000";
  EXPECT_EQ(lowerCaseOutput, expected_output);
}

TEST_F(JITFunction, FunctionDeciWithDeciTest) {
  std::string input = R"(

fun getSum(a:deci,b:deci)-> deci {
    return a + b

}

print(getSum(2.2,3.3))
)";
  setInput(input);
  runEvaluator();
  std::string lowerCaseOutput = getOutput();
  std::string expected_output = "5.50000000000000";
  EXPECT_EQ(lowerCaseOutput, expected_output);
}

TEST_F(JITFunction, FunctionDeciWithBoolTest) {
  std::string input = R"(

fun getSum(a:deci,b:bool)-> deci {
    return a + b

}

print(getSum(2.2,true))
)";
  setInput(input);
  runEvaluator();
  std::string lowerCaseOutput = getOutput();
  std::string expected_output = "3.20000000000000";
  EXPECT_EQ(lowerCaseOutput, expected_output);
}

TEST_F(JITFunction, FunctionDeciWithStringTest) {
  std::string input = R"(

fun getSum(a:deci,b:str)-> str {
    return a + b

}

print(getSum(2.2,"Hello"))
)";
  setInput(input);
  runEvaluator();
  std::string lowerCaseOutput = getOutput();
  std::string expected_output = "2.20000000000000Hello";
  EXPECT_EQ(lowerCaseOutput, expected_output);
}

// TEST_F(JITFunction, FunctionDeciWithNthgTest) {
//   std::string input = R"(

// fun getSum(a:deci,b:nthg)-> deci {
//     return a + b

// }

// print(getSum(2.2,3))
// )";
//   setInput(input);
//   runEvaluator();
//   std::string lowerCaseOutput = getOutput();
//   std::string expected_output = "5.200000";
//   EXPECT_EQ(lowerCaseOutput, expected_output);
// }

TEST_F(JITFunction, FunctionBoolWithIntTest) {
  std::string input = R"(

fun getSum(a:bool,b:int)-> int {
    return a + b

}

print(getSum(true,3))
)";
  setInput(input);
  runEvaluator();
  std::string lowerCaseOutput = getOutput();
  std::string expected_output = "4";
  EXPECT_EQ(lowerCaseOutput, expected_output);
}

TEST_F(JITFunction, FunctionBoolWithDeciTest) {
  std::string input = R"(

fun getSum(a:bool,b:deci)-> deci {
    return a + b

}

print(getSum(true,3.3))
)";
  setInput(input);
  runEvaluator();
  std::string lowerCaseOutput = getOutput();
  std::string expected_output = "4.30000000000000";
  EXPECT_EQ(lowerCaseOutput, expected_output);
}

TEST_F(JITFunction, FunctionBoolWithBoolTest) {
  std::string input = R"(

fun getSum(a:bool,b:bool)-> bool {
    return a && b

}

print(getSum(true,false))
)";
  setInput(input);
  runEvaluator();
  std::string lowerCaseOutput = getOutput();
  std::string expected_output = "false";
  EXPECT_EQ(lowerCaseOutput, expected_output);
}
#endif
