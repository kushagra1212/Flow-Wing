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
      "[1.10000000000000, 2.20000000000000, 3.30000000000000, "
      "4.40000000000000, 5.50000000000000]";
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

  std::string expected_output = "4.40000000000000";
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

  std::string expected_output = "10.10000000000000";
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
      "[1.10000000000000, 2.20000000000000, 3.30000000000000, "
      "4.40000000000000, 5.50000000000000]";
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

  std::string expected_output = "4.40000000000000";
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

  std::string expected_output = "10.10000000000000";
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

// Container Assignment Tests

TEST_F(ContainerTest, BasicContainerAssignmentIntDeclaration) {
  std::string input = R"({var a:int[5] = [1, 2, 3, 4, 5]
  a = [10, 20, 30, 40, 50]

print(a)})";

  std::string expected_output = "[10, 20, 30, 40, 50]";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest, BasicContainerAssignmentStringDeclaration) {
  std::string input = R"({var a:str[5] = ["a", "b", "c", "d", "e"]
  a = ["hello", "world", "this", "is", "a"]

print(a)})";

  std::string expected_output = "[hello, world, this, is, a]";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest, BasicContainerAssignmentBoolDeclaration) {
  std::string input = R"({var a:bool[5] = [true, false, true, false, true]
  a = [false, true, false, true, false]

print(a)})";

  std::string expected_output = "[false, true, false, true, false]";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest, BasicContainerAssignmentDeciDeclaration) {
  std::string input = R"({var a:deci[5] = [1.1, 2.2, 3.3, 4.4, 5.5]
  a = [10.10, 20.20, 30.35, 40.40, 50.50]

print(a)})";

  std::string expected_output =
      "[10.10000000000000, 20.20000000000000, "
      "30.35000000000000, 40.40000000000000, 50.50000000000000]";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest, BasicContainerAssignmentPartialIntDeclaration) {
  std::string input = R"({var a:int[5] = [1, 2, 3, 4, 5]
  a = [10, 20, 30]

print(a)})";

  std::string expected_output = "[10, 20, 30, 4, 5]";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest, BasicContainerAssignmentPartialStringDeclaration) {
  std::string input = R"({var a:str[5] = ["a", "b", "c", "d", "e"]
  a = ["hello", "world", "this"]

print(a)})";

  std::string expected_output = "[hello, world, this, d, e]";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest, BasicContainerAssignmentPartialBoolDeclaration) {
  std::string input = R"({var a:bool[5] = [true, false, true, false, true]
  a = [false, true, false]


print(a)})";

  std::string expected_output = "[false, true, false, false, true]";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest, BasicContainerAssignmentPartialDeciDeclaration) {
  std::string input = R"({var a:deci[5] = [1.1, 2.2, 3.3, 4.4, 5.5]
  a = [10.10, 20.20, 30.30]

print(a)})";

  std::string expected_output =
      "[10.10000000000000, 20.20000000000000, 30.30000000000000, "
      "4.40000000000000, 5.50000000000000]";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest, BasicContainerAssignmentPartialIntDeclarationGlobal) {
  std::string input = R"(var a:int[5] = [1, 2, 3, 4, 5]
  a = [10, 20, 30]


print(a))";

  std::string expected_output = "[10, 20, 30, 4, 5]";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest, BasicContainerAssignmentPartialStringDeclarationGlobal) {
  std::string input = R"(var a:str[5] = ["a", "b", "c", "d", "e"]
  a = ["hello", "world", "this"]

print(a))";

  std::string expected_output = "[hello, world, this, d, e]";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest, BasicContainerAssignmentPartialBoolDeclarationGlobal) {
  std::string input = R"(var a:bool[5] = [true, false, true, false, true]
  a = [false, true, false]


print(a))";

  std::string expected_output = "[false, true, false, false, true]";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest, BasicContainerAssignmentPartialDeciDeclarationGlobal) {
  std::string input = R"(var a:deci[5] = [1.1, 2.2, 3.3, 4.4, 5.5]
  a = [10.10, 20.20, 30.30]

print(a))";

  std::string expected_output =
      "[10.10000000000000, 20.20000000000000, 30.30000000000000, "
      "4.40000000000000, 5.50000000000000]";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest,
       BasicContainerAssignmentPartialIntDeclarationGlobalInsideScopeAccess) {
  std::string input = R"(var a:int[5] = [1, 2, 3, 4, 5]
{
  a = [10, 20, 30]



  print(a)

})";

  std::string expected_output = "[10, 20, 30, 4, 5]";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(
    ContainerTest,
    BasicContainerAssignmentPartialStringDeclarationGlobalInsideScopeAccess) {
  std::string input = R"(var a:str[5] = ["a", "b", "c", "d", "e"]
{
  a = ["hello", "world", "this"]

print(a)
})";

  std::string expected_output = "[hello, world, this, d, e]";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest,
       BasicContainerAssignmentPartialBoolDeclarationGlobalInsideScopeAccess) {
  std::string input = R"(var a:bool[5] = [true, false, true, false, true]
{
  a = [false, true, false]


print(a)

})";

  std::string expected_output = "[false, true, false, false, true]";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest,
       BasicContainerAssignmentPartialDeciDeclarationGlobalInsideScopeAccess) {
  std::string input = R"(var a:deci[5] = [1.1, 2.2, 3.3, 4.4, 5.5]
{
  a = [10.10, 20.20, 30.30]

print(a)
})";

  std::string expected_output =
      "[10.10000000000000, 20.20000000000000, 30.30000000000000, "
      "4.40000000000000, 5.50000000000000]";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest,
       BasicContainerAssignmentPartialIntDeclarationGlobalInsideScopeUpdate) {
  std::string input = R"(var a:int[5] = [1, 2, 3, 4, 5]
{
  a = [10, 20, 30]


  a[0] = 100
  print(a)

})";

  std::string expected_output = "[100, 20, 30, 4, 5]";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(
    ContainerTest,
    BasicContainerAssignmentPartialStringDeclarationGlobalInsideScopeUpdate) {
  std::string input = R"(var a:str[5] = ["a", "b", "c", "d", "e"]
{
  a = ["hello", "world", "this"]

a[0] = "hello world"

print(a)
})";

  std::string expected_output = "[hello world, world, this, d, e]";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest,
       BasicContainerAssignmentPartialBoolDeclarationGlobalInsideScopeUpdate) {
  std::string input = R"(var a:bool[5] = [true, false, true, false, true]
{
  a = [false, true, false]


a[0] = true
print(a)

})";

  std::string expected_output = "[true, true, false, false, true]";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest,
       BasicContainerAssignmentPartialDeciDeclarationGlobalInsideScopeUpdate) {
  std::string input = R"(var a:deci[5] = [1.1, 2.2, 3.3, 4.4, 5.5]
{
  a = [10.10, 20.20, 30.30]

a[0] = 100.10
print(a)
})";

  std::string expected_output =
      "[100.09999999999999, 20.20000000000000, 30.30000000000000, "
      "4.40000000000000, 5.50000000000000]";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(
    ContainerTest,
    BasicContainerAssignmentPartialIntDeclarationGlobalInsideScopeUpdateWithBinaryExpression) {
  std::string input = R"(var a:int[5] = [1, 2, 3, 4, 5]
{
  a = [10, 20, 30]


  a[0] = 10 + 10

  print(a)

})";

  std::string expected_output = "[20, 20, 30, 4, 5]";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

// Fill Assignment Tests

TEST_F(ContainerTest, BasicContainerFillAssignmentIntDeclaration) {
  std::string input = R"({var a:int[5] = [1, 2, 3, 4, 5]
  a = [2 fill 10]

print(a)})";

  std::string expected_output = "[10, 10, 3, 4, 5]";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest, BasicContainerFillAssignmentStringDeclaration) {
  std::string input = R"({var a:str[5] = ["a", "b", "c", "d", "e"]
  a = [5 fill "hello"]

print(a)})";

  std::string expected_output = "[hello, hello, hello, hello, hello]";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest, BasicContainerFillAssignmentBoolDeclaration) {
  std::string input = R"({var a:bool[5] = [true, false, true, false, true]
  a = [3 fill false]

print(a)})";

  std::string expected_output = "[false, false, false, false, true]";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest, BasicContainerFillAssignmentDeciDeclaration) {
  std::string input = R"({var a:deci[5] = [1.1, 2.2, 3.3, 4.4, 5.5]
  a = [2 fill 10.10]

print(a)})";

  std::string expected_output =
      "[10.10000000000000, 10.10000000000000, 3.30000000000000, "
      "4.40000000000000, 5.50000000000000]";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest, BasicContainerFillAssignmentPartialIntDeclaration) {
  std::string input = R"({var a:int[5] = [1, 2, 3, 4, 5]
  a = [2 fill 10]

print(a)})";

  std::string expected_output = "[10, 10, 3, 4, 5]";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest, BasicContainerFillAssignmentPartialStringDeclaration) {
  std::string input = R"({var a:str[5] = ["a", "b", "c", "d", "e"]
  a = [5 fill "hello"]


print(a)})";

  std::string expected_output = "[hello, hello, hello, hello, hello]";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

// Global Fill Assignment Tests

TEST_F(ContainerTest, BasicContainerFillAssignmentIntDeclarationGlobal) {
  std::string input = R"(var a:int[5] = [1, 2, 3, 4, 5]
  a = [2 fill 10]

print(a))";

  std::string expected_output = "[10, 10, 3, 4, 5]";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest, BasicContainerFillAssignmentStringDeclarationGlobal) {
  std::string input = R"(var a:str[5] = ["a", "b", "c", "d", "e"]
  a = [5 fill "hello"]

print(a))";

  std::string expected_output = "[hello, hello, hello, hello, hello]";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest, BasicContainerFillAssignmentBoolDeclarationGlobal) {
  std::string input = R"(var a:bool[5] = [true, false, true, false, true]
  a = [3 fill false]

print(a))";

  std::string expected_output = "[false, false, false, false, true]";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest, BasicContainerFillAssignmentDeciDeclarationGlobal) {
  std::string input = R"(var a:deci[5] = [1.1, 2.2, 3.3, 4.4, 5.5]
  a = [2 fill 10.10]

print(a))";

  std::string expected_output =
      "[10.10000000000000, 10.10000000000000, 3.30000000000000, "
      "4.40000000000000, 5.50000000000000]";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest, BasicContainerFillAssignmentPartialIntDeclarationGlobal) {
  std::string input = R"(var a:int[5] = [1, 2, 3, 4, 5]
  a = [2 fill 10]

print(a))";

  std::string expected_output = "[10, 10, 3, 4, 5]";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest,
       BasicContainerFillAssignmentPartialStringDeclarationGlobal) {
  std::string input = R"(var a:str[5] = ["a", "b", "c", "d", "e"]
  a = [5 fill "hello"]

print(a))";

  std::string expected_output = "[hello, hello, hello, hello, hello]";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

// Scope Fill Assignment Tests

TEST_F(ContainerTest,
       BasicContainerFillAssignmentIntDeclarationGlobalInsideScopeAccess) {
  std::string input = R"(var a:int[5] = [1, 2, 3, 4, 5]
{
  a = [2 fill 10]

print(a)

})";

  std::string expected_output = "[10, 10, 3, 4, 5]";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest,
       BasicContainerFillAssignmentStringDeclarationGlobalInsideScopeAccess) {
  std::string input = R"(var a:str[5] = ["a", "b", "c", "d", "e"]
{
  a = [5 fill "hello"]

print(a)
})";

  std::string expected_output = "[hello, hello, hello, hello, hello]";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest,
       BasicContainerFillAssignmentBoolDeclarationGlobalInsideScopeAccess) {
  std::string input = R"(var a:bool[5] = [true, false, true, false, true]
{
  a = [3 fill false]
  
print(a)
  
  })";

  std::string expected_output = "[false, false, false, false, true]";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest,
       BasicContainerFillAssignmentDeciDeclarationGlobalInsideScopeAccess) {
  std::string input = R"(var a:deci[5] = [1.1, 2.2, 3.3, 4.4, 5.5]
{
  a = [2 fill 10.10]
}
print(a)

)";

  std::string expected_output =
      "[10.10000000000000, 10.10000000000000, 3.30000000000000, "
      "4.40000000000000, 5.50000000000000]";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(
    ContainerTest,
    BasicContainerFillAssignmentPartialIntDeclarationGlobalInsideScopeAccess) {
  std::string input = R"(var a:int[5] = [1, 2, 3, 4, 5]
{
  a = [2 fill 10]

print(a)
  
  })";

  std::string expected_output = "[10, 10, 3, 4, 5]";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest,
       BasicContainerInitilizationWithVariableInsideScopeAccess) {
  std::string input = R"(var y = 10
    var a:int[5] = [1, 2, 3, 4, y]
    print(a)
  )";

  std::string expected_output = "[1, 2, 3, 4, 10]";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest,
       BasicContainerInitilizationWithVariableInsideScopeUpdate) {
  std::string input = R"(
    var y = 10
    var a:int[5] = [1, 2, 3, 4, y]
    a[0] = 100
    print(a)
  )";

  std::string expected_output = "[100, 2, 3, 4, 10]";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(
    ContainerTest,
    BasicContainerFillAssignmentPartialStringDeclarationGlobalInsideScopeAccess) {

  std::string input = R"(var a:str[5] = ["a", "b", "c", "d", "e"]
{ 
  var res = "hello"
  a = [5 fill res]
print(a)
       }
)";

  std::string expected_output = "[hello, hello, hello, hello, hello]";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(
    ContainerTest,
    BasicContainerFillAssignmentPartialBoolDeclarationGlobalInsideScopeAccess) {
  std::string input = R"(var a:bool[5] = [true, false, true, false, true]
{

  var isBool:bool = false
  var isbool = true
  a = [isBool, isbool, isBool]
print(a)
       }
)";

  std::string expected_output = "[false, true, false, false, true]";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(
    ContainerTest,
    BasicContainerFillAssignmentPartialDeciDeclarationGlobalInsideScopeAccess) {
  std::string input = R"(var a:deci[5] = [1.1, 2.2, 3.3, 4.4, 5.5]
{
  var res = 10.10
  a = [2 fill res]

print(a)
       }

)";

  std::string expected_output =
      "[10.10000000000000, 10.10000000000000, 3.30000000000000, "
      "4.40000000000000, 5.50000000000000]";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest, Complex) {
  std::string input = R"(var res = "hello"
var a:str[5] = ["a", "b", "c", "d", "e"]
{ 
  a = [2 fill res]
  print(a)
  a = ["b"]
  print(a)
  a = [1 fill "u"]
  print(a)
}
a = ["t"]
print(a)
a = [1 fill res]
print(a)
var res2:str = "val"
a = [res2,res2]
print(a)
)";

  std::string expected_output =
      R"([hello, hello, c, d, e][b, hello, c, d, e][u, hello, c, d, e][t, hello, c, d, e][hello, hello, c, d, e][val, val, c, d, e])";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest, Complex2) {
  std::string input = R"({
    var res = "hello"
var a:str[5] = ["a", "b", "c", "d", "e"]
{ 
  a = [2 fill res]
  print(a)
  a = ["b"]
  print(a)
  a = [1 fill "u"]
  print(a)
}
a = ["t"]
print(a)
a = [1 fill res]
print(a)
var res2:str = "val"
a = [res2,res2]
print(a)
{ 
    a = ["balls"]
    print(a)
}
}
)";

  std::string expected_output =
      R"([hello, hello, c, d, e][b, hello, c, d, e][u, hello, c, d, e][t, hello, c, d, e][hello, hello, c, d, e][val, val, c, d, e][balls, val, c, d, e])";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

#endif // JIT_TEST_MODE