#include "For-Loop.h"

// Basic for loop

TEST_F(ReplTest, BasicForLoop) {
  std::string input = R"(
       for var i = 0 to 5 {
            print(i)
       }
    )";

  std::string expected_output = "012345";

  std::string capturedOutput = runReplWithInputPrint(input);

  ASSERT_EQ(capturedOutput, expected_output);
}

// Basic for loop without declaration

TEST_F(ReplTest, BasicForLoopWithoutDeclaration) {
  std::string input = R"(
       var i = 0
       for i to 5 {
            print(i)
       }
    )";

  std::string expected_output = "000000";

  std::string capturedOutput = runReplWithInputPrint(input);

  ASSERT_EQ(capturedOutput, expected_output);
}

// Basic for loop with Bracket

TEST_F(ReplTest, BasicForLoopWithBracket) {
  std::string input = R"(
       for (var i = 0 to 5) {
            print(i)
       }
    )";

  std::string expected_output = "012345";

  std::string capturedOutput = runReplWithInputPrint(input);

  ASSERT_EQ(capturedOutput, expected_output);
}

// For loop with step

TEST_F(ReplTest, ForLoopWithStep) {
  std::string input = R"(
       for var i = 0 to 5 : 2 {
            print(i)
       }
    )";

  std::string expected_output = "024";

  std::string capturedOutput = runReplWithInputPrint(input);

  ASSERT_EQ(capturedOutput, expected_output);
}

// For loop with negative step

TEST_F(ReplTest, ForLoopWithNegativeStep) {
  std::string input = R"(
       for var i = 5 to 0 : -2 {
            print(i)
       }
    )";

  std::string expected_output = "531";

  std::string capturedOutput = runReplWithInputPrint(input);

  ASSERT_EQ(capturedOutput, expected_output);
}

// For loop with  step and negative start value

TEST_F(ReplTest, ForLoopWithNegativeStepAndNegativeStartValue) {
  std::string input = R"(
       for var i = -5 to 0 : 2 {
            print(i)
       }
    )";

  std::string expected_output = "-5-3-1";

  std::string capturedOutput = runReplWithInputPrint(input);

  ASSERT_EQ(capturedOutput, expected_output);
}

// continue keyword (For Loop)

// for loop without step with continue keyword

TEST_F(ReplTest, ForLoopWithoutStepWithContinueKeyword) {
  std::string input = R"(
       for var i = 0 to 5 {
            if i == 3 {
                continue
            }
            print(i)
       }
    )";

  std::string expected_output = "01245";

  std::string capturedOutput = runReplWithInputPrint(input);

  ASSERT_EQ(capturedOutput, expected_output);
}

// for with step with continue keyword

TEST_F(ReplTest, ForLoopWithStepWithContinueKeyword) {
  std::string input = R"(
       for var i = 0 to 5 : 2 {
            if i == 2 {
                continue
            }
            print(i)
       }
    )";

  std::string expected_output = "04";

  std::string capturedOutput = runReplWithInputPrint(input);

  ASSERT_EQ(capturedOutput, expected_output);
}

// for without step,  with loop variable and continue keyword

TEST_F(ReplTest, ForLoopWithoutStepWithLoopVariableAndContinueKeyword) {
  std::string input = R"(
    
       for var i = 0 to 5 {
            if i == 3 {
                continue
            }
            print(i)
       }
    )";

  std::string expected_output = "01245";

  std::string capturedOutput = runReplWithInputPrint(input);

  ASSERT_EQ(capturedOutput, expected_output);
}

// for with step,  with loop variable and continue keyword

TEST_F(ReplTest, ForLoopWithStepWithLoopVariableAndContinueKeyword) {
  std::string input = R"(
       for var i = 0 to 5 : 2 {
            if i == 2 {
                continue
            }
            print(i)
       }
    )";

  std::string expected_output = "04";

  std::string capturedOutput = runReplWithInputPrint(input);

  ASSERT_EQ(capturedOutput, expected_output);
}

// break keyword (For Loop)

// for without step with break keyword

TEST_F(ReplTest, ForLoopWithoutStepWithBreakKeyword) {
  std::string input = R"(
       for var i = 0 to 5 {
            if i == 3 {
                break
            }
            print(i)
       }
    )";

  std::string expected_output = "012";

  std::string capturedOutput = runReplWithInputPrint(input);

  ASSERT_EQ(capturedOutput, expected_output);
}

// for with step with break keyword

TEST_F(ReplTest, ForLoopWithStepWithBreakKeyword) {
  std::string input = R"(
       for var i = 0 to 5 : 2 {
            if i == 2 {
                break
            }
            print(i)
       }
    )";

  std::string expected_output = "0";

  std::string capturedOutput = runReplWithInputPrint(input);

  ASSERT_EQ(capturedOutput, expected_output);
}

// for without step,  with loop variable and break keyword

TEST_F(ReplTest, ForLoopWithoutStepWithLoopVariableAndBreakKeyword) {
  std::string input = R"(
       for var i = 0 to 5 {
            if i == 3 {
                break
            }
            print(i)
       }
    )";

  std::string expected_output = "012";

  std::string capturedOutput = runReplWithInputPrint(input);

  ASSERT_EQ(capturedOutput, expected_output);
}

// for with step,  with loop variable and break keyword

TEST_F(ReplTest, ForLoopWithStepWithLoopVariableAndBreakKeyword) {
  std::string input = R"(
       for var i = 0 to 5 : 2 {
            if i == 2 {
                break
            }
            print(i)
       }
    )";

  std::string expected_output = "0";

  std::string capturedOutput = runReplWithInputPrint(input);

  ASSERT_EQ(capturedOutput, expected_output);
}

// if ,or if, else (For Loop)

// for without step with break keyword and if , or if, else statement

TEST_F(ReplTest, ForLoopWithoutStepWithBreakKeywordAndIfOrIfElseStatement) {
  std::string input = R"(
       for var i = 0 to 5 {
            if i == 3 {
                break
            }
            or if i == 2 {
                print(i)
            }
            else {
                print(i)
            }
       }
    )";

  std::string expected_output = "012";

  std::string capturedOutput = runReplWithInputPrint(input);

  ASSERT_EQ(capturedOutput, expected_output);
}

// for without step with break keyword and if , or if, else statement with
// bracket

TEST_F(ReplTest,
       ForLoopWithoutStepWithBreakKeywordAndIfOrIfElseStatementWithBracket) {
  std::string input = R"(
       for var i = 0 to 5 {
            if i == 3 {
                break
            }
            or if i == 2 {
                print(i)
            }
            else {
                print(i)
            }
       }
    )";

  std::string expected_output = "012";

  std::string capturedOutput = runReplWithInputPrint(input);

  ASSERT_EQ(capturedOutput, expected_output);
}

// for with step with break keyword and if or if else

TEST_F(ReplTest, ForLoopWithStepWithBreakKeywordAndIfOrIfElseStatement) {
  std::string input = R"(
       for var i = 0 to 5 : 2 {
            if i == 2 {
                break
            }
            or if i == 2 {
                print(i)
            }
            else {
                print(i)
            }
       }
    )";

  std::string expected_output = "0";

  std::string capturedOutput = runReplWithInputPrint(input);

  ASSERT_EQ(capturedOutput, expected_output);
}

// for without step,  with loop variable and break keyword and if or if else

TEST_F(
    ReplTest,
    ForLoopWithoutStepWithLoopVariableAndBreakKeywordAndIfOrIfElseStatement) {
  std::string input = R"(
       for var i = 0 to 5 {
            if i == 3 {
                break
            }
            or if i == 2 {
                print(i)
            }
            else {
                print(i)
            }
       }
    )";

  std::string expected_output = "012";

  std::string capturedOutput = runReplWithInputPrint(input);

  ASSERT_EQ(capturedOutput, expected_output);
}

// for without step with continue keyword and if or if else

TEST_F(ReplTest, ForLoopWithoutStepWithContinueKeywordAndIfOrIfElseStatement) {
  std::string input = R"(
       for var i = 0 to 5 {
            if i == 3 {
                continue
            }
            or if i == 2 {
                print(i)
            }
            else {
                print(i)
            }
       }
    )";

  std::string expected_output = "01245";

  std::string capturedOutput = runReplWithInputPrint(input);

  ASSERT_EQ(capturedOutput, expected_output);
}

// for with step with continue keyword and if or if else

TEST_F(ReplTest, ForLoopWithStepWithContinueKeywordAndIfOrIfElseStatement) {
  std::string input = R"(
       for var i = 0 to 5 : 2 {
            if i == 2 {
                continue
            }
            or if i == 2 {
                print(i)
            }
            else {
                print(i)
            }
       }
    )";

  std::string expected_output = "04";

  std::string capturedOutput = runReplWithInputPrint(input);

  ASSERT_EQ(capturedOutput, expected_output);
}

// for without step,  with loop variable and continue keyword and if or if else

TEST_F(
    ReplTest,
    ForLoopWithoutStepWithLoopVariableAndContinueKeywordAndIfOrIfElseStatement) {
  std::string input = R"(
       for var i = 0 to 5 {
            if i == 3 {
                continue
            }
            or if i == 2 {
                print(i)
            }
            else {
                print(i)
            }
       }
    )";

  std::string expected_output = "01245";

  std::string capturedOutput = runReplWithInputPrint(input);

  ASSERT_EQ(capturedOutput, expected_output);
}

// for with step,  with loop variable and continue keyword and if or if else

TEST_F(
    ReplTest,
    ForLoopWithStepWithLoopVariableAndContinueKeywordAndIfOrIfElseStatement) {
  std::string input = R"(
       for var i = 0 to 5 : 2 {
            if i == 2 {
                continue
            }
            or if i == 2 {
                print(i)
            }
            else {
                print(i)
            }
       }
    )";

  std::string expected_output = "04";

  std::string capturedOutput = runReplWithInputPrint(input);

  ASSERT_EQ(capturedOutput, expected_output);
}

// Nested (For Loop)

// Nested for without step with break keyword and if or if else

TEST_F(ReplTest,
       NestedForLoopWithoutStepWithBreakKeywordAndIfOrIfElseStatement) {
  std::string input = R"(
       for var i = 0 to 5 {
            for var j = 0 to 5 {
                if j == 3 {
                    break
                }
                or if j == 2 {
                    print(j)
                }
                else {
                    print(j)
                }
            }
       }
    )";

  std::string expected_output = "012012012012012012";

  std::string capturedOutput = runReplWithInputPrint(input);

  ASSERT_EQ(capturedOutput, expected_output);
}

// Nested for with step with break keyword and if or if else

TEST_F(ReplTest, NestedForLoopWithStepWithBreakKeywordAndIfOrIfElseStatement) {
  std::string input = R"(
       for var i = 0 to 5 : 2 {
            for var j = 0 to 5 : 2 {
                if j == 2 {
                    break
                }
                or if j == 2 {
                    print(j)
                }
                else {
                    print(j)
                }
            }
       }
    )";

  std::string expected_output = "000";

  std::string capturedOutput = runReplWithInputPrint(input);

  ASSERT_EQ(capturedOutput, expected_output);
}

// Nested for without step,  with loop variable and break keyword and if or if
// else

TEST_F(
    ReplTest,
    NestedForLoopWithoutStepWithLoopVariableAndBreakKeywordAndIfOrIfElseStatement) {
  std::string input = R"(
       for var i = 0 to 5 {
            for var j = 0 to 5 {
                if j == 3 {
                    break
                }
                or if j == 2 {
                    print(j)
                }
                else {
                    print(j)
                }
            }
       }
    )";

  std::string expected_output = "012012012012012012";

  std::string capturedOutput = runReplWithInputPrint(input);

  ASSERT_EQ(capturedOutput, expected_output);
}

// Nested for with step,  with loop variable and break keyword and if or if else

TEST_F(
    ReplTest,
    NestedForLoopWithStepWithLoopVariableAndBreakKeywordAndIfOrIfElseStatement) {
  std::string input = R"(
       for var i = 0 to 5 : 2 {
            for var j = 0 to 5 : 2 {
                if j == 2 {
                    break
                }
                or if j == 2 {
                    print(j)
                }
                else {
                    print(j)
                }
            }
       }
    )";

  std::string expected_output = "000";

  std::string capturedOutput = runReplWithInputPrint(input);

  ASSERT_EQ(capturedOutput, expected_output);
}

// Nested for without step with continue keyword and if or if else

TEST_F(ReplTest,
       NestedForLoopWithoutStepWithContinueKeywordAndIfOrIfElseStatement) {
  std::string input = R"(
       for var i = 0 to 5 {
            for var j = 0 to 5 {
                if j == 3 {
                    continue
                }
                or if j == 2 {
                    print(j)
                }
                else {
                    print(j)
                }
            }
       }
    )";

  std::string expected_output = "012450124501245012450124501245";

  std::string capturedOutput = runReplWithInputPrint(input);

  ASSERT_EQ(capturedOutput, expected_output);
}

// Nested for with step with continue keyword and if or if else

TEST_F(ReplTest,
       NestedForLoopWithStepWithContinueKeywordAndIfOrIfElseStatement) {
  std::string input = R"(
       for var i = 0 to 5 : 2 {
            for var j = 0 to 5 : 2 {
                if j == 2 {
                    continue
                }
                or if j == 2 {
                    print(j)
                }
                else {
                    print(j)
                }
            }
       }
    )";

  std::string expected_output = "040404";

  std::string capturedOutput = runReplWithInputPrint(input);

  ASSERT_EQ(capturedOutput, expected_output);
}

// Nested for and while with step,  with loop variable and continue keyword
// and if or if else

TEST_F(
    ReplTest,
    NestedForAndWhileLoopWithStepWithLoopVariableAndContinueKeywordAndIfOrIfElseStatement) {
  std::string input = R"(
       for var i = 0 to 5 : 2 {
            var j = 0 
            while j <= 5 {
                if j == 2 {
                    j = j + 2
                    continue
                }
                or if j == 2 {
                    print(j)
                }
                else {
                    print(j)
                }
                j = j + 2
            }
       }
    )";

  std::string expected_output = "040404";

  std::string capturedOutput = runReplWithInputPrint(input);

  ASSERT_EQ(capturedOutput, expected_output);
}

// Nested for and while without step with break keyword and if or if else

TEST_F(ReplTest,
       NestedForAndWhileLoopWithoutStepWithBreakKeywordAndIfOrIfElseStatement) {
  std::string input = R"(
       for var i = 0 to 5 {
            var j = 0 
            while j <= 5 {
                if j == 3 {
                    break
                }
                or if j == 2 {
                    print(j)
                }
                else {
                    print(j)
                }
                j = j + 1
            }
       }
    )";

  std::string expected_output = "012012012012012012";

  std::string capturedOutput = runReplWithInputPrint(input);

  ASSERT_EQ(capturedOutput, expected_output);
}
