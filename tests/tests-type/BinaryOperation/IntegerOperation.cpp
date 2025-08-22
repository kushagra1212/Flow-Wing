/*
 * FlowWing Compiler
 * Copyright (C) 2023-2025 Kushagra Rathore
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */


#include "IntegerOperation.h"
/*

    INTEGER OPERATIONS

*/

/*

    INTEGER OPERATIONS WITH INTEGERS

*/

// Binary Operations on Integers with Integers ( Arithmetic Operations )

TEST_F(BinaryOperationTest, BasicIntegerOperationAddition) {
  std::string input = "2+2";
  std::string expected_output = "4";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(BinaryOperationTest, BasicIntegerOperationSubtraction) {
  std::string input = "2-2";
  std::string expected_output = "0";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(BinaryOperationTest, BasicIntegerOperationMultiplication) {
  std::string input = "2*2";
  std::string expected_output = "4";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(BinaryOperationTest, BasicIntegerOperationDivision) {
  std::string input = "2/2";
  std::string expected_output = "1.00000000000000";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(BinaryOperationTest, BasicIntegerOperationDivision2) {
  std::string input = "2/3";
  std::string expected_output = "0.66666666666667";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(BinaryOperationTest, BasicIntegerOperationDivision3) {
  std::string input = "5/2";
  std::string expected_output = "2.50000000000000";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

// Binary Operations on Integers with Integers ( Logical Operations )

TEST_F(BinaryOperationTest, BasicIntegerOperationLogicalAnd) {
  std::string input = "2&&2";
  std::string expected_output = "true";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(BinaryOperationTest, BasicIntegerOperationLogicalOr) {
  std::string input = "2||2";
  std::string expected_output = "true";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(BinaryOperationTest, BasicIntegerOperationLogicalNot) {
  std::string input = "!2";
  std::string expected_output = "false";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(BinaryOperationTest, BasicIntegerOperationLogicalNotNot) {
  std::string input = "!!2";
  std::string expected_output = "true";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

// Binary Operations on Integers with Integers ( Comparison Operations )

TEST_F(BinaryOperationTest, BasicIntegerOperationComparisonEqual) {
  std::string input = "2==2";
  std::string expected_output = "true";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(BinaryOperationTest, BasicIntegerOperationComparisonNotEqual) {
  std::string input = "2!=2";
  std::string expected_output = "false";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(BinaryOperationTest, BasicIntegerOperationComparisonLessThan) {
  std::string input = "2<2";
  std::string expected_output = "false";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(BinaryOperationTest, BasicIntegerOperationComparisonLessThanOrEqual) {
  std::string input = "2<=2";
  std::string expected_output = "true";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(BinaryOperationTest, BasicIntegerOperationComparisonGreaterThan) {
  std::string input = "2>2";
  std::string expected_output = "false";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(BinaryOperationTest, BasicIntegerOperationComparisonGreaterThanOrEqual) {
  std::string input = "2>=2";
  std::string expected_output = "true";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

// Binary Operations on Integers with Integers ( Bitwise Operations )

TEST_F(BinaryOperationTest, BasicIntegerOperationBitwiseAnd) {
  std::string input = "2&2";
  std::string expected_output = "2";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(BinaryOperationTest, BasicIntegerOperationBitwiseOr) {
  std::string input = "2|2";
  std::string expected_output = "2";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(BinaryOperationTest, BasicIntegerOperationBitwiseXor) {
  std::string input = "2^2";
  std::string expected_output = "0";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(BinaryOperationTest, BasicIntegerOperationNegation) {
  std::string input = "~2";
  std::string expected_output = "-3";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

/*

    INTEGER OPERATIONS WITH DOUBLES

*/

// Binary Operations on Integers with Doubles ( Arithmetic Operations )

TEST_F(BinaryOperationTest, BasicIntegerOperationAdditionWithDouble) {
  std::string input = "2+2.0";
  std::string expected_output = "4.00000000000000";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(BinaryOperationTest, BasicIntegerOperationSubtractionWithDouble) {
  std::string input = "2-2.0";
  std::string expected_output = "0.00000000000000";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(BinaryOperationTest, BasicIntegerOperationMultiplicationWithDouble) {
  std::string input = "2*2.0";
  std::string expected_output = "4.00000000000000";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(BinaryOperationTest, BasicIntegerOperationDivisionWithDouble) {
  std::string input = "2/2.0";
  std::string expected_output = "1.00000000000000";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

// Binary Operations on Integers with Doubles ( Comparison Operations )

TEST_F(BinaryOperationTest, BasicIntegerOperationComparisonEqualWithDouble) {
  std::string input = "2==2.0";
  std::string expected_output = "true";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(BinaryOperationTest, BasicIntegerOperationComparisonNotEqualWithDouble) {
  std::string input = "2!=2.0";
  std::string expected_output = "false";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(BinaryOperationTest, BasicIntegerOperationComparisonLessThanWithDouble) {
  std::string input = "2<2.0";
  std::string expected_output = "false";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(BinaryOperationTest,
       BasicIntegerOperationComparisonLessThanOrEqualWithDouble) {
  std::string input = "2<=2.0";
  std::string expected_output = "true";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(BinaryOperationTest,
       BasicIntegerOperationComparisonGreaterThanWithDouble) {
  std::string input = "2>2.0";
  std::string expected_output = "false";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(BinaryOperationTest,
       BasicIntegerOperationComparisonGreaterThanOrEqualWithDouble) {
  std::string input = "2>=2.0";
  std::string expected_output = "true";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

/*

    INTEGER OPERATIONS WITH BOOLEANS

*/

// Binary Operations on Integers with Booleans ( Arithmetic Operations )

TEST_F(BinaryOperationTest, BasicIntegerOperationAdditionWithBoolean) {
  std::string input = "2+true";
  std::string expected_output = "3";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(BinaryOperationTest, BasicIntegerOperationSubtractionWithBoolean) {
  std::string input = "2-true";
  std::string expected_output = "1";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

// Subtraction with False

TEST_F(BinaryOperationTest, BasicIntegerOperationSubtractionWithFalse) {
  std::string input = "2-false";
  std::string expected_output = "2";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(BinaryOperationTest, BasicIntegerOperationMultiplicationWithBoolean) {
  std::string input = "2*true";
  std::string expected_output = "2";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

// Multiplication with False

TEST_F(BinaryOperationTest, BasicIntegerOperationMultiplicationWithFalse) {
  std::string input = "2*false";
  std::string expected_output = "0";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(BinaryOperationTest, BasicIntegerOperationDivisionWithBoolean) {
  std::string input = "2/true";
  std::string expected_output = "2.00000000000000";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

// Binary Operations on Integers with Booleans ( Logical Operations )

TEST_F(BinaryOperationTest, BasicIntegerOperationLogicalAndWithBoolean) {
  std::string input = "2&&true";
  std::string expected_output = "true";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(BinaryOperationTest, BasicIntegerOperationLogicalOrWithBoolean) {
  std::string input = "2||true";
  std::string expected_output = "true";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

// Binary Operations on Integers with Booleans ( Comparison Operations )

TEST_F(BinaryOperationTest, BasicIntegerOperationComparisonEqualWithBoolean) {
  std::string input = "2==true";
  std::string expected_output = "false";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(BinaryOperationTest,
       BasicIntegerOperationComparisonNotEqualWithBoolean) {
  std::string input = "2!=true";
  std::string expected_output = "true";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(BinaryOperationTest,
       BasicIntegerOperationComparisonLessThanWithBoolean) {
  std::string input = "2<true";
  std::string expected_output = "false";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(BinaryOperationTest,
       BasicIntegerOperationComparisonLessThanOrEqualWithBoolean) {
  std::string input = "2<=true";
  std::string expected_output = "false";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(BinaryOperationTest,
       BasicIntegerOperationComparisonGreaterThanWithBoolean) {
  std::string input = "2>true";
  std::string expected_output = "true";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(BinaryOperationTest,
       BasicIntegerOperationComparisonGreaterThanOrEqualWithBoolean) {
  std::string input = "2>=true";
  std::string expected_output = "true";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

// Binary Operations on Integers with Booleans ( Bitwise Operations )

TEST_F(BinaryOperationTest, BasicIntegerOperationBitwiseAndWithBoolean) {
  std::string input = "2&true";
  std::string expected_output = "0";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(BinaryOperationTest, BasicIntegerOperationBitwiseOrWithBoolean) {
  std::string input = "2|true";
  std::string expected_output = "3";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(BinaryOperationTest, BasicIntegerOperationBitwiseXorWithBoolean) {
  std::string input = "2^true";
  std::string expected_output = "3";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

// Binary Operations on Integers with Strings ( Arithmetic Operations )

TEST_F(BinaryOperationTest, BasicIntegerOperationAdditionWithString) {
  std::string input = "2+\"Hello\"";
  std::string expected_output = "2Hello";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

// Binary Operations on Integers with Strings ( Comparison Operations )

TEST_F(BinaryOperationTest, BasicIntegerOperationComparisonEqualWithString) {
  std::string input = "2==\"Hello\"";
  std::string expected_output = "false";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(BinaryOperationTest, BasicIntegerOperationComparisonNotEqualWithString) {
  std::string input = "2!=\"Hello\"";
  std::string expected_output = "true";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(BinaryOperationTest, BasicIntegerOperationComparisonLessThanWithString) {
  std::string input = R"(2<"B")";
  std::string expected_output = "true";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(BinaryOperationTest,
       BasicIntegerOperationComparisonLessThanOrEqualWithString) {
  std::string input = "2<=\"Hello\"";
  std::string expected_output = "true";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(BinaryOperationTest,
       BasicIntegerOperationComparisonGreaterThanWithString) {
  std::string input = "2>\"Hello\"";
  std::string expected_output = "false";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(BinaryOperationTest,
       BasicIntegerOperationComparisonGreaterThanOrEqualWithString) {
  std::string input = "2>=\"Hello\"";
  std::string expected_output = "false";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(BinaryOperationTest, BasicIntegerOperationComparisonEqualWithString2) {
  std::string input = "2==\"2\"";
  std::string expected_output = "true";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}
