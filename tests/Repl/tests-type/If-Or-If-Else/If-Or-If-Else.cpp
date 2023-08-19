#include "If-Or-If-Else.h"

TEST_F(ReplTest, BasicIfRRepl) {
  std::string input = R"(
       if(true) {
            5
       }
   )";

  std::string expected_output = "5";

  std::string output = runReplWithInput(input);
  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, BasicIfElseRepl) {
  std::string input = R"(
       if(false) {
            5
       } else {
            6
       }
   )";

  std::string expected_output = "6";

  std::string output = runReplWithInput(input);
  EXPECT_EQ(output, expected_output);
}

// If-Else with Different Condition

TEST_F(ReplTest, BasicIfElseWithDifferentConditionRepl) {
  std::string input = R"(
       if(2 > 3) {
            5
       } else {
            6
       }
   )";

  std::string expected_output = "6";

  std::string output = runReplWithInput(input);
  EXPECT_EQ(output, expected_output);
}

// When If is false and there is no else

TEST_F(ReplTest, BasicIfFalseRepl) {
  std::string input = R"(
       if(false) {
            5
       }
   )";

  std::string expected_output = "";

  std::string output = runReplWithInput(input);
  EXPECT_EQ(output, expected_output);
}

// Nested If-Else

TEST_F(ReplTest, BasicNestedIfElseRepl) {
  std::string input = R"(
       if(true) {
            if(false) {
                5
            } else {
                6
            }
       } else {
            7
       }
   )";

  std::string expected_output = "6";

  std::string output = runReplWithInput(input);
  EXPECT_EQ(output, expected_output);
}

// Nested If-Else with Different Condition

TEST_F(ReplTest, BasicNestedIfElseWithDifferentConditionRepl) {
  std::string input = R"(
       if(true) {
            if(2 > 3) {
                5
            } else {
                6
            }
       } else {
            7
       }
   )";

  std::string expected_output = "6";

  std::string output = runReplWithInput(input);
  EXPECT_EQ(output, expected_output);
}
TEST_F(ReplTest, BasicIfElseRepl2) {
  std::string input = R"(
        if(true) {
            5
        } else {
            6
        }
    )";

  std::string expected_output = "5";

  std::string output = runReplWithInput(input);
  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, BasicOrIfRepl) {
  std::string input = R"(
        if(false) {
            4
        } or if(true) {
            5
        } else {
            6
        }
    )";

  std::string expected_output = "5";

  std::string output = runReplWithInput(input);
  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, BasicElseRepl) {
  std::string input = R"(
        if(false) {
            4
        } else {
            6
        }
    )";

  std::string expected_output = "6";

  std::string output = runReplWithInput(input);
  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, NestedIfElseOrIfRepl) {
  std::string input = R"(
        if(true) {
            if(2 > 3) {
                5
            } or if(4 > 3) {
                7
            } else {
                8
            }
        } else {
            9
        }
    )";

  std::string expected_output = "7";

  std::string output = runReplWithInput(input);
  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, MultipleOrIfRepl) {
  std::string input = R"(
        if(false) {
            4
        } or if(false) {
            5
        } or if(true) {
            6
        } else {
            7
        }
    )";

  std::string expected_output = "6";

  std::string output = runReplWithInput(input);
  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, NestedOrIfElseRepl) {
  std::string input = R"(
        if(false) {
            4
        } or if(true) {
            if(2 > 3) {
                5
            } else {
                6
            }
        } else {
            7
        }
    )";

  std::string expected_output = "6";

  std::string output = runReplWithInput(input);
  EXPECT_EQ(output, expected_output);
}
TEST_F(ReplTest, ComplexNestedIfOrIfElseRepl) {
  std::string input = R"(
        if(true) {
            if(false) {
                10
            } or if(true) {
                if(5 > 3) {
                    15
                } else {
                    20
                }
            } else {
                25
            }
        } else {
            30
        }
    )";

  std::string expected_output = "15";

  std::string output = runReplWithInput(input);
  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, ComplexOrIfElseRepl) {
  std::string input = R"(
        if(false) {
            10
        } or if(false) {
            20
        } or if(true) {
            if(7 > 5) {
                30
            } else {
                40
            }
        } else {
            50
        }
    )";

  std::string expected_output = "30";

  std::string output = runReplWithInput(input);
  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, ComplexNestedOrIfElseRepl) {
  std::string input = R"(
        if(false) {
            10
        } or if(true) {
            if(false) {
                20
            } else {
                if(8 > 5) {
                    35
                } else {
                    45
                }
            }
        } else {
            50
        }
    )";

  std::string expected_output = "35";

  std::string output = runReplWithInput(input);
  EXPECT_EQ(output, expected_output);
}
