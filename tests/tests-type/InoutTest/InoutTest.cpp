#include "InoutTest.h"

InoutTest::InoutTest() { _test = std::move(FlowWing::getTest()); }

void InoutTest::SetUp() { _test->SetUp(); }

void InoutTest::TearDown() { _test->TearDown(); }

void InoutTest::setInput(const std::string &input) { _test->setInput(input); }

std::string InoutTest::getOutput() const { return _test->getOutput(); }

void InoutTest::runEvaluator() { _test->runEvaluator(); }

TEST_F(InoutTest, InoutTestArrayOfObject) {
  I(R"(
type K = {
  e:deci,
  s:str 
}

type T ={
a:int,
b:deci,
c:str,
d:K[2]
}

fun pa(inout a:T[2]) -> nthg {
  a[0].d[0].e = 10.1 
  print(a)
  print("\n")
}

var a:T[2] = [2 fill {c:"hi",a:2}]
print(a)
print("\n")
pa(a)
print(a)
    )");

  O(R"([{ a : 2, b : 0.00000000000000, c : 'hi', d : [{ e : 0.00000000000000, s : '' }, { e : 0.00000000000000, s : '' }] }, { a : 2, b : 0.00000000000000, c : 'hi', d : [{ e : 0.00000000000000, s : '' }, { e : 0.00000000000000, s : '' }] }]
[{ a : 2, b : 0.00000000000000, c : 'hi', d : [{ e : 10.10000000000000, s : '' }, { e : 0.00000000000000, s : '' }] }, { a : 2, b : 0.00000000000000, c : 'hi', d : [{ e : 0.00000000000000, s : '' }, { e : 0.00000000000000, s : '' }] }]
[{ a : 2, b : 0.00000000000000, c : 'hi', d : [{ e : 10.10000000000000, s : '' }, { e : 0.00000000000000, s : '' }] }, { a : 2, b : 0.00000000000000, c : 'hi', d : [{ e : 0.00000000000000, s : '' }, { e : 0.00000000000000, s : '' }] }])");
}

TEST_F(InoutTest, InoutTestObjectTest) {
  I(R"(
type K = {
  e:deci,
  s:str 
}

type T ={
a:int,
b:deci,
c:str,
d:K[2]
}

fun pa(inout a:T) -> nthg {
  a.d[0].e = 10.1 
  a.c = "yo"
  print(a)
  print("\n")
}

var a:T = {c:"hi",a:2}
print(a)
print("\n")
pa(a)
print(a)
    )");

  O(R"({ a : 2, b : 0.00000000000000, c : 'hi', d : [{ e : 0.00000000000000, s : '' }, { e : 0.00000000000000, s : '' }] }
{ a : 2, b : 0.00000000000000, c : 'yo', d : [{ e : 10.10000000000000, s : '' }, { e : 0.00000000000000, s : '' }] }
{ a : 2, b : 0.00000000000000, c : 'yo', d : [{ e : 10.10000000000000, s : '' }, { e : 0.00000000000000, s : '' }] })");
}

TEST_F(InoutTest, primitivesWithOutInOut) {
  I(R"(
type K = {
  e:deci,
  s:str 
}

type T ={
a:int,
b:deci,
c:str,
d:K[2]
}

fun pa(a:int,b:str,c:deci,d:bool) -> nthg {
  a = 2 
  b = "s"
  c = 2.3 
  d = false
  print(a)
print("\n")
print(b)
print("\n")
print(c)
print("\n")
print(d)
print("\n")
}

var a:int = 5 
var b:str = "h"
var c:deci = 3.3 
var d:bool = true 
print(a)
print("\n")
print(b)
print("\n")
print(c)
print("\n")
print(d)
print("\n")
pa(a,b,c,d)
print(a)
print("\n")
print(b)
print("\n")
print(c)
print("\n")
print(d)
    )");

  O(R"(5
h
3.30000000000000
true
2
s
2.30000000000000
false
5
h
3.30000000000000
true)");
}

TEST_F(InoutTest, primitivestInOut) {
  I(R"(
type K = {
  e:deci,
  s:str 
}

type T ={
a:int,
b:deci,
c:str,
d:K[2]
}

fun pa(inout a:int,inout b:str,inout c:deci,inout d:bool) -> nthg {
  a = 2 
  b = "s"
  c = 2.3 
  d = false
  print(a)
print("\n")
print(b)
print("\n")
print(c)
print("\n")
print(d)
print("\n")
}

var a:int = 5 
var b:str = "h"
var c:deci = 3.3 
var d:bool = true 
print(a)
print("\n")
print(b)
print("\n")
print(c)
print("\n")
print(d)
print("\n")
pa(a,b,c,d)
print(a)
print("\n")
print(b)
print("\n")
print(c)
print("\n")
print(d)
    )");

  O(R"(5
h
3.30000000000000
true
2
s
2.30000000000000
false
2
s
2.30000000000000
false)");
}

TEST_F(InoutTest, passingPrimitiveContansts) {
  I(R"(
type K = {
  e:deci,
  s:str 
}

type T ={
a:int,
b:deci,
c:str,
d:K[2]
}

fun pa( a:int,b:str, c:deci,d:bool) -> nthg {
  a = 2 
b = "s"
  c = 2.3 
  d = false
  print(a)
print("\n")
print(b)
print("\n")
print(c)
print("\n")
print(d)
print("\n")
}

var a:int = 5 
var b:str = "h"
var c:deci = 3.3 
var d:bool = true 
print(a)
print("\n")
print(b)
print("\n")
print(c)
print("\n")
print(d)
print("\n")
pa(2,"sw",3.3,false)
print(a)
print("\n")
print(b)
print("\n")
print(c)
print("\n")
print(d)
    )");

  O(R"(5
h
3.30000000000000
true
2
s
2.30000000000000
false
5
h
3.30000000000000
true)");
}

TEST_F(InoutTest, passingObjectExpressions) {
  I(R"(
type K = {
  e:deci,
  s:str 
}

type T ={
a:int,
b:deci,
c:str,
d:K[2]
}

fun pa( a:int,b:str, c:deci,d:bool,u:T) -> nthg {
  print(u)
  u.a = 32
  print("\n")
  print(u)
}


pa(2,"sw",3.3,false, {a:2}) 
    )");

  O(R"({ a : 2, b : 0.00000000000000, c : '', d : [{ e : 0.00000000000000, s : '' }, { e : 0.00000000000000, s : '' }] }
{ a : 32, b : 0.00000000000000, c : '', d : [{ e : 0.00000000000000, s : '' }, { e : 0.00000000000000, s : '' }] })");
}

TEST_F(InoutTest, passingArrayExpressions) {
  I(R"(
type K = {
  e:deci,
  s:str 
}

type T ={
a:int,
b:deci,
c:str,
d:K[2]
}

fun pa( a:int,b:str, c:deci,d:bool,u:T[2]) -> nthg {
  print(u)
  u[1].a = 32
  print("\n")
  print(u)
}


pa(2,"sw",3.3,false, [{c:"hio"}]) 
    )");

  O(R"([{ a : 0, b : 0.00000000000000, c : 'hio', d : [{ e : 0.00000000000000, s : '' }, { e : 0.00000000000000, s : '' }] }, { a : 0, b : 0.00000000000000, c : '', d : [{ e : 0.00000000000000, s : '' }, { e : 0.00000000000000, s : '' }] }]
[{ a : 0, b : 0.00000000000000, c : 'hio', d : [{ e : 0.00000000000000, s : '' }, { e : 0.00000000000000, s : '' }] }, { a : 32, b : 0.00000000000000, c : '', d : [{ e : 0.00000000000000, s : '' }, { e : 0.00000000000000, s : '' }] }])");
}

TEST_F(InoutTest, passingArrayExpressionsMix) {
  I(R"(
type K = {
  e:deci,
  s:str 
}

type T ={
a:int,
b:deci,
c:str,
d:K[2]
}

fun pa( a:int,b:str,inout c:deci,d:bool,inout u:T[2]) -> nthg {
  print(u)
  print(c)
  c = 2.2
  print(c)
  u[1].a = 32
  print("\n")
  print(u)
}


pa(2,"sw",3.3,false, [{c:"hio"}]) 
    )");

  O(R"([{ a : 0, b : 0.00000000000000, c : 'hio', d : [{ e : 0.00000000000000, s : '' }, { e : 0.00000000000000, s : '' }] }, { a : 0, b : 0.00000000000000, c : '', d : [{ e : 0.00000000000000, s : '' }, { e : 0.00000000000000, s : '' }] }]3.300000000000002.20000000000000
[{ a : 0, b : 0.00000000000000, c : 'hio', d : [{ e : 0.00000000000000, s : '' }, { e : 0.00000000000000, s : '' }] }, { a : 32, b : 0.00000000000000, c : '', d : [{ e : 0.00000000000000, s : '' }, { e : 0.00000000000000, s : '' }] }])");
}

TEST_F(InoutTest, passingClassUsingVariableInoutInParams) {
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


fun main(inout a:A) -> nthg {
  print(a.obj)
  a.obj.a = 21
}

var a:A = new A({a:100})

main(a)

print("After Pass\n")
print(a.obj)
    )");

  O(R"({ a : 100 }After Pass
{ a : 21 })");
}

TEST_F(InoutTest, passingClassUsingVariableWithOutInoutInParams) {
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


fun main( a:A) -> nthg {
  print(a.obj)
  a.obj.a = 21
}

var a:A = new A({a:100})

main(a)

print("After Pass\n")
print(a.obj)
    )");

  O(R"({ a : 100 }After Pass
{ a : 100 })");
}