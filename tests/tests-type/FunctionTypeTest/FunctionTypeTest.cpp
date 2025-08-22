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


#include "FunctionTypeTest.h"

void FunctionTypeTest::SetUp() { _test->SetUp(); }

void FunctionTypeTest::TearDown() { _test->TearDown(); }

TEST_F(FunctionTypeTest, BasicTest) {
  I(R"(
fun printX(x: int) -> nthg {
    print("Printing X",x)
  }


fun main2(f:[(int)-> nthg]) -> nthg {
f(2)
}


  main2(printX)
    )");

  EXPECT_EQ(getOutput(), "Printing X2");
}
TEST_F(FunctionTypeTest, BasicWithPrimitiveType) {
  I(R"(
fun printX(x: int,y:deci,p:str,u:bool,ano:[(str)->nthg]) -> nthg {
    print("Printing X",x)
    print(y,p,u)
    ano("Hehe")
  }
fun printS(x: str) -> nthg {
  print("\n from printS",x)
}

fun main2(f:[(int,deci,str,bool,[(str)->nthg])-> nthg]) -> nthg {
f(2,2.2,"Sss",false,printS)
}


  main2(printX)
    )");

  EXPECT_EQ(getOutput(), R"(Printing X22.20000000000000Sssfalse
 from printSHehe)");
}

TEST_F(FunctionTypeTest, BasicWithPrimitiveType2) {
  I(R"(
fun printX(x: int,y:deci,p:str,u:bool,ano:[(str)->nthg]) -> nthg {
    print("Printing X",x)
    print(y,p,u)
    ano("Hehe")
  }
fun printS(x: str) -> nthg {
  print("\n from printS",x)
}

fun getDeci(y:int,j:str) -> deci  {
    print("\ny",y,"\nj",j)

    return 3.5
  }

fun main2(f:[(int,deci,str,bool,[(str)->nthg])-> nthg] , c: [(int,str)->deci]) -> int {
f(2,2.2,"Sss",false,printS)c(23,"getDeci")
return 2
}


  main2(printX,getDeci)
    )");

  EXPECT_EQ(getOutput(), R"(Printing X22.20000000000000Sssfalse
 from printSHehe
y23
jgetDeci)");
}
TEST_F(FunctionTypeTest, BasicWithPrimitiveType3) {
  I(R"(
fun printX(x: int,y:deci,p:str,u:bool,ano:[(str)->nthg],d:deci ) -> nthg {
    print("Printing X",x)
    print(y,p,u)
    ano("Hehe")
    print("D",d)
  }
fun printS(x: str) -> nthg {
  print("\n from printS",x)
}

fun getDeci(y:int,j:str) -> deci  {
    print("\ny",y,"\nj",j)

    return 3.5
  }

fun main2(f:[(int,deci,str,bool,[(str)->nthg],deci)-> nthg] , c: [(int,str)->deci]) -> int {
f(2,2.2,"Sss",false,printS,c(23,"getDeci"))return 2
}


  main2(printX,getDeci)
    )");

  EXPECT_EQ(getOutput(), R"(
y23
jgetDeciPrinting X22.20000000000000Sssfalse
 from printSHeheD3.50000000000000)");
}