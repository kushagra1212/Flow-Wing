#include "BooleanOperation.h"

/*

  BOOLEAN OPERATION

*/

// Boolean Operation on Boolean ( Arithmetic )

TEST_F(ReplTest, BasicBooleanOperationAddition) {
  std::string input = "true+true";

  std::string expected_output = "true";
  std::string capturedOutput = runReplWithInputPrint(input);
  EXPECT_EQ(capturedOutput, expected_output);
}

TEST_F(ReplTest, BasicBooleanOperationSubtraction) {
  std::string input = "true-true";
  std::string expected_output = "false";

  std::string output = runReplWithInputPrint(input);

  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, BasicBooleanOperationMultiplication) {
  std::string input = "true*true";
  std::string expected_output = "true";

  std::string output = runReplWithInputPrint(input);

  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, BasicBooleanOperationDivision) {
  std::string input = "true/true";
  std::string expected_output = "true";

  std::string output = runReplWithInputPrint(input);

  EXPECT_EQ(output, expected_output);
}

// Boolean Operation on Boolean ( Relational )

TEST_F(ReplTest, BasicBooleanOperationLessThan) {
  std::string input = "true<true";
  std::string expected_output = "false";

  std::string output = runReplWithInputPrint(input);

  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, BasicBooleanOperationLessThanEqual) {
  std::string input = "true<=true";
  std::string expected_output = "true";

  std::string output = runReplWithInputPrint(input);

  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, BasicBooleanOperationGreaterThan) {
  std::string input = "true>true";
  std::string expected_output = "false";

  std::string output = runReplWithInputPrint(input);

  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, BasicBooleanOperationGreaterThanEqual) {
  std::string input = "true>=true";
  std::string expected_output = "true";

  std::string output = runReplWithInputPrint(input);

  EXPECT_EQ(output, expected_output);
}

// Boolean Operation on Boolean ( Equality )

TEST_F(ReplTest, BasicBooleanOperationEqual) {
  std::string input = "true==true";
  std::string expected_output = "true";

  std::string output = runReplWithInputPrint(input);

  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, BasicBooleanOperationNotEqual) {
  std::string input = "true!=true";
  std::string expected_output = "false";

  std::string output = runReplWithInputPrint(input);

  EXPECT_EQ(output, expected_output);
}

// Boolean Operation on Boolean ( Logical )

TEST_F(ReplTest, BasicBooleanOperationLogicalAnd) {
  std::string input = "true&&true";
  std::string expected_output = "true";

  std::string output = runReplWithInputPrint(input);

  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, BasicBooleanOperationLogicalOr) {
  std::string input = "true||true";
  std::string expected_output = "true";

  std::string output = runReplWithInputPrint(input);

  EXPECT_EQ(output, expected_output);
}

/*

  BINARY OPERATION ON BOOLEAN AND DOUBLE

*/

// Boolean Operation on Double ( Arithmetic )

TEST_F(ReplTest, BasicBooleanOperationAdditionDouble) {
  std::string input = "true+1.0";
  std::string expected_output = "2.000000";

  std::string output = runReplWithInputPrint(input);

  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, BasicBooleanOperationSubtractionDouble) {
  std::string input = "true-1.0";
  std::string expected_output = "0.000000";

  std::string output = runReplWithInputPrint(input);

  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, BasicBooleanOperationMultiplicationDouble) {
  std::string input = "true*1.0";
  std::string expected_output = "1.000000";

  std::string output = runReplWithInputPrint(input);

  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, BasicBooleanOperationDivisionDouble) {
  std::string input = "true/1.0";
  std::string expected_output = "1.000000";

  std::string output = runReplWithInputPrint(input);

  EXPECT_EQ(output, expected_output);
}

// Boolean Operation on Double ( Relational )

TEST_F(ReplTest, BasicBooleanOperationLessThanDouble) {
  std::string input = "true<1.0";
  std::string expected_output = "false";

  std::string output = runReplWithInputPrint(input);

  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, BasicBooleanOperationLessThanEqualDouble) {
  std::string input = "true<=1.0";
  std::string expected_output = "true";

  std::string output = runReplWithInputPrint(input);

  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, BasicBooleanOperationGreaterThanDouble) {
  std::string input = "true>1.0";
  std::string expected_output = "false";

  std::string output = runReplWithInputPrint(input);

  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, BasicBooleanOperationGreaterThanEqualDouble) {
  std::string input = "true>=1.0";
  std::string expected_output = "true";

  std::string output = runReplWithInputPrint(input);

  EXPECT_EQ(output, expected_output);
}

// Boolean Operation on Double ( Equality )

TEST_F(ReplTest, BasicBooleanOperationEqualDouble) {
  std::string input = "true==1.0";
  std::string expected_output = "true";

  std::string output = runReplWithInputPrint(input);

  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, BasicBooleanOperationNotEqualDouble) {
  std::string input = "true!=1.0";
  std::string expected_output = "false";

  std::string output = runReplWithInputPrint(input);

  EXPECT_EQ(output, expected_output);
}
