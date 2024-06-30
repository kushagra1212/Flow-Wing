#include "MiscellaneousTest.h"

MiscellaneousTest::MiscellaneousTest() {
  _test = std::move(Tests::FlowWing::getTest());
}

void MiscellaneousTest::SetUp() { _test->SetUp(); }

void MiscellaneousTest::TearDown() { _test->TearDown(); }

void MiscellaneousTest::setInput(const std::string &input) {
  _test->setInput(input);
}

std::string MiscellaneousTest::getOutput() const { return _test->getOutput(); }

void MiscellaneousTest::runEvaluator() { _test->runEvaluator(); }

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
  O(R"({ a : 22 })");
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
  O(R"({ a : 22 })");
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
  O(R"({ a : 22 }{ a : 53 }2)");
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
  O(R"({ a : 22 }{ a : 53 }2)");
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
  O(R"({ a : 22 }{ a : 5 }2)");
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
  O(R"({ a : 22 }{ a : 5 }2)");
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
  O(R"({ a : 5 })");
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
  O(R"({ a : 5 })");
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
  O(R"([{ a : 5 }, { a : 10 }])");
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
  O(R"([{ a : 10 }, { a : 0 }])");
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
  O(R"([{ a : 11 }, { a : 0 }])");
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
  O(R"(B Class [{ a : 11 }, { a : 0 }])");
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
  O(R"(B Class [{ a : 11 }, { a : 0 }])");
}