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


#include "IndexTest.h"

void IndexTest::SetUp() { _test->SetUp(); }

void IndexTest::TearDown() { _test->TearDown(); }

TEST_F(IndexTest, IndexTestAssignmentBasicInsideClassUsingSelf) {
  I(R"(
class A{
    var x:int[2]
  

    init(x:int[2]) -> nthg {
      self.x[1] = x[1]
    }


  }


  var a: A = new A([2,3])


  print(a.x)
    )");

  EXPECT_EQ(getOutput(), R"([0, 3])");
}
TEST_F(IndexTest, IndexTestAssignmentBasicInsideClassUsingSelfObject) {
  I(R"(

class A{ 

  type T = {
      a:int 
    }
    var x:T[2]
  

    init(x:T[2]) -> nthg {
      self.x[1] = x[1]
    }


  }


  var a: A = new A([{},{a:10}])


  print(a.x)
    )");

  EXPECT_EQ(getOutput(), R"([{ a : 0 }, { a : 10 }])");
}