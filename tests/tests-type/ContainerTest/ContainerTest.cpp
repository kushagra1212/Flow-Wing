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

TEST_F(ContainerTest, IndexingWithVariable) {
  std::string input = R"(var a:int[5] = [1, 2, 3, 4, 5]
var b = 0
print(a[b])
)";

  std::string expected_output = "1";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest, IndexingWithVariable2) {
  std::string input = R"(var a:int[5] = [1, 2, 3, 4, 5]

var b = 0
a[b] = 10
print(a[b])
)";

  std::string expected_output = "10";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest, IndexingWithVariable3) {
  std::string input = R"(var a:int[5] = [1, 2, 3, 4, 5]

var b = 0
a[b+1] = 10

print(a[b+1])
)";

  std::string expected_output = "10";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest, IndexingWithVariable4) {
  std::string input = R"(var a:int[5] = [1, 2, 3, 4, 5]

var b = 0
a[b+1] = 10

print(a)
)";

  std::string expected_output = "[1, 10, 3, 4, 5]";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest, IndexingWithVariableWithScope) {
  std::string input = R"(var a:int[5] = [1, 2, 3, 4, 5]
{
  var b = 0
  print(a[b])
}
)";

  std::string expected_output = "1";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest, IndexingWithVariableWithScope2) {
  std::string input = R"(var a:int[5] = [1, 2, 3, 4, 5]
{
  var b = 0
  a[b] = 10
  print(a[b])
}
)";

  std::string expected_output = "10";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest, IndexingWithVariableWithScope3) {
  std::string input = R"(var a:int[5] = [1, 2, 3, 4, 5]
{
  var b = 0
  a[b+1] = 10
  print(a[b+1])
}
)";

  std::string expected_output = "10";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest, IndexingWithVariableWithScope4) {
  std::string input = R"(var a:int[5] = [1, 2, 3, 4, 5]
{
  var b = 0
  a[b+1] = 10
  print(a)
}
)";

  std::string expected_output = "[1, 10, 3, 4, 5]";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest, IndexingWithVariableWithScope5) {
  std::string input = R"(var a:int[5] = [1, 2, 3, 4, 5]
{
  var b = 0
  a[b+1] = 10
  print(a[b+1])
}
)";

  std::string expected_output = "10";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest, IndexingForLoopTest) {
  std::string input = R"(var x:int = 5
var a:int[5] = [1,2,3,4,5]
a[x-5] = 9
for(var i = 0  to 4:2) {
    print(a[i]+"\n")
})";

  std::string expected_output = "9\n3\n5\n";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest, IndexingForLoopTest2) {
  std::string input = R"(var x:int = 5
var a:int[5] = [1,2,3,4,5]

for(var i = 0  to 4:2) {
    a[i] = 9
    print(a[i]+"\n")
})";

  std::string expected_output = "9\n9\n9\n";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest, IndexingForLoopTest3) {
  std::string input = R"(var x:int = 5
var a:int[5] = [1,2,3,4,5]

for(var i:int = 0  to 4:2) {
    a[i] = 9
    print(a[i]+"\n")
    print(a[i]+"\n")
}
)";

  std::string expected_output = "9\n9\n9\n9\n9\n9\n";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest, IndexingForWhileLoopTest) {
  std::string input = R"(var x:int = 5
var a:int[5] = [1,2,3,4,5]
a[x-5] = 9
var i = 0
while(i < 5) {
    print(a[i]+"\n")
    i = i + 2
})";

  std::string expected_output = "9\n3\n5\n";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest, IndexingLocalScopeTest) {
  std::string input = R"(var x:int = 5
var a:int[5] = [1,2,3,4,5]
a[x-5] = 9
var i = 0
while(i < 5) {
    print(a[i]+"\n")
    i = i + 2
}
{
    var i = 0
    while(i < 5) {
        print(a[i]+"\n")
        i = i + 2
    }
})";

  std::string expected_output = "9\n3\n5\n9\n3\n5\n";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest, IndexingLocalScopeTestLocalScopeContainer) {
  std::string input = R"(var x:int = 5
{var a:int[5] = [1,2,3,4,5]
a[x-5] = 9
var i = 0
while(i < 5) {
    print(a[i]+"\n")
    i = i + 2
}
{
    var i = 0
    while(i < 5) {
        print(a[i]+"\n")
        i = i + 2
    }
}})";

  std::string expected_output = "9\n3\n5\n9\n3\n5\n";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest, IndexingLocalScopeTestLocalScopeContainerComplex) {
  std::string input = R"(var y = 8
{
    var x:int[10] = [1,2,3,4,5,5]
    for(var i = 0 to 10:y){
        print(x[i])
        print("\n")
    }
    x = [10 fill 10]
    print(x)
    y = y + 8
    x = [y,y]
    print(x)
    y = y - 6
    x = [10 fill y]
    print(x)
})";

  std::string expected_output =
      "1\n0\n[10, 10, 10, 10, 10, 10, 10, 10, 10, 10][16, 16, 10, 10, 10, 10, "
      "10, 10, 10, 10][10, 10, 10, 10, 10, 10, 10, 10, 10, 10]";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest, IndexingLocalScopeTestContainerComplex) {
  std::string input = R"(var y = 8

    var x:int[10] = [1,2,3,4,5,5]
    for(var i = 0 to 10:y){
        print(x[i])
        print("\n")
    }
    x = [10 fill 10]
    print(x)
    y = y + 8
    x = [y,y]
    print(x)
    y = y - 6
    x = [10 fill y]
    print(x)
)";

  std::string expected_output =
      "1\n0\n[10, 10, 10, 10, 10, 10, 10, 10, 10, 10][16, 16, 10, 10, 10, 10, "
      "10, 10, 10, 10][10, 10, 10, 10, 10, 10, 10, 10, 10, 10]";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest, ContainerAssignmentTest) {
  std::string input = R"(
var arr:int[5] = [1,2,3,4,5]
var arr2:int[10] = [3 fill 100]
print(arr2)
arr2 = arr
print(arr2)
)";

  std::string expected_output =
      "[100, 100, 100, 0, 0, 0, 0, 0, 0, 0][1, 2, 3, 4, 5, 0, 0, 0, 0, 0]";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest, ContainerAssignmentScopeTest) {
  std::string input = R"(
var arr:int[5] = [1,2,3,4,5]
var arr2:int[10] = [3 fill 100]
print(arr2)
{
    arr2 = arr
    print(arr2)
}
print(arr2)
arr[0]=20
print(arr)
)";

  std::string expected_output =
      "[100, 100, 100, 0, 0, 0, 0, 0, 0, 0][1, 2, 3, 4, 5, 0, 0, 0, 0, 0][1, "
      "2, 3, 4, 5, 0, 0, 0, 0, 0][20, 2, 3, 4, 5]";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest, ContainerAssignmentScopeTest2) {
  std::string input = R"(
var arr:int[5] = [1,2,3,4,5]
{
    var arr2:int[10] = [3 fill 100]
    print(arr2)
    arr2 = arr
    print(arr2)
}
)";

  std::string expected_output =
      "[100, 100, 100, 0, 0, 0, 0, 0, 0, 0][1, 2, 3, 4, 5, 0, 0, 0, 0, 0]";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest, ContainerAssignmentScopeTest3) {
  std::string input = R"(
    {
        var arr:int[5] = [1,2,3,4,5]
        var arr2:int[10] = [3 fill 100]
        print(arr2)
        arr2 = arr
        print(arr2)
    }

)";

  std::string expected_output =
      "[100, 100, 100, 0, 0, 0, 0, 0, 0, 0][1, 2, 3, 4, 5, 0, 0, 0, 0, 0]";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

// With Scope Fill Assignment Function Tests

TEST_F(
    ContainerTest,
    BasicContainerFillAssignmentIntDeclarationGlobalInsideScopeAccessFunction) {
  std::string input = R"(fun test()-> nthg {
    var a:int[5] = [1, 2, 3, 4, 5]
    {
      a = [2 fill 10]
    
    print(a)
    }
}

test()
)";

  std::string expected_output = "[10, 10, 3, 4, 5]";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest, ContainerTest2D) {
  std::string input = R"(
var x:int[2][3] = [[1,2,3],[4,5,6]]
print(x)
    )";

  std::string expected_output = "[[1, 2, 3], [4, 5, 6]]";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest, ContainerTest2DWithFill) {
  std::string input = R"(
var x:int[2][3] = [2 fill 5]
print(x)
    )";

  std::string expected_output = "[[5, 5, 0], [0, 0, 0]]";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest, ContainerTest2DWithFillScope) {
  std::string input = R"(
{var x:int[2][3] = [2 fill 5]
print(x)}
    )";

  std::string expected_output = "[[5, 5, 0], [0, 0, 0]]";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest, ContainerTest2DScope) {
  std::string input = R"(
{var x:int[2][3] = [[1,2,3],[4,5,6]]
print(x)}
    )";

  std::string expected_output = "[[1, 2, 3], [4, 5, 6]]";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest, ContainerTest2DWithFillScopeBoth) {
  std::string input = R"(
var x:int[2][3] = [2 fill 5]
print(x)
    )";

  std::string expected_output = "[[5, 5, 0], [0, 0, 0]]";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest, ContainerTest2DScopeBoth) {
  std::string input = R"(
var x:int[2][3] = [[1,2,3],[4,5,6]]
print(x)
    )";

  std::string expected_output = "[[1, 2, 3], [4, 5, 6]]";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

// LATER
//  TEST_F(ContainerTest, ContainerAsParameterTest) {
//    std::string input = R"(
//      fun test(arr:int[5]) -> nthg{
//          print(arr)
//      }
//      var arr:int[5] = [1,2,3,4,5]
//      test(arr)
//      )";

//   std::string expected_output = "[1, 2, 3, 4, 5]";

//   setInput(input);
//   runEvaluator();
//   EXPECT_EQ(getOutput(), expected_output);
// }

// TEST_F(ContainerTest, ContainerAsParameterTestAssignment) {
//   std::string input = R"(
//     fun test(arr:int[5])-> nthg{
//         print(arr)
//         arr[0] = 10
//         print(arr)
//     }
//     var arr:int[5] = [1,2,3,4,5]
//     test(arr)
//     )";

//   std::string expected_output = "[1, 2, 3, 4, 5][10, 2, 3, 4, 5]";

//   setInput(input);
//   runEvaluator();
//   EXPECT_EQ(getOutput(), expected_output);
// }

// TEST_F(ContainerTest, ContainerAsParameterTestAssignmentWithScope) {
//   std::string input = R"(
//     fun test(arr:int[5])-> nthg{
//         print(arr)
//         arr[0] = 10
//         print(arr)
//     }
//     var arr:int[5] = [1,2,3,4,5]
//     {
//         test(arr)
//     }
//     )";

//   std::string expected_output = "[1, 2, 3, 4, 5][10, 2, 3, 4, 5]";

//   setInput(input);
//   runEvaluator();
//   EXPECT_EQ(getOutput(), expected_output);
// }

// TEST_F(ContainerTest, ContainerAsParameterTestAssignmentWholeContainer) {
//   std::string input = R"(
//     fun test(arr:int[5])-> nthg{
//         print(arr)
//         arr = [10,10,10,10,10]
//         print(arr)
//     }
//     var arr:int[5] = [1,2,3,4,5]
//     {
//         test(arr)
//     }
//     )";

//   std::string expected_output = "[1, 2, 3, 4, 5][10, 10, 10, 10, 10]";

//   setInput(input);
//   runEvaluator();
//   EXPECT_EQ(getOutput(), expected_output);
// }

// TEST_F(ContainerTest,
//        ContainerAsParameterTestAssignmentWholeContainerWithFill) {
//   std::string input = R"(
//     fun test(arr:int[5])-> nthg{
//         print(arr)
//         arr = [2 fill 10]
//         print(arr)
//     }
//     var arr:int[5] = [1,2,3,4,5]
//     {
//         test(arr)
//     }
//     )";

//   std::string expected_output = "[1, 2, 3, 4, 5][10, 10, 3, 4, 5]";

//   setInput(input);
//   runEvaluator();
//   EXPECT_EQ(getOutput(), expected_output);
// }

//// passng local array as parameter and updating index and printing

// TEST_F(
//     ContainerTest,
//     BasicContainerFillAssignmentIntDeclarationGlobalInsideScopeAccessFunctionParameterLocalUpdateIndex)
//     {
//   std::string input = R"(fun test(a:int[5])-> nthg{

//       a = [2 fill 10]

//     print(a)
//     a[0] = 100
//     print(a)
// }

// {
//     var a:int[5] = [1, 2, 3, 4, 5]

//     test(a)
//     print(a)
// }
// )";

//   std::string expected_output =
//       "[10, 10, 3, 4, 5][100, 10, 3, 4, 5][1, 2, 3, 4, 5]";

//   setInput(input);
//   runEvaluator();
//   EXPECT_EQ(getOutput(), expected_output);
// }

// // FOr String

// TEST_F(
//     ContainerTest,
//     BasicContainerFillAssignmentStringDeclarationGlobalInsideScopeAccessFunctionParameterLocalUpdateIndex)
//     {
//   std::string input = R"(fun test(a:str[5])-> nthg{

//       a = [2 fill "hello"]

//     print(a)
//     a[0] = "hello world"
//     print(a)
// }

// {
//     var a:str[5] = ["a", "b", "c", "d", "e"]

//     test(a)
//     print(a)
// }
// )";

//   std::string expected_output =
//       "[hello, hello, c, d, e][hello world, hello, c, d, e][a, b, c, d, e]";

//   setInput(input);
//   runEvaluator();
//   EXPECT_EQ(getOutput(), expected_output);
// }

// // For Bool

// TEST_F(
//     ContainerTest,
//     BasicContainerFillAssignmentBoolDeclarationGlobalInsideScopeAccessFunctionParameterLocalUpdateIndex)
//     {
//   std::string input = R"(fun test(a:bool[5])-> nthg{

//       a = [2 fill false]

//     print(a)
//     a[0] = true
//     print(a)
// }

// {
//     var a:bool[5] = [true, false, true, false, true]

//     test(a)
//     print(a)
// }
// )";

//   std::string expected_output =
//       "[false, false, true, false, true][true, false, true, false,
//       true][true, " "false, true, false, true]";

//   setInput(input);
//   runEvaluator();
//   EXPECT_EQ(getOutput(), expected_output);
// }

// // For Deci

// TEST_F(
//     ContainerTest,
//     BasicContainerFillAssignmentDeciDeclarationGlobalInsideScopeAccessFunctionParameterLocalUpdateIndex)
//     {
//   std::string input = R"(fun test(a:deci[5])-> nthg{

//       a = [2 fill 10.10]

//     print(a)
//     a[0] = 100.10
//     print(a)
// }

// {
//     var a:deci[5] = [1.1, 2.2, 3.3, 4.4, 5.5]

//     test(a)
//     print(a)
// }
// )";

//   std::string expected_output =
//       "[10.10000000000000, 10.10000000000000, 3.30000000000000, "
//       "4.40000000000000, 5.50000000000000][100.09999999999999, "
//       "10.10000000000000, 3.30000000000000, 4.40000000000000, "
//       "5.50000000000000][1.10000000000000, 2.20000000000000, 3.30000000000000,
//       " "4.40000000000000, 5.50000000000000]";

//   setInput(input);
//   runEvaluator();
//   EXPECT_EQ(getOutput(), expected_output);
// }

// // For Int

// TEST_F(
//     ContainerTest,
//     BasicContainerFillAssignmentIntDeclarationGlobalInsideScopeAccessFunctionParameterLocalUpdateIndex2)
//     {
//   std::string input = R"(fun test(a:int[5])-> nthg{

//       a = [2 fill 10]

//     print(a)
//     a[0] = 100
//     print(a)
// }

// {
//     var a:int[5] = [1, 2, 3, 4, 5]

//     test(a)
//     print(a)
// }
// )";

//   std::string expected_output =
//       "[10, 10, 3, 4, 5][100, 10, 3, 4, 5][1, 2, 3, 4, 5]";

//   setInput(input);
//   runEvaluator();
//   EXPECT_EQ(getOutput(), expected_output);
// }

// // For Int Bool String Deci in one function call global scope

// TEST_F(
//     ContainerTest,
//     BasicContainerFillAssignmentIntBoolStringDeciDeclarationGlobalInsideScopeAccessFunctionParameterLocalUpdateIndex)
//     {
//   std::string input =
//       R"(fun test(a:int[5], b:bool[5], c:str[5], d:deci[5])-> nthg{

//       a = [2 fill 10]
//       b = [2 fill false]
//       c = [2 fill "hello"]
//       d = [2 fill 10.10]

//     print(a)
//     print(b)
//     print(c)
//     print(d)
//     a[0] = 100
//     b[0] = true
//     c[0] = "hello world"
//     d[0] = 100.10
//     print(a)
//     print(b)
//     print(c)
//     print(d)
// }

// {
//     var a:int[5] = [1, 2, 3, 4, 5]
//     var b:bool[5] = [true, false, true, false, true]
//     var c:str[5] = ["a", "b", "c", "d", "e"]
//     var d:deci[5] = [1.1, 2.2, 3.3, 4.4, 5.5]

//     test(a, b, c, d)
//     print(a)
//     print(b)
//     print(c)
//     print(d)
// }
// )";

//   std::string expected_output =
//       "[10, 10, 3, 4, 5][false, false, true, false, true][hello, hello, c, d,
//       " "e][10.10000000000000, 10.10000000000000, 3.30000000000000, "
//       "4.40000000000000, 5.50000000000000][100, 10, 3, 4, 5][true, false, "
//       "true, false, true][hello world, hello, c, d, e][100.09999999999999, "
//       "10.10000000000000, 3.30000000000000, 4.40000000000000, "
//       "5.50000000000000][1, 2, 3, 4, 5][true, false, true, false, true][a, b,
//       " "c, d, e][1.10000000000000, 2.20000000000000, 3.30000000000000, "
//       "4.40000000000000, 5.50000000000000]";

//   setInput(input);
//   runEvaluator();

//   EXPECT_EQ(getOutput(), expected_output);
// }

// TEST_F(
//     ContainerTest,
//     BasicContainerFillAssignmentIntBoolStringDeciDeclarationGlobalInsideScopeAccessFunctionParameterLocalUpdateIndex2)
//     {
//   std::string input =
//       R"(fun test(a:int[5], b:bool[5], c:str[5], d:deci[5])-> nthg{

//       a = [2 fill 10]
//       b = [2 fill false]
//       c = [2 fill "hello"]
//       d = [2 fill 10.10]

//     print(a)
//     print(b)
//     print(c)
//     print(d)
//     a[0] = 100
//     b[0] = true
//     c[0] = "hello world"
//     d[0] = 100.10
//     print(a)
//     print(b)
//     print(c)
//     print(d)
// }

//     var a:int[5] = [1, 2, 3, 4, 5]
//     var b:bool[5] = [true, false, true, false, true]
//     var c:str[5] = ["a", "b", "c", "d", "e"]
//     var d:deci[5] = [1.1, 2.2, 3.3, 4.4, 5.5]

//     test(a, b, c, d)
//     print(a)
//     print(b)
//     print(c)
//     print(d)

// )";

//   std::string expected_output =
//       "[10, 10, 3, 4, 5][false, false, true, false, true][hello, hello, c, d,
//       " "e][10.10000000000000, 10.10000000000000, 3.30000000000000, "
//       "4.40000000000000, 5.50000000000000][100, 10, 3, 4, 5][true, false, "
//       "true, false, true][hello world, hello, c, d, e][100.09999999999999, "
//       "10.10000000000000, 3.30000000000000, 4.40000000000000, "
//       "5.50000000000000][1, 2, 3, 4, 5][true, false, true, false, true][a, b,
//       " "c, d, e][1.10000000000000, 2.20000000000000, 3.30000000000000, "
//       "4.40000000000000, 5.50000000000000]";

//   setInput(input);
//   runEvaluator();

//   EXPECT_EQ(getOutput(), expected_output);
// }

// // For Int Bool String Deci in one function call local scope

// TEST_F(
//     ContainerTest,
//     BasicContainerFillAssignmentIntBoolStringDeciDeclarationGlobalInsideScopeAccessFunctionParameterLocalUpdateIndexLocalScope)
//     {
//   std::string input =
//       R"(fun test(a:int[5], b:bool[5], c:str[5], d:deci[5])-> nthg{
//     {
//       a = [2 fill 10]
//       b = [2 fill false]
//       c = [2 fill "hello"]
//       d = [2 fill 10.10]

//     print(a)
//     print(b)
//     print(c)
//     print(d)
//     a[0] = 100
//     b[0] = true
//     c[0] = "hello world"
//     d[0] = 100.10
//     print(a)
//     print(b)
//     print(c)
//     print(d)
//     }
// }

// {
//     var a:int[5] = [1, 2, 3, 4, 5]
//     var b:bool[5] = [true, false, true, false, true]
//     var c:str[5] = ["a", "b", "c", "d", "e"]
//     var d:deci[5] = [1.1, 2.2, 3.3, 4.4, 5.5]

//     test(a, b, c, d)
//     print(a)
//     print(b)
//     print(c)
//     print(d)
// }
// )";

//   std::string expected_output =
//       "[10, 10, 3, 4, 5][false, false, true, false, true][hello, hello, c, d,
//       " "e][10.10000000000000, 10.10000000000000, 3.30000000000000, "
//       "4.40000000000000, 5.50000000000000][100, 10, 3, 4, 5][true, false, "
//       "true, false, true][hello world, hello, c, d, e][100.09999999999999, "
//       "10.10000000000000, 3.30000000000000, 4.40000000000000, "
//       "5.50000000000000][1, 2, 3, 4, 5][true, false, true, false, true][a, b,
//       " "c, d, e][1.10000000000000, 2.20000000000000, 3.30000000000000, "
//       "4.40000000000000, 5.50000000000000]";

//   setInput(input);

//   runEvaluator();

//   EXPECT_EQ(getOutput(), expected_output);
// }

// // For Int Bool String Deci in one function call local scope

// TEST_F(
//     ContainerTest,
//     BasicContainerFillAssignmentIntBoolStringDeciDeclarationGlobalInsideScopeAccessFunctionParameterLocalUpdateIndexLocalScope2)
//     {
//   std::string input =
//       R"(fun test(a:int[5], b:bool[5], c:str[5], d:deci[5])-> nthg{
//     {
//       a = [2 fill 10]
//       b = [2 fill false]
//       c = [2 fill "hello"]
//       d = [2 fill 10.10]

//     print(a)
//     print(b)
//     print(c)
//     print(d)
//     a[0] = 100
//     b[0] = true
//     c[0] = "hello world"
//     d[0] = 100.10
//     print(a)
//     print(b)
//     print(c)
//     print(d)
//     }
// }

//     var a:int[5] = [1, 2, 3, 4, 5]
//     var b:bool[5] = [true, false, true, false, true]
//     var c:str[5] = ["a", "b", "c", "d", "e"]
//     var d:deci[5] = [1.1, 2.2, 3.3, 4.4, 5.5]

//     test(a, b, c, d)
//     print(a)
//     print(b)
//     print(c)
//     print(d)

// )";

//   std::string expected_output =
//       "[10, 10, 3, 4, 5][false, false, true, false, true][hello, hello, c, d,
//       " "e][10.10000000000000, 10.10000000000000, 3.30000000000000, "
//       "4.40000000000000, 5.50000000000000][100, 10, 3, 4, 5][true, false, "
//       "true, false, true][hello world, hello, c, d, e][100.09999999999999, "
//       "10.10000000000000, 3.30000000000000, 4.40000000000000, "
//       "5.50000000000000][1, 2, 3, 4, 5][true, false, true, false, true][a, b,
//       " "c, d, e][1.10000000000000, 2.20000000000000, 3.30000000000000, "
//       "4.40000000000000, 5.50000000000000]";

//   setInput(input);

//   runEvaluator();

//   EXPECT_EQ(getOutput(), expected_output);
// }

// // For Int Bool String Deci in one function call do not Update array

// TEST_F(
//     ContainerTest,
//     BasicContainerFillAssignmentIntBoolStringDeciDeclarationGlobalInsideScopeAccessFunctionParameterLocalUpdateIndexLocalScope3)
//     {
//   std::string input =
//       R"(fun test(a:int[5], b:bool[5], c:str[5], d:deci[5])-> nthg{

//     print(a)
//     print(b)
//     print(c)
//     print(d)
//     a[0] = 100
//     b[0] = true
//     c[0] = "hello world"
//     d[0] = 100.10
//     print(a)
//     print(b)
//     print(c)
//     print(d)

// }

//     var a:int[5] = [1, 2, 3, 4, 5]
//     var b:bool[5] = [true, false, true, false, true]
//     var c:str[5] = ["a", "b", "c", "d", "e"]
//     var d:deci[5] = [1.1, 2.2, 3.3, 4.4, 5.5]

//     test(a, b, c, d)
//     print(a)
//     print(b)
//     print(c)
//     print(d)

// )";

//   std::string expected_output =
//       "[1, 2, 3, 4, 5][true, false, true, false, true][a, b, c, d, "
//       "e][1.10000000000000, 2.20000000000000, 3.30000000000000, "
//       "4.40000000000000, 5.50000000000000][100, 2, 3, 4, 5][true, false, "
//       "true, false, true][hello world, b, c, d, e][100.09999999999999, "
//       "2.20000000000000, 3.30000000000000, 4.40000000000000, "
//       "5.50000000000000][1, 2, 3, 4, 5][true, false, true, false, true][a, b,
//       " "c, d, e][1.10000000000000, 2.20000000000000, 3.30000000000000, "
//       "4.40000000000000, 5.50000000000000]";

//   setInput(input);

//   runEvaluator();

//   EXPECT_EQ(getOutput(), expected_output);
// }

// // For Int Bool String Deci in one function call do not Update array local
// scope

// TEST_F(
//     ContainerTest,
//     BasicContainerFillAssignmentIntBoolStringDeciDeclarationGlobalInsideScopeAccessFunctionParameterLocalUpdateIndexLocalScope4)
//     {
//   std::string input =
//       R"(fun test(a:int[5], b:bool[5], c:str[5], d:deci[5])-> nthg{
//     {
//     print(a)
//     print(b)
//     print(c)
//     print(d)
//     a[0] = 100
//     b[0] = true
//     c[0] = "hello world"
//     d[0] = 100.10
//     print(a)
//     print(b)
//     print(c)
//     print(d)
//     }
// }

//     var a:int[5] = [1, 2, 3, 4, 5]
//     var b:bool[5] = [true, false, true, false, true]
//     var c:str[5] = ["a", "b", "c", "d", "e"]
//     var d:deci[5] = [1.1, 2.2, 3.3, 4.4, 5.5]

//     test(a, b, c, d)
//     print(a)
//     print(b)
//     print(c)
//     print(d)

// )";

//   std::string expected_output =
//       "[1, 2, 3, 4, 5][true, false, true, false, true][a, b, c, d, "
//       "e][1.10000000000000, 2.20000000000000, 3.30000000000000, "
//       "4.40000000000000, 5.50000000000000][100, 2, 3, 4, 5][true, false, "
//       "true, false, true][hello world, b, c, d, e][100.09999999999999, "
//       "2.20000000000000, 3.30000000000000, 4.40000000000000, "
//       "5.50000000000000][1, 2, 3, 4, 5][true, false, true, false, true][a, b,
//       " "c, d, e][1.10000000000000, 2.20000000000000, 3.30000000000000, "
//       "4.40000000000000, 5.50000000000000]";

//   setInput(input);

//   runEvaluator();

//   EXPECT_EQ(getOutput(), expected_output);
// }

// // For Int Bool String Deci in one function call do not Update array local
// scope

// TEST_F(
//     ContainerTest,
//     BasicContainerFillAssignmentIntBoolStringDeciDeclarationGlobalInsideScopeAccessFunctionParameterLocalUpdateIndexLocalScope5)
//     {
//   std::string input =
//       R"(fun test(a:int[5], b:bool[5], c:str[5], d:deci[5])-> nthg{
//     {
//     print(a)
//     print(b)
//     print(c)
//     print(d)
//     a[0] = 100
//     b[0] = true
//     c[0] = "hello world"
//     d[0] = 100.10
//     print(a)
//     print(b)
//     print(c)
//     print(d)
//     }
// }

//     var a:int[5] = [1, 2, 3, 4, 5]
//     var b:bool[5] = [true, false, true, false, true]
//     var c:str[5] = ["a", "b", "c", "d", "e"]
//     var d:deci[5] = [1.1, 2.2, 3.3, 4.4, 5.5]

//     test(a, b, c, d)
//     print(a)
//     print(b)
//     print(c)
//     print(d)

// )";

//   std::string expected_output =
//       "[1, 2, 3, 4, 5][true, false, true, false, true][a, b, c, d, "
//       "e][1.10000000000000, 2.20000000000000, 3.30000000000000, "
//       "4.40000000000000, 5.50000000000000][100, 2, 3, 4, 5][true, false, "
//       "true, false, true][hello world, b, c, d, e][100.09999999999999, "
//       "2.20000000000000, 3.30000000000000, 4.40000000000000, "
//       "5.50000000000000][1, 2, 3, 4, 5][true, false, true, false, true][a, b,
//       " "c, d, e][1.10000000000000, 2.20000000000000, 3.30000000000000, "
//       "4.40000000000000, 5.50000000000000]";

//   setInput(input);

//   runEvaluator();

//   EXPECT_EQ(getOutput(), expected_output);
// }

// // For Int Bool String Deci in one function call do not Update array Global
// // scope

// TEST_F(
//     ContainerTest,
//     BasicContainerFillAssignmentIntBoolStringDeciDeclarationGlobalInsideScopeAccessFunctionParameterLocalUpdateIndexLocalScope6)
//     {
//   std::string input =
//       R"(fun test(a:int[5], b:bool[5], c:str[5], d:deci[5])-> nthg{

//     print(a)
//     print(b)
//     print(c)
//     print(d)
//     a[0] = 100
//     b[0] = true
//     c[0] = "hello world"
//     d[0] = 100.10
//     print(a)
//     print(b)
//     print(c)
//     print(d)
// }

//     var a:int[5] = [1, 2, 3, 4, 5]
//     var b:bool[5] = [true, false, true, false, true]
//     var c:str[5] = ["a", "b", "c", "d", "e"]
//     var d:deci[5] = [1.1, 2.2, 3.3, 4.4, 5.5]

//     test(a, b, c, d)
//     print(a)
//     print(b)
//     print(c)
//     print(d)

// )";

//   std::string expected_output =
//       "[1, 2, 3, 4, 5][true, false, true, false, true][a, b, c, d, "
//       "e][1.10000000000000, 2.20000000000000, 3.30000000000000, "
//       "4.40000000000000, 5.50000000000000][100, 2, 3, 4, 5][true, false,
//       true, " "false, true][hello world, b, c, d, e][100.09999999999999, "
//       "2.20000000000000, 3.30000000000000, 4.40000000000000, "
//       "5.50000000000000][1, 2, 3, 4, 5][true, false, true, false, true][a, b,
//       " "c, d, e][1.10000000000000, 2.20000000000000, 3.30000000000000, "
//       "4.40000000000000, 5.50000000000000]";

//   setInput(input);

//   runEvaluator();

//   EXPECT_EQ(getOutput(), expected_output);
// }

// //Passing as parameter with scope local

// TEST_F(
//     ContainerTest,
//     BasicContainerFillAssignmentIntDeclarationGlobalInsideScopeAccessFunctionParameter)
//     {
//   std::string input = R"(fun test(a:int[5])-> nthg{
//     {
//       a = [2 fill 10]

//     print(a)
//     }
// }

// var a:int[5] = [1, 2, 3, 4, 5]

// test(a)
// )";

//   std::string expected_output = "[10, 10, 3, 4, 5]";

//   setInput(input);
//   runEvaluator();
//   EXPECT_EQ(getOutput(), expected_output);
// }

// // Pssing local array as parameter

// TEST_F(
//     ContainerTest,
//     BasicContainerFillAssignmentIntDeclarationGlobalInsideScopeAccessFunctionParameterLocal)
//     {
//   std::string input = R"(fun test(a:int[5])-> nthg{
//     {
//       a = [2 fill 10]

//     print(a)
//     }
// }

// {
//     var a:int[5] = [1, 2, 3, 4, 5]

//     test(a)
// }
// )";

//   std::string expected_output = "[10, 10, 3, 4, 5]";

//   setInput(input);
//   runEvaluator();
//   EXPECT_EQ(getOutput(), expected_output);
// }

// // passng local array as parameter and updating and printing

// TEST_F(
//     ContainerTest,
//     BasicContainerFillAssignmentIntDeclarationGlobalInsideScopeAccessFunctionParameterLocalUpdate)
//     {
//   std::string input = R"(fun test(a:int[5])-> nthg{

//       a = [2 fill 10]

//     print(a)

// }

// {
//     var a:int[5] = [1, 2, 3, 4, 5]

//     test(a)
//     print(a)
// }
// )";

//   std::string expected_output = "[10, 10, 3, 4, 5][1, 2, 3, 4, 5]";

//   setInput(input);
//   runEvaluator();
//   EXPECT_EQ(getOutput(), expected_output);
// }
// TEST_F(ContainerTest, ContainerTestComplexWithFunctionCall) {
//   std::string input = R"(
// fun main(arr:int[5]) -> nthg {
//     var x:int[5] = [5 fill 100]
//     x = arr
//     x[3] = 10
//     print(x)

// }
// var x:int[10] = [10 fill 2]
// main(x)
// x[4]  = 7
// main(x)

//     )";

//   std::string expected_output = "[2, 2, 2, 10, 2][2, 2, 2, 10, 7]";

//   setInput(input);
//   runEvaluator();
//   EXPECT_EQ(getOutput(), expected_output);
// }
#endif // JIT_TEST_MODE