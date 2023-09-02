#include "If-Or-If-Else.h"

IfORIFELSEReplTest::IfORIFELSEReplTest() { repl = std::make_unique<Repl>(); }

void IfORIFELSEReplTest::SetUp() {
  saved_cout_buf = std::cout.rdbuf(output_stream.rdbuf());
}
void IfORIFELSEReplTest::TearDown() { std::cout.rdbuf(saved_cout_buf); }

void IfORIFELSEReplTest::setInput(const std::string &input) {
  input_stream.str(input);
}

std::string IfORIFELSEReplTest::getOutput() const {
  return output_stream.str();
}

void IfORIFELSEReplTest::runEvaluator() {
  repl->runTests(input_stream, output_stream);
}

// TESTS

TEST_F(IfORIFELSEReplTest, BasicIfRRepl) {
  std::string input = R"(if(true) { print(5) })";
  std::string expected_output = "5";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(IfORIFELSEReplTest, BasicIfElseRepl) {
  std::string input = R"(if(false) { print( 5) } else { print( 6) })";
  std::string expected_output = "6";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(IfORIFELSEReplTest, BasicIfElseWithDifferentConditionRepl) {
  std::string input = R"(if(2 > 3) { print( 5) } else { print( 6) })";
  std::string expected_output = "6";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(IfORIFELSEReplTest, BasicIfFalseRepl) {
  std::string input = R"(if(false) { print(5) })";
  std::string expected_output = "";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(IfORIFELSEReplTest, BasicNestedIfElseRepl) {
  std::string input =
      R"(if(true) { if(false) { print( 5) } else { print( 6) } } else {
      print( 7) })";
  std::string expected_output = "6";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(IfORIFELSEReplTest, BasicNestedIfElseWithDifferentConditionRepl) {
  std::string input =
      R"(if(true) { if(2 > 3) { print( 5) } else { print( 6) } } else {
      print( 7) })";
  std::string expected_output = "6";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(IfORIFELSEReplTest, BasicIfElseRepl2) {
  std::string input = R"(if(true) { print( 5) } else { print( 6) })";
  std::string expected_output = "5";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(IfORIFELSEReplTest, BasicOrIfRepl) {
  std::string input =
      R"(if(false) { print( 4) } or if(true) { print( 5) } else { print( 6)})";
  std::string expected_output = "5";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(IfORIFELSEReplTest, BasicElseRepl) {
  std::string input = R"(if(false) { print( 4) } else { print( 6) })";
  std::string expected_output = "6";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(IfORIFELSEReplTest, NestedIfElseOrIfRepl) {
  std::string input =
      R"(if(true) { if(2 > 3) { print( 5) } or if(4 > 3) { print( 7) } else {
      print( 8) } } else { print( 9) })";
  std::string expected_output = "7";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(IfORIFELSEReplTest, MultipleOrIfRepl) {
  std::string input =
      R"(if(false) { print( 4) } or if(false) { print( 5) } or if(true) {
      print( 6) } else { print( 7) })";
  std::string expected_output = "6";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(IfORIFELSEReplTest, NestedOrIfElseRepl) {
  std::string input =
      R"(if(false) { print( 4) } or if(true) { if(2 > 3) { print( 5) } else {
      print( 6) } } else { print( 7) })";
  std::string expected_output = "6";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(IfORIFELSEReplTest, ComplexNestedIfOrIfElseRepl) {
  std::string input =
      R"(if(true) { if(false) { print(10) } or if(true) { if(5 > 3) {
      print(15) } else { print(20) } } else { print(25) } } else { print(30)
      })";
  std::string expected_output = "15";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(IfORIFELSEReplTest, ComplexOrIfElseRepl) {
  std::string input =
      R"(if(false) { print(10) } or if(false) { print(20) } or if(true) {
      if(7 > 5) { print(30) } else { print(40) } } else { print(50) })";
  std::string expected_output = "30";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(IfORIFELSEReplTest, ComplexNestedOrIfElseRepl) {
  std::string input =
      R"(if(false) { print(10) } or if(true) { if(false) { print(20) } else {
      if(8 > 5) { print(35) } else { print(45) } } } else { print(50) })";
  std::string expected_output = "35";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}
