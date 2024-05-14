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