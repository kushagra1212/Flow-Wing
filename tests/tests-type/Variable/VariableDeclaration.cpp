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


#include "VariableDeclaration.h"

void VariableDeclaration::SetUp() { _test->SetUp(); }

void VariableDeclaration::TearDown() { _test->TearDown(); }

// Variable Declaration

// REPL TESTS

// Variable Declaration
TEST_F(VariableDeclaration, BasicVariableDeclaration) {
  std::string input = R"(var a = 2)";
  std::string expected_output = "";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

// Variable Re-Declaration in the Different scope
TEST_F(VariableDeclaration, BasicVariableReDeclarationInDifferentScope) {
  std::string input = R"(var a = 2 { var a = 3 })";
  std::string expected_output = "";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

// Variable Declaration with Different Identifier
TEST_F(VariableDeclaration, BasicVariableDeclarationWithDifferentIdentifier) {
  std::string input = R"(var a = 2 var b = 3)";

  std::string expected_output = "";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

// Variable Declaration with Different Initializer
TEST_F(VariableDeclaration, BasicVariableDeclarationWithDifferentInitializer) {
  std::string input = R"(var a = 2 + 3)";

  std::string expected_output = "";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

// Constant Variable Declaration
TEST_F(VariableDeclaration, BasicConstantVariableDeclaration) {
  std::string input = R"(const a = 2)";

  std::string expected_output = "";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

// Constant Variable Re-Declaration in Different Scope
TEST_F(VariableDeclaration,
       BasicConstantVariableReDeclarationInDifferentScope) {
  std::string input = R"(const a = 2 { const a = 3 })";

  std::string expected_output = "";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

// Constant Variable Declaration with Different Identifier
TEST_F(VariableDeclaration,
       BasicConstantVariableDeclarationWithDifferentIdentifier) {
  std::string input = R"(const a = 2 const b = 3)";

  std::string expected_output = "";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(VariableDeclaration, VariableDeclarationAndASSIGNMENT) {
  std::string input =
      R"(fun main2() -> int {
      var x = 2
      print(2) print(x) print(x+2) print(x+true) print(x+false)
      print(x+1.1) x = 2.2 print(x+2) print(x+false) print(x+true)
      x  =  true
      print(x==false) print(x+false)
      print(x+true) print(x+1) print(x+1.1)
      print(x+"Hello")
      return (0)
      }
      var y:int = main2()
      )";

  std::string expected_output =
      "224323.100000000000004.200000000000002.200000000000003."
      "20000000000000falsetruetrue22.10000000000000trueHello";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(VariableDeclaration, VariableDeclarationAndASSIGNMENTForGlobalVariable) {
  std::string input =
      R"(
      var x = 2
      print(2) print(x) print(x+2) print(x+true) print(x+false)
      print(x+1.1) x = 2.2 print(x+2) print(x+false) print(x+true)
      x  =  true
      print(x==false) print(x+false)
      print(x+true) print(x+1) print(x+1.1)
      print(x+"Hello")
      )";

  std::string expected_output =
      "224323.100000000000004.200000000000002.200000000000003."
      "20000000000000falsetruetrue22.10000000000000trueHello";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}

TEST_F(VariableDeclaration, VariableDeclarationAndASSIGNMENT2) {
  std::string input =
      R"(
print("String"+"\n")
var x = "This is a string"
print(x+"\n")
x = 2
print(x+"\n")
x = true
print(x+"\n")
x = 2.0
print(x+"\n")

print("Int"+"\n")
var y = 2
print(y+"\n")
y = 2.0
print(y+"\n")
y = true
print(y+"\n")
y = "This is a string"
print(y+"\n")

print("Bool"+"\n")
var z = true
print(z+"\n")
z = 2
print(z+"\n")
z = 2.0
print(z+"\n")
z = "This is a string"
print(z+"\n")

print("Float"+"\n")
var a = 2.0
print(a+"\n")
a = 2
print(a+"\n")
a = true
print(a+"\n")
a = "This is a string"
print(a+"\n"))";

  std::string expected_output =
      R"(String
This is a string
2
true
2.00000000000000
Int
2
2.00000000000000
true
This is a string
Bool
true
2
2.00000000000000
This is a string
Float
2.00000000000000
2
true
This is a string
)";

  setInput(input);
  runEvaluator();
  EXPECT_EQ(getOutput(), expected_output);
}
