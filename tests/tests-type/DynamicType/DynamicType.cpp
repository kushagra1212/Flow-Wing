#include "DynamicType.h"
#include "gtest/gtest.h"

void DynamicTypeTest::SetUp() { _test->SetUp(); }

void DynamicTypeTest::TearDown() { _test->TearDown(); }

TEST_F(DynamicTypeTest, Class) {
  I(R"(

class A {
  var x:int 
  init(x:int) -> nthg {
      self.x = x 
    }
}

var a:A = new A(2)
  if(a == Nir) {
    print("")
  })");

  EXPECT_EQ(getOutput(), R"()");
}

TEST_F(DynamicTypeTest, Class2) {
  I(R"(
class A {
  var x:int 
  init(x:int) -> nthg {
      self.x = x 
    }
}

var a:A = Nir
  if(a == Nir) {
    print("Is Nir")
  }
  )");

  EXPECT_EQ(getOutput(), R"(Is Nir)");
}

TEST_F(DynamicTypeTest, Class3) {
  I(R"(
class A {
  var x:int 
  init(x:int) -> nthg {
      self.x = x 
    }
}

var a:A = Nir

  if(a != Nir) {
    print("Is not Nir")
  }
  )");

  EXPECT_EQ(getOutput(), R"()");
}

TEST_F(DynamicTypeTest, Class4) {
  I(R"(

class A {
  var x:int 
  init(x:int) -> nthg {
      self.x = x 
    }
}

var a:A = new A(2)

if(a == a) {
  print("Is equal")
}

if(a != a) {
  print("Is not equal")
}

  )");

  EXPECT_EQ(getOutput(), R"(Is equal)");
}

TEST_F(DynamicTypeTest, Class5) {
  I(R"(

class A {
  var x:int 
  init(x:int) -> nthg {
      self.x = x 
    }
}

var a:A = new A(2)

var b:A = new A(3)

if(a == b) {
  print("Is equal")
}

if(a != b) {
  print("Is not equal")
}

  )");

  EXPECT_EQ(getOutput(), R"(Is not equal)");
}

TEST_F(DynamicTypeTest, UltimateClassBinaryAndUnaryTest) {
  I(R"(

    class A {
      var x:int 
      init(x:int) -> nthg {
          self.x = x 
        }
    }
    
    var a:A = new A(2)
    
    var b:A = new A(3)
    print("Both a and b are not null and are different","\n")
    if(true && a == b) {
      print("true && a == b","\n")
    }
    
    if(false && a == b) {
      print("false && a == b","\n")
    }
    
    if(true || a == b) {
      print("true || a == b","\n")
    }
    
    if(false || a == b) {
      print("false || a == b","\n")
    }
    
    
    if(true && a != b) {
      print("true && a != b","\n")
    }
    
    if(false && a != b) {
      print("false && a != b","\n")
    }
    
    
    if(true || a != b) {
      print("true || a != b","\n")
    }
    
    if(false || a != b) {
      print("false || a != b","\n")
    }
    
    
    if(true && a) {
      print("true && a","\n")
    }
    
    if(false && a) {
      print("false && a","\n")
    }
    
    
    if(true && !a) {
      print("true && !a","\n")
    }
    
    if(false && !a) {
      print("false && !a","\n")
    }
    
    
    
    
    
    if(true || a) {
      print("true || a","\n")
    }
    
    if(false || a) {
      print("false || a","\n")
    }
    
    
    if(true || !a) {
      print("true || !a","\n")
    }
    
    if(false || !a) {
      print("false || !a","\n")
    }
    
    if(a) {
      print("a","\n")
    }
    
    if(!a) {
      print("!a","\n")
    }
    
    
    
    
    
    if(a && b) {
      print("a && b","\n")
    }
    
    
    if(a && !b) {
      print("a && !b","\n")
    }
    
    
    if(!a && b) {
      print("!a && b","\n")
    }
    
    
    if(!a && !b) {
      print("!a && !b","\n")
    }
    
    
    
    
    if(a || b) {
      print("a || b","\n")
    }
    
    
    if(a || !b) {
      print("a || !b","\n")
    }
    
    
    if(!a || b) {
      print("!a || b","\n")
    }
    
    
    if(!a || !b) {
      print("!a || !b","\n")
    }
    
    
    
    
    b = Nir
    print("b set to Nir","\n")
    
    if(b) {
      print("b","\n")
    }
    
    
    if(!b) {
      print("!b","\n")
    }
    
    
    if(true && b) {
      print("true && b","\n")
    }
    
    
    if(false && b) {
      print("false && b","\n")
    }
    
    
    
    if(true && !b) {
      print("true && !b","\n")
    }
    
    
    if(false && !b) {
      print("false && !b","\n")
    }
    
    
    
    
    
    if(true || b) {
      print("true || b","\n")
    }
    
    
    if(false || b) {
      print("false || b","\n")
    }
    
    
    
    if(true || !b) {
      print("true || !b","\n")
    }
    
    
    if(false || !b) {
      print("false || !b","\n")
    }
    
    
    
    
    if(a && b) {
      print("a && b","\n")
    }
    
    
    if(a && !b) {
      print("a && !b","\n")
    }
    
    
    if(!a && b) {
      print("!a && b","\n")
    }
    
    
    if(!a && !b) {
      print("!a && !b","\n")
    }
    
    
    
    
    if(a || b) {
      print("a || b","\n")
    }
    
    
    if(a || !b) {
      print("a || !b","\n")
    }
    
    
    if(!a || b) {
      print("!a || b","\n")
    }
    
    
    if(!a || !b) {
      print("!a || !b","\n")
    }
    
    
    
    if(true && b == Nir) {
      print("true && b == Nir","\n")
    }
    
    if(false && b == Nir) {
      print("false && b == Nir","\n")
    }
    
    
    if(true || b == Nir) {
      print("true || b == Nir","\n")
    }
    
    if(false || b == Nir) {
      print("false || b == Nir","\n")
    }
    
    
    
    if(true && b != Nir) {
      print("true && b != Nir","\n")
    }
    
    if(false && b != Nir) {
      print("false && b != Nir","\n")
    }
    
    
    if(true || b != Nir) {
      print("true || b != Nir","\n")
    }
    
    if(false || b != Nir) {
      print("false || b != Nir","\n")
    }
    
    
    
    print("Setting a to a","\n")
    
    b = a
     
    
    if(true && a == b) {
      print("true && a == b","\n")
    }
    
    if(false && a == b) {
      print("false && a == b","\n")
    }
    
    if(true || a == b) {
      print("true || a == b","\n")
    }
    
    if(false || a == b) {
      print("false || a == b","\n")
    }
    
    
    if(true && a != b) {
      print("true && a != b","\n")
    }
    
    if(false && a != b) {
      print("false && a != b","\n")
    }
    
    
    if(true || a != b) {
      print("true || a != b","\n")
    }
    
    if(false || a != b) {
      print("false || a != b","\n")
    }
    
  )");

  EXPECT_EQ(getOutput(), R"(Both a and b are not null and are different
true || a == b
true && a != b
true || a != b
false || a != b
true && a
true || a
false || a
true || !a
a
a && b
a || b
a || !b
!a || b
b set to Nir
!b
true && !b
true || b
true || !b
false || !b
a && !b
a || b
a || !b
!a || !b
true && b == Nir
true || b == Nir
false || b == Nir
true || b != Nir
Setting a to a
true && a == b
true || a == b
false || a == b
true || a != b
)");
}

TEST_F(DynamicTypeTest, Class7) {
  I(R"(

class A {
  var x:int 
  init(x:int) -> nthg {
      self.x = x 
    }
}

var x:int, a:A = 2, new A(2)

print(x, "\n")
print(a.x, "\n")

if(a != Nir) {
  print("Is not Nir")
}

if(a == Nir) {
  print("Is Nir")
}

var b:A, c:int = new A(2), 2


if(a == b) {
  print("Is equal")
}or if(a != b) {
  print("Is not equal")
}

if(c == Nir) {
}or if(c != Nir) {
  print("Is not Nir")
}

var g, l:A = 2, new A(2)

if(g == l) {
  print("Is equal")
}or if(g != l) {
  print("Is not equal")
}


print(g, "\n")

var k:deci, m:A = 2.2, new A(2)

if(k == m) {
  print("Is equal")
}or if(k != m) {
  print("Is not equal")
}

print(k, "\n")

var p:bool, q:A = true, new A(2)

if(p && q) {
  print("Is true")
}or if(p && q) {
  print("Is false")
}

if(p && q) {
  print("Is true")
}or if(p && q) {
  print("Is false")
}

var r:str, s:A = "Hello", Nir

if(r == s) {  
  print("Is equal")
}or if(r != s) {
  print("Is not equal")
}

if(r == Nir) {
  print("Is Nir")
}

if(r != Nir) {  
  print("Is not Nir")
}

if(s == Nir) {
  print("S is Nir")
}

if(r == "Hello") {
  print("Is equal")
}or if(r != "Hello") {
  print("Is not equal")
}

if(r == 2) {
  print("Is equal")
}or if(r != 2) {
  print("Is not equal")
}

if(r == 2.2) {
  print("Is equal")
}or if(r != 2.2) {
  print("Is not equal")
}



  )");

  EXPECT_EQ(getOutput(), R"(2
2
Is not NirIs not equalIs not NirIs not equal2
Is not equal2.20000000000000
Is trueIs trueIs not equalIs not NirS is NirIs equalIs not equalIs not equal)");
}

TEST_F(DynamicTypeTest, DynamicType) {
  I(R"(
 var x: int = 2
print(x, "\n")
var y = 3
print(y, "\n")
y = 5 
print(y, "\n")
y = x + 5 
print(y, "\n")
y = "Hello" 
print(y, "\n")
var z = 2
print(z, "\n")
y = y + z 
print(y, "\n")
var j = 5
print(j, "\n")
y = y + j 
y = y + 2 
y = y + "Hello" 
print(y, "\n")
var k: int[5] = [1, 2, 3, 4, y]
print(k, "\n")
var p = 45
print(p, "\n")
var arr: int[5] = [p, 2, p, 4, p]
print(arr, "\n")

  )");

  EXPECT_EQ(getOutput(), R"(2
3
5
7
Hello
2
Hello2
5
Hello252Hello
[1, 2, 3, 4, 0]
45
[45, 2, 45, 4, 45]
)");
}

TEST_F(DynamicTypeTest, Reassign) {
  I(R"(
 {
 var x = 2
print(x, "\n")
x = "Hello" 
print(x, "\n")

 }

 {
 var x = 2
var y: str = "Hello"
x = 5 
x = y + 2 + x + y 
print(x, "\n")
}

{
  var x = 2
  print(x, "\n")
}
{
  var x = 2
  x = 5 
  print(x, "\n")
}
{
  var x = 2
  x = "Hello" 
  print(x, "\n")
}
{
  var x = 2
  x = x + 2 
  print(x, "\n")
}
{
  var x = 2
  x = 5 
  x = x + 2 
  print(x, "\n")
}
{
  var x = 2
  var y = 10
  x = 5 
  x = y 
  print(x, "\n")
}
{
  var x = 2
  var y = 10
  x = 5 
  x = y + 2 
  print(x, "\n")
}
{
  var x = 2
  var y = 10
  x = 5 
  x = y + 2 + x + y 
  print(x, "\n")
}
{
  var x = 2
  var y: int = 10
  x = 5 
  x = y + 2 + x + y 
  print(x, "\n")
}

  )");

  EXPECT_EQ(getOutput(), R"(2
Hello
Hello25Hello
2
5
Hello
4
7
10
12
27
27
)");
}

TEST_F(DynamicTypeTest, AssignmentToStatic) {
  I(R"(
 {
 var x: int = 5
print(x, "\n")
var y = 12
x = y 
print(x, "\n")

 }

 {var x: int = 5
print(x, "\n")
var y = 12
x = y + 10 
print(x, "\n")
}

{
var x: int = 5
print(x, "\n")
var y = 12
x = "Hello" + y 
print(x, "\n")

}

{var x: int = 5
print(x, "\n")
var y = 12
x = y + "Hello" 
print(x, "\n")
}
  )");

  EXPECT_EQ(getOutput(), R"(5
12
5
22
5
0
5
12
)");
}

TEST_F(DynamicTypeTest, FloatTest) {
  I(R"(
 {
  var x = 1.232d
  var y: str = "Hello"
  print(x, "\n")
  x = x + x + y + y 
  print(x, "\n")
}
{
  var x = 1.2332322d
  var y = 2.2d
  print(x, "\n")
  x = x + 10 + y 
  print(x, "\n")
}
{
  var x = 1.2d
  var y: int = 2
  print(x, "\n")
  x = x + 10 + y 
  print(x, "\n")
}
{
  var x = 1.2d
  var y = "Hello"
  print(x, "\n")
  x = x + 10 + y 
  print(x, "\n")
}
{
  var x = 1.2d
  print(x, "\n")
  x = x + 10 
  print(x, "\n")
}
{
  var x = 1.2d
  x = x + x 
  print(x, "\n")
}


  )");

  EXPECT_EQ(getOutput(), R"(1.2320000
2.46399998664856HelloHello
1.2332321
13.4332323
1.2000000
13.1999998
1.2000000
11.19999980926514Hello
1.2000000
11.1999998
2.4000001
)");
}

TEST_F(DynamicTypeTest, DoubleTest) {
  I(R"(
 var x = 1.232
var y = "Hello"
var z: int = 5
print(x, "\n")
x = x + x + y + y + z 
print(x, "\n")


  )");

  EXPECT_EQ(getOutput(), R"(1.23200000000000
2.46400000000000HelloHello5
)");
}

TEST_F(DynamicTypeTest, BooleanTest) {
  I(R"(
{
  var x = true
  var y = 2.2
  print(x, "\n")
  x = x + y 
  print(x, "\n")
}
{
  var x = true
  var y = false
  print(x, "\n")
  x = x + y 
  print(x, "\n")
}
{
  var x = true
  var y: int = 2
  print(x, "\n")
  x = x + y 
  print(x, "\n")
}
{
  var x = true
  var y = 2
  print(x, "\n")
  x = x + y 
  print(x, "\n")
}
{
  var x = true
  var y = "Hello"
  print(x, "\n")
  x = x + y 
  print(x, "\n")
}
{
  var x = true
  print(x, "\n")
  x = x + x + 1 
  print(x, "\n")
}
{
  var x = true
  print(x, "\n")
  x = x + x 
  print(x, "\n")
}


  )");

  EXPECT_EQ(getOutput(), R"(true
3.20000000000000
true
true
true
3
true
3
true
trueHello
true
2
true
true
)");
}

TEST_F(DynamicTypeTest, CharorInt8Test) {
  I(R"(
{
  var z: char = 'a'
  var x = 'a'
  var y = 'b'
  print(x, "\n")
  x = z + "ac" 
  print(x, "\n")
}
{
  var z: char = 'a'
  var x = 'a'
  var y = 'b'
  print(x, "\n")
  x = y 
  print(x, "\n")
}
{
  var z: char = 'a'
  var x = z
  var y = 2.2
  print(x, "\n")
  x = x + y 
  print(x, "\n")
}
{
  var z: char = 'a'
  var x = 'a'
  var y = 'b'
  print(x, "\n")
  x = z + "ac" 
  print(x, "\n")
}
{
  var z: char = 'a'
  var x = 'a'
  var y = 'b'
  print(x, "\n")
  x = y 
  print(x, "\n")
}
{
  var z: char = 'a'
  var x = z
  var y = 2.2
  print(x, "\n")
  x = x + y 
  print(x, "\n")
}

  )");

  EXPECT_EQ(getOutput(), R"(a
97ac
a
b
a
99.20000000000000
a
97ac
a
b
a
99.20000000000000
)");
}

TEST_F(DynamicTypeTest, MultipleVariableDeclaration) {
  I(R"(
 var i, j = 2,"Hello"
var k, l = 3,4
print(i, j, k, l, "\n")
l, k = "Hello", 2.5d 
print(l, k, "\n")


  )");

  EXPECT_EQ(getOutput(), R"(2Hello34
Hello2.5000000
)");
}

TEST_F(DynamicTypeTest, ForLoop) {
  I(R"(
 {
  var i = 0
  var step = 2
  var limit = 10
  for i to limit : step {
    print(i, " ")
  }
}
print("\n")
{
  var i: int = 0
  var step = 2
  var limit = 10
  for i to limit : step {
    print(i, " ")
  }
}
print("\n")
{
  var i: int = 0
  var step = 2
  for i to 10 : step {
    print(i, " ")
  }
}
print("\n")
{
  var i: int = 0
  var step: int = 2
  for i to 10 : step {
    print(i, " ")
  }
}
print("\n")
{
  var i: int = 0
  for i to 10 : 2 {
    print(i, " ")
  }
}
print("\n")
{
  var i: int = 0
  for i to 10 {
    print(i, " ")
  }
}
print("\n")
{
  var c = 10
  var step: int = 2
  for var i: int = 0 to c : step {
    print(i, " ")
  }
}
print("\n")
{
  var c = 10
  var step = 2
  for var i: int = 0 to c : step {
    print(i, " ")
  }
}
print("\n")
{
  var c = 10
  for var i: int = 0 to c : 2 {
    print(i, " ")
  }
}
print("\n")
{
  for var i: int = 0 to 10 : 2 {
    print(i, " ")
  }
}
print("\n")
{
  for var i = 0 to 10 : 2 {
    print(i, " ")
  }
}
print("\n")
for var i = 0 to 10 {
  print(i, " ")
}
print("\n")
for var i: int = 0 to 10 {
  print(i, " ")
}
print("\n")
{
  var c = 10
  for var i: int = 0 to c {
    print(i, " ")
  }
}
print("\n")
{
  var c: int = 10
  for var i: int = 0 to c {
    print(i, " ")
  }
}
print("\n")
var c = 10
for var i = 0 to c {
  print(i, " ")
}



  )");

  EXPECT_EQ(getOutput(), R"(0 0 0 0 0 0 
0 0 0 0 0 0 
0 0 0 0 0 0 
0 0 0 0 0 0 
0 0 0 0 0 0 
0 0 0 0 0 0 0 0 0 0 0 
0 2 4 6 8 10 
0 2 4 6 8 10 
0 2 4 6 8 10 
0 2 4 6 8 10 
0 2 4 6 8 10 
0 1 2 3 4 5 6 7 8 9 10 
0 1 2 3 4 5 6 7 8 9 10 
0 1 2 3 4 5 6 7 8 9 10 
0 1 2 3 4 5 6 7 8 9 10 
0 1 2 3 4 5 6 7 8 9 10 )");
}

TEST_F(DynamicTypeTest, WhileLoopTest) {
  I(R"(
 var x = 'a'
while x < 'c' {
  print(x, " ")
  x = 'c' 
}
print("\n")
{
  var x: int = 0
  while x < 10 {
    print(x, " ")
    x = x + 1 
  }
}
print("\n")
{
  var x = 0
  while x < 10 {
    print(x, " ")
    x = x + 1 
  }
}
print("\n")
{
  var x = 0.0
  while x < 10 {
    print(x, " ")
    x = x + 1 
  }
}

  )");

  EXPECT_EQ(getOutput(), R"(a 
0 1 2 3 4 5 6 7 8 9 
0 1 2 3 4 5 6 7 8 9 
0.00000000000000 1.00000000000000 2.00000000000000 3.00000000000000 4.00000000000000 5.00000000000000 6.00000000000000 7.00000000000000 8.00000000000000 9.00000000000000 )");
}

TEST_F(DynamicTypeTest, NirTest) {
  I(R"(
  {
  var x: int = 22
  if (x) {
    print("x is true")
  }
}
print("\n")
{
  var x: str = "Hello"
  if (x) {
    print("x is true")
  }
}
print("\n")
{
  var x = "Hello"
  if (x) {
    print("x is true")
  }
}
print("\n")
{
  var x = 22
  if (x) {
    print("x is true")
  }
}
print("\n")
{
  var x = 0
  if (x) {
    print("x is true")
  }
}
print("\n")
{
  var x = 22
  if (x != Nir) {
    print("x is not Nir")
  }
}
print("\n")
{
  var x = Nir
  if (x == Nir) {
    print("x is Nir")
  }
}
print("\n")
{
  var x: str = "Hello"
  if (x == Nir) {
    print("x is Nir")
  }
}
print("\n")
{
  var x = 2
  if (x == Nir) {
    print("x is Nir")
  }
}
print("\n")
{
  var x = 2
  if (x == Nir) {
    print("x is Nir")
  }
}
print("\n")
{
  var x = 0
  if (x == Nir) {
    print("x is Nir")
  }
}


  )");

  EXPECT_EQ(getOutput(), R"(x is true
x is true
x is true
x is true

x is not Nir
x is Nir



)");
}

TEST_F(DynamicTypeTest, ClassTest1) {
  I(R"(
class A {
  var x: int = 22
  init() -> nthg {
    x = 22 
  }


  printX() -> nthg {
    print("x is true", self.x)
  }


}
{
  var a: A = new A()
  a.printX()
  if (a) {
    print("Not Nir")
  }
}
print("\n")
{
  var a: A = new A()
  if (a != Nir) {
    print("Not Nir")
  }
}

  )");

  EXPECT_EQ(getOutput(), R"(x is true22Not Nir
Not Nir)");
}

// TEST_F(DynamicTypeTest, ErrModuleWithNir) {
//   I(R"(
//  bring Err
// fun f() -> int,Err::Result {
//   return 22,Err::Result("Error")
// }

// fun returnNir() -> int,Err::Result {
//   return 22,Nir
// }

// fun singleNir() -> Err::Result {
//   return Nir
// }

// fun singleErr() -> Err::Result {
//   return Err::Result("Error")
// }

// var a:int, err:Err::Result = f()
// if (err != Nir) {
//   print("Error")
// }
// {

// var a:int, err:Err::Result = returnNir()
// if (err != Nir) {
//   print("Error")
// }else {
//   print("No Error")
// }
// }

// {
//   var err:Err::Result = singleNir()
//   if (err != Nir) {
//     print("Error")
//   }else {
//     print("No Error")
//   }
// }

// {
//   var err:Err::Result = singleErr()
//   if (err != Nir) {
//     print("Error")
//   }else {
//     print("No Error")
//   }
// }

//   )");

//   EXPECT_EQ(getOutput(), R"(ErrorNo ErrorNo ErrorError)");
// }

TEST_F(DynamicTypeTest, NotEqualTest) {
  I(R"(
 class A {
  var x: int = 22
  init() -> nthg {
    x = 22 
  }


}
var decimalA = 2.2
if (decimalA != Nir) {
  print("\ndecimalA is not Nir")
}
var decimalB = 2.2d
if (decimalB != Nir) {
  print("\ndecimalB is not Nir")
}
var integerA = 5
if (integerA != Nir) {
  print("\nintegerA is not Nir")
}
var stringA = "Hello"
if (stringA != Nir) {
  print("\nstringA is not Nir")
}
var booleanA = false
if (booleanA != Nir) {
  print("\nbooleanA is not Nir")
}
var classObjectA = new A()
if (classObjectA != Nir) {
  print("\nclassObjectA is not Nir")
}

  )");

  EXPECT_EQ(getOutput(), R"(
decimalA is not Nir
decimalB is not Nir
integerA is not Nir
stringA is not Nir
booleanA is not Nir
classObjectA is not Nir)");
}

TEST_F(DynamicTypeTest, NirIsNir) {
  I(R"(
class A {
  var x: int = 22
  init() -> nthg {
    x = 22 
  }
}

var decimal = 2.2
if (decimal == Nir) {
  print( "decimal is Nir")
}

var decimal32 = 2.2d
if (decimal32 == Nir) {
  print("decimal32 is Nir")
}

var integer = 5
if (integer == Nir) {
  print("integer is Nir")
}

var string = "Hello"
if (string == Nir) {
  print("string is Nir")
}

var boolean = false
if (boolean == Nir) {
  print("boolean is Nir")
}

var boolean2 = true
if (boolean2 == Nir) {
  print("boolean2 is Nir")
}

var nir = Nir
if (nir == Nir) {
  print("nir is Nir")
}


var classObject = new A()
if (classObject == Nir) {
  print("classObject is Nir")
}
  )");

  EXPECT_EQ(getOutput(), R"(nir is Nir)");
}

TEST_F(DynamicTypeTest, ContainerTest) {
  I(R"(
var a: int[5] = [1, 2, 3, 4, 5]
var b = 0
print(a[b])


  )");

  EXPECT_EQ(getOutput(), R"(1)");
}

TEST_F(DynamicTypeTest, NirTest2) {
  I(R"(
  class A {
  var x:int 
  init(x:int) -> nthg {
      self.x = x 
    }

}
{
var a:A = Nir
if(a == Nir){
  print("a is Nir")
}}
print("\n")
{
var a:A = Nir
if(a != Nir){
  print("a is not Nir")
}}
print("\n")
{
var a:A = new A(2)
if(a != Nir){
  print("a is not Nir")
}}
print("\n")
{
var a:A = new A(2)
if(a == Nir){
  print("a is Nir")
}
}
print("\n")
var x = 2
var y: int = 3
y = y + x 
print(y)
  )");

  EXPECT_EQ(getOutput(), R"(a is Nir

a is not Nir

5)");
}

TEST_F(DynamicTypeTest, Assign) {
  I(R"(
  var x = "Hello"
var k: int = 5
var y = 2 + (20 + 22 + k)
print(k, "\n")
k = x 
print(k, "\n")

  )");

  EXPECT_EQ(getOutput(), R"(5
0
)");
}

TEST_F(DynamicTypeTest, OperationsOnNir) {
  I(R"(
{
  var x = Nir
  x = x + 1
  print(x)
}
print("\n")
{
  var x = Nir
  x = 1 + x
  print(x)
}
print("\n")
{
  var x = Nir
  x = x + "a"
  print(x)
}
print("\n")
{
  var x = Nir
  x = "a" + x
  print(x)
}
print("\n")
{
  var x = Nir
  if(x) {
    print("is true")
  } else {
    print("is false")
  }
}
print("\n")
{
  var x:int = Nir
  print(x)
}
  )");

  EXPECT_EQ(getOutput(), R"(1
1
a
a
is false
0)");
}

TEST_F(DynamicTypeTest, DynamicUnaryOps) {
  I(R"(
{
  var x = 10
  print(-x, "\n")
}
{
  var x = 10.5
  print(-x, "\n")
}
{
  var x = true
  print(!x, "\n")
}
{
  var x = false
  print(!x, "\n")
}
{
  var x = 0
  print(!x, "\n")
}
{
  var x = 1
  print(!x, "\n")
}
{
  var x = "hello"
  print(!x, "\n")
}
{
  var x = ""
  print(!x, "\n")
}
{
  var x = Nir
  print(!x, "\n")
}
  )");

  EXPECT_EQ(getOutput(), R"(-10
-10.50000000000000
false
true
true
false
false
true
true
)");
}

TEST_F(DynamicTypeTest, DynamicMixedTypeExpressions) {
  I(R"(
{
  var x = 1 + "a"
  print(x, "\n")
}
{
  var x = "a" + 1
  print(x, "\n")
}
{
  var x = 1 + 2.5
  print(x, "\n")
}
{
  var x = true + 1
  print(x, "\n")
}
{
  var x = 1 + true
  print(x, "\n")
}
{
  var x = "a" + true
  print(x, "\n")
}
{
  var x = true + "a"
  print(x, "\n")
}
{
  var x = 1 + 2 + "a" + (3 + 4)
  print(x, "\n")
}
  )");

  EXPECT_EQ(getOutput(), R"(1a
a1
3.50000000000000
2
2
atrue
truea
3a7
)");
}

// TEST_F(DynamicTypeTest, DynamicClassMember) {
//   I(R"(
// class A {
//   var data
// }
// var obj = new A()
// obj.data = 10
// print(obj.data, "\n")
// obj.data = "hello"
// print(obj.data, "\n")
// obj.data = true
// print(obj.data, "\n")
// obj.data = Nir
// print(obj.data, "\n")
//   )");

//   EXPECT_EQ(getOutput(), R"(10
// hello
// true
// Nir
// )");
// }

TEST_F(DynamicTypeTest, FunctionCallWithConstant) {
  I(R"(

fun testFun(a) -> nthg {
  print(a, "\n")
}

testFun(10)
testFun("Hello")
testFun(10.2)
testFun(10.2d)
testFun(true)
testFun(false)
testFun(Nir)
  )");

  EXPECT_EQ(getOutput(), R"(10
Hello
10.20000000000000
10.1999998
true
false
(null)
)");
}

TEST_F(DynamicTypeTest, FunctionCallWithDynamicType) {
  I(R"(

fun testFun(a) -> nthg {
  print(a, "\n")
}

var x = 10
testFun(x)
var y = "Hello"
testFun(y)
var z = 10.2
testFun(z)
var w = 10.2d
testFun(w)
var a = true
testFun(a)
var b = false
testFun(b)
var c = Nir
testFun(c)
  )");

  EXPECT_EQ(getOutput(), R"(10
Hello
10.20000000000000
10.1999998
true
false
(null)
)");
}

TEST_F(DynamicTypeTest, PassingDynamicToFunction) {
  I(R"(

fun testFun(a) -> nthg {
  print(a, "\n")
}

var i: int = 10
testFun(i)
var j: str = "Hello"
testFun(j)
var k: deci = 10.2
testFun(k)
var e: deci32 = 10.2d
testFun(e)
var l: bool = true
testFun(l)
var m: bool = false
testFun(m)
  )");

  EXPECT_EQ(getOutput(), R"(10
Hello
10.20000000000000
10.1999998
true
false
)");
}

TEST_F(DynamicTypeTest, PassingByValue) {
  I(R"(

fun testFun(a) -> nthg {
  print(a, "\n")
  a = 30 
  print(a, "\n")
}

var x = 20
testFun(x)
print(x, "\n")
var y = "Hello"
testFun(y)
print(y, "\n")
var z = 30.2
testFun(z)
print(z, "\n")
var w = 30.2d
testFun(w)
print(w, "\n")
var v = true
testFun(v)
print(v, "\n")
var u = false
testFun(u)
print(u, "\n")
var j = Nir
testFun(j)
print(j, "\n")
  )");

  EXPECT_EQ(getOutput(), R"(20
30
20
Hello
30
Hello
30.20000000000000
30
30.20000000000000
30.2000008
30
30.2000008
true
30
true
false
30
false
(null)
30
(null)
)");
}

TEST_F(DynamicTypeTest, PassingByReference) {
  I(R"(
fun testFun(inout a) -> nthg {
  print(a, "\n")
  a = 30 
  print(a, "\n")
}

var x = 20
testFun(x)
print(x, "\n")
var y = "Hello"
testFun(y)
print(y, "\n")
var z = 30.2
testFun(z)
print(z, "\n")
var w = 30.2d
testFun(w)
print(w, "\n")
var v = true
testFun(v)
print(v, "\n")
var u = false
testFun(u)
print(u, "\n")
var j = Nir
testFun(j)
print(j, "\n")
  )");

  EXPECT_EQ(getOutput(), R"(20
30
30
Hello
30
30
30.20000000000000
30
30
30.2000008
30
30
true
30
30
false
30
30
(null)
30
30
)");
}

TEST_F(DynamicTypeTest, PassingByValueNonDynamic) {
  I(R"(
fun testFun(a) -> nthg {
  print(a, "\n")
  a = 30 
  print(a, "\n")
}

var x: int = 20
testFun(x)
print(x, "\n")
var y: str = "Hello"
testFun(y)
print(y, "\n")
var z: deci = 30.2
testFun(z)
print(z, "\n")
var w: deci32 = 30.2d
testFun(w)
print(w, "\n")
var v: bool = true
testFun(v)
print(v, "\n")
var u: bool = false
testFun(u)
print(u, "\n")
  )");

  EXPECT_EQ(getOutput(), R"(20
30
20
Hello
30
Hello
30.20000000000000
30
30.20000000000000
30.2000008
30
30.2000008
true
30
true
false
30
false
)");
}

TEST_F(DynamicTypeTest, PassingByReferenceNonDynamicNoEffect) {
  I(R"(
fun testFun(inout a) -> nthg {
  print(a, "\n")
  a = 30 
  print(a, "\n")
}

var x: int = 20
testFun(x)
print(x, "\n")
var y: str = "Hello"
testFun(y)
print(y, "\n")
var z: deci = 30.2
testFun(z)
print(z, "\n")
var w: deci32 = 30.2d
testFun(w)
print(w, "\n")
var v: bool = true
testFun(v)
print(v, "\n")
var u: bool = false
testFun(u)
print(u, "\n")
  )");

  EXPECT_EQ(getOutput(), R"(20
30
20
Hello
30
Hello
30.20000000000000
30
30.20000000000000
30.2000008
30
30.2000008
true
30
true
false
30
false
)");
}

TEST_F(DynamicTypeTest, WithOptionalParam) {
  I(R"(

fun test2(a: int, b: str, c = 2.2) -> nthg {
  print("A ", a, "\n")
  print("B ", b, "\n")
  print("C ", c, "\n")
}

test2(2, "3")
  )");

  EXPECT_EQ(getOutput(), R"(A 2
B 3
C 2.20000000000000
)");
}

TEST_F(DynamicTypeTest, WithOptionalParam2) {
  I(R"(

fun test2(a: int, b: str, c = 2.2) -> nthg {
  print("A ", a, "\n")
  print("B ", b, "\n")
  print("C ", c, "\n")
}

test2(2, "3", "Hello")
test2(2, "3", 2)
test2(2, "3", 3.5d)
test2(2, "3", 3.5)
test2(2, "3", true)
test2(2, "3", false)
test2(2, "3", Nir)
  )");

  EXPECT_EQ(getOutput(), R"(A 2
B 3
C Hello
A 2
B 3
C 2
A 2
B 3
C 3.5000000
A 2
B 3
C 3.50000000000000
A 2
B 3
C true
A 2
B 3
C false
A 2
B 3
C (null)
)");
}