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


#include "If-Or-If-Else.h"

void IfORIFELSEReplTest::SetUp() { _test->SetUp(); }

void IfORIFELSEReplTest::TearDown() { _test->TearDown(); }

// TESTS

TEST_F(IfORIFELSEReplTest, BasicIfRRepl) {
  std::string input = R"(if(true) { print(5) })";
  std::string expected_output = "5";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(IfORIFELSEReplTest, BasicIfElseRepl) {
  std::string input = R"(if(false) { print( 5) } else { print( 6) })";
  std::string expected_output = "6";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(IfORIFELSEReplTest, BasicIfElseWithDifferentConditionRepl) {
  std::string input = R"(if(2 > 3) { print( 5) } else { print( 6) })";
  std::string expected_output = "6";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(IfORIFELSEReplTest, BasicIfFalseRepl) {
  std::string input = R"(if(false) { print(5) })";
  std::string expected_output = "";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(IfORIFELSEReplTest, BasicNestedIfElseRepl) {
  std::string input =
      R"(if(true) { if(false) { print( 5) } else { print( 6) } } else {
      print( 7) })";
  std::string expected_output = "6";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(IfORIFELSEReplTest, BasicNestedIfElseWithDifferentConditionRepl) {
  std::string input =
      R"(if(true) { if(2 > 3) { print( 5) } else { print( 6) } } else {
      print( 7) })";
  std::string expected_output = "6";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(IfORIFELSEReplTest, BasicIfElseRepl2) {
  std::string input = R"(if(true) { print( 5) } else { print( 6) })";
  std::string expected_output = "5";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(IfORIFELSEReplTest, BasicOrIfRepl) {
  std::string input =
      R"(if(false) { print( 4) } or if(true) { print( 5) } else { print( 6)})";
  std::string expected_output = "5";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(IfORIFELSEReplTest, BasicElseRepl) {
  std::string input = R"(if(false) { print( 4) } else { print( 6) })";
  std::string expected_output = "6";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(IfORIFELSEReplTest, NestedIfElseOrIfRepl) {
  std::string input =
      R"(if(true) { if(2 > 3) { print( 5) } or if(4 > 3) { print( 7) } else {
      print( 8) } } else { print( 9) })";
  std::string expected_output = "7";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(IfORIFELSEReplTest, MultipleOrIfRepl) {
  std::string input =
      R"(if(false) { print( 4) } or if(false) { print( 5) } or if(true) {
      print( 6) } else { print( 7) })";
  std::string expected_output = "6";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(IfORIFELSEReplTest, NestedOrIfElseRepl) {
  std::string input =
      R"(if(false) { print( 4) } or if(true) { if(2 > 3) { print( 5) } else {
      print( 6) } } else { print( 7) })";
  std::string expected_output = "6";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(IfORIFELSEReplTest, ComplexNestedIfOrIfElseRepl) {
  std::string input =
      R"(if(true) { if(false) { print(10) } or if(true) { if(5 > 3) {
      print(15) } else { print(20) } } else { print(25) } } else { print(30)
      })";
  std::string expected_output = "15";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(IfORIFELSEReplTest, ComplexOrIfElseRepl) {
  std::string input =
      R"(if(false) { print(10) } or if(false) { print(20) } or if(true) {
      if(7 > 5) { print(30) } else { print(40) } } else { print(50) })";
  std::string expected_output = "30";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(IfORIFELSEReplTest, ComplexNestedOrIfElseRepl) {
  std::string input =
      R"(if(false) { print(10) } or if(true) { if(false) { print(20) } else {
      if(8 > 5) { print(35) } else { print(45) } } } else { print(50) })";
  std::string expected_output = "35";
  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}
