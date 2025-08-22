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


#include "FunctionTest.h"

void FunctionTest::SetUp() { _test->SetUp(); }

void FunctionTest::TearDown() { _test->TearDown(); }

#if defined(JIT_TEST_MODE) || defined(AOT_TEST_MODE)

// TEST_F(FunctionTest, F) {
//   I(R"(
// fun gS() -> str  {
//   return "Something"
// }

// fun gI() -> int   {
//   return 11
// }
// {
//     var x:deci = Decimal(input(gS()))
// print("x: ",x+2)
// var y:int =  Int32(input(gI()))
// print("y :",y+2)

//   }

// var x:deci = Decimal(input("Enter"))
// print("x: ",x+2)
// var y:int =  Int32(input("Enter"))
// print("y :",y+2)
// var z:bool = Bool(input("Enter Bool: "))
// print("z :",z+2)
// var s:str = input("Enter")
// print("s: ",s+2)
// var ss:str =  String(input("Enter String: "))
// print("ss: ",ss+2)
//     )");

//   EXPECT_EQ(getOutput(),R"(22222222)");
// }

#endif