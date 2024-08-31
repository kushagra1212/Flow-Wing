#include "MiscellaneousTest.h"

void MiscellaneousTest::SetUp() { _test->SetUp(); }

void MiscellaneousTest::TearDown() { _test->TearDown(); }

TEST_F(MiscellaneousTest, ClassesBasic1) {
  I(R"(type T = {
  a:int 
}

class A{
  var obj:T 

  init(obj:T) -> nthg {
    self.obj = obj 
  }
}

fun getA() -> A {
  

  return new A({a:22}) 
}

var a:A = getA()
print(a.obj))");
  EXPECT_EQ(getOutput(), R"({ a : 22 })");
}
TEST_F(MiscellaneousTest, ClassesBasic2) {
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
  var x:A = new A({a:22})

  return x 
}

var a:A = getA()
print(a.obj)

)");
  EXPECT_EQ(getOutput(), R"({ a : 22 })");
}
TEST_F(MiscellaneousTest, ClassesBasic3) {
  I(R"(
type T = {
  a:int 
}

class A{
  var obj:T 
  var r:int 
  var u:T 
  init(obj:T,r:int,u:T ) -> nthg {
    self.obj = obj 
  
    self.u =  u 
    self.r  =r
  }
}


fun getR() -> int {
    return 2 
  }
fun getU() -> T {
    return {a:53}
  }

fun getA() -> A {
  var x:A = new A({a:22},getR(),getU())

  return x 
}

var a:A = getA()
print(a.obj)
print(a.u)
print(a.r)
)");
  EXPECT_EQ(getOutput(), R"({ a : 22 }{ a : 53 }2)");
}
TEST_F(MiscellaneousTest, ClassesBasic4) {
  I(R"(
type T = {
  a:int 
}

class A{
  var obj:T 
  var r:int 
  var u:T 
  init(obj:T,r:int,u:T ) -> nthg {
    self.obj = obj 
  
    self.u =  u 
    self.r  =r
  }
}


fun getR(r:int ) -> int {
    return r 
  }
fun getU(u:T ) -> T {
    return u 
  }

fun getA() -> A {
  var x:A = new A({a:22},getR(2),getU({a:53}))

  return x 
}

var a:A = getA()
print(a.obj)
print(a.u)
print(a.r)
)");
  EXPECT_EQ(getOutput(), R"({ a : 22 }{ a : 53 }2)");
}
TEST_F(MiscellaneousTest, ClassesBasic5) {
  I(R"(
type T = {
  a:int 
}

class A{
  var obj:T 
  var r:int 
  var u:T 
  init(obj:T,r:int,u:T ) -> nthg {
    self.obj = obj 
  
    self.u =  u 
    self.r  =r
  }
}


fun getR(r:int ) -> int {
    return r 
  }
fun getU(u:T ) -> T {
    return u 
  }

fun getA() -> A {
  var x:A = new A({a:22},getR(2),getU({a:getR(5)}))

  return x 
}

var a:A = getA()
print(a.obj)
print(a.u)
print(a.r)
)");
  EXPECT_EQ(getOutput(), R"({ a : 22 }{ a : 5 }2)");
}
TEST_F(MiscellaneousTest, ClassesBasic6) {
  I(R"(
type T = {
  a:int 
}

class A{
  var obj:T 
  var r:int 
  var u:T 
  var ua:T[2]
  init(obj:T,r:int,u:T,ua:T[2] ) -> nthg {
    self.obj = obj 
  
    self.u =  u 
    self.r  =r

    self.ua = ua 
  }
}


fun getR(r:int ) -> int {
    return r 
  }
fun getU(u:T ) -> T {
    return u 
  }

fun getA() -> A {
  var x:A = new A({a:22},getR(2),getU({a:getR(5)}),[getU({a:getR(10)})])

  return x 
}

var a:A = getA()
print(a.obj)
print(a.u)
print(a.r)
)");
  EXPECT_EQ(getOutput(), R"({ a : 22 }{ a : 5 }2)");
}
TEST_F(MiscellaneousTest, Basic1) {
  I(R"(
type T = {
  a:int 
}

class A{
  var obj:T 
  var r:int 
  var u:T 
  var ua:T[2]
  init(obj:T,r:int,u:T,ua:T[2] ) -> nthg {
    self.obj = obj 
  
    self.u =  u 
    self.r  =r

    self.ua = ua 
  }
}


fun getR(r:int ) -> int {
    return r 
  }
fun getU(u:T ) -> T {
    return u 
  }
fun getUA(ua:T[2]) -> T[2] {
    return ua 
  }
fun getA() -> A {
  var x:A = new A({a:22},getR(2),getU({a:getR(5)}),getUA([getU({a:getR(10)})]))

  return x 
}

var i:T = {a:getR(5)}
print(i)
)");
  EXPECT_EQ(getOutput(), R"({ a : 5 })");
}
TEST_F(MiscellaneousTest, Basic2) {
  I(R"(
type T = {
  a:int 
}

class A{
  var obj:T 
  var r:int 
  var u:T 
  var ua:T[2]
  init(obj:T,r:int,u:T,ua:T[2] ) -> nthg {
    self.obj = obj 
  
    self.u =  u 
    self.r  =r

    self.ua = ua 
  }
}


fun getR(r:int ) -> int {
    return r 
  }
fun getU(u:T ) -> T {
    return u 
  }
fun getUA(ua:T[2]) -> T[2] {
    return ua 
  }
fun getA() -> A {
  var x:A = new A({a:22},getR(2),getU({a:getR(5)}),getUA([getU({a:getR(10)})]))

  return x 
}

var i:T = getU({a:getR(5)})
print(i)
)");
  EXPECT_EQ(getOutput(), R"({ a : 5 })");
}
TEST_F(MiscellaneousTest, Basic3) {
  I(R"(
type T = {
  a:int 
}

class A{
  var obj:T 
  var r:int 
  var u:T 
  var ua:T[2]
  init(obj:T,r:int,u:T,ua:T[2] ) -> nthg {
    self.obj = obj 
  
    self.u =  u 
    self.r  =r

    self.ua = ua 
  }
}


fun getR(r:int ) -> int {
    return r 
  }
fun getU(u:T ) -> T {
    return u 
  }
fun getUA(ua:T[2]) -> T[2] {
    return ua 
  }
fun getA() -> A {
  var x:A = new A({a:22},getR(2),getU({a:getR(5)}),getUA([getU({a:getR(10)})]))

  return x 
}


var uB:T[2] = [{a:getR(5)},getU({a:getR(10)})]
print(uB)
)");
  EXPECT_EQ(getOutput(), R"([{ a : 5 }, { a : 10 }])");
}
TEST_F(MiscellaneousTest, Basic4) {
  I(R"(
type T = {
  a:int 
}

class A{
  var obj:T 
  var r:int 
  var u:T 
  var ua:T[2]
  init(obj:T,r:int,u:T,ua:T[2] ) -> nthg {
    self.obj = obj 
  
    self.u =  u 
    self.r  =r

    self.ua = ua 
  }
}


fun getR(r:int ) -> int {
    return r 
  }
fun getU(u:T ) -> T {
    return u 
  }
fun getUA(ua:T[2]) -> T[2] {
    return ua 
  }
fun getA() -> A {
  var x:A = new A({a:22},getR(2),getU({a:getR(5)}),getUA([getU({a:getR(10)})]))

  return x 
}


var uB:T[2] = getUA([getU({a:getR(10)})]) 
print(uB)
)");
  EXPECT_EQ(getOutput(), R"([{ a : 10 }, { a : 0 }])");
}
TEST_F(MiscellaneousTest, Basic5) {
  I(R"(
type T = {
  a:int 
}

class A{
  var obj:T 
  var r:int 
  var u:T 
  var ua:T[2]
  init(obj:T,r:int,u:T,ua:T[2] ) -> nthg {
    self.obj = obj 
  
    self.u =  u 
    self.r  =r

    self.ua = ua 
  }
}


fun getR(r:int ) -> int {
    return r 
  }
fun getU(u:T ) -> T {
    return u 
  }
fun getUA(ua:T[2]) -> T[2] {
  var uu:T[2] = ([getU({a:getR(11)})]) 
    return uu 
  }
fun getA() -> A {
  var x:A = new A({a:22},getR(2),getU({a:getR(5)}),getUA([getU({a:getR(10)})]))

  return x 
}


var uB:T[2] = getUA([])

print(uB)
)");
  EXPECT_EQ(getOutput(), R"([{ a : 11 }, { a : 0 }])");
}
TEST_F(MiscellaneousTest, Basic6) {
  I(R"(
type T = {
  a:int 
}

class B {
    var className:str 


    init(cn:str) -> nthg {
        className  = cn 
      }

    getClassName() -> str {
        return className 
      }
  }

class A{
  var obj:T 
  var r:int 
  var u:T 
  var ua:T[2]

  init(obj:T,r:int,u:T,ua:T[2] ) -> nthg {
    self.obj = obj 
    var b:B = new B("B Class ")
    print(b.className)
 self.u =  u 
    self.r  =r

    self.ua = ua 
  }

  getR(r:int ) -> int {
    return r 
  }
getU(u:T ) -> T {
    return u 
  }
getUA(ua:T[2]) -> T[2] {
  var uu:T[2] = ([getU({a:getR(11)})]) 
    return uu 
  }

  printB() -> nthg{
    }

}

var a:A = new A({a:33},3,{},[])
print(a.getUA([]))
)");
  EXPECT_EQ(getOutput(), R"(B Class [{ a : 11 }, { a : 0 }])");
}

TEST_F(MiscellaneousTest, Basic7) {
  I(R"(
type T = {
  a:int 
}

class B {
    var className:str 


    init(cn:str) -> nthg {
        className  = cn 
      }

    getClassName() -> str {
        return className 
      }
  }

class A{
  var obj:T 
  var r:int 
  var u:T 
  var ua:T[2]

  init(obj:T,r:int,u:T,ua:T[2] ) -> nthg {
    self.obj = obj 
    var b:B = new B("B Class ")
    print(b.className)
 self.u =  u 
    self.r  =r

    self.ua = ua 
  }

  getR(r:int ) -> int {
    return r 
  }
getU(u:T ) -> T {
    return u 
  }
getUA(ua:T[2]) -> T[2] {
  var uu:T[2] = ([getU({a:getR(11)})]) 
    return uu 
  }

  printB() -> nthg{
    }

}

var a:A = new A({a:33},3,{},[])
print(a.getUA([]))
)");
  EXPECT_EQ(getOutput(), R"(B Class [{ a : 11 }, { a : 0 }])");
}

TEST_F(MiscellaneousTest, AssigningObjectPropertyUsingFunctionCall) {
  I(R"(
  class A {
type T ={
    white:int 
  }
getColor(r:int , g: int, b: int,  a:int ) -> int {
return (a*256*256*256 + b * 256 * 256 + g*256 + r ) 
}
var x:T 

init() -> nthg {
x = {
    white: getColor(255,255,255,255 )
  }
  }


}

var a:A  = new A()


print(a.x)
)");
  EXPECT_EQ(getOutput(), R"({ white : -1 })");
}

TEST_F(MiscellaneousTest, IfOrElseTestWithClassesSimple) {
  I(R"(
class A {
  var x:int 
  init(x:int) -> nthg {
      self.x = x 
    }
}

var a:A = new A(2)

if(a){
  print("A")
}
)");
  EXPECT_EQ(getOutput(), R"(A)");
}
TEST_F(MiscellaneousTest, IfOrElseTestWithClassesSimpleOrIF) {
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

TEST_F(MiscellaneousTest, IfOrElseTestWithClassesSimpleOrIFBinary) {
  I(R"(
class A {
  var x:int 
  init(x:int) -> nthg {
      self.x = x 
    }
}

var a:A = new A(2)

if(a && false){
  print("A")
}or if(a && true){
    print("or A")
  }
)");
  EXPECT_EQ(getOutput(), R"(or A)");
}
TEST_F(MiscellaneousTest, IfOrElseTestWithClassesSimpleOrIFUnary) {
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
}or if(a && true){
    print("or A")
  }
)");
  EXPECT_EQ(getOutput(), R"(or A)");
}
TEST_F(MiscellaneousTest, IfOrElseTestWithClassesSimpleOrIFUnaryWithoutNir) {
  I(R"(
class A {
  var x:int 
  init(x:int) -> nthg {
      self.x = x 
    }
}

var a:A 

if(!a){
  print("A")
}or if(a && true){
    print("or A")
  }
)");
  EXPECT_EQ(getOutput(), R"(A)");
}
TEST_F(MiscellaneousTest,
       IfOrElseTestWithClassesSimpleOrIFUnaryWithoutNirLogical) {
  I(R"(
class A {
  var x:int 
  init(x:int) -> nthg {
      self.x = x 
    }
}

var a:A 

if(a && 2){
  print("A")
}
)");
  EXPECT_EQ(getOutput(), R"()");
}
TEST_F(MiscellaneousTest,
       IfOrElseTestWithClassesSimpleOrIFUnaryWithoutNirLogical2) {
  I(R"(
class A {
  var x:int 
  init(x:int) -> nthg {
      self.x = x 
    }
}

var a:A 

if(a || 2){
  print("A")
}
)");
  EXPECT_EQ(getOutput(), R"(A)");
}
TEST_F(MiscellaneousTest,
       IfOrElseTestWithClassesSimpleOrIFUnaryWithoutNirLogical3) {
  I(R"(
class a {
  var x:int 
  init(x:int) -> nthg {
      self.x = x 
    }
}

var a:a  = new a(2)

if(a && 2){
  print("a")
}
)");
  EXPECT_EQ(getOutput(), R"(a)");
}
TEST_F(MiscellaneousTest, IfOrElseTestWithClassesSimpleOrIFUnaryWithNir) {
  I(R"(
class a {
  var x:int 
  init(x:int) -> nthg {
      self.x = x 
    }
}

var a:a  = new a(2)

if(a == Nir){
  print("a")
}
)");
  EXPECT_EQ(getOutput(), R"()");
}
TEST_F(MiscellaneousTest, IfOrElseTestWithClassesSimpleOrIFUnaryWithNir2) {
  I(R"(
class a {
  var x:int 
  init(x:int) -> nthg {
      self.x = x 
    }
}

var a:a  = new a(2)

if(a == Nir){
  print("a")
}
)");
  EXPECT_EQ(getOutput(), R"()");
}
TEST_F(MiscellaneousTest, IfOrElseTestWithClassesSimpleOrIFUnaryWithNir3) {
  I(R"(
class a {
  var x:int 
  init(x:int) -> nthg {
      self.x = x 
    }
}

var a:a  = new a(2)

if(a != Nir){
  print("a")
}
)");
  EXPECT_EQ(getOutput(), R"(a)");
}
TEST_F(MiscellaneousTest, IfOrElseTestWithClassesSimpleOrIFUnaryWithNir4) {
  I(R"(
class a {
  var x:int 
  init(x:int) -> nthg {
      self.x = x 
    }
}

var a:a 
if(a != Nir){
  print("a")
}
)");
  EXPECT_EQ(getOutput(), R"()");
}
TEST_F(MiscellaneousTest, OptionalArgumentsBasic) {
  I(R"(
fun test(a:int,b:int = 3 ,c:int = 2,d:deci = 3.3) -> nthg {
  
  print("a: ",a,b,c,d)
}

test(2,5,10)
)");
  EXPECT_EQ(getOutput(), R"(a: 25103.30000000000000)");
}
TEST_F(MiscellaneousTest, OptionalArgumentsBasic2) {
  I(R"(
fun test(a:int,b:int = 3 ,c:int = 2,d:deci = 3.3) -> nthg {
  
  print("a: ",a,b,c,d)
}

test(2)
)");
  EXPECT_EQ(getOutput(), R"(a: 2323.30000000000000)");
}
TEST_F(MiscellaneousTest, OptionalArgumentsBasicReturnCall) {
  I(R"(
fun test(a:int,b:int = 3 ,c:int = 2,d:deci = 3.3) -> deci  {
  
  print("a: ",a,b,c,d)
  return 2.3 
}

var e:deci = test(2)
print("\nE:",e)
)");
  EXPECT_EQ(getOutput(), R"(a: 2323.30000000000000
E:2.30000000000000)");
}
TEST_F(MiscellaneousTest, OptionalArgumentsBasicReturnCall2) {
  I(R"(
fun test(a:int,b:int = 3 ,c:int = 2,d:deci = 3.3) -> deci  {
  
  print("a: ",a,b,c,d)
  return 2.3 
}

var e:deci = test(2,100)
print("\nE:",e)
)");
  EXPECT_EQ(getOutput(), R"(a: 210023.30000000000000
E:2.30000000000000)");
}
TEST_F(MiscellaneousTest, OptionalArgumentsBasicReturnCall2WithPairReturn) {
  I(R"(
fun test(a:int,b:int = 3 ,c:int = 2,d:deci = 3.3) -> deci,str  {
  
  print("a: ",a,b,c,d)
  return 2.3,"Hello World"
}

var e:deci,s:str = test(2,100)
print("\nE:",e,s)
)");
  EXPECT_EQ(getOutput(), R"(a: 210023.30000000000000
E:2.30000000000000Hello World)");
}
TEST_F(MiscellaneousTest, NotUnaryOperationTest1) {
  I(R"(
var x:str 

if(!x){
    print("x",x)
  }
)");
  EXPECT_EQ(getOutput(), R"(x)");
}
TEST_F(MiscellaneousTest, NotUnaryOperationTest2) {
  I(R"(
var x:str = "" 

if(!x){
    print("x",x)
  }
)");
  EXPECT_EQ(getOutput(), R"(x)");
}
TEST_F(MiscellaneousTest, NotUnaryOperationTest3) {
  I(R"(
var x:str = "d" 

if(!x){
    print("x",x)
  }
)");
  EXPECT_EQ(getOutput(), R"()");
}
TEST_F(MiscellaneousTest, UnaryOperationTestIden1) {
  I(R"(
var x:str = "" 

if(x){
    print("x",x)
  }
)");
  EXPECT_EQ(getOutput(), R"()");
}
TEST_F(MiscellaneousTest, UnaryOperationTestIden2) {
  I(R"(
var x:str

if(x){
    print("x",x)
  }
)");
  EXPECT_EQ(getOutput(), R"()");
}
TEST_F(MiscellaneousTest, UnaryOperationTestIden3) {
  I(R"(
var x:str = "d" 

if(x){
    print("x",x)
  }
)");
  EXPECT_EQ(getOutput(), R"(xd)");
}
TEST_F(MiscellaneousTest, UnaryOperationEqTest1) {
  I(R"(
var x:str 

if(x == ""){
    print("x",x)
  }
)");
  EXPECT_EQ(getOutput(), R"(x)");
}
TEST_F(MiscellaneousTest, UnaryOperationEqTest2) {
  I(R"(
var x:str = ""

if(x == ""){
    print("x",x)
  }
)");
  EXPECT_EQ(getOutput(), R"(x)");
}
TEST_F(MiscellaneousTest, UnaryOperationEqTest3) {
  I(R"(
var x:str = "d"

if(x == ""){
    print("x",x)
  }
)");
  EXPECT_EQ(getOutput(), R"()");
}
TEST_F(MiscellaneousTest, UnaryOperationTest4) {
  I(R"(
var x:str = "" 

if(x != ""){
    print("x",x)
  }
)");
  EXPECT_EQ(getOutput(), R"()");
}
TEST_F(MiscellaneousTest, UnaryOperationTest5) {
  I(R"(
var x:str 

if(!x){
    print("x",x)
  }
)");
  EXPECT_EQ(getOutput(), R"(x)");
}
TEST_F(MiscellaneousTest, UnaryOperationTest6) {
  I(R"(
var x:str 

if(x ){
    print("x",x)
  }
)");
  EXPECT_EQ(getOutput(), R"()");
}