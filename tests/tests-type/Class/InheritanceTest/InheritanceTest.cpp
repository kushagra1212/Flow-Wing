#include "InheritanceTest.h"

void InheritanceTest::SetUp() { _test->SetUp(); }

void InheritanceTest::TearDown() { _test->TearDown(); }

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
  EXPECT_EQ(
      getOutput(),
      R"({ a : 2, b : '', c : { d : 0.00000000000000 }, d : [{ d : 0.00000000000000 }, { d : 0.00000000000000 }] })");
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
  EXPECT_EQ(
      getOutput(),
      R"({ a : 0, b : '', c : { d : 0.00000000000000 }, d : [{ d : 0.00000000000000 }, { d : 0.00000000000000 }] })");
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
  EXPECT_EQ(
      getOutput(),
      R"({ a : 2, b : '', c : { d : 0.00000000000000 }, d : [{ d : 0.00000000000000 }, { d : 0.00000000000000 }] })");
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
  EXPECT_EQ(getOutput(), R"(Not printing it )");
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
  EXPECT_EQ(getOutput(), R"(02.20000000000000
2
hi
0.00000000000000Not printing it { a : 2, b : '', c : { d : 0.00000000000000 }, d : [{ d : 0.00000000000000 }, { d : 0.00000000000000 }] })");
}
TEST_F(InheritanceTest,
       BasicWithObjectOfBWithSuperBaseClassRefAndChildClassObj3) {
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

var b:B = new B({a:2})
b.printX()
print(b.x)
)");
  EXPECT_EQ(getOutput(), R"(02.20000000000000
2
hi
0.00000000000000Not printing it { a : 2, b : '', c : { d : 0.00000000000000 }, d : [{ d : 0.00000000000000 }, { d : 0.00000000000000 }] })");
}

TEST_F(InheritanceTest,
       BasicWithObjectOfBWithSuperBaseClassRefAndChildClassObj4) {
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

var b:A = new A({a:2})
b.printX()
print(b.x)
)");
  EXPECT_EQ(
      getOutput(),
      R"({ a : 2, b : '', c : { d : 0.00000000000000 }, d : [{ d : 0.00000000000000 }, { d : 0.00000000000000 }] }{ a : 2, b : '', c : { d : 0.00000000000000 }, d : [{ d : 0.00000000000000 }, { d : 0.00000000000000 }] })");
}

TEST_F(InheritanceTest,
       BasicWithObjectOfBWithSuperBaseClassRefAndChildClassObj5) {
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
  printNice()-> nthg {
    print(a)
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

var b:A = new A({a:2})
b.printX()
b.printNice()
print(b.x)
)");
  EXPECT_EQ(
      getOutput(),
      R"({ a : 2, b : '', c : { d : 0.00000000000000 }, d : [{ d : 0.00000000000000 }, { d : 0.00000000000000 }] }{ u : 'Nice' }{ a : 2, b : '', c : { d : 0.00000000000000 }, d : [{ d : 0.00000000000000 }, { d : 0.00000000000000 }] })");
}

TEST_F(InheritanceTest,
       BasicWithObjectOfBWithSuperBaseClassRefAndChildClassObj6) {
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
  printNice()-> nthg {
    print("Hi Printint Nice")
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

var b:B = new B({a:2})
b.printX()
b.printNice()
print(b.x)
)");
  EXPECT_EQ(getOutput(), R"(02.20000000000000
2
hi
0.00000000000000Not printing it Hi Printint Nice{ a : 2, b : '', c : { d : 0.00000000000000 }, d : [{ d : 0.00000000000000 }, { d : 0.00000000000000 }] })");
}

TEST_F(InheritanceTest,
       BasicWithObjectOfBWithSuperBaseClassRefAndChildClassObj7) {
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
  printNice()-> nthg {
    print("Hi Printint Nice")
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
b.printNice()
print(b.x)
)");
  EXPECT_EQ(getOutput(), R"(02.20000000000000
2
hi
0.00000000000000Not printing it Hi Printint Nice{ a : 2, b : '', c : { d : 0.00000000000000 }, d : [{ d : 0.00000000000000 }, { d : 0.00000000000000 }] })");
}

//

TEST_F(InheritanceTest, BasicLocal) {
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

{
  var a:A = new A({a:2})
a.printX()
}
)");
  EXPECT_EQ(
      getOutput(),
      R"({ a : 2, b : '', c : { d : 0.00000000000000 }, d : [{ d : 0.00000000000000 }, { d : 0.00000000000000 }] })");
}
TEST_F(InheritanceTest, BasicWithObjectOfBWithOutSuperLocal) {
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
{
  b.printX()
}
)");
  EXPECT_EQ(
      getOutput(),
      R"({ a : 0, b : '', c : { d : 0.00000000000000 }, d : [{ d : 0.00000000000000 }, { d : 0.00000000000000 }] })");
}
TEST_F(InheritanceTest, BasicWithObjectOfBWithSuperLocal) {
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

{
  var b:B = new B({a:2})
b.printX()
}
)");
  EXPECT_EQ(
      getOutput(),
      R"({ a : 2, b : '', c : { d : 0.00000000000000 }, d : [{ d : 0.00000000000000 }, { d : 0.00000000000000 }] })");
}
TEST_F(InheritanceTest,
       BasicWithObjectOfBWithSuperBaseClassRefAndChildClassObjLocal) {
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
{

var b:A = new B({a:2})
b.printX()
}
)");
  EXPECT_EQ(getOutput(), R"(Not printing it )");
}
TEST_F(InheritanceTest,
       BasicWithObjectOfBWithSuperBaseClassRefAndChildClassObj2Local) {
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

{
  var b:A = new B({a:2})
b.printX()
print(b.x)
}
)");
  EXPECT_EQ(getOutput(), R"(02.20000000000000
2
hi
0.00000000000000Not printing it { a : 2, b : '', c : { d : 0.00000000000000 }, d : [{ d : 0.00000000000000 }, { d : 0.00000000000000 }] })");
}
TEST_F(InheritanceTest,
       BasicWithObjectOfBWithSuperBaseClassRefAndChildClassObj3Local) {
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

{
  var b:B = new B({a:2})
b.printX()
print(b.x)
}
)");
  EXPECT_EQ(getOutput(), R"(02.20000000000000
2
hi
0.00000000000000Not printing it { a : 2, b : '', c : { d : 0.00000000000000 }, d : [{ d : 0.00000000000000 }, { d : 0.00000000000000 }] })");
}

TEST_F(InheritanceTest,
       BasicWithObjectOfBWithSuperBaseClassRefAndChildClassObj4Local) {
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

{
  var b:A = new A({a:2})
b.printX()
print(b.x)
}
)");
  EXPECT_EQ(
      getOutput(),
      R"({ a : 2, b : '', c : { d : 0.00000000000000 }, d : [{ d : 0.00000000000000 }, { d : 0.00000000000000 }] }{ a : 2, b : '', c : { d : 0.00000000000000 }, d : [{ d : 0.00000000000000 }, { d : 0.00000000000000 }] })");
}

TEST_F(InheritanceTest,
       BasicWithObjectOfBWithSuperBaseClassRefAndChildClassObj5Local) {
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
  printNice()-> nthg {
    print(a)
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

{
  var b:A = new A({a:2})
b.printX()
b.printNice()
print(b.x)
}
)");
  EXPECT_EQ(
      getOutput(),
      R"({ a : 2, b : '', c : { d : 0.00000000000000 }, d : [{ d : 0.00000000000000 }, { d : 0.00000000000000 }] }{ u : 'Nice' }{ a : 2, b : '', c : { d : 0.00000000000000 }, d : [{ d : 0.00000000000000 }, { d : 0.00000000000000 }] })");
}

TEST_F(InheritanceTest,
       BasicWithObjectOfBWithSuperBaseClassRefAndChildClassObj6Local) {
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
  printNice()-> nthg {
    print("Hi Printint Nice")
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

{
  var b:B = new B({a:2})
b.printX()
b.printNice()
print(b.x)
}
)");
  EXPECT_EQ(getOutput(), R"(02.20000000000000
2
hi
0.00000000000000Not printing it Hi Printint Nice{ a : 2, b : '', c : { d : 0.00000000000000 }, d : [{ d : 0.00000000000000 }, { d : 0.00000000000000 }] })");
}

TEST_F(InheritanceTest,
       BasicWithObjectOfBWithSuperBaseClassRefAndChildClassObj7Local) {
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
  printNice()-> nthg {
    print("Hi Printint Nice")
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

{
  var b:A = new B({a:2})
b.printX()
b.printNice()
print(b.x)
}
)");
  EXPECT_EQ(getOutput(), R"(02.20000000000000
2
hi
0.00000000000000Not printing it Hi Printint Nice{ a : 2, b : '', c : { d : 0.00000000000000 }, d : [{ d : 0.00000000000000 }, { d : 0.00000000000000 }] })");
}

TEST_F(
    InheritanceTest,
    BasicWithObjectOfBWithSuperBaseClassRefAndChildClassObj7DynamicMethodDispatch) {
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
  printNice()-> nthg {
    print("Hi Printint Nice")
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

var b:A = new A({a:2})
b.printX()
b.printNice()
print(b.x)
b = new B({a:3})

b.printX()
b.printNice()
print(b.x)

)");
  EXPECT_EQ(
      getOutput(),
      R"({ a : 2, b : '', c : { d : 0.00000000000000 }, d : [{ d : 0.00000000000000 }, { d : 0.00000000000000 }] }Hi Printint Nice{ a : 2, b : '', c : { d : 0.00000000000000 }, d : [{ d : 0.00000000000000 }, { d : 0.00000000000000 }] }02.20000000000000
2
hi
0.00000000000000Not printing it Hi Printint Nice{ a : 3, b : '', c : { d : 0.00000000000000 }, d : [{ d : 0.00000000000000 }, { d : 0.00000000000000 }] })");
}

TEST_F(
    InheritanceTest,
    BasicWithObjectOfBWithSuperBaseClassRefAndChildClassObj7DynamicMethodDispatchGettingClassFromFunction) {
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
  printNice()-> nthg {
    print("Hi Printint Nice")
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
fun getB() -> B {
    var b:B  = new B({a:5})
    return b 
}
var b:A = new A({a:2})
b.printX()
b.printNice()
print(b.x)
b = getB() 

b.printX()
b.printNice()
print(b.x)
)");
  EXPECT_EQ(
      getOutput(),
      R"({ a : 2, b : '', c : { d : 0.00000000000000 }, d : [{ d : 0.00000000000000 }, { d : 0.00000000000000 }] }Hi Printint Nice{ a : 2, b : '', c : { d : 0.00000000000000 }, d : [{ d : 0.00000000000000 }, { d : 0.00000000000000 }] }02.20000000000000
2
hi
0.00000000000000Not printing it Hi Printint Nice{ a : 5, b : '', c : { d : 0.00000000000000 }, d : [{ d : 0.00000000000000 }, { d : 0.00000000000000 }] })");
}
TEST_F(
    InheritanceTest,
    BasicWithObjectOfBWithSuperBaseClassRefAndChildClassObj7DynamicMethodDispatchGettingClassInitialObjOfB) {
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
  printNice()-> nthg {
    print("Hi Printint Nice")
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
fun getB() -> B {
    var b:B  = new B({a:5})

    return b 
}
var b:A = new B({a:2})

b.printX()
b.printNice()
print(b.x)
b = new A({a:5})
b.printX()
b.printNice()
print(b.x)
)");
  EXPECT_EQ(getOutput(), R"(02.20000000000000
2
hi
0.00000000000000Not printing it Hi Printint Nice{ a : 2, b : '', c : { d : 0.00000000000000 }, d : [{ d : 0.00000000000000 }, { d : 0.00000000000000 }] }{ a : 5, b : '', c : { d : 0.00000000000000 }, d : [{ d : 0.00000000000000 }, { d : 0.00000000000000 }] }Hi Printint Nice{ a : 5, b : '', c : { d : 0.00000000000000 }, d : [{ d : 0.00000000000000 }, { d : 0.00000000000000 }] })");
}
TEST_F(
    InheritanceTest,
    BasicWithObjectOfBWithSuperBaseClassRefAndChildClassObj7DynamicMethodDispatchGettingClassInitialObjOpposite) {
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
  printNice()-> nthg {
    print("Hi Printint Nice")
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
fun getB() -> B {
    var b:B  = new B({a:5})

    return b 
}
var b:A = new A({a:2})

b.printX()
b.printNice()
print(b.x)
b = new B({a:5})
b.printX()
b.printNice()
print(b.x)
)");
  EXPECT_EQ(
      getOutput(),
      R"({ a : 2, b : '', c : { d : 0.00000000000000 }, d : [{ d : 0.00000000000000 }, { d : 0.00000000000000 }] }Hi Printint Nice{ a : 2, b : '', c : { d : 0.00000000000000 }, d : [{ d : 0.00000000000000 }, { d : 0.00000000000000 }] }02.20000000000000
2
hi
0.00000000000000Not printing it Hi Printint Nice{ a : 5, b : '', c : { d : 0.00000000000000 }, d : [{ d : 0.00000000000000 }, { d : 0.00000000000000 }] })");
}
TEST_F(
    InheritanceTest,
    BasicWithObjectOfBWithSuperBaseClassRefAndChildClassObj7DynamicMethodDispatchGettingClassInitialObjOppositeGetB) {
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
  printNice()-> nthg {
    print("Hi Printint Nice")
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
fun getB() -> B {
    var b:B  = new B({a:5})

    return b 
}
var b:A = new A({a:2})

b.printX()
b.printNice()
print(b.x)
b = getB()
b.printX()
b.printNice()
print(b.x)
)");
  EXPECT_EQ(
      getOutput(),
      R"({ a : 2, b : '', c : { d : 0.00000000000000 }, d : [{ d : 0.00000000000000 }, { d : 0.00000000000000 }] }Hi Printint Nice{ a : 2, b : '', c : { d : 0.00000000000000 }, d : [{ d : 0.00000000000000 }, { d : 0.00000000000000 }] }02.20000000000000
2
hi
0.00000000000000Not printing it Hi Printint Nice{ a : 5, b : '', c : { d : 0.00000000000000 }, d : [{ d : 0.00000000000000 }, { d : 0.00000000000000 }] })");
}
TEST_F(
    InheritanceTest,
    BasicWithObjectOfBWithSuperBaseClassRefAndChildClassObj7DynamicMethodDispatchGettingClassInitialObjOppositeGetBReturning) {
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
  printNice()-> nthg {
    print("Hi Printint Nice")
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
fun getB() -> B {
    var b:B  = new B({a:5})

    return b 
}

fun getA() -> A {
  var b:A = new A({a:2})

  return b
}
var b:B = getB() 
b.printX()
b.printNice()
print(b.x)
)");
  EXPECT_EQ(getOutput(), R"(02.20000000000000
2
hi
0.00000000000000Not printing it Hi Printint Nice{ a : 5, b : '', c : { d : 0.00000000000000 }, d : [{ d : 0.00000000000000 }, { d : 0.00000000000000 }] })");
}
TEST_F(
    InheritanceTest,
    BasicWithObjectOfBWithSuperBaseClassRefAndChildClassObj7DynamicMethodDispatchGettingClassInitialObjOppositeGetAReturning) {
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
  printNice()-> nthg {
    print("Hi Printint Nice")
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
fun getB() -> B {
    var b:B  = new B({a:5})

    return b 
}

fun getA() -> A {
  var b:A = new A({a:2})

  return b
}
var b:A = getA() 
b.printX()
b.printNice()
print(b.x)
)");
  EXPECT_EQ(
      getOutput(),
      R"({ a : 2, b : '', c : { d : 0.00000000000000 }, d : [{ d : 0.00000000000000 }, { d : 0.00000000000000 }] }Hi Printint Nice{ a : 2, b : '', c : { d : 0.00000000000000 }, d : [{ d : 0.00000000000000 }, { d : 0.00000000000000 }] })");
}

TEST_F(
    InheritanceTest,
    BasicWithObjectOfBWithSuperBaseClassRefAndChildClassObj7DynamicMethodDispatchGettingClassInitialObjOppositeGetBReturninginA) {
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
  printNice()-> nthg {
    print("Hi Printint Nice")
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
fun getB() -> B {
    var b:B  = new B({a:5})

    return b 
}

fun getA() -> A {
  var b:A = new A({a:2})

  return b
}
var b:A = getB() 
b.printX()
b.printNice()
print(b.x)
)");
  EXPECT_EQ(getOutput(), R"(02.20000000000000
2
hi
0.00000000000000Not printing it Hi Printint Nice{ a : 5, b : '', c : { d : 0.00000000000000 }, d : [{ d : 0.00000000000000 }, { d : 0.00000000000000 }] })");
}
TEST_F(
    InheritanceTest,
    BasicWithObjectOfBWithSuperBaseClassRefAndChildClassObj7DynamicMethodDispatchGettingClassInitialObjOppositeGetBReturninginAOpposite) {
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
  printNice()-> nthg {
    print("Hi Printint Nice")
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
fun getB() -> B {
    var b:B  = new B({a:5})

    return b 
}

fun getA() -> A {
  var b:A = new A({a:2})

  return b
}
var b:A = getB() 
b.printX()
b.printNice()
print(b.x)
b = getA()
b.printX()
b.printNice()
print(b.x)
)");
  EXPECT_EQ(getOutput(), R"(02.20000000000000
2
hi
0.00000000000000Not printing it Hi Printint Nice{ a : 5, b : '', c : { d : 0.00000000000000 }, d : [{ d : 0.00000000000000 }, { d : 0.00000000000000 }] }{ a : 2, b : '', c : { d : 0.00000000000000 }, d : [{ d : 0.00000000000000 }, { d : 0.00000000000000 }] }Hi Printint Nice{ a : 2, b : '', c : { d : 0.00000000000000 }, d : [{ d : 0.00000000000000 }, { d : 0.00000000000000 }] })");
}
TEST_F(InheritanceTest, DogAndAnimalExample) {
  I(R"(
 class Animal {
  var age:int 
  var species:str 
  init(age:int) -> nthg {
    self.age = age
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
}
fun printAge(a: Animal) ->nthg{
  print("I'm "+a.getAge()+" years old!\n")
}
fun main2() -> nthg {
  var animal:Animal = new Animal(2)
  var  dog:Dog = new Dog(2)

  printAge(animal) 
  printAge(dog) 
}

main2()
)");
  EXPECT_EQ(getOutput(), R"(I'm 2 years old!
I'm 14 years old!
)");
}