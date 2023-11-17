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
  std::string input = R"({container<int> a = [1, 2, 3, 4, 5] 
print(a)})";

  std::string expected_output = "[1, 2, 3, 4, 5]";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest, BasicContainerStringDeclaration) {
  std::string input = R"({container<str> a = ["a", "b", "c", "d", "e"]
print(a)})";

  std::string expected_output = "[a, b, c, d, e]";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest, BasicContainerBoolDeclaration) {
  std::string input = R"({container<bool> a = [true, false, true, false, true]

print(a)})";

  std::string expected_output = "[true, false, true, false, true]";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest, BasicContainerDeciDeclaration) {
  std::string input = R"({container<deci> a = [1.1, 2.2, 3.3, 4.4, 5.5]
print(a)})";

  std::string expected_output =
      "[1.1000000000000001, 2.2000000000000002, 3.2999999999999998, "
      "4.4000000000000004, 5.5000000000000000]";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest, BasicContainerIntIndexing) {
  std::string input = R"({container<int> a = [1, 2, 3, 4, 5]
print(a[0])})";

  std::string expected_output = "1";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest, BasicContainerStringIndexing) {
  std::string input = R"({container<str> a = ["a", "yay", "c", "d", "e"]
print(a[1])})";

  std::string expected_output = "yay";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest, BasicContainerBoolIndexing) {
  std::string input = R"({container<bool> a = [true, false, true, false, true]

print(a[2])})";

  std::string expected_output = "true";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest, BasicContainerDeciIndexing) {
  std::string input = R"({container<deci> a = [1.1, 2.2, 3.3, 4.4, 5.5]

print(a[3])})";

  std::string expected_output = "4.4000000000000004";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest, BasicContainerIntIndexingAssignment) {
  std::string input = R"({container<int> a = [1, 2, 3, 4, 5]
a[0] = 10
print(a[0])})";

  std::string expected_output = "10";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest, BasicContainerUpdate) {
  std::string input = R"({container<int> a = [1, 2, 3, 4, 5]
a[0] = 10
print(a)})";

  std::string expected_output = "[10, 2, 3, 4, 5]";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest, BasicContainerStringIndexingAssignment) {
  std::string input = R"({container<str> a = ["a", "yay", "c", "d", "e"]
a[1] = "hello"
print(a[1])})";

  std::string expected_output = "hello";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest, BasicContainerBoolIndexingAssignment) {
  std::string input = R"({container<bool> a = [true, false, true, false, true]

a[2] = false  
print(a[2])})";

  std::string expected_output = "false";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest, BasicContainerDeciIndexingAssignment) {
  std::string input = R"({container<deci> a = [1.1, 2.2, 3.3, 4.4, 5.5]

a[3] = 10.10
print(a[3])})";

  std::string expected_output = "10.0999999999999996";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest, BasicContainerUpdateAssignment) {
  std::string input = R"({container<int> a = [1, 2, 3, 4, 5]
a[0] = 10
print(a)})";

  std::string expected_output = "[10, 2, 3, 4, 5]";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

// TEST_F(ContainerTest, BasicContainerOutofBoundsIndexing) {
//   std::string input = R"({container<int> a = [1, 2, 3, 4, 5]
// print(a[10])})";

//   setInput(input);
//   runEvaluator();
//   // Expected output should be in the of the output
//   std::string lowerCaseOutput = getOutput();

//   std::transform(lowerCaseOutput.begin(), lowerCaseOutput.end(),
//                  lowerCaseOutput.begin(), ::tolower);

//   std::string expected_output =
//       "Index out of bounds of 'a' in index expression, array size is 5";
//   std::transform(expected_output.begin(), expected_output.end(),
//                  expected_output.begin(), ::tolower);

//   // check expected output is substring of the output or not

//   EXPECT_TRUE(Utils::isSubstring(lowerCaseOutput, expected_output));
// }
TEST_F(ContainerTest, BasicContainerUpdateWithBinaryExpression) {
  std::string input = R"({container<int> a = [1, 2, 3, 4, 5]
a[0] = 10 + 10
print(a)})";

  std::string expected_output = "[20, 2, 3, 4, 5]";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest, BasicContainerUpdateWithUnaryExpression) {
  std::string input = R"({container<int> a = [1, 2, 3, 4, 5]
a[0] = -10
print(a)})";

  std::string expected_output = "[-10, 2, 3, 4, 5]";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest, BasicContainerUpdateWithFunctionCall) {
  std::string input = R"({container<int> a = [1, 2, 3, 4, 5]
a[0] = Int32(10)
print(a)})";

  std::string expected_output = "[10, 2, 3, 4, 5]";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest, BasicContainerUpdateWithVariable) {
  std::string input = R"({container<int> a = [1, 2, 3, 4, 5]
var b = 10
a[0] = b
print(a)})";

  std::string expected_output = "[10, 2, 3, 4, 5]";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(ContainerTest, BasicContainerUpdateWithConstVariable) {
  std::string input = R"({container<int> a = [1, 2, 3, 4, 5]
const b = 10
a[0] = b
print(a)})";

  std::string expected_output = "[10, 2, 3, 4, 5]";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

// TODO: ADD GLOBAL CONTAINER ASSIGNMENT TESTS

#endif // JIT_TEST_MODE