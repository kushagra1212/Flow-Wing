#include "For-Loop.h"

ForLoopReplTest::ForLoopReplTest() {
#ifdef JIT_TEST_MODE
  _test = std::make_unique<JITCompilerTest>();
#endif

#ifdef REPL_TEST_MODE
  _test = std::make_unique<ReplTest>();
#endif
}

void ForLoopReplTest::SetUp() { _test->SetUp(); }

void ForLoopReplTest::TearDown() { _test->TearDown(); }

void ForLoopReplTest::setInput(const std::string &input) {
  _test->setInput(input);
}

std::string ForLoopReplTest::getOutput() const { return _test->getOutput(); }

void ForLoopReplTest::runEvaluator() { _test->runEvaluator(); }

// Basic for loop
TEST_F(ForLoopReplTest, BasicForLoop) {
  std::string input = R"(for var i = 0 to 5 { print(i) })";
  std::string expected_output = "012345";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

// Basic for loop without declaration
TEST_F(ForLoopReplTest, BasicForLoopWithoutDeclaration) {
  std::string input = R"(var i = 0 for i to 5 { print(i) })";
  std::string expected_output = "000000";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

// Basic for loop with Bracket
TEST_F(ForLoopReplTest, BasicForLoopWithBracket) {
  std::string input = R"(for (var i = 0 to 5) { print(i) })";
  std::string expected_output = "012345";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

// For loop with step
TEST_F(ForLoopReplTest, ForLoopWithStep) {
  std::string input = R"(for var i = 0 to 5 : 2 { print(i) })";
  std::string expected_output = "024";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

// For loop with negative step
TEST_F(ForLoopReplTest, ForLoopWithNegativeStep) {
  std::string input = R"(for var i = 5 to 0 : -2 { print(i) })";
  std::string expected_output = "531";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

// For loop with  step and negative start value

TEST_F(ForLoopReplTest, ForLoopWithNegativeStepAndNegativeStartValue) {
  std::string input = R"(for var i = -5 to 0 : 2 { print(i) })";

  std::string expected_output = "-5-3-1";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

// continue keyword (For Loop)

// for loop without step with continue keyword
TEST_F(ForLoopReplTest, ForLoopWithoutStepWithContinueKeyword) {
  std::string input =
      R"(for var i = 0 to 5 { if i == 3 { continue } print(i) })";
  std::string expected_output = "01245";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

// for with step with continue keyword
TEST_F(ForLoopReplTest, ForLoopWithStepWithContinueKeyword) {
  std::string input =
      R"(for var i = 0 to 5 : 2 { if i == 2 { continue } print(i) })";
  std::string expected_output = "04";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

// for without step, with loop variable and continue keyword
TEST_F(ForLoopReplTest, ForLoopWithoutStepWithLoopVariableAndContinueKeyword) {
  std::string input =
      R"(for var i = 0 to 5 { if i == 3 { continue } print(i) })";
  std::string expected_output = "01245";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

// for with step, with loop variable and continue keyword
TEST_F(ForLoopReplTest, ForLoopWithStepWithLoopVariableAndContinueKeyword) {
  std::string input =
      R"(for var i = 0 to 5 : 2 { if i == 2 { continue } print(i) })";
  std::string expected_output = "04";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

// break keyword (For Loop)

// for without step with break keyword
TEST_F(ForLoopReplTest, ForLoopWithoutStepWithBreakKeyword) {
  std::string input = R"(for var i = 0 to 5 { if i == 3 { break } print(i) })";
  std::string expected_output = "012";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

// for with step with break keyword
TEST_F(ForLoopReplTest, ForLoopWithStepWithBreakKeyword) {
  std::string input =
      R"(for var i = 0 to 5 : 2 { if i == 2 { break } print(i) })";
  std::string expected_output = "0";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

// for without step, with loop variable and break keyword
TEST_F(ForLoopReplTest, ForLoopWithoutStepWithLoopVariableAndBreakKeyword) {
  std::string input = R"(for var i = 0 to 5 { if i == 3 { break }
   print(i) })";
  std::string expected_output = "012";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

// for with step, with loop variable and break keyword
TEST_F(ForLoopReplTest, ForLoopWithStepWithLoopVariableAndBreakKeyword) {
  std::string input =
      R"(for var i = 0 to 5 : 2 { if i == 2 { break } print(i) })";
  std::string expected_output = "0";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

// if, or if, else (For Loop)
// for without step with break keyword and if, or if, else statement
TEST_F(ForLoopReplTest,
       ForLoopWithoutStepWithBreakKeywordAndIfOrIfElseStatement) {
  std::string input =
      R"(for var i = 0 to 5 { if i == 3 { break } or if i == 2 { print(i) }
      else { print(i) } })";
  std::string expected_output = "012";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

// for without step with break keyword and if, or if, else statement with
// bracket
TEST_F(ForLoopReplTest,
       ForLoopWithoutStepWithBreakKeywordAndIfOrIfElseStatementWithBracket) {
  std::string input =
      R"(for var i = 0 to 5 { if i == 3 { break } or if i == 2 { print(i) }
      else { print(i) } })";
  std::string expected_output = "012";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

// for with step with break keyword and if or if else
TEST_F(ForLoopReplTest, ForLoopWithStepWithBreakKeywordAndIfOrIfElseStatement) {
  std::string input =
      R"(for var i = 0 to 5 : 2 { if i == 2 { break } or if i == 2 { print(i)
      } else { print(i) } })";
  std::string expected_output = "0";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

// for without step, with loop variable and break keyword and if or if else
TEST_F(
    ForLoopReplTest,
    ForLoopWithoutStepWithLoopVariableAndBreakKeywordAndIfOrIfElseStatement) {
  std::string input =
      R"(for var i = 0 to 5 { if i == 3 { break } or if i == 2 { print(i) }
      else { print(i) } })";
  std::string expected_output = "012";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

// for without step with continue keyword and if or if else

TEST_F(ForLoopReplTest,
       ForLoopWithoutStepWithContinueKeywordAndIfOrIfElseStatement) {
  std::string input =
      R"(for var i = 0 to 5 { if i == 3 { continue } or if i == 2 { print(i)
      } else { print(i) } })";

  std::string expected_output = "01245";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

// for with step with continue keyword and if or if else

TEST_F(ForLoopReplTest,
       ForLoopWithStepWithContinueKeywordAndIfOrIfElseStatement) {
  std::string input =
      R"(for var i = 0 to 5 : 2 { if i == 2 { continue } or if i == 2 {
      print(i) } else { print(i) } })";

  std::string expected_output = "04";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

// for without step, with loop variable and continue keyword and if or if

TEST_F(
    ForLoopReplTest,
    ForLoopWithoutStepWithLoopVariableAndContinueKeywordAndIfOrIfElseStatement) {
  std::string input =
      R"(for var i = 0 to 5 { if i == 3 { continue } or if i == 2 { print(i)
      } else { print(i) } })";

  std::string expected_output = "01245";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

// for with step, with loop variable and continue keyword and if or if else

TEST_F(
    ForLoopReplTest,
    ForLoopWithStepWithLoopVariableAndContinueKeywordAndIfOrIfElseStatement) {
  std::string input =
      R"(for var i = 0 to 5 : 2 { if i == 2 { continue } or if i == 2 {
      print(i) } else { print(i) } })";

  std::string expected_output = "04";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

// Nested (For Loop)

// Nested for without step with break keyword and if or if else

TEST_F(ForLoopReplTest,
       NestedForLoopWithoutStepWithBreakKeywordAndIfOrIfElseStatement) {
  std::string input =
      R"(for var i = 0 to 5 { for var j = 0 to 5 { if j == 3 { break } or if
      j == 2 { print(j) } else { print(j) } } })";

  std::string expected_output = "012012012012012012";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

// Nested for with step with break keyword and if or if else

TEST_F(ForLoopReplTest,
       NestedForLoopWithStepWithBreakKeywordAndIfOrIfElseStatement) {
  std::string input =
      R"(for var i = 0 to 5 : 2 { for var j = 0 to 5 : 2 { if j == 2 { break
      } or if j == 2 { print(j) } else { print(j) } } })";

  std::string expected_output = "000";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

// Nested for without step, with loop variable and break keyword and if or if
// else

TEST_F(
    ForLoopReplTest,
    NestedForLoopWithoutStepWithLoopVariableAndBreakKeywordAndIfOrIfElseStatement) {
  std::string input =
      R"(for var i = 0 to 5 { for var j = 0 to 5 { if j == 3 { break } or if
      j == 2 { print(j) } else { print(j) } } })";

  std::string expected_output = "012012012012012012";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

// Nested for with step, with loop variable and break keyword and if or if

TEST_F(
    ForLoopReplTest,
    NestedForLoopWithStepWithLoopVariableAndBreakKeywordAndIfOrIfElseStatement) {
  std::string input =
      R"(for var i = 0 to 5 : 2 { for var j = 0 to 5 : 2 { if j == 2 { break
      } or if j == 2 { print(j) } else { print(j) } } })";

  std::string expected_output = "000";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

// Nested for without step with continue keyword and if or if else

TEST_F(ForLoopReplTest,
       NestedForLoopWithoutStepWithContinueKeywordAndIfOrIfElseStatement) {
  std::string input =
      R"(for var i = 0 to 5 { for var j = 0 to 5 { if j == 3 { continue } or
      if j == 2 { print(j) } else { print(j) } } })";

  std::string expected_output = "012450124501245012450124501245";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

// Nested for with step with continue keyword and if or if else

TEST_F(ForLoopReplTest,
       NestedForLoopWithStepWithContinueKeywordAndIfOrIfElseStatement) {
  std::string input =
      R"(for var i = 0 to 5 : 2 { for var j = 0 to 5 : 2 { if j == 2 {
      continue } or if j == 2 { print(j) } else { print(j) } } })";

  std::string expected_output = "040404";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

// Nested for and while with step, with loop variable and continue keyword
// and if or if else

TEST_F(
    ForLoopReplTest,
    NestedForAndWhileLoopWithStepWithLoopVariableAndContinueKeywordAndIfOrIfElseStatement) {
  std::string input =
      R"(
        for var i = 0 to 5 : 2 { 
          var j = 0 
          while j <= 5 { 
            if j == 2 { 
              j = j + 2 
              continue 
            } or if j == 2 { 
              print(j) 
            } else { 
              print(j) 
            } 
            j = j + 2 
          }
      })";

  std::string expected_output = "040404";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

// Nested for and while without step with break keyword and if or if else

TEST_F(ForLoopReplTest,
       NestedForAndWhileLoopWithoutStepWithBreakKeywordAndIfOrIfElseStatement) {
  std::string input =
      R"(for var i = 0 to 5 { var j = 0 while j <= 5 { if j == 3 { break } or
      if j == 2 { print(j) } else { print(j) } j = j + 1 } })";

  std::string expected_output = "012012012012012012";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}
