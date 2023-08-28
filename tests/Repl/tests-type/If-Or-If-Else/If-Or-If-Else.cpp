#include "If-Or-If-Else.h"

IfORIFELSEReplTest::IfORIFELSEReplTest() {
  repl = std::make_unique<Repl>(true);
}

void IfORIFELSEReplTest::SetUp() {
  cout_backup = std::cout.rdbuf();
  std::cout.rdbuf(captured_output.rdbuf());
}

void IfORIFELSEReplTest::TearDown() { std::cout.rdbuf(cout_backup); }

std::string IfORIFELSEReplTest::runReplWithInput(const std::string &input) {

  repl->addTextString(input);
  repl->runForTest(std::cin, std::cout);

  return captured_output.str();
}
std::string IfORIFELSEReplTest::runReplWithInputPrint(std::string input) {

  testing::internal::CaptureStdout();

  repl->addTextString(input);
  repl->runForTest(std::cin, std::cout);

  return testing::internal::GetCapturedStdout();
}
TEST_F(IfORIFELSEReplTest, BasicIfRRepl) {
  std::string input = R"(if(true) { print(5) })";
  std::string expected_output = "5";
  std::string capturedOutput = runReplWithInputPrint(input);
  ASSERT_EQ(capturedOutput, expected_output);
}

TEST_F(IfORIFELSEReplTest, BasicIfElseRepl) {
  std::string input = R"(if(false) { print( 5) } else { print( 6) })";
  std::string expected_output = "6";
  std::string capturedOutput = runReplWithInputPrint(input);
  EXPECT_EQ(capturedOutput, expected_output);
}

TEST_F(IfORIFELSEReplTest, BasicIfElseWithDifferentConditionRepl) {
  std::string input = R"(if(2 > 3) { print( 5) } else { print( 6) })";
  std::string expected_output = "6";
  std::string output = runReplWithInputPrint(input);
  EXPECT_EQ(output, expected_output);
}

TEST_F(IfORIFELSEReplTest, BasicIfFalseRepl) {
  std::string input = R"(if(false) { print(5) })";
  std::string expected_output = "";
  std::string output = runReplWithInputPrint(input);
  EXPECT_EQ(output, expected_output);
}

TEST_F(IfORIFELSEReplTest, BasicNestedIfElseRepl) {
  std::string input =
      R"(if(true) { if(false) { print( 5) } else { print( 6) } } else { print( 7) })";
  std::string expected_output = "6";
  std::string output = runReplWithInputPrint(input);
  EXPECT_EQ(output, expected_output);
}

TEST_F(IfORIFELSEReplTest, BasicNestedIfElseWithDifferentConditionRepl) {
  std::string input =
      R"(if(true) { if(2 > 3) { print( 5) } else { print( 6) } } else { print( 7) })";
  std::string expected_output = "6";
  std::string output = runReplWithInputPrint(input);
  EXPECT_EQ(output, expected_output);
}

TEST_F(IfORIFELSEReplTest, BasicIfElseRepl2) {
  std::string input = R"(if(true) { print( 5) } else { print( 6) })";
  std::string expected_output = "5";
  std::string output = runReplWithInputPrint(input);
  EXPECT_EQ(output, expected_output);
}

TEST_F(IfORIFELSEReplTest, BasicOrIfRepl) {
  std::string input =
      R"(if(false) { print( 4) } or if(true) { print( 5) } else { print( 6) })";
  std::string expected_output = "5";
  std::string output = runReplWithInputPrint(input);
  EXPECT_EQ(output, expected_output);
}

TEST_F(IfORIFELSEReplTest, BasicElseRepl) {
  std::string input = R"(if(false) { print( 4) } else { print( 6) })";
  std::string expected_output = "6";
  std::string output = runReplWithInputPrint(input);
  EXPECT_EQ(output, expected_output);
}

TEST_F(IfORIFELSEReplTest, NestedIfElseOrIfRepl) {
  std::string input =
      R"(if(true) { if(2 > 3) { print( 5) } or if(4 > 3) { print( 7) } else { print( 8) } } else { print( 9) })";
  std::string expected_output = "7";
  std::string output = runReplWithInputPrint(input);
  EXPECT_EQ(output, expected_output);
}

TEST_F(IfORIFELSEReplTest, MultipleOrIfRepl) {
  std::string input =
      R"(if(false) { print( 4) } or if(false) { print( 5) } or if(true) { print( 6) } else { print( 7) })";
  std::string expected_output = "6";
  std::string output = runReplWithInputPrint(input);
  EXPECT_EQ(output, expected_output);
}

TEST_F(IfORIFELSEReplTest, NestedOrIfElseRepl) {
  std::string input =
      R"(if(false) { print( 4) } or if(true) { if(2 > 3) { print( 5) } else { print( 6) } } else { print( 7) })";
  std::string expected_output = "6";
  std::string output = runReplWithInputPrint(input);
  EXPECT_EQ(output, expected_output);
}

TEST_F(IfORIFELSEReplTest, ComplexNestedIfOrIfElseRepl) {
  std::string input =
      R"(if(true) { if(false) { print(10) } or if(true) { if(5 > 3) { print(15) } else { print(20) } } else { print(25) } } else { print(30) })";
  std::string expected_output = "15";
  std::string output = runReplWithInputPrint(input);
  EXPECT_EQ(output, expected_output);
}

TEST_F(IfORIFELSEReplTest, ComplexOrIfElseRepl) {
  std::string input =
      R"(if(false) { print(10) } or if(false) { print(20) } or if(true) { if(7 > 5) { print(30) } else { print(40) } } else { print(50) })";
  std::string expected_output = "30";
  std::string output = runReplWithInputPrint(input);
  EXPECT_EQ(output, expected_output);
}

TEST_F(IfORIFELSEReplTest, ComplexNestedOrIfElseRepl) {
  std::string input =
      R"(if(false) { print(10) } or if(true) { if(false) { print(20) } else { if(8 > 5) { print(35) } else { print(45) } } } else { print(50) })";
  std::string expected_output = "35";
  std::string output = runReplWithInputPrint(input);
  EXPECT_EQ(output, expected_output);
}
