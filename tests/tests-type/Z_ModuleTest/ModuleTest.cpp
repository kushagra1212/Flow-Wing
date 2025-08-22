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

#include "ModuleTest.h"

void ModuleTest::SetUp() { _test->SetUp(); }

void ModuleTest::TearDown() { _test->TearDown(); }

TEST_F(ModuleTest, ModuleImportTest) {
  writeFile("test-module.fg", R"(module [test]
  
    var x:int = 2
  )");

  writeFile("temp.fg", R"(
    bring test
    print(test::x)
  )");

  std::system(createBuildAndRunCmd("temp.fg").c_str());

#if AOT_TEST_MODE
  EXPECT_EQ(getOutput(), "\n2");

#else
  EXPECT_EQ(getOutput(), "2\n");
#endif
}

TEST_F(ModuleTest, ModuleImportTestFunction) {
  writeFile("test2-module.fg", R"(module [test2]
  
    var x:int = 2
 
 fun main2(x:int,s:str) -> nthg {
    print("Printing from Module Test "+x+s)
}
  )");

  writeFile("temp2.fg", R"(
bring test2

test2::main2(2,"s")
  )");

  std::system(createBuildAndRunCmd("temp2.fg").c_str());
#if AOT_TEST_MODE
  EXPECT_EQ(getOutput(), "\nPrinting from Module Test 2s");

#else
  EXPECT_EQ(getOutput(), "Printing from Module Test 2s\n");
#endif
}

TEST_F(ModuleTest, ModuleImportTestCustomTypes) {
  writeFile("local-module.fg", R"(
module [local]


type T = {
    a:int
  }

  var x:local::T

fun main() -> nthg {
  print(local::x)
  }

  )");

  writeFile("temp.fg", R"(
bring local

local::main()
print(local::x)
  )");

  std::system(createBuildAndRunCmd("temp.fg").c_str());
#if AOT_TEST_MODE
  EXPECT_EQ(getOutput(), "\n{ a : 0 }{ a : 0 }");
#else
  EXPECT_EQ(getOutput(), "{ a : 0 }{ a : 0 }\n");
#endif
}
TEST_F(ModuleTest, ModuleImportTestCustomTypesAssignment) {
  writeFile("local-module.fg", R"(
module [local]


type T = {
    a:int
  }

  var x:local::T

fun main() -> nthg {
  local::x = {a:2}
print(local::x)
}

  )");

  writeFile("temp.fg", R"(
bring local


local::main()
  )");

  std::system(createBuildAndRunCmd("temp.fg").c_str());
#if AOT_TEST_MODE
  EXPECT_EQ(getOutput(), "\n{ a : 2 }");
#else
  EXPECT_EQ(getOutput(), "{ a : 2 }\n");
#endif
}
TEST_F(ModuleTest, ModuleImportTestCustomTypesAssignment2) {
  writeFile("local-module.fg", R"(
module [local]


type T = {
    a:int
  }

  var x:local::T

fun main() -> nthg {
  local::x = {a:2}
  var k:local::T
  print(k)
print(local::x)
}

  )");

  writeFile("temp.fg", R"(
bring local


local::main()
  )");

  std::system(createBuildAndRunCmd("temp.fg").c_str());
#if AOT_TEST_MODE
  EXPECT_EQ(getOutput(), "\n{ a : 0 }{ a : 2 }");
#else
  EXPECT_EQ(getOutput(), "{ a : 0 }{ a : 2 }\n");
#endif
}

TEST_F(ModuleTest, ModuleImportTestCustomTypesAssignment3) {
  writeFile("local-module.fg", R"(
module [local]


type T = {
    a:int
  }

  var x:local::T

fun main() -> nthg {
  local::x = {a:2}
  var k:local::T
  print(k)
print(local::x)
}

  )");

  writeFile("temp.fg", R"(
bring local



local::x = {a:3}
print(local::x)
local::main()

local::x = {a:3}
print(local::x)
  )");

  std::system(createBuildAndRunCmd("temp.fg").c_str());
#if AOT_TEST_MODE
  EXPECT_EQ(getOutput(), "\n{ a : 3 }{ a : 0 }{ a : 2 }{ a : 3 }");
#else
  EXPECT_EQ(getOutput(), "{ a : 3 }{ a : 0 }{ a : 2 }{ a : 3 }\n");
#endif
}
TEST_F(ModuleTest, ModuleImportTestCustomTypes2) {
  writeFile("local-module.fg", R"(
module [local]


type P ={
    a:int 
  }

type T = {
    a:int,
    b:str,
    c:deci,
    d:deci32,
    e:bool,
    f:local::P
  }

  var x:local::T

fun main() -> nthg {
  local::x = {a:2}
  var k:local::T
  print(k)
print(local::x)
}
  )");

  writeFile("temp.fg", R"(
bring local


var j:local::T = {a:5}


print(j)
  )");

  std::system(createBuildAndRunCmd("temp.fg").c_str());
#if AOT_TEST_MODE
  EXPECT_EQ(getOutput(), "\n{ a : 5, b : '', c : 0.00000000000000, d : "
                         "0.0000000, e : false, f : { "
                         "a : 0 } }");
#else
  EXPECT_EQ(getOutput(), "{ a : 5, b : '', c : 0.00000000000000, d : "
                         "0.0000000, e : false, f : { "
                         "a : 0 } }\n");
#endif
}
TEST_F(ModuleTest, ModuleImportTestFunctionTest) {
  writeFile("local-module.fg", R"(
module [local]


type P ={
    a:int 
  }

type T = {
    a:int,
    b:str,
    c:deci,
    d:deci32,
    e:bool,
    f:local::P
  }

  var x:local::T


fun callMe(y:local::T) -> local::T {
  var p:local::T = y

  p.e = true

  return p

  
}

fun main() -> nthg {
  local::x = {a:2}
  var k:local::T
  print(k)
print(local::x)
}
  )");

  writeFile("temp.fg", R"(
bring local


print(local::callMe({a:10}))
  )");

  std::system(createBuildAndRunCmd("temp.fg").c_str());
#if AOT_TEST_MODE
  EXPECT_EQ(getOutput(), "\n{ a : 10, b : '', c : 0.00000000000000, d : "
                         "0.0000000, e : true, f : { "
                         "a : 0 } }");
#else
  EXPECT_EQ(getOutput(), "{ a : 10, b : '', c : 0.00000000000000, d : "
                         "0.0000000, e : true, f : { "
                         "a : 0 } }\n");
#endif
}

TEST_F(ModuleTest, ModuleImportTestFunctionTest2) {
  writeFile("local-module.fg", R"(
module [local]


type P ={
    a:int 
  }

type T = {
    a:int,
    b:str,
    c:deci,
    d:deci32,
    e:bool,
    f:local::P
  }

  var x:local::T

fun main() -> nthg {
  local::x = {a:2}
  var k:local::T
  print(k)
print(local::x)
}
fun callMe(y:local::T) -> local::T {
  var p:local::T = y

  p.e = true
local::main()
  return p

  
}
  )");

  writeFile("temp.fg", R"(
bring local


print(local::callMe({a:10}))
  )");

  std::system(createBuildAndRunCmd("temp.fg").c_str());
#if AOT_TEST_MODE
  EXPECT_EQ(getOutput(), "\n{ a : 0, b : '', c : 0.00000000000000, d : "
                         "0.0000000, e : false, f : { "
                         "a : 0 } }{ a : 2, b : '', c : 0.00000000000000, d : "
                         "0.0000000, e : false, "
                         "f : { a : 0 } }{ a : 10, b : '', c : "
                         "0.00000000000000, d : 0.0000000, e : "
                         "true, f : { a : 0 } }");
#else
  EXPECT_EQ(getOutput(), "{ a : 0, b : '', c : 0.00000000000000, d : "
                         "0.0000000, e : false, f : { "
                         "a : 0 } }{ a : 2, b : '', c : 0.00000000000000, d : "
                         "0.0000000, e : false, "
                         "f : { a : 0 } }{ a : 10, b : '', c : "
                         "0.00000000000000, d : 0.0000000, e : "
                         "true, f : { a : 0 } }\n");
#endif
}

TEST_F(ModuleTest, ModuleImportTestUsingClass) {
  writeFile("local-module.fg", R"(
module [local]


type T ={
    a:int 
  }
var x:int


class A {

  var x:local::T 
  var u:int


  init() -> nthg {

  }
}


var g:local::T = {}

fun main()-> nthg {
var a:local::A =  new local::A()
print(a.u)
a.x = {a:100}

print(a.x)

}
  )");

  writeFile("temp.fg", R"(
bring local


print(local::main())
  )");

  std::system(createBuildAndRunCmd("temp.fg").c_str());
#if AOT_TEST_MODE
  EXPECT_EQ(getOutput(), "\n0{ a : 100 }");
#else
  EXPECT_EQ(getOutput(), "0{ a : 100 }\n");
#endif
}
TEST_F(ModuleTest, ModuleImportTestUsingClassAccess) {
  writeFile("local-module.fg", R"(
module [local]


type T ={
    a:int 
  }
var x:int


class A {

  var x:local::T 
  var u:int


  init() -> nthg {

  }
}





  )");

  writeFile("temp.fg", R"(
bring local

var g:local::T = {}
var a:local::A =  new local::A()

print(a.x)
print(a.u)
a.x = {a:21}
print(a.x)
  )");

  std::system(createBuildAndRunCmd("temp.fg").c_str());
#if AOT_TEST_MODE
  EXPECT_EQ(getOutput(), "\n{ a : 0 }0{ a : 21 }");
#else
  EXPECT_EQ(getOutput(), "{ a : 0 }0{ a : 21 }\n");
#endif
}
//! Not Supported as of now
// TEST_F(ModuleTest, ModuleImportTestUsingClassAccess3) {
//   writeFile("local-module.fg", R"(
// module [local]

// type T ={
//     a:int
//   }
// var x:int

// class A {

//   var x:local::T
//   var u:int

//   init() -> nthg {

//   }
// }

// var g:local::T = {}
// var a:local::A =  new local::A()

//   )");

//   writeFile("temp.fg", R"(
// bring local

// print(local::a.x)
// print(local::a.u)
// local::a.x = {a:21}
// print(local::a.x)
//   )");

//   std::system(createBuildAndRunCmd("temp.fg").c_str());
// #if AOT_TEST_MODE
//   EXPECT_EQ(getOutput(), "\n{ a : 0 }0{ a : 21 }");
// #else
//   EXPECT_EQ(getOutput(), "{ a : 0 }0{ a : 21 }\n");
// #endif
// }
TEST_F(ModuleTest, ModuleImportTestUsingClassAccess2) {
  writeFile("local-module.fg", R"(
module [local]


var x:int


class A {

type T ={
    a:int 
  }
  var x:T 
  var u:int


  init() -> nthg {

  }
}


  )");

  writeFile("temp.fg", R"(
bring local

var a:local::A =  new local::A()

print(a.x)
print(a.u)
a.x = {a:21}
print(a.x)
  )");

  std::system(createBuildAndRunCmd("temp.fg").c_str());
#if AOT_TEST_MODE
  EXPECT_EQ(getOutput(), "\n{ a : 0 }0{ a : 21 }");
#else
  EXPECT_EQ(getOutput(), "{ a : 0 }0{ a : 21 }\n");
#endif
}
TEST_F(ModuleTest, ModuleImportTestUsingClassAccess3) {
  writeFile("local-module.fg", R"(
module [local]


var x:int


class A {

type T ={
    a:int 
  }
  var x:T 
  var u:int


  init() -> nthg {

  }
}
  )");

  writeFile("temp.fg", R"(
bring local
var a:local::A =  new local::A()
print(a.x)
print(a.u)
a.x = {a:21}
print(a.x)
  )");

  std::system(createBuildAndRunCmd("temp.fg").c_str());
#if AOT_TEST_MODE
  EXPECT_EQ(getOutput(), "\n{ a : 0 }0{ a : 21 }");
#else
  EXPECT_EQ(getOutput(), "{ a : 0 }0{ a : 21 }\n");
#endif
}
TEST_F(ModuleTest, ModuleImportTestUsingClassAccess4) {
  writeFile("local-module.fg", R"(
module [local]


var x:int


class A {

type T ={
    a:int 
  }
  var x:T 
  var u:int


  init() -> nthg {

  }

  printX() -> nthg {
      print(self.x)
    }
}
  )");

  writeFile("temp.fg", R"(
bring local
var a:local::A =  new local::A()
print(a.x)
print(a.u)
a.x = {a:21}
a.printX()
  )");

  std::system(createBuildAndRunCmd("temp.fg").c_str());
#if AOT_TEST_MODE
  EXPECT_EQ(getOutput(), "\n{ a : 0 }0{ a : 21 }");
#else
  EXPECT_EQ(getOutput(), "{ a : 0 }0{ a : 21 }\n");
#endif
}
