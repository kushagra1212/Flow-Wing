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


#include "BringTest.h"

void BringTest::SetUp() { _test->SetUp(); }

void BringTest::TearDown() { _test->TearDown(); }

TEST_F(BringTest, BringTestBasicTestAll) {

  writeFile("file1.fg", R"(
var x:int = 2

type TB = {
    s:str 
  }

type T  ={
    a:int,
    b:TB[2]
}

var k:T = {}

var j:T[2] 

class  A {
  var x:int 
  var y:T  
  
  init(y:T ) -> nthg {
    self.y = y 
  }

  printY() -> nthg {
      print(self.y)
  }

}




fun callS(x:int ) -> nthg {
  var aF:A = new A({b:[{s:"Hello"}]})
  print("Printing af ",aF.y)

  print("Printing k ",k)

  print("Print local x",x)
}
  )");

  writeFile("task.fg", R"(
bring "file1.fg"


print(x)

print(k)

print(j)



callS(88)

var p:T  

p = {a:2 }
print("print p ",p )
  )");

  std::system(createBuildAndRunCmd("task.fg").c_str());

#if AOT_TEST_MODE
  EXPECT_EQ(getOutput(), "\n2{ a : 0, b : [{ s : '' }, { s : '' }] }[{ a : 0, "
                         "b : [{ s : '' }, { s "
                         ": '' }] }, { a : 0, b : [{ s : '' }, { s : '' }] "
                         "}]Printing af { a : 0, b "
                         ": [{ s : 'Hello' }, { s : '' }] }Printing k { a : 0, "
                         "b : [{ s : '' }, { s "
                         ": '' }] }Print local x88print p { a : 2, b : [{ s : "
                         "'' }, { s : '' }] }");
#else

  EXPECT_EQ(getOutput(), "2{ a : 0, b : [{ s : '' }, { s : '' }] }[{ a : 0, "
                         "b : [{ s : '' }, { s "
                         ": '' }] }, { a : 0, b : [{ s : '' }, { s : '' }] "
                         "}]Printing af { a : 0, b "
                         ": [{ s : 'Hello' }, { s : '' }] }Printing k { a : 0, "
                         "b : [{ s : '' }, { s "
                         ": '' }] }Print local x88print p { a : 2, b : [{ s : "
                         "'' }, { s : '' }] }\n");

#endif
}

TEST_F(BringTest, BringTestBasicTestAllChoosy) {

  writeFile("file1.fg", R"(
expose var x:int = 2

expose type TB = {
    s:str 
  }

expose type T  ={
    a:int,
    b:TB[2]
}

expose var k:T = {}

expose var j:T[2] 

expose class  A {
  var x:int 
  var y:T  
  
  init(y:T ) -> nthg {
    self.y = y 
  }

  printY() -> nthg {
      print(self.y)
  }

}




expose fun callS(x:int ) -> nthg {
  var aF:A = new A({b:[{s:"Hello"}]})
  print("Printing af ",aF.y)

  print("Printing k ",k)

  print("Print local x",x)
}
  )");

  writeFile("task.fg", R"(
bring {x,k,j,callS,A} from "file1.fg"


print(x)

print(k)

print(j)



callS(88)

var p:T  

p = {a:2 }
print("print p ",p )

var g:A = new A({})

g.printY()
  )");

  std::system(createBuildAndRunCmd("task.fg").c_str());
#if AOT_TEST_MODE
  EXPECT_EQ(getOutput(), "\n2{ a : 0, b : [{ s : '' }, { s : '' }] }[{ a : 0, "
                         "b : [{ s : '' }, { s "
                         ": '' }] }, { a : 0, b : [{ s : '' }, { s : '' }] "
                         "}]Printing af { a : 0, b "
                         ": [{ s : 'Hello' }, { s : '' }] }Printing k { a : 0, "
                         "b : [{ s : '' }, { s "
                         ": '' }] }Print local x88print p { a : 2, b : [{ s : "
                         "'' }, { s : '' }] }{ "
                         "a : 0, b : [{ s : '' }, { s : '' }] }");
#else
  EXPECT_EQ(getOutput(), "2{ a : 0, b : [{ s : '' }, { s : '' }] }[{ a : 0, "
                         "b : [{ s : '' }, { s "
                         ": '' }] }, { a : 0, b : [{ s : '' }, { s : '' }] "
                         "}]Printing af { a : 0, b "
                         ": [{ s : 'Hello' }, { s : '' }] }Printing k { a : 0, "
                         "b : [{ s : '' }, { s "
                         ": '' }] }Print local x88print p { a : 2, b : [{ s : "
                         "'' }, { s : '' }] }{ "
                         "a : 0, b : [{ s : '' }, { s : '' }] }\n");

#endif
}