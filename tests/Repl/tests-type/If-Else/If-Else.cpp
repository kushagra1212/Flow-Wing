#include "If-Else.h"

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
