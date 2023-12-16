#include "ContainerTest.h"

ContainerTest::ContainerTest() {
#ifdef JIT_TEST_MODE
  _test = std::make_unique<JITCompilerTest>();
#endif

#ifdef REPL_TEST_MODE
  _test = std::make_unique<ReplTest>();
#endif
}

void ContainerTest::SetUp() { _test->SetUp(); }

void ContainerTest::TearDown() { _test->TearDown(); }

void ContainerTest::setInput(const std::string &input) {
  _test->setInput(input);
}

std::string ContainerTest::getOutput() const { return _test->getOutput(); }

void ContainerTest::runEvaluator() { _test->runEvaluator(); }

#ifdef JIT_TEST_MODE

TEST_F(ContainerTest, BasicContainerIntDeclaration) {
  std::string input = R"({var a:int[5] = [1, 2, 3, 4, 5] 
print(a)})";

  std::string expected_output = "[1, 2, 3, 4, 5]";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest, BasicContainerStringDeclaration) {
  std::string input = R"({ var a:str[5] = ["a", "b", "c", "d", "e"]
print(a)})";

  std::string expected_output = "[a, b, c, d, e]";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest, BasicContainerBoolDeclaration) {
  std::string input = R"({var a:bool[5] = [true, false, true, false, true]

print(a)})";

  std::string expected_output = "[true, false, true, false, true]";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest, BasicContainerDeciDeclaration) {
  std::string input = R"({var a:deci[5] = [1.1, 2.2, 3.3, 4.4, 5.5]
print(a)})";

  std::string expected_output =
      "[1.1000000000000001, 2.2000000000000002, 3.2999999999999998, "
      "4.4000000000000004, 5.5000000000000000]";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest, BasicContainerIntIndexing) {
  std::string input = R"({var a:int[5] = [1, 2, 3, 4, 5]
print(a[0])})";

  std::string expected_output = "1";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest, BasicContainerStringIndexing) {
  std::string input = R"({var a:str[5] = ["a", "yay", "c", "d", "e"]
print(a[1])})";

  std::string expected_output = "yay";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest, BasicContainerBoolIndexing) {
  std::string input = R"({var a:bool[5] = [true, false, true, false, true]

print(a[2])})";

  std::string expected_output = "true";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest, BasicContainerDeciIndexing) {
  std::string input = R"({var a:deci[5] = [1.1, 2.2, 3.3, 4.4, 5.5]

print(a[3])})";

  std::string expected_output = "4.4000000000000004";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest, BasicContainerIntIndexingAssignment) {
  std::string input = R"({var a:int[5] = [1, 2, 3, 4, 5]
a[0] = 10
print(a[0])})";

  std::string expected_output = "10";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest, BasicContainerUpdate) {
  std::string input = R"({var a:int[5] = [1, 2, 3, 4, 5]
a[0] = 10
print(a)})";

  std::string expected_output = "[10, 2, 3, 4, 5]";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest, BasicContainerStringIndexingAssignment) {
  std::string input = R"({var a:str[5] = ["a", "yay", "c", "d", "e"]
a[1] = "hello"
print(a[1])})";

  std::string expected_output = "hello";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest, BasicContainerBoolIndexingAssignment) {
  std::string input = R"({var a:bool[5] = [true, false, true, false, true]

a[2] = false  
print(a[2])})";

  std::string expected_output = "false";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest, BasicContainerDeciIndexingAssignment) {
  std::string input = R"({var a:deci[5] = [1.1, 2.2, 3.3, 4.4, 5.5]

a[3] = 10.10
print(a[3])})";

  std::string expected_output = "10.0999999999999996";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest, BasicContainerUpdateAssignment) {
  std::string input = R"({var a:int[5] = [1, 2, 3, 4, 5]
a[0] = 10
print(a)})";

  std::string expected_output = "[10, 2, 3, 4, 5]";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

// TEST_F(ContainerTest, BasicContainerOutofBoundsIndexing) {
//   std::string expected_output =
//       "Index out of bounds of 'a' in index expression, array size is 5";

//   try {
//     std::string input = R"({var a:int[5] = [1, 2, 3, 4, 5]
// print(a[10])})";

//     setInput(input);
//     runEvaluator();

//     EXPECT_EQ(getOutput(), expected_output);
//     // If the function does not throw an exception, fail the test
//     FAIL() << "Expected exception not thrown";
//   } catch (const std::runtime_error &e) {
//     // Compare the error message with the expected error message
//     EXPECT_STREQ(
//         e.what(),
//         "Index out of bounds of 'a' in index expression, array size is 5");
//   } catch (...) {
//     // If the thrown exception is not of type std::runtime_error, fail the
//     test FAIL() << "Unexpected exception type thrown";
//   }
// }

TEST_F(ContainerTest, BasicContainerUpdateWithBinaryExpression) {
  std::string input = R"({var a:int[5] = [1, 2, 3, 4, 5]
a[0] = 10 + 10
print(a)})";

  std::string expected_output = "[20, 2, 3, 4, 5]";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest, BasicContainerUpdateWithUnaryExpression) {
  std::string input = R"({var a:int[5] = [1, 2, 3, 4, 5]
a[0] = -10
print(a)})";

  std::string expected_output = "[-10, 2, 3, 4, 5]";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest, BasicContainerUpdateWithFunctionCall) {
  std::string input = R"({var a:int[5] = [1, 2, 3, 4, 5]
a[0] = Int32(10)
print(a)})";

  std::string expected_output = "[10, 2, 3, 4, 5]";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest, BasicContainerUpdateWithVariable) {
  std::string input = R"({var a:int[5] = [1, 2, 3, 4, 5]
var b = 10
a[0] = b
print(a)})";

  std::string expected_output = "[10, 2, 3, 4, 5]";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest, BasicContainerUpdateWithConstVariable) {
  std::string input = R"({var a:int[5] = [1, 2, 3, 4, 5]
const b = 10
a[0] = b
print(a)})";

  std::string expected_output = "[10, 2, 3, 4, 5]";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

// TODO: ADD GLOBAL CONTAINER ASSIGNMENT TESTS

// TEST_F(ContainerTest, BasicContainerOutofBoundsIndexing) {
//   std::string expected_output =
//       "Index out of bounds of 'a' in index expression, array size is 5";

//   try {
//     std::string input = R"({var a:int[5] = [1, 2, 3, 4, 5]
// print(a[10])})";

//     setInput(input);
//     runEvaluator();

//     EXPECT_EQ(getOutput(), expected_output);
//     // If the function does not throw an exception, fail the test
//     FAIL() << "Expected exception not thrown";
//   } catch (const std::runtime_error &e) {
//     // Compare the error message with the expected error message
//     EXPECT_STREQ(
//         e.what(),
//         "Index out of bounds of 'a' in index expression, array size is 5");
//   } catch (...) {
//     // If the thrown exception is not of type std::runtime_error, fail the
//     test FAIL() << "Unexpected exception type thrown";
//   }
// }

TEST_F(ContainerTest, BasicContainerUpdateWithBinaryExpressionGlobal) {
  std::string input = R"(var a:int[5] = [1, 2, 3, 4, 5]
a[0] = 10 + 10
print(a))";

  std::string expected_output = "[20, 2, 3, 4, 5]";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

// TODO: ADD GLOBAL CONTAINER ASSIGNMENT TESTS

TEST_F(ContainerTest, BasicContainerIntDeclarationGlobal) {
  std::string input = R"(var a:int[5] = [1, 2, 3, 4, 5] 
print(a))";

  std::string expected_output = "[1, 2, 3, 4, 5]";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest, BasicContainerStringDeclarationGlobal) {
  std::string input = R"(var a:str[5] = ["a", "b", "c", "d", "e"]
print(a))";

  std::string expected_output = "[a, b, c, d, e]";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest, BasicContainerBoolDeclarationGlobal) {
  std::string input = R"(var a:bool[5] = [true, false, true, false, true]

print(a))";

  std::string expected_output = "[true, false, true, false, true]";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest, BasicContainerDeciDeclarationGlobal) {
  std::string input = R"(var a:deci[5] = [1.1, 2.2, 3.3, 4.4, 5.5]
print(a))";

  std::string expected_output =
      "[1.1000000000000001, 2.2000000000000002, 3.2999999999999998, "
      "4.4000000000000004, 5.5000000000000000]";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest, BasicContainerIntIndexingGlobal) {
  std::string input = R"(var a:int[5] = [1, 2, 3, 4, 5]
print(a[0]))";

  std::string expected_output = "1";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest, BasicContainerStringIndexingGlobal) {
  std::string input = R"(var a:str[5] = ["a", "yay", "c", "d", "e"]
print(a[1]))";

  std::string expected_output = "yay";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest, BasicContainerBoolIndexingGlobal) {
  std::string input = R"(var a:bool[5] = [true, false, true, false, true]

print(a[2]))";

  std::string expected_output = "true";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest, BasicContainerDeciIndexingGlobal) {
  std::string input = R"(var a:deci[5] = [1.1, 2.2, 3.3, 4.4, 5.5]

print(a[3]))";

  std::string expected_output = "4.4000000000000004";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest, BasicContainerIntIndexingAssignmentGlobal) {
  std::string input = R"(var a:int[5] = [1, 2, 3, 4, 5]
a[0] = 10
print(a[0]))";

  std::string expected_output = "10";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest, BasicContainerUpdateGlobal) {
  std::string input = R"(var a:int[5] = [1, 2, 3, 4, 5]
a[0] = 10
print(a))";

  std::string expected_output = "[10, 2, 3, 4, 5]";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest, BasicContainerStringIndexingAssignmentGlobal) {
  std::string input = R"(var a:str[5] = ["a", "yay", "c", "d", "e"]
a[1] = "hello"
print(a[1]))";

  std::string expected_output = "hello";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest, BasicContainerBoolIndexingAssignmentGlobal) {
  std::string input = R"(var a:bool[5] = [true, false, true, false, true]

a[2] = false  
print(a[2]))";

  std::string expected_output = "false";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest, BasicContainerDeciIndexingAssignmentGlobal) {
  std::string input = R"(var a:deci[5] = [1.1, 2.2, 3.3, 4.4, 5.5]

a[3] = 10.10
print(a[3]))";

  std::string expected_output = "10.0999999999999996";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest, BasicContainerUpdateAssignmentGlobal) {
  std::string input = R"(var a:int[5] = [1, 2, 3, 4, 5]
a[0] = 10
print(a))";

  std::string expected_output = "[10, 2, 3, 4, 5]";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

// TEST_F(ContainerTest, BasicContainerOutofBoundsIndexing) {
//   std::string expected_output =
//       "Index out of bounds of 'a' in index expression, array size is 5";

//   try {
//     std::string input = R"({var a:int[5] = [1, 2, 3, 4, 5]
// print(a[10])})";

//     setInput(input);
//     runEvaluator();

//     EXPECT_EQ(getOutput(), expected_output);
//     // If the function does not throw an exception, fail the test
//     FAIL() << "Expected exception not thrown";
//   } catch (const std::runtime_error &e) {
//     // Compare the error message with the expected error message
//     EXPECT_STREQ(
//         e.what(),
//         "Index out of bounds of 'a' in index expression, array size is 5");
//   } catch (...) {
//     // If the thrown exception is not of type std::runtime_error, fail the
//     test FAIL() << "Unexpected exception type thrown";
//   }
// }

TEST_F(ContainerTest, BasicContainerUpdateWithUnaryExpressionGlobal) {
  std::string input = R"(var a:int[5] = [1, 2, 3, 4, 5]
a[0] = -10
print(a))";

  std::string expected_output = "[-10, 2, 3, 4, 5]";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest, BasicContainerUpdateWithFunctionCallGlobal) {
  std::string input = R"(var a:int[5] = [1, 2, 3, 4, 5]
a[0] = Int32(10)
print(a))";

  std::string expected_output = "[10, 2, 3, 4, 5]";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest, BasicContainerUpdateWithVariableGlobal) {
  std::string input = R"(var a:int[5] = [1, 2, 3, 4, 5]
var b = 10
a[0] = b
print(a))";

  std::string expected_output = "[10, 2, 3, 4, 5]";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest, BasicContainerUpdateWithConstVariableGlobal) {
  std::string input = R"(var a:int[5] = [1, 2, 3, 4, 5]
const b = 10
a[0] = b
print(a))";

  std::string expected_output = "[10, 2, 3, 4, 5]";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest, BasicContainerGlobalInsideScopeAccess) {
  std::string input = R"(var a:int[5] = [1, 2, 3, 4, 5]
{
  print(a)
})";

  std::string expected_output = "[1, 2, 3, 4, 5]";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest, BasicContainerGlobalInsideScopeUpdate) {
  std::string input = R"(var a:int[5] = [1, 2, 3, 4, 5]
{
  a[0] = 10
  print(a)
})";

  std::string expected_output = "[10, 2, 3, 4, 5]";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

#endif // JIT_TEST_MODE