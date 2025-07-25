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


#include "Malloc.h"

void Malloc::SetUp() { _test->SetUp(); }

void Malloc::TearDown() { _test->TearDown(); }

#if defined(JIT_TEST_MODE) || defined(AOT_TEST_MODE)
TEST_F(Malloc, MallocTestForPremitives) {
  I(R"(
var x:int = new 5 
print(x)
print("\n")
x = 100
print(x+"\n")
var d:deci = new 2.2
print(d)
print("\n")
var s:str = new "Home"
print(s)
var b:bool = new true
print("\n"+b)

    )");

  EXPECT_EQ(getOutput(), R"(5
100
2.20000000000000
Home
true)");
}
TEST_F(Malloc, MallocTestForPremitivesLocal) {
  I(R"(
{
    var x:int = new 5 
print(x)
print("\n")
x = 100
print(x+"\n")
var d:deci = new 2.2
print(d)
print("\n")
var s:str = new "Home"
print(s)
var b:bool = new true
print("\n"+b)
}

    )");

  EXPECT_EQ(getOutput(), R"(5
100
2.20000000000000
Home
true)");
}

TEST_F(Malloc, MallocTestForObject) {
  I(R"(
type obj  = {
    a:int,
    b:str,
    c:deci,
    d:bool,
    p:int[2]
}
var o:obj = new {a:2}
o.p[1] = 10
print(o)


    )");

  EXPECT_EQ(
      getOutput(),
      R"({ a : 2, b : '', c : 0.00000000000000, d : false, p : [0, 10] })");
}

TEST_F(Malloc, MallocTestForObjectArray) {
  I(R"(
type obj  = {
    a:int,
    b:str,
    c:deci,
    d:bool,
    p:int[2]
}
var o:obj[2] = new [{a:2}]
o[1].p[1] = 10
print(o)


    )");

  EXPECT_EQ(
      getOutput(),
      R"([{ a : 2, b : '', c : 0.00000000000000, d : false, p : [0, 0] }, { a : 0, b : '', c : 0.00000000000000, d : false, p : [0, 10] }])");
}

TEST_F(Malloc, MallocTestForObjectLocal) {
  I(R"(
{
    type obj  = {
    a:int,
    b:str,
    c:deci,
    d:bool,
    p:int[2]
}
var o:obj = new {a:2}
o.p[1] = 10
print(o)
}


    )");

  EXPECT_EQ(
      getOutput(),
      R"({ a : 2, b : '', c : 0.00000000000000, d : false, p : [0, 10] })");
}

TEST_F(Malloc, MallocTestForObjectArrayLocal) {
  I(R"(
{
    type obj  = {
    a:int,
    b:str,
    c:deci,
    d:bool,
    p:int[2]
}
var o:obj[2] = new [{a:2}]
o[1].p[1] = 10
print(o)

}

    )");

  EXPECT_EQ(
      getOutput(),
      R"([{ a : 2, b : '', c : 0.00000000000000, d : false, p : [0, 0] }, { a : 0, b : '', c : 0.00000000000000, d : false, p : [0, 10] }])");
}

TEST_F(Malloc, MallocTestForObjectArrayComplexLocal) {
  I(R"(
 type obj = {
    i:int,
    s:str
  }
type k = {
  o: int,
  s: str,
  d: deci,
  i: int,
  ob:obj
}
type par = {
  u: str,
  g: k[2]
}
type t = {
  x: int,
  y: str,
  a: deci,
  b: bool,
  ar: par[1]
}
fun getGKA() -> k[2] {
  var gka: k  = {
  i:1022,
 o: 102,
  s: "sora"
  
}
var x:k[2] = [gka]

    return x
  }

fun getT()-> t{
  var tt:t = {y:"NO",b:true,ar:[{u:"eeet",g:getGKA()}]}
  return tt
  }

fun getArr()-> t[2] {
var a:t[2] = [{x:2,y:"hello",a:3.3,b:true,ar:[{u:"get",g:getGKA()}]}]
return a
  }
{
  var arr:t[2] = new [{x:300,y:"eee",a:4.3,b:true,ar:[{g:getGKA()}]}]
print(arr)
print("\n\n")
arr = new [{x:2}]
print(arr)
arr[0].ar[0].g = getGKA()
}

    )");

  EXPECT_EQ(
      getOutput(),
      R"([{ x : 300, y : 'eee', a : 4.30000000000000, b : true, ar : [{ u : '', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }]

[{ x : 2, y : 'eee', a : 4.30000000000000, b : true, ar : [{ u : '', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }])");
}

TEST_F(Malloc, MallocTestForObjectArrayComplex2Local) {
  I(R"(
 type obj = {
    i:int,
    s:str
  }
type k = {
  o: int,
  s: str,
  d: deci,
  i: int,
  ob:obj
}
type par = {
  u: str,
  g: k[2]
}
type t = {
  x: int,
  y: str,
  a: deci,
  b: bool,
  ar: par[1]
}
fun getGKA() -> k[2] {
  var gka: k  = {
  i:1022,
 o: 102,
  s: "sora"
  
}
var x:k[2] = [gka]

    return x
  }

fun getT()-> t{
  var tt:t = {y:"NO",b:true,ar:[{u:"eeet",g:getGKA()}]}
  return tt
  }

fun getArr()-> t[2] {
var a:t[2] = [{x:2,y:"hello",a:3.3,b:true,ar:[{u:"get",g:getGKA()}]}]
return a
  }
{
  var arr:t[2] = new [{x:300,y:"eee",a:4.3,b:true,ar:[{g:getGKA()}]}]
print(arr)
print("\n\n")
arr <- new [{x:2}]
print(arr)
arr[0].ar[0].g = getGKA()
}

    )");

  EXPECT_EQ(
      getOutput(),
      R"([{ x : 300, y : 'eee', a : 4.30000000000000, b : true, ar : [{ u : '', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }]

[{ x : 2, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }])");
}

TEST_F(Malloc, MallocTestForObjectArrayComplex) {
  I(R"(
 type obj = {
    i:int,
    s:str
  }
type k = {
  o: int,
  s: str,
  d: deci,
  i: int,
  ob:obj
}
type par = {
  u: str,
  g: k[2]
}
type t = {
  x: int,
  y: str,
  a: deci,
  b: bool,
  ar: par[1]
}
fun getGKA() -> k[2] {
  var gka: k  = {
  i:1022,
 o: 102,
  s: "sora"
  
}
var x:k[2] = [gka]

    return x
  }

fun getT()-> t{
  var tt:t = {y:"NO",b:true,ar:[{u:"eeet",g:getGKA()}]}
  return tt
  }

fun getArr()-> t[2] {
var a:t[2] = [{x:2,y:"hello",a:3.3,b:true,ar:[{u:"get",g:getGKA()}]}]
return a
  }

  var arr:t[2] = new [{x:300,y:"eee",a:4.3,b:true,ar:[{g:getGKA()}]}]
print(arr)
print("\n\n")
arr = new [{x:2}]
print(arr)
arr[0].ar[0].g = getGKA()


    )");

  EXPECT_EQ(
      getOutput(),
      R"([{ x : 300, y : 'eee', a : 4.30000000000000, b : true, ar : [{ u : '', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }]

[{ x : 2, y : 'eee', a : 4.30000000000000, b : true, ar : [{ u : '', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }])");
}

TEST_F(Malloc, MallocTestForObjectArrayComplex2) {
  I(R"(
 type obj = {
    i:int,
    s:str
  }
type k = {
  o: int,
  s: str,
  d: deci,
  i: int,
  ob:obj
}
type par = {
  u: str,
  g: k[2]
}
type t = {
  x: int,
  y: str,
  a: deci,
  b: bool,
  ar: par[1]
}
fun getGKA() -> k[2] {
  var gka: k  = {
  i:1022,
 o: 102,
  s: "sora"
  
}
var x:k[2] = [gka]

    return x
  }

fun getT()-> t{
  var tt:t = {y:"NO",b:true,ar:[{u:"eeet",g:getGKA()}]}
  return tt
  }

fun getArr()-> t[2] {
var a:t[2] = [{x:2,y:"hello",a:3.3,b:true,ar:[{u:"get",g:getGKA()}]}]
return a
  }

  var arr:t[2] = new [{x:300,y:"eee",a:4.3,b:true,ar:[{g:getGKA()}]}]
print(arr)
print("\n\n")
arr <- new [{x:2}]
print(arr)
arr[0].ar[0].g = getGKA()


    )");

  EXPECT_EQ(
      getOutput(),
      R"([{ x : 300, y : 'eee', a : 4.30000000000000, b : true, ar : [{ u : '', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }]

[{ x : 2, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }])");
}

TEST_F(Malloc, DefaultInitialize) {
  I(R"(
var x:int 
print(x)
var y:str 
print(y)
var b:bool 
print(b)
var d:deci 
print(d)
var u:int[2]
print(u)
type me = {
    s:str 
  }
type ob ={
    st:str,
    a:int,
    b:bool,
    c:deci,
    j:me,
    ja:me[2]
}
var ua:ob[2]
print(ua)
var uo:ob 
print(uo)


    )");

  EXPECT_EQ(
      getOutput(),
      R"(0false0.00000000000000[0, 0][{ st : '', a : 0, b : false, c : 0.00000000000000, j : { s : '' }, ja : [{ s : '' }, { s : '' }] }, { st : '', a : 0, b : false, c : 0.00000000000000, j : { s : '' }, ja : [{ s : '' }, { s : '' }] }]{ st : '', a : 0, b : false, c : 0.00000000000000, j : { s : '' }, ja : [{ s : '' }, { s : '' }] })");
}

TEST_F(Malloc, DefaultInitializeLocal) {
  I(R"(
{
  var x:int 
print(x)
var y:str 
print(y)
var b:bool 
print(b)
var d:deci 
print(d)
var u:int[2]
print(u)
type me = {
    s:str 
  }
type ob ={
    st:str,
    a:int,
    b:bool,
    c:deci,
    j:me,
    ja:me[2]
}
var ua:ob[2]
print(ua)
var uo:ob 
print(uo)

}

    )");

  EXPECT_EQ(
      getOutput(),
      R"(0false0.00000000000000[0, 0][{ st : '', a : 0, b : false, c : 0.00000000000000, j : { s : '' }, ja : [{ s : '' }, { s : '' }] }, { st : '', a : 0, b : false, c : 0.00000000000000, j : { s : '' }, ja : [{ s : '' }, { s : '' }] }]{ st : '', a : 0, b : false, c : 0.00000000000000, j : { s : '' }, ja : [{ s : '' }, { s : '' }] })");
}
#endif