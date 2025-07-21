#include "ClassesTests.h"

void ClassesTests::SetUp() { _test->SetUp(); }

void ClassesTests::TearDown() { _test->TearDown(); }

TEST_F(ClassesTests, PrintNiceOutsideClass) {
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
  }

  printNice() -> nthg {
      print("Nice")
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
a.printNice()

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
0Nice)");
}

TEST_F(ClassesTests, PrintNiceInsideClassWithSelf) {
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
    self.printNice()
  }

  printNice() -> nthg {
      print("Nice")
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
0Nice)");
}

TEST_F(ClassesTests, PrintNiceInsideClassWithoutSelf) {
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
    printNice()
  }

  printNice() -> nthg {
      print("Nice")
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
0Nice)");
}

TEST_F(ClassesTests, PrintNiceInsideClassFunctionOutsideClass) {
  I(R"(
type X = {
  x1: str,
  x2: int
}
type Complex = {
  a: int[3],
  j: X[2]
}
fun printNice() -> nthg {
    print("Not Nice")
  }

  fun outsidefun()-> nthg {
      print("Outsidefunction")
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
    printNice()
    self.printNice()
    outsidefun()
  }

  printNice() -> nthg {
      print("Nice")
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
a.printNice()
printNice()
outsidefun()

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
0NiceNiceOutsidefunctionNiceNot NiceOutsidefunction)");
}

TEST_F(ClassesTests, PrintNiceInsideClassFunctionOutsideClassInScope) {
  I(R"(
type X = {
  x1: str,
  x2: int
}
type Complex = {
  a: int[3],
  j: X[2]
}
fun printNice() -> nthg {
    print("Not Nice")
  }

  fun outsidefun()-> nthg {
      print("Outsidefunction")
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
    printNice()
    self.printNice()
    outsidefun()
  }

  printNice() -> nthg {
      print("Nice")
    }

}
{
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
a.printNice()
printNice()
outsidefun()
}

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
0NiceNiceOutsidefunctionNiceNot NiceOutsidefunction)");
}

TEST_F(ClassesTests,
       PrintNiceInsideClassFunctionOutsideClassPassingAnotherObjectOfSameType) {
  I(R"(
type X = {
  x1: str,
  x2: int
}
type Complex = {
  a: int[3],
  j: X[2]
}
fun printNice() -> nthg {
    print("Not Nice")
  }

  fun outsidefun()-> nthg {
      print("Outsidefunction")
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
    printNice()
    self.printNice()
    outsidefun()
  }

  printNice() -> nthg {
      print("Nice")
  }

  printBsa(b: A) -> nthg {
   print("\n\n\n")
   b.printAll()
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
a.printNice()
printNice()
outsidefun()
var b:A = new A(5,"e",5.5,{
    x1:"s",
    x2:22
})
a.printBsa(b)
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
0NiceNiceOutsidefunctionNiceNot NiceOutsidefunctioninitCalled


0
2
WAY
{ x1 : 's', x2 : 22 }
22
s
{ a : [0, 0, 0], j : [{ x1 : '', x2 : 0 }, { x1 : '', x2 : 0 }] }
{ a : [1, 1, 0], j : [{ x1 : 'Ge', x2 : 2 }, { x1 : '', x2 : 0 }] }
{ a : [0, 0, 0], j : [{ x1 : '', x2 : 0 }, { x1 : '', x2 : 0 }] }
[0, 0, 0]
0NiceNiceOutsidefunction)");
}

TEST_F(ClassesTests, ReturnClassObjectFromFunction) {
  I(R"(
type T = {
  a:int 
}

class A{
  var obj:T 

  init(obj:T) -> nthg {
    self.obj = obj 
  }
}


fun getA() -> A {
var d:A= new A({a:100})

 d.obj.a = 21
  return d
}
var a:A =  getA()  
a.obj = {a:32}
print(a.obj)
a = getA()
print("After Pass")
print(a.obj)
)");
  EXPECT_EQ(getOutput(), R"({ a : 32 }After Pass{ a : 21 })");
}

TEST_F(ClassesTests, ReturnClassObjectFromFunction2) {
  I(R"(
type T = {
  a:int 
}

class A{
  var obj:T 

  init(obj:T) -> nthg {
    self.obj = obj 
  }
}


fun getA() -> A {
var d:A= new A({a:100})

 d.obj.a = 21
  return d
}
var a:A =  getA()  
a.obj = {a:32}
print(a.obj)
a = getA()
print("After Pass")
print(a.obj)
)");
  EXPECT_EQ(getOutput(), R"({ a : 32 }After Pass{ a : 21 })");
}
TEST_F(ClassesTests, ReturnClassObjectFromFunctionReturining) {
  I(R"(
type T = {
  a:int 
}

class A{
  var obj:T 

  init(obj:T) -> nthg {
    self.obj = obj 
  }
}


fun getA() -> A {
var d:A= new A({a:100})

 d.obj.a = 21
  return d
}

fun getAA() -> A {
  return getA()
}

var a:A =  getAA()  
a.obj = {a:32}
print(a.obj)
a = getA()
print("After Pass")
print(a.obj)
)");
  EXPECT_EQ(getOutput(), R"({ a : 32 }After Pass{ a : 21 })");
}

TEST_F(
    ClassesTests,
    DefaultInitilizerScopeSelfAndFunctionBlockAssignmentAssigningThroughArgsWithUpdateFunction2ComplexInMemberBodyWithOutSelfBeforeAndAfterUpdate) {
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
  init(a: int, b: str, yesD: deci,obj: X) -> nthg {

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
  updateComplex(ar:Complex[2]) -> nthg {
    arr = ar
  }

  printComplex() -> nthg {
    print(self.arr)
  }

}

var a: A  = new A(2, "Hello", 3.3,{x1:"HI",x2:45})
a.printDefaults()
print("\n")
a.updateComplex([{a:[2 fill 5],j:[{x1:"yo",x2:40}]}])
a.printComplex()
)");
  EXPECT_EQ(
      getOutput(),
      R"(initCalled2Hello3.30000000000000false{ x1 : 'HI', x2 : 45 }[{ a : [0, 0, 0], j : [{ x1 : '', x2 : 0 }, { x1 : '', x2 : 0 }] }, { a : [0, 0, 0], j : [{ x1 : '', x2 : 0 }, { x1 : '', x2 : 0 }] }]
[{ a : [5, 5, 0], j : [{ x1 : 'yo', x2 : 40 }, { x1 : '', x2 : 0 }] }, { a : [0, 0, 0], j : [{ x1 : '', x2 : 0 }, { x1 : '', x2 : 0 }] }])");
}

TEST_F(
    ClassesTests,
    DefaultInitilizerScopeSelfAndFunctionBlockAssignmentAssigningThroughArgsWithUpdateFunction2ComplexInMemberBodyWithOutSelfBeforeAndAfterUpdateAccessingOutSideClass) {
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
    print(self.arr )
  }

}
var a: A  = new A(2, "Hello", 3.3, {
  x1: "HI",
  x2: 45
})
a.printDefaults() 
print("\n")
print("Before Update\n")
print(a.arr )
a.updateComplex([{
  a: [2 fill 5],
  j: [{
    x1: "yo",
    x2: 40
  }]
}]) 
print("\nAfter Update\n")
print(a.arr )
print("\nprint nested\n")
print(a.arr[0].a[1] )
print("\n")
print(a.arr[0].j[0].x2 )
print("\n")
a.arr[0].j[1].x1 = "WAY" 
print(a.arr[0].j[1].x1 )
print("\n")
print(a.obj )
print("\n")
print(a.obj.x2 )
print("\n")
print(a.obj.x1 )
print("\n")
print(a.obj2 )
print("\n")
print(a.obj2.a )
print("\n")
print(a.obj2.j[0].x2 ) 
)");
  EXPECT_EQ(
      getOutput(),
      R"(initCalled2Hello3.30000000000000false{ x1 : 'HI', x2 : 45 }[{ a : [0, 0, 0], j : [{ x1 : '', x2 : 0 }, { x1 : '', x2 : 0 }] }, { a : [0, 0, 0], j : [{ x1 : '', x2 : 0 }, { x1 : '', x2 : 0 }] }]
Before Update
[{ a : [0, 0, 0], j : [{ x1 : '', x2 : 0 }, { x1 : '', x2 : 0 }] }, { a : [0, 0, 0], j : [{ x1 : '', x2 : 0 }, { x1 : '', x2 : 0 }] }]
After Update
[{ a : [5, 5, 0], j : [{ x1 : 'yo', x2 : 40 }, { x1 : '', x2 : 0 }] }, { a : [0, 0, 0], j : [{ x1 : '', x2 : 0 }, { x1 : '', x2 : 0 }] }]
print nested
5
40
WAY
{ x1 : 'HI', x2 : 45 }
45
HI
{ a : [0, 0, 0], j : [{ x1 : '', x2 : 0 }, { x1 : '', x2 : 0 }] }
[0, 0, 0]
0)");
}

TEST_F(
    ClassesTests,
    DefaultInitilizerScopeSelfAndFunctionBlockAssignmentAssigningThroughArgsWithUpdateFunction2ComplexInMemberBodyWithOutSelfBeforeAndAfterUpdateAccessingOutSideClassAssignment) {
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
    print(self.arr )
  }

}
var a: A  = new A(2, "Hello", 3.3, {
  x1: "HI",
  x2: 45
})
a.printDefaults() 
print("\n")
print("Before Update\n")
print(a.arr )
a.updateComplex([{
  a: [2 fill 5],
  j: [{
    x1: "yo",
    x2: 40
  }]
}]) 
print("\n")
print(a.arr[0].j[0].x2 )
a.arr[0].j[0].x2 = 2
print("\n")
print(a.arr[0].j[0].x2)
print("\n")
a.arr[0].j[1].x1 = "WAY" 
print(a.arr[0].j[1].x1 )
print("\n")
print(a.obj )
print("\n")
print(a.obj.x2 )
print("\n")
print(a.obj.x1 )
print("\n")
print(a.obj2 )
print("\n")
a.obj2 = {j:[{x2:2,x1:"Ge"}], a:[2 fill 1]}
print(a.obj2)
print("\n")
a.obj2 <- {}
print(a.obj2)
print("\n")
print(a.obj2.a )
print("\n")
print(a.obj2.j[0].x2 ) 
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
0)");
}

TEST_F(
    ClassesTests,
    DefaultInitilizerScopeSelfAndFunctionBlockAssignmentAssigningThroughArgsWithUpdateFunction2ComplexInMemberBodyWithOutSelfBeforeInsideScopeAndAfterUpdateAccessingOutSideClassAssignment) {
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
    print(self.arr )
  }

}
{
var a: A  = new A(2, "Hello", 3.3, {
  x1: "HI",
  x2: 45
})
a.printDefaults() 
print("\n")
print("Before Update\n")
print(a.arr )
a.updateComplex([{
  a: [2 fill 5],
  j: [{
    x1: "yo",
    x2: 40
  }]
}]) 

    print("\n")
print(a.arr[0].j[0].x2 )
a.arr[0].j[0].x2 = 2
print("\n")
print(a.arr[0].j[0].x2)
print("\n")
a.arr[0].j[1].x1 = "WAY" 
print(a.arr[0].j[1].x1 )
print("\n")
print(a.obj )
print("\n")
print(a.obj.x2 )
print("\n")
print(a.obj.x1 )
print("\n")
print(a.obj2 )
print("\n")
a.obj2 = {j:[{x2:2,x1:"Ge"}], a:[2 fill 1]}
print(a.obj2)
print("\n")
a.obj2 <- {}
print(a.obj2)
print("\n")
print(a.obj2.a )
print("\n")
print(a.obj2.j[0].x2 ) 
}
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
0)");
}

TEST_F(
    ClassesTests,
    DefaultInitilizerScopeSelfAndFunctionBlockAssignmentAssigningThroughArgsWithUpdateFunction2ComplexInMemberBodyWithOutSelfBeforeInsideScopeAndAfterUpdatePartialScopeAccessingOutSideClassAssignment) {
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
    print(self.arr )
  }

}
var a: A  = new A(2, "Hello", 3.3, {
  x1: "HI",
  x2: 45
})
a.printDefaults() 
print("\n")
print("Before Update\n")
print(a.arr )
a.updateComplex([{
  a: [2 fill 5],
  j: [{
    x1: "yo",
    x2: 40
  }]
}]) 
{
    print("\n")
print(a.arr[0].j[0].x2 )
a.arr[0].j[0].x2 = 2
print("\n")
print(a.arr[0].j[0].x2)
print("\n")
a.arr[0].j[1].x1 = "WAY" 
print(a.arr[0].j[1].x1 )
print("\n")
print(a.obj )
print("\n")
print(a.obj.x2 )
print("\n")
print(a.obj.x1 )
print("\n")
print(a.obj2 )
print("\n")
a.obj2 = {j:[{x2:2,x1:"Ge"}], a:[2 fill 1]}
print(a.obj2)
print("\n")
a.obj2 <- {}
print(a.obj2)
print("\n")
print(a.obj2.a )
print("\n")
print(a.obj2.j[0].x2 ) 
}
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
0)");
}

TEST_F(ClassesTests, InsideClassPrint) {
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
    print(self.arr[0].j[0].x2)
    arr[0].j[0].x2= 2
    print("\n")
    print(self.arr[0].j[0].x2)
    print("\n")
    arr[0].j[1].x1= "WAY"
    print(self.arr[0].j[1].x1)
    print("\n")
    print(self.obj)
    print("\n")
    print(self.obj.x2)
    print("\n")
    print(self.obj.x1)
    print("\n")
    print(self.obj2)
    print("\n")
    obj2 = {
      j: [{
        x2: 2,
        x1: "Ge"
      }],
      a: [2 fill 1]
    } 
    print(self.obj2)
    print("\n")
    obj2 <- {

    } 
    print(self.obj2)
    print("\n")
    print(self.obj2.a)
    print("\n")
    print(self.obj2.j[0].x2)
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
0)");
}

TEST_F(ClassesTests, InsideClassPrintAssignWithSelf) {
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
    print(self.arr[0].j[0].x2)
    arr[0].j[0].x2= 2
    print("\n")
    print(self.arr[0].j[0].x2)
    print("\n")
    self.arr[0].j[1].x1= "WAY"
    print(self.arr[0].j[1].x1)
    print("\n")
    print(self.obj)
    print("\n")
    print(self.obj.x2)
    print("\n")
    print(self.obj.x1)
    print("\n")
    print(self.obj2)
    print("\n")
    self.obj2 = {
      j: [{
        x2: 2,
        x1: "Ge"
      }],
      a: [2 fill 1]
    } 
    print(self.obj2)
    print("\n")
    obj2 <- {

    } 
    print(self.obj2)
    print("\n")
    print(self.obj2.a)
    print("\n")
    print(self.obj2.j[0].x2)
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
0)");
}

TEST_F(ClassesTests, InsideClassPrintAssignWithOutSelf) {
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
0)");
}

TEST_F(
    ClassesTests,
    DefaultInitilizerScopeSelfAndFunctionBlockAssignmentAssigningThroughArgsWithUpdateFunction2ComplexInMemberBodyWithOutSelf) {
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
  init(a: int, b: str, yesD: deci,obj: X) -> nthg {

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
  updateComplex(ar:Complex[2]) -> nthg {
    arr = ar
  }

  printComplex() -> nthg {
    print(self.arr)
  }

}

var a: A  = new A(2, "Hello", 3.3,{x1:"HI",x2:45})
a.printDefaults()
print("\n")
a.updateComplex([{a:[2 fill 5],j:[{x1:"yo",x2:40}]}])
a.printComplex()
)");
  EXPECT_EQ(
      getOutput(),
      R"(initCalled2Hello3.30000000000000false{ x1 : 'HI', x2 : 45 }[{ a : [0, 0, 0], j : [{ x1 : '', x2 : 0 }, { x1 : '', x2 : 0 }] }, { a : [0, 0, 0], j : [{ x1 : '', x2 : 0 }, { x1 : '', x2 : 0 }] }]
[{ a : [5, 5, 0], j : [{ x1 : 'yo', x2 : 40 }, { x1 : '', x2 : 0 }] }, { a : [0, 0, 0], j : [{ x1 : '', x2 : 0 }, { x1 : '', x2 : 0 }] }])");
}

TEST_F(
    ClassesTests,
    DefaultInitilizerScopeSelfAndFunctionBlockAssignmentAssigningThroughArgsWithUpdateFunction2ComplexInMemberBody) {
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
  init(a: int, b: str, yesD: deci,obj: X) -> nthg {

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
  updateComplex(arr:Complex[2]) -> nthg {
    arr = arr 
  }

  printComplex() -> nthg {
    print(self.arr)
  }

}

var a: A  = new A(2, "Hello", 3.3,{x1:"HI",x2:45})
a.printDefaults()
print("\n")
a.updateComplex([{a:[2 fill 5],j:[{x1:"yo",x2:40}]}])
a.printComplex()
)");
  EXPECT_EQ(
      getOutput(),
      R"(initCalled2Hello3.30000000000000false{ x1 : 'HI', x2 : 45 }[{ a : [0, 0, 0], j : [{ x1 : '', x2 : 0 }, { x1 : '', x2 : 0 }] }, { a : [0, 0, 0], j : [{ x1 : '', x2 : 0 }, { x1 : '', x2 : 0 }] }]
[{ a : [0, 0, 0], j : [{ x1 : '', x2 : 0 }, { x1 : '', x2 : 0 }] }, { a : [0, 0, 0], j : [{ x1 : '', x2 : 0 }, { x1 : '', x2 : 0 }] }])");
}

TEST_F(ClassesTests, DefaultInitilizer) {
  I(R"(
class A {
  var a: int
  var b: str
  var d: deci
  var e: bool
  type X = {
    x1: str,
    x2: int
  }
  var obj: X 
  type Complex = {
    a:int[3],
    j:X[2]
  }
  var arr:X[2] 
  init() -> nthg {
    var obj:X
    print("Pinting u: ")
    print(obj)
  }
  printDefaults()-> nthg {
    print(a)
    print(b)
    print(d)
    print(e)
    print(obj)
    print(arr)
    print(arr)
  }
}
var a: A  = new A() 
a.printDefaults()
)");
  EXPECT_EQ(
      getOutput(),
      "Pinting u: { x1 : '', x2 : 0 }00.00000000000000false{ x1 : '', x2 : 0 "
      "}[{ "
      "x1 : '', x2 : 0 }, { x1 : '', x2 : 0 }][{ x1 : '', x2 : 0 }, { x1 : '', "
      "x2 : 0 }]");
}

TEST_F(ClassesTests, DefaultInitilizerScopeSelfAndFunctionBlock) {
  I(R"(
class A {
  var a: int
  var b: str
  var d: deci
  var e: bool
  type X = {
    x1: str,
    x2: int
  }
  var obj: X 
  type Complex = {
    a:int[3],
    j:X[2]
  }
  var arr:X[2] 
  init(a:int,b:str,yesD:deci) -> nthg {
    var obj:X
    print("Pinting u: ")
    print(obj)
    print(a)
    a = a 
    b = b 
    d = yesD
  }
  printDefaults()-> nthg {
    print(a)
    print(b)
    print(d)
    print(e)
    print(obj)
    print(arr)
    print(arr)
  }
}
var a: A  = new A(2,"Hello",3.3) 
a.printDefaults()
)");
  EXPECT_EQ(
      getOutput(),
      "Pinting u: { x1 : '', x2 : 0 }203.30000000000000false{ x1 : '', x2 : 0 "
      "}[{ x1 : '', x2 : 0 }, { x1 : '', x2 : 0 }][{ x1 : '', x2 : 0 }, { x1 : "
      "'', x2 : 0 }]");
}

TEST_F(ClassesTests, DefaultInitilizerScopeSelfAndFunctionBlockAssignment) {
  I(R"(
class A {
  var a: int
  var b: str
  var d: deci
  var e: bool
  type X = {
    x1: str,
    x2: int
  }
  var obj: X 
  type Complex = {
    a:int[3],
    j:X[2]
  }
  var arr:X[2] 
  init(a:int,b:str,yesD:deci) -> nthg {
    var obj:X
    print("Pinting u: ")
    print(obj)
    print(a)
    self.a = a 
    self.b = b 
    d = yesD
  }
  printDefaults()-> nthg {
    print(a)
    print(b)
    print(d)
    print(e)
    print(obj)
    print(arr)
    print(arr)
  }
}
var a: A  = new A(2,"Hello",3.3) 
a.printDefaults()
)");
  EXPECT_EQ(getOutput(), "Pinting u: { x1 : '', x2 : 0 "
                         "}22Hello3.30000000000000false{ x1 : '', x2 : "
                         "0 }[{ x1 : '', x2 : 0 }, { x1 : '', x2 : 0 }][{ x1 : "
                         "'', x2 : 0 }, { x1 : "
                         "'', x2 : 0 }]");
}

TEST_F(ClassesTests,
       DefaultInitilizerScopeSelfAndFunctionBlockAssignmentOveride) {
  I(R"(
type X = {    
    x1: str,  
    x2: int   
}             
   
class A {
  var a: int
  var b: str
  var d: deci
  var e: bool


type X = { 
    x1: str, 
    x2: int  
}      

  var obj: X 
  type Complex = {
    a: int[3],
    j: X[2]
  }
  var arr: X[2]
  init(a: int, b: str, yesD: deci,obj: X) -> nthg {
    var obj: X 
    print("Pinting u: ")
    print(obj)
    print(a)
    self.a = a 
    self.b = b 
    d = yesD
    self.obj = obj 
  }

  printDefaults() -> nthg {
    print(a)
    print(b)
    print(d)
    print(e)
    print(obj)
    print(arr)
  }

}

var a: A  = new A(2, "Hello", 3.3,{x1:"HI",x2:45})
a.printDefaults()  
)");
  EXPECT_EQ(getOutput(), "Pinting u: { x1 : '', x2 : 0 "
                         "}22Hello3.30000000000000false{ x1 : '', x2 : "
                         "0 }[{ x1 : '', x2 : 0 }, { x1 : '', x2 : 0 }]");
}

TEST_F(
    ClassesTests,
    DefaultInitilizerScopeSelfAndFunctionBlockAssignmentAssigningThroughArgs) {
  I(R"(
type X = {    
    x1: str,  
    x2: int   
}             
   
class A {
  var a: int
  var b: str
  var d: deci
  var e: bool


  var obj: X 
  type Complex = {
    a: int[3],
    j: X[2]
  }
  var arr: X[2]
  init(a: int, b: str, yesD: deci,obj: X) -> nthg {

    print(a)
    self.a = a 
    self.b = b 
    d = yesD
    self.obj = obj 
  }

  printDefaults() -> nthg {
    print(a)
    print(b)
    print(d)
    print(e)
    print(obj)
    print(arr)
  }

}

var a: A  = new A(2, "Hello", 3.3,{x1:"HI",x2:45})
a.printDefaults()  
)");
  EXPECT_EQ(getOutput(), "22Hello3.30000000000000false{ x1 : 'HI', x2 : 45 }[{ "
                         "x1 : '', x2 : 0 }, { "
                         "x1 : '', x2 : 0 }]");
}

TEST_F(
    ClassesTests,
    DefaultInitilizerScopeSelfAndFunctionBlockAssignmentAssigningThroughArgsWithUpdateFunction) {
  I(R"(
type X = {    
    x1: str,  
    x2: int   
}             
   
class A {
  var a: int
  var b: str
  var d: deci
  var e: bool


  var obj: X 
  type Complex = {
    a: int[3],
    j: X[2]
  }
  var arr: X[2]
  init(a: int, b: str, yesD: deci,obj: X) -> nthg {

    print("initCalled")
    self.a = a 
    self.b = b 
    d = yesD
    self.obj = obj 
  }

  updateA() -> nthg {
      a = 100
  }

  printDefaults() -> nthg {
    print(a)
    print(b)
    print(d)
    print(e)
    print(obj)
    print(arr)
  }

}

var a: A  = new A(2, "Hello", 3.3,{x1:"HI",x2:45})
print("BeforeUpdate\n")
a.printDefaults()  
print("AfterUpdate\n")
a.updateA()
a.printDefaults()
)");
  EXPECT_EQ(getOutput(), R"(initCalledBeforeUpdate
2Hello3.30000000000000false{ x1 : 'HI', x2 : 45 }[{ x1 : '', x2 : 0 }, { x1 : '', x2 : 0 }]AfterUpdate
100Hello3.30000000000000false{ x1 : 'HI', x2 : 45 }[{ x1 : '', x2 : 0 }, { x1 : '', x2 : 0 }])");
}

TEST_F(
    ClassesTests,
    DefaultInitilizerScopeSelfAndFunctionBlockAssignmentAssigningThroughArgsWithUpdateFunction2) {
  I(R"(
type X = {    
    x1: str,  
    x2: int   
}             
   
class A {
  var a: int
  var b: str
  var d: deci
  var e: bool


  var obj: X 
  type Complex = {
    a: int[3],
    j: X[2]
  }
  var arr: X[2]
  init(a: int, b: str, yesD: deci,obj: X) -> nthg {

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

}

var a: A  = new A(2, "Hello", 3.3,{x1:"HI",x2:45})
print("BeforeUpdate\n")
a.printDefaults()  
print("AfterUpdate\n")
a.updateA()
a.printDefaults()
)");
  EXPECT_EQ(getOutput(), R"(initCalledBeforeUpdate
2Hello3.30000000000000false{ x1 : 'HI', x2 : 45 }[{ x1 : '', x2 : 0 }, { x1 : '', x2 : 0 }]AfterUpdate
100Nice2.20000000000000false{ x1 : 'HI', x2 : 45 }[{ x1 : '', x2 : 0 }, { x1 : '', x2 : 0 }])");
}

TEST_F(
    ClassesTests,
    DefaultInitilizerScopeSelfAndFunctionBlockAssignmentAssigningThroughArgsWithUpdateFunction2Complex) {
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
  init(a: int, b: str, yesD: deci,obj: X) -> nthg {

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
  updateComplex(arr:Complex[2]) -> nthg {
    self.arr = arr 
  }

  printComplex() -> nthg {
    print(self.arr)
  }

}

var a: A  = new A(2, "Hello", 3.3,{x1:"HI",x2:45})
a.printDefaults()
print("\n")
a.updateComplex([{a:[2 fill 5],j:[{x1:"yo",x2:40}]}])
a.printComplex()
)");
  EXPECT_EQ(
      getOutput(),
      R"(initCalled2Hello3.30000000000000false{ x1 : 'HI', x2 : 45 }[{ a : [0, 0, 0], j : [{ x1 : '', x2 : 0 }, { x1 : '', x2 : 0 }] }, { a : [0, 0, 0], j : [{ x1 : '', x2 : 0 }, { x1 : '', x2 : 0 }] }]
[{ a : [5, 5, 0], j : [{ x1 : 'yo', x2 : 40 }, { x1 : '', x2 : 0 }] }, { a : [0, 0, 0], j : [{ x1 : '', x2 : 0 }, { x1 : '', x2 : 0 }] }])");
}

TEST_F(
    ClassesTests,
    DefaultInitilizerScopeSelfAndFunctionBlockAssignmentAssigningThroughArgsWithUpdateFunction2ComplexOwnMember) {
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
  init(a: int, b: str, yesD: deci,obj: X) -> nthg {

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
  updateComplex(ar:Complex[2]) -> nthg {
    self.arr = arr 
  }

  printComplex() -> nthg {
    print(self.arr)
  }

}

var a: A  = new A(2, "Hello", 3.3,{x1:"HI",x2:45})
a.printDefaults()
print("\n")
a.updateComplex([{a:[2 fill 5],j:[{x1:"yo",x2:40}]}])
a.printComplex()
)");
  EXPECT_EQ(
      getOutput(),
      R"(initCalled2Hello3.30000000000000false{ x1 : 'HI', x2 : 45 }[{ a : [0, 0, 0], j : [{ x1 : '', x2 : 0 }, { x1 : '', x2 : 0 }] }, { a : [0, 0, 0], j : [{ x1 : '', x2 : 0 }, { x1 : '', x2 : 0 }] }]
[{ a : [0, 0, 0], j : [{ x1 : '', x2 : 0 }, { x1 : '', x2 : 0 }] }, { a : [0, 0, 0], j : [{ x1 : '', x2 : 0 }, { x1 : '', x2 : 0 }] }])");
}

TEST_F(ClassesTests, ReturnClassObjectFromFunctionReturiningComplexTwo) {
  I(R"(
type T = {
  a:int 
}

class A{
  var obj:T 

  init(obj:T) -> nthg {
    self.obj = obj 
  }
}


fun getA(d:A) -> A {

 d.obj.a = 21
  return d
}

fun getAA(a:A) -> A {
  return getA(a)
}

var a:A =  getAA(new A({a:22}))  
print(a.obj)
a.obj = {a:32}
print("After Pass")
print(a.obj)
)");
  EXPECT_EQ(getOutput(), R"({ a : 21 }After Pass{ a : 32 })");
}
TEST_F(ClassesTests, ReturnClassObjectFromFunctionReturiningComplexTwo3) {
  I(R"(
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

var a:A =  getAA(new A({a:22}))  
print(a.obj)
a.obj = {a:32}
print("After Pass")
var d:B = new B({j:[{a:2}]})
print(d.getU())
)");
  EXPECT_EQ(getOutput(),
            R"({ a : 21 }After Pass{ j : [{ a : 2 }, { a : 0 }] })");
}
TEST_F(ClassesTests, ReturnClassObjectFromFunctionReturiningComplexTwo3Direct) {
  I(R"(
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

var a:A =  getAA(new A({a:22}))  
print(a.obj)
a.obj = {a:32}
print("After Pass")
print(a.printB( new B({j:[{a:2}]})))
)");
  EXPECT_EQ(getOutput(),
            R"({ a : 21 }After Pass{ j : [{ a : 2 }, { a : 0 }] })");
}
TEST_F(ClassesTests, CreatingObjectFromFunction) {
  I(R"(
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
var a:A =  createA() 
print(a.obj)
a.obj = {a:32}
print("After Pass")
print(a.printB( new B({j:[{a:2}]})))
)");
  EXPECT_EQ(getOutput(),
            R"({ a : 22 }After Pass{ j : [{ a : 2 }, { a : 0 }] })");
}

TEST_F(ClassesTests, CreatingObjectFromFunctionAssignment) {
  I(R"(
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
a.obj = {a:32}
print("After Pass")
print(a.printB(new B({j:[{a:2}]})))
)");
  EXPECT_EQ(
      getOutput(),
      R"({ a : 1 }{ a : 22 }{ a : 322 }After Pass{ j : [{ a : 2 }, { a : 0 }] })");
}
TEST_F(ClassesTests, CreatingObjectFromFunctionAssignmentLocal) {
  I(R"(

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

{
    var a:A = new A({a:1})
print(a.obj)
a = createA()
print(a.obj)
a = new A({a:322})
print(a.obj)
a.obj = {a:32}
print("After Pass")
print(a.printB(new B({j:[{a:2}]})))

  }
)");
  EXPECT_EQ(
      getOutput(),
      R"({ a : 1 }{ a : 22 }{ a : 322 }After Pass{ j : [{ a : 2 }, { a : 0 }] })");
}
TEST_F(ClassesTests, ClassTestBasicInheritanceWithSuper) {
  I(R"(
class C {
  var z:deci 
  var v:str 
  init() -> nthg {
    z  = 22.2
    v ="Hello"
    print("C Constructor is Called\n",z)
    self.z = z+2.2
  }
  init(x:int) -> nthg {
print("Called super",x)
    }
  printW() -> nthg {
    print("world")
  }
}

class B extends C {
  var z:int
  var j:deci
  init() -> nthg  {
    z =1 
    print(j,"B Constructor is Called\n",self.z)
  }

  init(j:str) -> nthg {
      print(j)
    }

  getZ() -> int {
    
    return z
  }
  getS() -> deci {
    return 2.4
  }
}


class A extends B {
  var x: int
  var y: deci
  init() -> nthg {
    super("CalledB")
    print("A Constructor is Called\n",self.z)
    print(v)
  }

  getX() -> int {

    return x
  }

  getZ() -> int {
 
    return z
  }

  getS() -> deci {
    return 45.2
  }

}

var a:A = new A()
print(a.z)

)");
  EXPECT_EQ(getOutput(), R"(C Constructor is Called
22.200000000000000.00000000000000B Constructor is Called
1C Constructor is Called
22.20000000000000CalledBA Constructor is Called
1Hello1)");
}

TEST_F(ClassesTests, ClassTestBasicInheritanceWithSuper2) {
  I(R"(
class C {
  var z:deci 
  var v:str 
  init() -> nthg {
    z  = 22.2
    v ="Hello"
    print("C Constructor is Called\n",z)
    self.z = z+2.2
  }
  init(x:int) -> nthg {
print("Called super",x)
    }
  printW() -> nthg {
    print("world")
  }
}

class B extends C {
  var z:int
  var j:deci
  init() -> nthg  {
    z =1
    super(3)
    print(j,"B Constructor is Called\n",self.z)
  }

  getZ() -> int {
    
    return z
  }
  getS() -> deci {
    return 2.4
  }
}


class A extends B {
  var x: int
  var y: deci
  init() -> nthg {

    print("A Constructor is Called\n",self.z)
    print(v)
  }

  getX() -> int {

    return x
  }

  getZ() -> int {
 
    return z
  }

  getS() -> deci {
    return 45.2
  }

}

var a:A = new A()
print(a.z)
)");
  EXPECT_EQ(getOutput(), R"(C Constructor is Called
22.20000000000000Called super30.00000000000000B Constructor is Called
1A Constructor is Called
1Hello1)");
}

TEST_F(ClassesTests, ClassTestBasicInheritanceWithConstructor) {
  I(R"(
class C {
  var z:deci 
  var v:str 
  init() -> nthg {
    z  = 22.2
    v ="Hello"
    print("C Constructor is Called",z)
    self.z = z+2.2
  }
  init(x:int) -> nthg {
print("Called super",x)
    }
  printW() -> nthg {
    print("world")
  }
}

class B extends C {
  var z:int
  var j:deci
  init() -> nthg  {
    z =1
  
    print(j,"\nB Constructor is Called",self.z)
  }

  getZ() -> int {
    
    return z
  }
  getS() -> deci {
    return 2.4
  }
}


class A extends B {
  var x: int
  var y: deci
  init() -> nthg {

    print("\nA Constructor is Called",self.z)
    print(v)
  }

  getX() -> int {

    return x
  }

  getZ() -> int {
 
    return z
  }

  getS() -> deci {
    return 45.2
  }

}

var a:A = new A()
print(a.z)
)");
  EXPECT_EQ(getOutput(),
            R"(C Constructor is Called22.200000000000000.00000000000000
B Constructor is Called1
A Constructor is Called1Hello1)");
}

TEST_F(ClassesTests, ClassTestBasicInheritanceWithConstructorFunctionCheck) {
  I(R"(
class C {
  var z:deci 
  var v:str 
  init() -> nthg {
    z  = 22.2
    v ="Hello"
    print("C Constructor is Called",z)
    self.z = z+2.2
  }
  init(x:int) -> nthg {
print("Called super",x)
    }
  printW() -> nthg {
    print("world")
  }
}

class B extends C {
  var z:int
  var j:deci
  init() -> nthg  {
    z =1
  
    print(j,"\nB Constructor is Called",self.z)
  }

  printFromB()-> nthg {
    print("Print from B\n")
  }

  getZ() -> int {
    
    return z+2
  }
  getS() -> deci {
    return 2.4
  }
}


class A extends B {
  var x: int
  var y: deci
  init(y:deci ) -> nthg {
    self.y = y
    print("\nA Constructor is Called",self.z)
    print(v)
  }

  getX() -> int {

    return x
  }

  getZ() -> int {
 
    return z
  }

  getS() -> deci {
    return y
  }

}

var a:A = new A(4.4)
print("\n",a.getZ(),"\n",a.getS(),"\n",a.getX(),"\n",a.printFromB(),"\n",a.printW())
)");
  EXPECT_EQ(getOutput(),
            R"(C Constructor is Called22.200000000000000.00000000000000
B Constructor is Called1
A Constructor is Called1Hello
1
4.40000000000000
0
Print from B

world)");
}
TEST_F(ClassesTests,
       ClassTestBasicInheritanceWithConstructorFunctionCheckWithScope) {
  I(R"(
class C {
  var z:deci 
  var v:str 
  init() -> nthg {
    z  = 22.2
    v ="Hello"
    print("C Constructor is Called",z)
    self.z = z+2.2
  }
  init(x:int) -> nthg {
print("Called super",x)
    }
  printW() -> nthg {
    print("world")
  }
}

class B extends C {
  var z:int
  var j:deci
  init() -> nthg  {
    z =1
  
    print(j,"\nB Constructor is Called",self.z)
  }

  printFromB()-> nthg {
    print("Print from B\n")
  }

  getZ() -> int {
    
    return z+2
  }
  getS() -> deci {
    return 2.4
  }
}


class A extends B {
  var x: int
  var y: deci
  init(y:deci ) -> nthg {
    self.y = y
    print("\nA Constructor is Called",self.z)
    print(v)
  }

  getX() -> int {

    return x
  }

  getZ() -> int {
 
    return z
  }

  getS() -> deci {
    return y
  }

}
{

var a:A = new A(4.4)
print("\n",a.getZ(),"\n",a.getS(),"\n",a.getX(),"\n",a.printFromB(),"\n",a.printW())
}
)");
  EXPECT_EQ(getOutput(),
            R"(C Constructor is Called22.200000000000000.00000000000000
B Constructor is Called1
A Constructor is Called1Hello
1
4.40000000000000
0
Print from B

world)");
}
TEST_F(
    ClassesTests,
    ClassTestBasicInheritanceWithConstructorFunctionCheckWithScopeinitilizationBeforeInit) {
  I(R"(
type T = {
    a:int,
    b:deci
  }

class A {
  var x:int = 10
  var a:deci = 22.2
  const u:T = {a:43,b:54.2}
  init(x:int) -> nthg {
    self.x = x
  }

  getTT() -> T {
    var j:T = {a:2}
    return j
  }

  getT(s:str ) -> T {
    print(s)

    return getTT()
  }
}

var a:A = new A(2)

print(a.a)
print(a.x)
print(a.u)
)");
  EXPECT_EQ(getOutput(),
            R"(22.200000000000002{ a : 43, b : 54.20000000000000 })");
}
TEST_F(
    ClassesTests,
    ClassTestBasicInheritanceWithConstructorFunctionCheckWithScopeinitilizationBeforeInitRetrun) {
  I(R"(
type T = {
    a:int 
}
class A {
var i:deci32
var x:int 
var s:str 
var t:T
var g:T[2]
init(s: str) -> nthg{
  self.s = s 
}

getT() -> T {
    return t  
  }

getTA() -> T[2] {
    return g
  }
}

fun printT(t: T) -> nthg {
  print(t)
}
fun printTAr(ta:T[2]) -> nthg {
    print(ta)
  }

var a:A = new A("Hello")

printT(a.getT())
printTAr(a.getTA())
)");
  EXPECT_EQ(getOutput(), R"({ a : 0 }[{ a : 0 }, { a : 0 }])");
}
TEST_F(
    ClassesTests,
    ClassTestBasicInheritanceWithConstructorFunctionCheckWithScopeinitilizationBeforeInitRetrun2) {
  I(R"(

type T = {
    a:int,
    b:str
}
class A {
var i:deci32
var x:int 
var s:str 
var t:T
var g:T[2]
init(s: str) -> nthg{
  self.s = s 
}

getT(b:str) -> T {
   t.b = b
   return t  
  }

getTA(b:str ) -> T[2] {
  g[0].b =b 
    return g
  }
}

fun printT(t: T) -> nthg {
  print(t)
}
fun printTAr(ta:T[2]) -> nthg {
    print(ta)
  }

var a:A = new A("Hello")

printT(a.getT("IH"))
printTAr(a.getTA("Hi"))
)");
  EXPECT_EQ(getOutput(),
            R"({ a : 0, b : 'IH' }[{ a : 0, b : 'Hi' }, { a : 0, b : '' }])");
}
TEST_F(
    ClassesTests,
    ClassTestBasicInheritanceWithConstructorFunctionCheckWithScopeinitilizationBeforeInitRetrun3) {
  I(R"(
 type T  = {
      x:int,
      d:str 
    }
class Animal {
  var age:int 
  var species:str


  var t:T 
  init(age:int) -> nthg {
    self.age = age
    self.t = {d:"Hi",x:12}
  }
  getAge() -> int {
    return self.age
  }
  printSpecies() -> nthg { 
    print("Species: ",species)
  }
}
class Dog extends Animal {
   var breed:str 
  
  init(age:int) -> nthg {
    super(age)
  }

  getAge() ->int {
    return 7*self.age  
  }
  printBreed() -> nthg { 
    print("breed "+breed)
  }


  getT() -> T {
      return self.t
    }
}
fun printAge(a: Animal) ->nthg{
 print("I'm "+a.getAge()+" years old!\n")
}
fun main2() -> nthg {
  var animal:Animal = new Animal(2)
  var  dog:Dog = new Dog(2)
var x:int = dog.getAge()
print("x ",x)
print(dog.getT())
print(dog.getAge())
print(animal.getAge())
printAge(animal) 
 printAge(dog) 
}
main2()

)");
  EXPECT_EQ(getOutput(), R"(x 14{ x : 12, d : 'Hi' }142I'm 2 years old!
I'm 14 years old!
)");
}
TEST_F(
    ClassesTests,
    ClassTestBasicInheritanceWithConstructorFunctionCheckWithScopeinitilizationBeforeInitRetrun4) {
  I(R"(
   type T = {
    a:int,
    b:str
}
class A {
var s:str 
var k:T
var x:int
init(s: str) -> nthg{
  self.s = s 
}
  getHell() -> str {
      return "Hell"
    }
  setHell(s:str) -> nthg {
    
      print(s)
    }


      getC() -> int {
      return  3
    }
  setC(i:int) -> nthg{
    
      print(i)
    }
      getT() -> T {
        var x:T = {b:"hel"}
      return x 
    }
  setT(i:T) -> nthg{
    
      print(i)
    }

   getX(x:int ) -> int  {
      return x 
    } 

   getXX() -> int  {
      return 3 
    }

    setX(x:int ) -> nthg {
        self.x = x
      print("x: ",x)
      }

      getXXX(x:int) -> int {
          return x
        }
}



var a:A = new A("Hello")

a.setC(a.getC())
print(a.getC())
a.setHell(a.getHell())
print(a.getHell())
a.setT(a.getT())
print(a.getT())
print(a.getX(a.getXX()))
a.setX(a.getX(a.getXX()))
a.setX(a.getX(a.getXXX(5))) 
)");
  EXPECT_EQ(getOutput(),
            R"(33HellHell{ a : 0, b : 'hel' }{ a : 0, b : 'hel' }3x: 3x: 5)");
}

TEST_F(
    ClassesTests,
    ClassTestBasicInheritanceWithConstructorFunctionCheckWithScopeinitilizationBeforeInitRetrun4LocalandGlobal) {
  I(R"(
    type T = {
    a:int,
    b:str
}
class A {
var s:str 
var k:T
var x:int
init(s: str) -> nthg{
  self.s = s 
}
  getHell() -> str {
      return "Hell"
    }
  setHell(s:str) -> nthg {
    
  print(s)
    }


      getC() -> int {
      return  3
    }
  setC(i:int) -> nthg{
    
   print(i)
    }
      getT() -> T {
        var x:T = {b:"hel"}
      return x 
    }
  setT(i:T) -> nthg{
    
     print(i)
    }

   getX(x:int ) -> int  {
      return x 
    } 

   getXX() -> int  {
      return 3 
    }

    setX(x:int ) -> nthg {
        self.x = x
      print("x: ",x)
      }

      getXXX(x:int) -> int {
          return x
        }
}



var a:A = new A("Hello")

fun main2() -> int {

   print(a.s) 
    return 0 
  }

  main2()
)");
  EXPECT_EQ(getOutput(), R"(Hello)");
}
TEST_F(
    ClassesTests,
    ClassTestBasicInheritanceWithConstructorFunctionCheckWithScopeinitilizationBeforeInitRetrun4LocalandGlobal2) {
  I(R"(
  class A{
    var x:int 

    init() -> nthg {
         x = 3 
    }

    getX()->int {
        return x
      }

  }

var a:A = new A() 

fun getX() -> int {
    return a.x 
  }


{
if(true){
    var x:int 
}
var x:int 
print(getX())
}
)");
  EXPECT_EQ(getOutput(), R"(3)");
}
TEST_F(ClassesTests, ClassInitTest) {
  I(R"(
class A {
  var x:int 
  var b:str 
  init(x:int,b: str = "Hello" ) -> nthg {
      self.x = x
      print("init B ",x,b)
      self.b = b 
  }
  init(x:int) -> nthg {
      self.x = x
  }
  test(a:int,k:deci = 3.3 ) -> nthg {
    print("a: "+a)
    print("\nb: "+b)
    print("\nx: "+self.x)
    print("\nk: "+k)
  }
  
}

var a:A = new A(10,"Nice")


a.test(2,5.3)
)");
  EXPECT_EQ(getOutput(), R"(init B 10Nicea: 2
b: Nice
x: 10
k: 5.30000000000000)");
}
TEST_F(ClassesTests, ClassInitTest2) {
  I(R"(
class A {
  var x:int 
  var b:str 
  init(x:int,b: str = "Hello" ) -> nthg {
      self.x = x
      print("init B ",x,b)
      self.b = b 
  }
  init(x:int) -> nthg {
      self.x = x
      self.b = "He"
  }
  test(a:int,k:deci = 3.3 ) -> nthg {
    print("a: "+a)
    print("\nb: "+b)
    print("\nx: "+self.x)
    print("\nk: "+k)
  }
  
}

var a:A = new A(10)


a.test(2,5.3)
)");
  EXPECT_EQ(getOutput(), R"(a: 2
b: He
x: 10
k: 5.30000000000000)");
}
TEST_F(ClassesTests, ClassInitTest3) {
  I(R"(
class A {
  var x:int 
  var b:str 
  init(x:int,b: str = "Hello" ) -> nthg {
      self.x = x
      print("init B ",x,b)
      self.b = b 
  }
  init(x:int) -> nthg {
      self.x = x
      self.b = "He"
  }
  test(a:int,k:deci = 3.3 ) -> nthg {
    print("a: "+a)
    print("\nb: "+b)
    print("\nx: "+self.x)
    print("\nk: "+k)
  }
  
}

var a:A = new A(10)


a.test(2)
)");
  EXPECT_EQ(getOutput(), R"(a: 2
b: He
x: 10
k: 3.30000000000000)");
}

TEST_F(ClassesTests, ClassInitTest4WithMultiRetrun) {
  I(R"(
class A {
  var x:int 
  var b:str 
  init(x:int,b: str = "Hello" ) -> nthg {
      self.x = x
      print("init B ",x,b)
      self.b = b 
  }
  init(x:int) -> nthg {
      self.x = x
      self.b = "He"
  }
  test(a:int,b:int = 4,k:str ="Hello" ) -> int,deci  {
    print("a: "+a)
   print("\nb: "+b)
    print("\nx: "+self.x)
    print("\nk: "+k)

    return 23,35.5
  } 
}

var a:A = new A(10)
var b:int,c:deci = a.test(2)
print(b,c)
)");
  EXPECT_EQ(getOutput(), R"(a: 2
b: 4
x: 10
k: Hello2335.50000000000000)");
}
TEST_F(ClassesTests, ClassInitTest4WithMultiRetrunAssignment) {
  I(R"(
class A {
  var x:int 
  var b:str 
  init(x:int,b: str = "Hello" ) -> nthg {
      self.x = x
      print("init B ",x,b)
      self.b = b 
  }
  init(x:int) -> nthg {
      self.x = x
      self.b = "He"
  }
  test(a:int,b:int = 4,k:str ="Hello" ) -> int,deci  {
    print("a: "+a)
   print("\nb: "+b)
    print("\nx: "+self.x)
    print("\nk: "+k)

    return 23,35.5
  } 
}

var a:A = new A(10)
var b:int,c:deci 


b,c =a.test(2)
print(b,c)
)");
  EXPECT_EQ(getOutput(), R"(a: 2
b: 4
x: 10
k: Hello2335.50000000000000)");
}
TEST_F(ClassesTests, ClassInitTest4WithMultiRetrunAssignment2) {
  I(R"(
class A {
  var x:int 
  var b:str 
  init(x:int,b: str = "Hello" ) -> nthg {
      self.x = x
      print("init B ",x,b)
      self.b = b 
  }
  init(x:int) -> nthg {
      self.x = x
      self.b = "He"
  }
  test(a:int,b:int = 4,k:str ="Hello" ) -> int,deci  {
    print("a: "+a)
   print("\nb: "+b)
    print("\nx: "+self.x)
    print("\nk: "+k)

    return 23,35.5
  } 
}

var a:A = new A(10)
var b:int,c:deci 


b,c =a.test(2,53)
print(b,c)
)");
  EXPECT_EQ(getOutput(), R"(a: 2
b: 53
x: 10
k: Hello2335.50000000000000)");
}

TEST_F(ClassesTests, ClassInitTest4WithMultiRetrunAssignmentClassItSelf) {
  I(R"(
class B {
    init()->nthg {

      }
  }
class A {

  var x:int 
  init(x:int )-> nthg {
    self.x = x
  }
  
  getA() -> A {
    return new A(12)    
  }

  getB() -> B {
      return new B()
    }

}

var a:A = new A(11)
var b:A = a.getA()

var ba:B = a.getB()
print(a.x)
print(b.x)
)");
  EXPECT_EQ(getOutput(), R"(1112)");
}
TEST_F(ClassesTests, ClassInitTest4WithMultiRetrunAssignmentClassItSelf2) {
  I(R"(

class B {
    init()->nthg {

      }
  }
class A {

  var x:int
  var y:deci 
  init(x:int )-> nthg {
    self.x = x
  }
  
  getAS() -> A {

    self.x = 12
    return self 
  }
  getA() -> A {
    x =32

    return self 
  }
  printX() -> nthg {
    print("Y: ",y)
  }

  getB() -> B {
      return new B()
    }

}

var a:A = new A(11)
print(a.x)

var b:A = a.getA()

print(b.x)
a.getAS()
print(a.x)
print(b.x)
)");
  EXPECT_EQ(getOutput(), R"(11321212)");
}

TEST_F(ClassesTests, ClassEqualityOperator) {
  I(R"(
class A {
  var x:int 
  init(x:int) -> nthg {
      self.x = x 
    }
}

var a:A = new A(2)
var b:A = new A(2)
var aRef:A = a
if(a) {
  print("Class A","\n")
}

if(a && true) {
  print("Class A and true","\n")
}

if(a && false) {
  print("Class A and false","\n")
}

if(a || true) {
  print("Class A or true","\n")
}

if(a || false) {
  print("Class A or false","\n")
}

if(a == a){
  print("Class A == A","\n")
}

if(a != a){
  print("Class A != A","\n")
}


if(a == b){
  print("Class A == B","\n")
}

if(a != b){
  print("Class A != B","\n")
}

if(a == aRef){
  print("Class A == ARef","\n")
}

if(a != aRef){
  print("Class A != ARef","\n")
}

)");
  EXPECT_EQ(getOutput(), R"(Class A
Class A and true
Class A or true
Class A or false
Class A == A
Class A != B
Class A == ARef
)");
}

TEST_F(ClassesTests, LogicalNotForClass) {
  I(R"(
class A {
  var x:int 
  init(x:int) -> nthg {
      self.x = x 
    }
}

var a:A = new A(2)

if(!a){
  print("A")
}or if(a){
    print("or A")
  }
)");

  EXPECT_EQ(getOutput(), R"(or A)");
}