#include "InheritanceTest.h"

InheritanceTest::InheritanceTest() { _test = std::move(FlowWing::getTest()); }

void InheritanceTest::SetUp() { _test->SetUp(); }

void InheritanceTest::TearDown() { _test->TearDown(); }

void InheritanceTest::setInput(const std::string &input) {
  _test->setInput(input);
}

std::string InheritanceTest::getOutput() const { return _test->getOutput(); }

void InheritanceTest::runEvaluator() { _test->runEvaluator(); }

TEST_F(InheritanceTest, Basic) {
  I(R"(
 type T2 = {
   d:deci 
  }

 type T1 = {
    a:int,
    b:str,
    c:T2,
    d:T2[2]
  }
class A {
type T3A = {
  u:str,
}

 var x:T1 
 var a:T3A
  init(x:T1) -> nthg {
    self.x = x
    a = {u:"Nice"}
  }
  

  printX() -> nthg {
    print(self.x)
  }
}

class B extends A  {
  init(y:T1) -> nthg {
    super(y)
  }
}

var a:A = new A({a:2})
a.printX()
)");
  O(R"({ a : 2, b : '', c : { d : 0.00000000000000 }, d : [{ d : 0.00000000000000 }, { d : 0.00000000000000 }] })");
}
TEST_F(InheritanceTest, BasicWithObjectOfBWithOutSuper) {
  I(R"(
 type T2 = {
   d:deci 
  }

 type T1 = {
    a:int,
    b:str,
    c:T2,
    d:T2[2]
  }
class A {
type T3A = {
  u:str,
}

 var x:T1 
 var a:T3A
  init(x:T1) -> nthg {
    self.x = x
    a = {u:"Nice"}
  }
  

  printX() -> nthg {
    print(self.x)
  }
}

class B extends A  {
  init(y:T1) -> nthg {
  }
}

var b:B = new B({a:2})
b.printX()
)");
  O(R"({{ a : 0, b : '', c : { d : 0.00000000000000 }, d : [{ d : 0.00000000000000 }, { d : 0.00000000000000 }] })");
}
TEST_F(InheritanceTest, BasicWithObjectOfBWithSuper) {
  I(R"(
 type T2 = {
   d:deci 
  }

 type T1 = {
    a:int,
    b:str,
    c:T2,
    d:T2[2]
  }
class A {
type T3A = {
  u:str,
}

 var x:T1 
 var a:T3A
  init(x:T1) -> nthg {
    self.x = x
    a = {u:"Nice"}
  }
  

  printX() -> nthg {
    print(self.x)
  }
}

class B extends A  {
  init(y:T1) -> nthg {
    super(y)
  }
}

var b:B = new B({a:2})
b.printX()
)");
  O(R"({ a : 2, b : '', c : { d : 0.00000000000000 }, d : [{ d : 0.00000000000000 }, { d : 0.00000000000000 }] })");
}
TEST_F(InheritanceTest,
       BasicWithObjectOfBWithSuperBaseClassRefAndChildClassObj) {
  I(R"(

 type T2 = {
   d:deci 
  }

 type T1 = {
    a:int,
    b:str,
    c:T2,
    d:T2[2]
  }
class A {
type T3A = {
  u:str,
}

 var x:T1 
 var a:T3A
  init(x:T1) -> nthg {
    self.x = x
    a = {u:"Nice"}
  }
  

  printX() -> nthg {
    print(self.x)
  }
}

class B extends A  {
  init(y:T1) -> nthg {
    super(y)
  }

  printX()-> nthg {
      print("Not printing it ")
    }
}

var b:A = new B({a:2})
b.printX()
)");
  O(R"(Not printing it )");
}
TEST_F(InheritanceTest,
       BasicWithObjectOfBWithSuperBaseClassRefAndChildClassObj2) {
  I(R"(

 type T2 = {
   d:deci 
  }

 type T1 = {
    a:int,
    b:str,
    c:T2,
    d:T2[2]
  }
class A {
type T3A = {
  u:str,
}

 var x:T1 
 var a:T3A
  init(x:T1) -> nthg {
    self.x = x
    a = {u:"Nice"}
  }
  

  printX() -> nthg {
    print(self.x)
  }
}

class B extends A  {

var a:deci
var j:int
var s:str
var k:deci
var u:int

init(y:T1) -> nthg {

super(y)
j = 2
a = 2.2
s = "hi"
}

  printX()-> nthg {
  print(u) 
    print(a,"\n",j,"\n",s,"\n",k)
      print("Not printing it ")
    }
}

var b:A = new B({a:2})
b.printX()
print(b.x)
)");
  O(R"(00.00000000000000
2
hi
0.00000000000000Not printing it { a : 2, b : '', c : { d : 0.00000000000000 }, d : [{ d : 0.00000000000000 }, { d : 0.00000000000000 }] })");
}
