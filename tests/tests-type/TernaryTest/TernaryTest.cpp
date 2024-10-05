#include "TernaryTest.h"

void TernaryTest::SetUp() { _test->SetUp(); }

void TernaryTest::TearDown() { _test->TearDown(); }

TEST_F(TernaryTest, BasicPrint) {
  I(R"(
print(true ? "Hello" : "Bye")
print(false ? "Hello" : "Bye")
print("Hello" ? "Hello" : "Bye")
print("Bye" ? "Hello" : "Bye")
print(1 ? "Hello" : "Bye")
print(0 ? "Hello" : "Bye")
print(1.5 ? "Hello" : "Bye")
print(0.5 ? "Hello" : "Bye")
print(0.0 ? "Hello" : "Bye")
print(1.0 ? "Hello" : "Bye")

    )");

  EXPECT_EQ(getOutput(), R"(HelloByeHelloHelloHelloByeHelloHelloByeHello)");
}

TEST_F(TernaryTest, BasicPrintTestWithBinaryOperatorsInt) {
  I(R"(
 
print((1 > 2) ? "Hello" : "Bye")
print((1 < 2) ? "Hello" : "Bye")
print((1 == 2) ? "Hello" : "Bye")
print((1 != 2) ? "Hello" : "Bye")
print((1 >= 2) ? "Hello" : "Bye")
print((1 <= 2) ? "Hello" : "Bye")
    )");

  EXPECT_EQ(getOutput(), R"(ByeHelloByeHelloByeHello)");
}
TEST_F(TernaryTest, BasicPrintTestWithBinaryOperatorsOtherTypes) {
  I(R"(

print((1 > 2) ? "Hello" : "Bye")
print(("Hl" == "hl") ? "Hello" : "Bye")
print(("Hl" == "Hl") ? "Hello" : "Bye")
print((2.2 == 2.2) ? "Hello" : "Bye")
print((2.2 != 2.2) ? "Hello" : "Bye")
print((false == false) ? "Hello" : "Bye")
print((false == true) ? "Hello" : "Bye")
    )");

  EXPECT_EQ(getOutput(), R"(ByeByeHelloHelloByeHelloBye)");
}

TEST_F(TernaryTest, VarDec) {
  I(R"(
var x:str = true ? "Hello" : "Bye"
var y:str = false ? "Hello" : "Bye"

print(x)
print(y)
    )");

  EXPECT_EQ(getOutput(), R"(HelloBye)");
}
TEST_F(TernaryTest, VarAssignment) {
  I(R"(
var x:str = true ? "Hello" : "Bye"
var y:str = false ? "Hello" : "Bye"

x = "Hello"
y = (1 == 1 )? "Hello" : "Bye"

print(x)
print(y)
    )");

  EXPECT_EQ(getOutput(), R"(HelloHello)");
}

TEST_F(TernaryTest, CallingFunctionAndRetruningObject) {
  I(R"(
type B ={
    s:int 
  }

fun printA() -> B {
    print("A ")
    return {s:0}
  }


fun printB() -> B {

    print("B")

    return {s:2} 
}

{
var g:int = 2 
 var x: B= ( (g==2) ? printA() : printB() )  

print(x)
}
    )");

  EXPECT_EQ(getOutput(), R"(A { s : 0 })");
}

TEST_F(TernaryTest, CallingFunctionAndRetruningObject2) {
  I(R"(
type B ={
    s:int 
  }
type D = {
    a:int,
    s:str
}
fun printA(d:D) -> B {
    print("A ",d)
    return {s:0}
  }


fun printB() -> B {

    print("B")

    return {s:2} 
}

{
var g:int = 2 
 var x: B= ( (g==2) ? printA({a:1,s:"hello"}) : printB() )  

print(x)

}
    )");

  EXPECT_EQ(getOutput(), R"(A { a : 1, s : 'hello' }{ s : 0 })");
}

TEST_F(TernaryTest, CallingFunctionAndRetruningObject3) {
  I(R"(
type B ={
    s:int 
  }
type D = {
    a:int,
    s:str
}
fun printA(d:D) -> B {
    print("A ",d)
    return {s:20}
  }


fun printB() -> B {

    print("B")

    return {s:2} 
}

{
var g:int = 2 
 var x: B
 
 x= ( (g==2) ? printA({a:1,s:"hello"}) : printB() )  

print(x)

}
    )");

  EXPECT_EQ(getOutput(), R"(A { a : 1, s : 'hello' }{ s : 20 })");
}
TEST_F(TernaryTest, CallingFunctionAndRetruningInt) {
  I(R"(

fun printA() -> int {
  
    return 2
  }


fun printB() -> int {

    return 3
}

{
var g:int = 3 
 var x: int= ( (g==2) ? printA() : printB() )  

print(x)
}


    )");

  EXPECT_EQ(getOutput(), R"(3)");
}

TEST_F(TernaryTest, CallingFunctionAndRetruningIntButAssignNothing) {
  I(R"(

fun printA() -> int {
  print("A")
    return 2
  }


fun printB() -> int {
  print("B")
    return 3
}

{
var g:int = 3 
 ( (g==2) ? printA() : printB() )  

}

    )");

  EXPECT_EQ(getOutput(), R"(B)");
}
// Global

TEST_F(TernaryTest, VarAssignmentGlobal) {
  I(R"(
var x:str = true ? "Hello" : "Bye"
var y:str = false ? "Hello" : "Bye"

x = "Hello"
y = (1 == 1 )? "Hello" : "Bye"

print(x)
print(y)
    )");

  EXPECT_EQ(getOutput(), R"(HelloHello)");
}

TEST_F(TernaryTest, CallingFunctionAndRetruningObjectGlobal) {
  I(R"(
type B ={
    s:int 
  }

fun printA() -> B {
    print("A ")
    return {s:0}
  }


fun printB() -> B {

    print("B")

    return {s:2} 
}

var g:int = 2 
 var x: B= ( (g==2) ? printA() : printB() )  

print(x)

    )");

  EXPECT_EQ(getOutput(), R"(A { s : 0 })");
}

TEST_F(TernaryTest, CallingFunctionAndRetruningObject2Global) {
  I(R"(
type B ={
    s:int 
  }
type D = {
    a:int,
    s:str
}
fun printA(d:D) -> B {
    print("A ",d)
    return {s:0}
  }


fun printB() -> B {

    print("B")

    return {s:2} 
}

var g:int = 2 
 var x: B= ( (g==2) ? printA({a:1,s:"hello"}) : printB() )  

print(x)

    )");

  EXPECT_EQ(getOutput(), R"(A { a : 1, s : 'hello' }{ s : 0 })");
}
TEST_F(TernaryTest, CallingFunctionAndRetruningObject2NoAssignment) {
  I(R"(
type B ={
    s:int 
  }
type D = {
    a:int,
    s:str
}
fun printA(d:D) -> B {
    print("A ",d)
    return {s:20}
  }


fun printB() -> int {

    print("B")

    return 2
}

{
var g:int = 2 

 
( (g==2) ? printA({a:1,s:"hello"}) : printB() )  


}
    )");

  EXPECT_EQ(getOutput(), R"(A { a : 1, s : 'hello' })");
}