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


#include "DoubleOperation.h"

/*

  DOUBLE OPERATION

*/

// Double Operation on Double ( Arithmetic )

TEST_F(BinaryOperationTest, BasicDoubleOperationAddition) {
  std::string input = "1.0+1.0";
  std::string expected_output = "2.00000000000000";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(BinaryOperationTest, BasicDoubleOperationSubtraction) {
  std::string input = "1.0-1.0";
  std::string expected_output = "0.00000000000000";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(BinaryOperationTest, BasicDoubleOperationMultiplication) {
  std::string input = "1.0*1.0";
  std::string expected_output = "1.00000000000000";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(BinaryOperationTest, BasicDoubleOperationDivision) {
  std::string input = "1.0/1.0";
  std::string expected_output = "1.00000000000000";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

// Double Operation on Double ( Comparison )

TEST_F(BinaryOperationTest, BasicDoubleOperationLessThan) {
  std::string input = "1.0<1.0";
  std::string expected_output = "false";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(BinaryOperationTest, BasicDoubleOperationLessThanOrEqual) {
  std::string input = "1.0<=1.0";
  std::string expected_output = "true";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

// Double Operation on Double ( Equality )

TEST_F(BinaryOperationTest, BasicDoubleOperationEqual) {
  std::string input = "1.0==1.0";
  std::string expected_output = "true";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(BinaryOperationTest, BasicDoubleOperationNotEqual) {
  std::string input = "1.0!=1.0";
  std::string expected_output = "false";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}
