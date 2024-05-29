#include "ClassesTests.h"

ClassesTests::ClassesTests() { _test = std::move(FlowWing::getTest()); }

void ClassesTests::SetUp() { _test->SetUp(); }

void ClassesTests::TearDown() { _test->TearDown(); }

void ClassesTests::setInput(const std::string &input) {
  _test->setInput(input);
}

std::string ClassesTests::getOutput() const { return _test->getOutput(); }

void ClassesTests::runEvaluator() { _test->runEvaluator(); }

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
  O("Pinting u: { x1 : '', x2 : 0 }00.00000000000000false{ x1 : '', x2 : 0 }[{ "
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
  O("Pinting u: { x1 : '', x2 : 0 }203.30000000000000false{ x1 : '', x2 : 0 "
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
  O("Pinting u: { x1 : '', x2 : 0 }22Hello3.30000000000000false{ x1 : '', x2 : "
    "0 }[{ x1 : '', x2 : 0 }, { x1 : '', x2 : 0 }][{ x1 : '', x2 : 0 }, { x1 : "
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
  O("Pinting u: { x1 : '', x2 : 0 }22Hello3.30000000000000false{ x1 : '', x2 : "
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
  O("22Hello3.30000000000000false{ x1 : 'HI', x2 : 45 }[{ x1 : '', x2 : 0 }, { "
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
  O(R"(initCalledBeforeUpdate
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
  O(R"(initCalledBeforeUpdate
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
  O(R"(initCalled2Hello3.30000000000000false{ x1 : 'HI', x2 : 45 }[{ a : [0, 0, 0], j : [{ x1 : '', x2 : 0 }, { x1 : '', x2 : 0 }] }, { a : [0, 0, 0], j : [{ x1 : '', x2 : 0 }, { x1 : '', x2 : 0 }] }]
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
  O(R"(initCalled2Hello3.30000000000000false{ x1 : 'HI', x2 : 45 }[{ a : [0, 0, 0], j : [{ x1 : '', x2 : 0 }, { x1 : '', x2 : 0 }] }, { a : [0, 0, 0], j : [{ x1 : '', x2 : 0 }, { x1 : '', x2 : 0 }] }]
[{ a : [0, 0, 0], j : [{ x1 : '', x2 : 0 }, { x1 : '', x2 : 0 }] }, { a : [0, 0, 0], j : [{ x1 : '', x2 : 0 }, { x1 : '', x2 : 0 }] }])");
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
  O(R"(initCalled2Hello3.30000000000000false{ x1 : 'HI', x2 : 45 }[{ a : [0, 0, 0], j : [{ x1 : '', x2 : 0 }, { x1 : '', x2 : 0 }] }, { a : [0, 0, 0], j : [{ x1 : '', x2 : 0 }, { x1 : '', x2 : 0 }] }]
[{ a : [0, 0, 0], j : [{ x1 : '', x2 : 0 }, { x1 : '', x2 : 0 }] }, { a : [0, 0, 0], j : [{ x1 : '', x2 : 0 }, { x1 : '', x2 : 0 }] }])");
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
  O(R"(initCalled2Hello3.30000000000000false{ x1 : 'HI', x2 : 45 }[{ a : [0, 0, 0], j : [{ x1 : '', x2 : 0 }, { x1 : '', x2 : 0 }] }, { a : [0, 0, 0], j : [{ x1 : '', x2 : 0 }, { x1 : '', x2 : 0 }] }]
[{ a : [5, 5, 0], j : [{ x1 : 'yo', x2 : 40 }, { x1 : '', x2 : 0 }] }, { a : [0, 0, 0], j : [{ x1 : '', x2 : 0 }, { x1 : '', x2 : 0 }] }])");
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
  O(R"(initCalled2Hello3.30000000000000false{ x1 : 'HI', x2 : 45 }[{ a : [0, 0, 0], j : [{ x1 : '', x2 : 0 }, { x1 : '', x2 : 0 }] }, { a : [0, 0, 0], j : [{ x1 : '', x2 : 0 }, { x1 : '', x2 : 0 }] }]
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
  O(R"(initCalled2Hello3.30000000000000false{ x1 : 'HI', x2 : 45 }[{ a : [0, 0, 0], j : [{ x1 : '', x2 : 0 }, { x1 : '', x2 : 0 }] }, { a : [0, 0, 0], j : [{ x1 : '', x2 : 0 }, { x1 : '', x2 : 0 }] }]
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
  O(R"(initCalled2Hello3.30000000000000false{ x1 : 'HI', x2 : 45 }[{ a : [0, 0, 0], j : [{ x1 : '', x2 : 0 }, { x1 : '', x2 : 0 }] }, { a : [0, 0, 0], j : [{ x1 : '', x2 : 0 }, { x1 : '', x2 : 0 }] }]
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
  O(R"(initCalled2Hello3.30000000000000false{ x1 : 'HI', x2 : 45 }[{ a : [0, 0, 0], j : [{ x1 : '', x2 : 0 }, { x1 : '', x2 : 0 }] }, { a : [0, 0, 0], j : [{ x1 : '', x2 : 0 }, { x1 : '', x2 : 0 }] }]
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
  O(R"(initCalled2Hello3.30000000000000false{ x1 : 'HI', x2 : 45 }[{ a : [0, 0, 0], j : [{ x1 : '', x2 : 0 }, { x1 : '', x2 : 0 }] }, { a : [0, 0, 0], j : [{ x1 : '', x2 : 0 }, { x1 : '', x2 : 0 }] }]
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
  O(R"(initCalled2Hello3.30000000000000false{ x1 : 'HI', x2 : 45 }[{ a : [0, 0, 0], j : [{ x1 : '', x2 : 0 }, { x1 : '', x2 : 0 }] }, { a : [0, 0, 0], j : [{ x1 : '', x2 : 0 }, { x1 : '', x2 : 0 }] }]
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
  O(R"(initCalled2Hello3.30000000000000false{ x1 : 'HI', x2 : 45 }[{ a : [0, 0, 0], j : [{ x1 : '', x2 : 0 }, { x1 : '', x2 : 0 }] }, { a : [0, 0, 0], j : [{ x1 : '', x2 : 0 }, { x1 : '', x2 : 0 }] }]
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
  O(R"(initCalled2Hello3.30000000000000false{ x1 : 'HI', x2 : 45 }[{ a : [0, 0, 0], j : [{ x1 : '', x2 : 0 }, { x1 : '', x2 : 0 }] }, { a : [0, 0, 0], j : [{ x1 : '', x2 : 0 }, { x1 : '', x2 : 0 }] }]
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

TEST_F(ClassesTests, InsideClassPrintAssignWithOutSelfFunctionCall) {
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
  O(R"(initCalled2Hello3.30000000000000false{ x1 : 'HI', x2 : 45 }[{ a : [0, 0, 0], j : [{ x1 : '', x2 : 0 }, { x1 : '', x2 : 0 }] }, { a : [0, 0, 0], j : [{ x1 : '', x2 : 0 }, { x1 : '', x2 : 0 }] }]
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
  O(R"(initCalled2Hello3.30000000000000false{ x1 : 'HI', x2 : 45 }[{ a : [0, 0, 0], j : [{ x1 : '', x2 : 0 }, { x1 : '', x2 : 0 }] }, { a : [0, 0, 0], j : [{ x1 : '', x2 : 0 }, { x1 : '', x2 : 0 }] }]
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
  O(R"(initCalled2Hello3.30000000000000false{ x1 : 'HI', x2 : 45 }[{ a : [0, 0, 0], j : [{ x1 : '', x2 : 0 }, { x1 : '', x2 : 0 }] }, { a : [0, 0, 0], j : [{ x1 : '', x2 : 0 }, { x1 : '', x2 : 0 }] }]
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
  O(R"(initCalled2Hello3.30000000000000false{ x1 : 'HI', x2 : 45 }[{ a : [0, 0, 0], j : [{ x1 : '', x2 : 0 }, { x1 : '', x2 : 0 }] }, { a : [0, 0, 0], j : [{ x1 : '', x2 : 0 }, { x1 : '', x2 : 0 }] }]
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
  O(R"(initCalled2Hello3.30000000000000false{ x1 : 'HI', x2 : 45 }[{ a : [0, 0, 0], j : [{ x1 : '', x2 : 0 }, { x1 : '', x2 : 0 }] }, { a : [0, 0, 0], j : [{ x1 : '', x2 : 0 }, { x1 : '', x2 : 0 }] }]
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
  O(R"(initCalled2Hello3.30000000000000false{ x1 : 'HI', x2 : 45 }[{ a : [0, 0, 0], j : [{ x1 : '', x2 : 0 }, { x1 : '', x2 : 0 }] }, { a : [0, 0, 0], j : [{ x1 : '', x2 : 0 }, { x1 : '', x2 : 0 }] }]
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
  O(R"(initCalled2Hello3.30000000000000false{ x1 : 'HI', x2 : 45 }[{ a : [0, 0, 0], j : [{ x1 : '', x2 : 0 }, { x1 : '', x2 : 0 }] }, { a : [0, 0, 0], j : [{ x1 : '', x2 : 0 }, { x1 : '', x2 : 0 }] }]
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
  O(R"({ a : 32 }After Pass{ a : 21 })");
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
  O(R"({ a : 32 }After Pass{ a : 21 })");
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
  O(R"({ a : 32 }After Pass{ a : 21 })");
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
  O(R"({ a : 21 }After Pass{ a : 32 })");
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
  O(R"({ a : 21 }After Pass{ j : [{ a : 2 }, { a : 0 }] })");
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
  O(R"({ a : 21 }After Pass{ j : [{ a : 2 }, { a : 0 }] })");
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
  O(R"({ a : 22 }After Pass{ j : [{ a : 2 }, { a : 0 }] })");
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
  O(R"({ a : 1 }{ a : 22 }{ a : 322 }After Pass{ j : [{ a : 2 }, { a : 0 }] })");
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
  O(R"({ a : 1 }{ a : 22 }{ a : 322 }After Pass{ j : [{ a : 2 }, { a : 0 }] })");
}
TEST_F(ClassesTests, CreatingObjectFromFunctionAssignmentLocalVaradicPrint) {
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
print(a.obj,a.printB(new B({j:[]})))
a.obj = {a:32}
print("After Pass")
print(a.printB(new B({j:[{a:2}]})))
)");
  O(R"(123ssdweqdfwe{ a : 1 }{ a : 22 }{ a : 322 }{ j : [{ a : 0 }, { a : 0 }] }After Pass{ j : [{ a : 2 }, { a : 0 }] })");
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
    super()
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
  O(R"(C Constructor is Called
22.200000000000000.00000000000000B Constructor is Called
10.00000000000000B Constructor is Called
1A Constructor is Called
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
  O(R"(C Constructor is Called
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
  O(R"(C Constructor is Called22.200000000000000.00000000000000
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
  O(R"(C Constructor is Called22.200000000000000.00000000000000
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
  O(R"(C Constructor is Called22.200000000000000.00000000000000
B Constructor is Called1
A Constructor is Called1Hello
1
4.40000000000000
0
Print from B

world)");
}