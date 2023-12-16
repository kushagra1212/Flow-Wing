#include "BooleanOperation.h"

/*

  BOOLEAN OPERATION

*/

// Boolean Operation on Boolean ( Arithmetic )

TEST_F(BinaryOperationTest, BasicBooleanOperationAddition) {
  std::string input = "true+true";
  std::string expected_output = "true";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(BinaryOperationTest, BasicBooleanOperationSubtraction) {
  std::string input = "true-true";
  std::string expected_output = "false";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(BinaryOperationTest, BasicBooleanOperationMultiplication) {
  std::string input = "true*true";
  std::string expected_output = "true";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(BinaryOperationTest, BasicBooleanOperationDivision) {
  std::string input = "true/true";
  std::string expected_output = "true";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

// Boolean Operation on Boolean ( Relational )

TEST_F(BinaryOperationTest, BasicBooleanOperationLessThan) {
  std::string input = "true<true";
  std::string expected_output = "false";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(BinaryOperationTest, BasicBooleanOperationLessThanEqual) {
  std::string input = "true<=true";
  std::string expected_output = "true";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(BinaryOperationTest, BasicBooleanOperationGreaterThan) {
  std::string input = "true>true";
  std::string expected_output = "false";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(BinaryOperationTest, BasicBooleanOperationGreaterThanEqual) {
  std::string input = "true>=true";
  std::string expected_output = "true";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

// Boolean Operation on Boolean ( Equality )

TEST_F(BinaryOperationTest, BasicBooleanOperationEqual) {
  std::string input = "true==true";
  std::string expected_output = "true";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(BinaryOperationTest, BasicBooleanOperationNotEqual) {
  std::string input = "true!=true";
  std::string expected_output = "false";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

// Boolean Operation on Boolean ( Logical )

TEST_F(BinaryOperationTest, BasicBooleanOperationLogicalAnd) {
  std::string input = "true&&true";
  std::string expected_output = "true";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(BinaryOperationTest, BasicBooleanOperationLogicalOr) {
  std::string input = "true||true";
  std::string expected_output = "true";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

/*

  BINARY OPERATION ON BOOLEAN AND DOUBLE

*/

// Boolean Operation on Double ( Arithmetic )

TEST_F(BinaryOperationTest, BasicBooleanOperationAdditionDouble) {
  std::string input = "true+1.0";
  std::string expected_output = "2.0000000000000000";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(BinaryOperationTest, BasicBooleanOperationSubtractionDouble) {
  std::string input = "true-1.0";
  std::string expected_output = "0.0000000000000000";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(BinaryOperationTest, BasicBooleanOperationMultiplicationDouble) {
  std::string input = "true*1.0";
  std::string expected_output = "1.0000000000000000";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
  ;
}

TEST_F(BinaryOperationTest, BasicBooleanOperationDivisionDouble) {
  std::string input = "true/1.0";
  std::string expected_output = "1.0000000000000000";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}
TEST_F(BinaryOperationTest, BasicBooleanOperationDivisionDouble2) {
  std::string input = "true/1";
  std::string expected_output = "1.0000000000000000";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

// Boolean Operation on Double ( Relational )

TEST_F(BinaryOperationTest, BasicBooleanOperationLessThanDouble) {
  std::string input = "true<1.0";
  std::string expected_output = "false";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(BinaryOperationTest, BasicBooleanOperationLessThanEqualDouble) {
  std::string input = "true<=1.0";
  std::string expected_output = "true";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(BinaryOperationTest, BasicBooleanOperationGreaterThanDouble) {
  std::string input = "true>1.0";
  std::string expected_output = "false";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(BinaryOperationTest, BasicBooleanOperationGreaterThanEqualDouble) {
  std::string input = "true>=1.0";
  std::string expected_output = "true";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

// Boolean Operation on Double ( Equality )

TEST_F(BinaryOperationTest, BasicBooleanOperationEqualDouble) {
  std::string input = "true==1.0";
  std::string expected_output = "true";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(BinaryOperationTest, BasicBooleanOperationNotEqualDouble) {
  std::string input = "true!=1.0";
  std::string expected_output = "false";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}
