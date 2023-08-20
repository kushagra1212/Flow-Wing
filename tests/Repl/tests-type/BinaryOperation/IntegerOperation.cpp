#include "IntegerOperation.h"
/*

    INTEGER OPERATIONS

*/

/*

    INTEGER OPERATIONS WITH INTEGERS

*/

// Binary Operations on Integers with Integers ( Arithmetic Operations )

TEST_F(ReplTest, BasicIntegerOperationAddition) {
  std::string input = "2+2";
  std::string expected_output = "4\n";

  std::string output = runReplWithInputPrint(input);

  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, BasicIntegerOperationSubtraction) {
  std::string input = "2-2";
  std::string expected_output = "0\n";

  std::string output = runReplWithInputPrint(input);

  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, BasicIntegerOperationMultiplication) {
  std::string input = "2*2";
  std::string expected_output = "4\n";

  std::string output = runReplWithInputPrint(input);

  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, BasicIntegerOperationDivision) {
  std::string input = "2/2";
  std::string expected_output = "1\n";

  std::string output = runReplWithInputPrint(input);

  EXPECT_EQ(output, expected_output);
}

// Binary Operations on Integers with Integers ( Logical Operations )

TEST_F(ReplTest, BasicIntegerOperationLogicalAnd) {
  std::string input = "2&&2";
  std::string expected_output = "true\n";

  std::string output = runReplWithInputPrint(input);

  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, BasicIntegerOperationLogicalOr) {
  std::string input = "2||2";
  std::string expected_output = "true\n";

  std::string output = runReplWithInputPrint(input);

  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, BasicIntegerOperationLogicalNot) {
  std::string input = "!2";
  std::string expected_output = "false\n";

  std::string output = runReplWithInputPrint(input);

  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, BasicIntegerOperationLogicalNotNot) {
  std::string input = "!!2";
  std::string expected_output = "true\n";

  std::string output = runReplWithInputPrint(input);

  EXPECT_EQ(output, expected_output);
}

// Binary Operations on Integers with Integers ( Comparison Operations )

TEST_F(ReplTest, BasicIntegerOperationComparisonEqual) {
  std::string input = "2==2";
  std::string expected_output = "true\n";

  std::string output = runReplWithInputPrint(input);

  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, BasicIntegerOperationComparisonNotEqual) {
  std::string input = "2!=2";
  std::string expected_output = "false\n";

  std::string output = runReplWithInputPrint(input);

  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, BasicIntegerOperationComparisonLessThan) {
  std::string input = "2<2";
  std::string expected_output = "false\n";

  std::string output = runReplWithInputPrint(input);

  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, BasicIntegerOperationComparisonLessThanOrEqual) {
  std::string input = "2<=2";
  std::string expected_output = "true\n";

  std::string output = runReplWithInputPrint(input);

  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, BasicIntegerOperationComparisonGreaterThan) {
  std::string input = "2>2";
  std::string expected_output = "false\n";

  std::string output = runReplWithInputPrint(input);

  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, BasicIntegerOperationComparisonGreaterThanOrEqual) {
  std::string input = "2>=2";
  std::string expected_output = "true\n";

  std::string output = runReplWithInputPrint(input);

  EXPECT_EQ(output, expected_output);
}

// Binary Operations on Integers with Integers ( Bitwise Operations )

TEST_F(ReplTest, BasicIntegerOperationBitwiseAnd) {
  std::string input = "2&2";
  std::string expected_output = "2\n";

  std::string output = runReplWithInputPrint(input);

  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, BasicIntegerOperationBitwiseOr) {
  std::string input = "2|2";
  std::string expected_output = "2\n";

  std::string output = runReplWithInputPrint(input);

  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, BasicIntegerOperationBitwiseXor) {
  std::string input = "2^2";
  std::string expected_output = "0\n";

  std::string output = runReplWithInputPrint(input);

  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, BasicIntegerOperationNegation) {
  std::string input = "~2";
  std::string expected_output = "-3\n";

  std::string output = runReplWithInputPrint(input);

  EXPECT_EQ(output, expected_output);
}

/*

    INTEGER OPERATIONS WITH DOUBLES

*/

// Binary Operations on Integers with Doubles ( Arithmetic Operations )

TEST_F(ReplTest, BasicIntegerOperationAdditionWithDouble) {
  std::string input = "2+2.0";
  std::string expected_output = "4.000000\n";

  std::string output = runReplWithInputPrint(input);

  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, BasicIntegerOperationSubtractionWithDouble) {
  std::string input = "2-2.0";
  std::string expected_output = "0.000000\n";

  std::string output = runReplWithInputPrint(input);

  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, BasicIntegerOperationMultiplicationWithDouble) {
  std::string input = "2*2.0";
  std::string expected_output = "4.000000\n";

  std::string output = runReplWithInputPrint(input);

  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, BasicIntegerOperationDivisionWithDouble) {
  std::string input = "2/2.0";
  std::string expected_output = "1.000000\n";

  std::string output = runReplWithInputPrint(input);

  EXPECT_EQ(output, expected_output);
}

// Binary Operations on Integers with Doubles ( Comparison Operations )

TEST_F(ReplTest, BasicIntegerOperationComparisonEqualWithDouble) {
  std::string input = "2==2.0";
  std::string expected_output = "true\n";

  std::string output = runReplWithInputPrint(input);

  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, BasicIntegerOperationComparisonNotEqualWithDouble) {
  std::string input = "2!=2.0";
  std::string expected_output = "false\n";

  std::string output = runReplWithInputPrint(input);

  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, BasicIntegerOperationComparisonLessThanWithDouble) {
  std::string input = "2<2.0";
  std::string expected_output = "false\n";

  std::string output = runReplWithInputPrint(input);

  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, BasicIntegerOperationComparisonLessThanOrEqualWithDouble) {
  std::string input = "2<=2.0";
  std::string expected_output = "true\n";

  std::string output = runReplWithInputPrint(input);

  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, BasicIntegerOperationComparisonGreaterThanWithDouble) {
  std::string input = "2>2.0";
  std::string expected_output = "false\n";

  std::string output = runReplWithInputPrint(input);

  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, BasicIntegerOperationComparisonGreaterThanOrEqualWithDouble) {
  std::string input = "2>=2.0";
  std::string expected_output = "true\n";

  std::string output = runReplWithInputPrint(input);

  EXPECT_EQ(output, expected_output);
}

/*

    INTEGER OPERATIONS WITH BOOLEANS

*/

// Binary Operations on Integers with Booleans ( Arithmetic Operations )

TEST_F(ReplTest, BasicIntegerOperationAdditionWithBoolean) {
  std::string input = "2+true";
  std::string expected_output = "3\n";

  std::string output = runReplWithInputPrint(input);

  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, BasicIntegerOperationSubtractionWithBoolean) {
  std::string input = "2-true";
  std::string expected_output = "1\n";

  std::string output = runReplWithInputPrint(input);

  EXPECT_EQ(output, expected_output);
}

// Subtraction with False

TEST_F(ReplTest, BasicIntegerOperationSubtractionWithFalse) {
  std::string input = "2-false";
  std::string expected_output = "2\n";

  std::string output = runReplWithInputPrint(input);

  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, BasicIntegerOperationMultiplicationWithBoolean) {
  std::string input = "2*true";
  std::string expected_output = "2\n";

  std::string output = runReplWithInputPrint(input);

  EXPECT_EQ(output, expected_output);
}

// Multiplication with False

TEST_F(ReplTest, BasicIntegerOperationMultiplicationWithFalse) {
  std::string input = "2*false";
  std::string expected_output = "0\n";

  std::string output = runReplWithInputPrint(input);

  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, BasicIntegerOperationDivisionWithBoolean) {
  std::string input = "2/true";
  std::string expected_output = "2\n";

  std::string output = runReplWithInputPrint(input);

  EXPECT_EQ(output, expected_output);
}

// Binary Operations on Integers with Booleans ( Logical Operations )

TEST_F(ReplTest, BasicIntegerOperationLogicalAndWithBoolean) {
  std::string input = "2&&true";
  std::string expected_output = "true\n";

  std::string output = runReplWithInputPrint(input);

  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, BasicIntegerOperationLogicalOrWithBoolean) {
  std::string input = "2||true";
  std::string expected_output = "true\n";

  std::string output = runReplWithInputPrint(input);

  EXPECT_EQ(output, expected_output);
}

// Binary Operations on Integers with Booleans ( Comparison Operations )

TEST_F(ReplTest, BasicIntegerOperationComparisonEqualWithBoolean) {
  std::string input = "2==true";
  std::string expected_output = "false\n";

  std::string output = runReplWithInputPrint(input);

  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, BasicIntegerOperationComparisonNotEqualWithBoolean) {
  std::string input = "2!=true";
  std::string expected_output = "true\n";

  std::string output = runReplWithInputPrint(input);

  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, BasicIntegerOperationComparisonLessThanWithBoolean) {
  std::string input = "2<true";
  std::string expected_output = "false\n";

  std::string output = runReplWithInputPrint(input);

  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, BasicIntegerOperationComparisonLessThanOrEqualWithBoolean) {
  std::string input = "2<=true";
  std::string expected_output = "false\n";

  std::string output = runReplWithInputPrint(input);

  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, BasicIntegerOperationComparisonGreaterThanWithBoolean) {
  std::string input = "2>true";
  std::string expected_output = "true\n";

  std::string output = runReplWithInputPrint(input);

  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, BasicIntegerOperationComparisonGreaterThanOrEqualWithBoolean) {
  std::string input = "2>=true";
  std::string expected_output = "true\n";

  std::string output = runReplWithInputPrint(input);

  EXPECT_EQ(output, expected_output);
}

// Binary Operations on Integers with Booleans ( Bitwise Operations )

TEST_F(ReplTest, BasicIntegerOperationBitwiseAndWithBoolean) {
  std::string input = "2&true";
  std::string expected_output = "0\n";

  std::string output = runReplWithInputPrint(input);

  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, BasicIntegerOperationBitwiseOrWithBoolean) {
  std::string input = "2|true";
  std::string expected_output = "3\n";

  std::string output = runReplWithInputPrint(input);

  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, BasicIntegerOperationBitwiseXorWithBoolean) {
  std::string input = "2^true";
  std::string expected_output = "3\n";

  std::string output = runReplWithInputPrint(input);

  EXPECT_EQ(output, expected_output);
}

// Binary Operations on Integers with Strings ( Arithmetic Operations )

TEST_F(ReplTest, BasicIntegerOperationAdditionWithString) {
  std::string input = "2+\"Hello\"";
  std::string expected_output = "2Hello\n";

  std::string output = runReplWithInputPrint(input);

  EXPECT_EQ(output, expected_output);
}

// Binary Operations on Integers with Strings ( Comparison Operations )

TEST_F(ReplTest, BasicIntegerOperationComparisonEqualWithString) {
  std::string input = "2==\"Hello\"";
  std::string expected_output = "false\n";

  std::string output = runReplWithInputPrint(input);

  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, BasicIntegerOperationComparisonNotEqualWithString) {
  std::string input = "2!=\"Hello\"";
  std::string expected_output = "true\n";

  std::string output = runReplWithInputPrint(input);

  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, BasicIntegerOperationComparisonLessThanWithString) {
  std::string input = R"(2<"B")";
  std::string expected_output = "true\n";

  std::string output = runReplWithInputPrint(input);

  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, BasicIntegerOperationComparisonLessThanOrEqualWithString) {
  std::string input = "2<=\"Hello\"";
  std::string expected_output = "true\n";

  std::string output = runReplWithInputPrint(input);

  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, BasicIntegerOperationComparisonGreaterThanWithString) {
  std::string input = "2>\"Hello\"";
  std::string expected_output = "false\n";

  std::string output = runReplWithInputPrint(input);

  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, BasicIntegerOperationComparisonGreaterThanOrEqualWithString) {
  std::string input = "2>=\"Hello\"";
  std::string expected_output = "false\n";

  std::string output = runReplWithInputPrint(input);

  EXPECT_EQ(output, expected_output);
}

TEST_F(ReplTest, BasicIntegerOperationComparisonEqualWithString2) {
  std::string input = "2==\"2\"";
  std::string expected_output = "true\n";

  std::string output = runReplWithInputPrint(input);

  EXPECT_EQ(output, expected_output);
}
