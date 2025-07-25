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


#include "ClassPrintTest.h"

void ClassPrintTest::SetUp() { _test->SetUp(); }

void ClassPrintTest::TearDown() { _test->TearDown(); }
TEST_F(ClassPrintTest, InsideClassPrintAssignWithOutSelfFunctionCall) {
  I(R"(
type X = {
  x1: str,
  x2: int
}
type Complex = {
  a: int[3],
  j: X[2]
}
class A {
  var a: int
  var b: str
  var d: deci
  var e: bool
  var obj: X 
  var arr: Complex[2]
  var obj2: Complex 
  init(a: int, b: str, yesD: deci, obj: X ) -> nthg {
    print("initCalled")
    self.a = a 
    self.b = b 
    d = yesD 
    self.obj = obj 
  }

  updateA() -> nthg {
    a = 100 
    self.d = 2.2 
    b = "Nice" 
  }

  printDefaults() -> nthg {
    print(a)
    print(b)
    print(d)
    print(e)
    print(obj)
    print(arr)
  }

  updateComplex(ar: Complex[2]) -> nthg {
    arr = ar 
  }

  printComplex() -> nthg {
    print(self.arr)
  }

  printAll() -> nthg {
    print(arr[0].j[0].x2)
    arr[0].j[0].x2= 2
    print("\n")
    print(arr[0].j[0].x2)
    print("\n")
    arr[0].j[1].x1= "WAY"
    print(arr[0].j[1].x1)
    print("\n")
    print(obj)
    print("\n")
    print(obj.x2)
    print("\n")
    print(obj.x1)
    print("\n")
    print(obj2)
    print("\n")
    obj2 = {
      j: [{
        x2: 2,
        x1: "Ge"
      }],
      a: [2 fill 1]
    } 
    print(obj2)
    print("\n")
    obj2 <- {

    } 
    print(obj2)
    print("\n")
    print(obj2.a)
    print("\n")
    print(obj2.j[0].x2)
    printComplex()
  }

}
var a: A  = new A(2, "Hello", 3.3, {
  x1: "HI",
  x2: 45
})
a.printDefaults()
print("\n")
print("Before Update\n")
print(a.arr)
a.updateComplex([{
  a: [2 fill 5],
  j: [{
    x1: "yo",
    x2: 40
  }]
}])
print("\n")
a.printAll() 
)");
  EXPECT_EQ(
      getOutput(),
      R"(initCalled2Hello3.30000000000000false{ x1 : 'HI', x2 : 45 }[{ a : [0, 0, 0], j : [{ x1 : '', x2 : 0 }, { x1 : '', x2 : 0 }] }, { a : [0, 0, 0], j : [{ x1 : '', x2 : 0 }, { x1 : '', x2 : 0 }] }]
Before Update
[{ a : [0, 0, 0], j : [{ x1 : '', x2 : 0 }, { x1 : '', x2 : 0 }] }, { a : [0, 0, 0], j : [{ x1 : '', x2 : 0 }, { x1 : '', x2 : 0 }] }]
40
2
WAY
{ x1 : 'HI', x2 : 45 }
45
HI
{ a : [0, 0, 0], j : [{ x1 : '', x2 : 0 }, { x1 : '', x2 : 0 }] }
{ a : [1, 1, 0], j : [{ x1 : 'Ge', x2 : 2 }, { x1 : '', x2 : 0 }] }
{ a : [0, 0, 0], j : [{ x1 : '', x2 : 0 }, { x1 : '', x2 : 0 }] }
[0, 0, 0]
0[{ a : [5, 5, 0], j : [{ x1 : 'yo', x2 : 2 }, { x1 : 'WAY', x2 : 0 }] }, { a : [0, 0, 0], j : [{ x1 : '', x2 : 0 }, { x1 : '', x2 : 0 }] }])");
}

TEST_F(ClassPrintTest, CreatingObjectFromFunctionAssignmentLocalVaradicPrint) {
  I(R"(
print(1,2,3,"ssdweqdfwe")

type T = {
  a:int 
}

type K = {
  j:T[2]
}

class B {
  var u:K

  init(u:K) -> nthg {
    self.u = u
  }

  getU() -> K {
    return u
  }
}

class A{
  var obj:T 

  init(obj:T) -> nthg {
    self.obj = obj 
  }

  printB(b:B) -> nthg {
    print(b.getU())
  }
}


fun getA(d:A) -> A {
 d.obj.a = 21
  return d
}
fun getAA(a:A) -> A {
  return getA(a)
}
fun createA() -> A {
  return new A({a:22})
}

    var a:A = new A({a:1})
print(a.obj)
a = createA()
print(a.obj)
a = new A({a:322})
print(a.obj)
a.printB(new B({j:[]}))
a.obj = {a:32}
print("After Pass")
a.printB(new B({j:[{a:2}]}))
)");
  EXPECT_EQ(
      getOutput(),
      R"(123ssdweqdfwe{ a : 1 }{ a : 22 }{ a : 322 }{ j : [{ a : 0 }, { a : 0 }] }After Pass{ j : [{ a : 2 }, { a : 0 }] })");
}
