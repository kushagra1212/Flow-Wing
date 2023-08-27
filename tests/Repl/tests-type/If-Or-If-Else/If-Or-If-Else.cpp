#include "If-Or-If-Else.h"

std::string capturePrintfOutput(std::function<void()> function) {
  // Backup the original stdout buffer
  std::streambuf *originalBuf = std::cout.rdbuf();

  // Create a stringstream to capture the output
  std::stringstream capturedOutput;
  std::cout.rdbuf(capturedOutput.rdbuf());

  // Call the function that contains printf calls
  function();

  // Restore the original stdout buffer
  std::cout.rdbuf(originalBuf);

  return capturedOutput.str();
}

TEST_F(ReplTest, BasicIfRRepl) {
  std::string input = R"(
       if(true) {
           print(5)
       }
   )";

  std::string expected_output = "5";

  std::string capturedOutput = runReplWithInputPrint(input);

  ASSERT_EQ(capturedOutput, expected_output);
}

TEST_F(ReplTest, BasicIfElseRepl) {
  std::string input = R"(
       if(false) {
           print( 5)
       } else {
           print( 6)
       }
   )";

  std::string expected_output = "6";

  std::string capturedOutput = runReplWithInputPrint(input);

  EXPECT_EQ(capturedOutput, expected_output);
}

// If-Else with Different Condition

TEST_F(ReplTest, BasicIfElseWithDifferentConditionRepl) {
  std::string input = R"(
       if(2 > 3) {
           print( 5)
       } else {
           print( 6)
       }
   )";

  std::string expected_output = "6";

  std::string output = runReplWithInputPrint(input);
  EXPECT_EQ(output, expected_output);
}

// When If is false and there is no else

TEST_F(ReplTest, BasicIfFalseRepl) {
  std::string input = R"(
       if(false) {
           print(5)
       }
   )";

  std::string expected_output = "";

  std::string output = runReplWithInputPrint(input);
  EXPECT_EQ(output, expected_output);
}

// Nested If-Else

TEST_F(ReplTest, BasicNestedIfElseRepl) {
  std::string input = R"(
       if(true) {
            if(false) {
               print( 5)
            } else {
               print( 6)
            }
       } else {
           print( 7)
       }
   )";

  std::string expected_output = "6";

  std::string output = runReplWithInputPrint(input);
  EXPECT_EQ(output, expected_output);
}

// Nested If-Else with Different Condition

TEST_F(ReplTest, BasicNestedIfElseWithDifferentConditionRepl) {
  std::string input = R"(
       if(true) {
            if(2 > 3) {
               print( 5)
            } else {
               print( 6)
            }
       } else {
           print( 7)
       }
   )";

  std::string expected_output = "6";

  std::string output = runReplWithInputPrint(input);
  EXPECT_EQ(output, expected_output);
}
TEST_F(ReplTest, BasicIfElseRepl2) {
  std::string input = R"(
        if(true) {
           print( 5)
        } else {
           print( 6)
        }
    )";

  std::string expected_output = "5";

  std::string output = runReplWithInputPrint(input);
  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, BasicOrIfRepl) {
  std::string input = R"(
        if(false) {
           print( 4)
        } or if(true) {
           print( 5)
        } else {
           print( 6)
        }
    )";

  std::string expected_output = "5";

  std::string output = runReplWithInputPrint(input);
  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, BasicElseRepl) {
  std::string input = R"(
        if(false) {
           print( 4)
        } else {
           print( 6)
        }
    )";

  std::string expected_output = "6";

  std::string output = runReplWithInputPrint(input);
  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, NestedIfElseOrIfRepl) {
  std::string input = R"(
        if(true) {
            if(2 > 3) {
               print( 5)
            } or if(4 > 3) {
               print( 7)
            } else {
               print( 8)
            }
        } else {
           print( 9)
        }
    )";

  std::string expected_output = "7";

  std::string output = runReplWithInputPrint(input);
  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, MultipleOrIfRepl) {
  std::string input = R"(
        if(false) {
           print( 4)
        } or if(false) {
           print( 5)
        } or if(true) {
           print( 6)
        } else {
           print( 7)
        }
    )";

  std::string expected_output = "6";

  std::string output = runReplWithInputPrint(input);
  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, NestedOrIfElseRepl) {
  std::string input = R"(
        if(false) {
           print( 4)
        } or if(true) {
            if(2 > 3) {
               print( 5)
            } else {
               print( 6)
            }
        } else {
           print( 7)
        }
    )";

  std::string expected_output = "6";

  std::string output = runReplWithInputPrint(input);
  EXPECT_EQ(output, expected_output);
}
TEST_F(ReplTest, ComplexNestedIfOrIfElseRepl) {
  std::string input = R"(
        if(true) {
            if(false) {
                print(10)
            } or if(true) {
                if(5 > 3) {
                    print(15)
                } else {
                    print(20)
                }
            } else {
                print(25)
            }
        } else {
            print(30)
        }
    )";

  std::string expected_output = "15";

  std::string output = runReplWithInputPrint(input);
  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, ComplexOrIfElseRepl) {
  std::string input = R"(
        if(false) {
            print(10)
        } or if(false) {
            print(20)
        } or if(true) {
            if(7 > 5) {
                print(30)
            } else {
                print(40)
            }
        } else {
            print(50)
        }
    )";

  std::string expected_output = "30";

  std::string output = runReplWithInputPrint(input);
  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, ComplexNestedOrIfElseRepl) {
  std::string input = R"(
        if(false) {
            print(10)
        } or if(true) {
            if(false) {
                print(20)
            } else {
                if(8 > 5) {
                    print(35)
                } else {
                    print(45)
                }
            }
        } else {
            print(50)
        }
    )";

  std::string expected_output = "35";

  std::string output = runReplWithInputPrint(input);
  EXPECT_EQ(output, expected_output);
}
