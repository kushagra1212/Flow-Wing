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


#include "StringOperation.h"
/*

    STRING OPERATIONS

*/

// Binary Operations on Strings

TEST_F(BinaryOperationTest, BasicStringOperationConcatWithNumber) {
  std::string input = R"("Hello"+2)";
  std::string expected_output = "Hello2";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(BinaryOperationTest, BasicStringOperationConcat) {
  std::string input = R"("Hello"+"FlowWing")";
  std::string expected_output = "HelloFlowWing";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(BinaryOperationTest, BasicStringOperationConcatWithDouble) {
  std::string input = R"("Hello"+2.0)";
  std::string expected_output = "Hello2.00000000000000";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(BinaryOperationTest, BasicStringOperationConcatWithBoolean) {
  std::string input = R"("Hello"+true)";
  std::string expected_output = "Hellotrue";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

// Binary Operations on Strings with Strings

TEST_F(BinaryOperationTest, BasicStringOperationConcatWithStrings) {
  std::string input = R"("Hello"+"FlowWing")";
  std::string expected_output = "HelloFlowWing";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

// Binary Operations on Strings with Strings ( Comparison Operations )

TEST_F(BinaryOperationTest, BasicStringOperationComparisonEqual) {
  std::string input = R"("Hello"=="Hello")";
  std::string expected_output = "true";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(BinaryOperationTest, BasicStringOperationComparisonNotEqual) {
  std::string input = R"("Hello"!="Hello")";
  std::string expected_output = "false";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(BinaryOperationTest, BasicStringOperationComparisonLessThan) {
  std::string input = R"("Hello"<"Hello")";
  std::string expected_output = "false";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(BinaryOperationTest, BasicStringOperationComparisonLessThanOrEqual) {
  std::string input = R"("Hello"<="Hello")";
  std::string expected_output = "true";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(BinaryOperationTest, BasicStringOperationComparisonGreaterThan) {
  std::string input = R"("Hello">"Hello")";
  std::string expected_output = "false";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(BinaryOperationTest, BasicStringOperationComparisonGreaterThanOrEqual) {
  std::string input = R"("Hello">="Hello")";
  std::string expected_output = "true";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(BinaryOperationTest, ComplexStringDoubleIntBoolOperation) {
  std::string input =
      R"(true*false*0*(1+true)+1.1*true+"S"+1*2+false*0.01+"1111"+"hello")";
  std::string expected_output = "1.10000000000000S20.000000000000001111hello";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(BinaryOperationTest, ComplexStringDoubleIntBoolOperationCompare) {
  std::string input =
      R"(true*false*0*(1+true)+1.1*true+"S"+1*2+false*0.01+"1111"+"hello"=="1.10000000000000S20.000000000000001111hello")";
  std::string expected_output = "true";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}