#include "ObjectLocalTest.h"

ObjectLocalTest::ObjectLocalTest() { _test = std::move(FlowWing::getTest()); }

void ObjectLocalTest::SetUp() { _test->SetUp(); }

void ObjectLocalTest::TearDown() { _test->TearDown(); }

void ObjectLocalTest::setInput(const std::string &input) {
  _test->setInput(input);
}

std::string ObjectLocalTest::getOutput() const { return _test->getOutput(); }

void ObjectLocalTest::runEvaluator() { _test->runEvaluator(); }

#if defined(JIT_TEST_MODE) || defined(AOT_TEST_MODE)

// Declarations

TEST_F(ObjectLocalTest, ObjectLocalTest1) {
  I(R"(
    {
             type t1 = {
      a:str,
      b:int,
      c:deci,
      d:bool
     }

     var x:t1 = { 
       a:"hello",
       b:10,
       c:10.10,
       d:true
     }
     print(x)
    }
  )");
  O(R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true })");
}
TEST_F(ObjectLocalTest, ObjectLocalTest1Mix) {
  I(R"(

             type t1 = {
      a:str,
      b:int,
      c:deci,
      d:bool
     }
    {
     var x:t1 = { 
       a:"hello",
       b:10,
       c:10.10,
       d:true
     }
     print(x)
    }
  )");
  O(R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true })");
}

TEST_F(ObjectLocalTest, ObjectLocalTestDec) {
  I(R"(
     
     type parent = {
      pa:str,
      pb:int,
      pc:deci,
      pd:bool
     }

     type t1 = {
      a:str,
      b:int,
      c:deci,
      d:bool,
      p:parent
     }
    {

     var x:t1 = { 
       a:"hello",
       b:10,
       c:10.10,
       d:true
     }
     print(x)
    }
  )");
  O(R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : '', pb : 0, pc : 0.00000000000000, pd : false } })");
}

TEST_F(ObjectLocalTest, ObjectLocalTestDecUse) {
  I(R"(
     
    {
             type parent = {
      pa:str,
      pb:int,
      pc:deci,
      pd:bool
     }

     type t1 = {
      a:str,
      b:int,
      c:deci,
      d:bool,
      p:parent
     }

     var x:t1 = { 
       a:"hello",
       b:10,
       c:10.10,
       d:true,
       p:{ pa : "Hello" }
     }
     print(x)
    }
  )");
  O(R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : 'Hello', pb : 0, pc : 0.00000000000000, pd : false } })");
}

TEST_F(ObjectLocalTest, ObjectLocalTestDecUse2) {
  I(R"(
     
     type parent = {
      pa:str,
      pb:int,
      pc:deci,
      pd:bool
     }
    {

     type t1 = {
      a:str,
      b:int,
      c:deci,
      d:bool,
      p:parent
     }

     var x:t1 = { 
       a:"hello",
       b:10,
       c:10.10,
       d:true,
       p:{ pa : "hello", pb : 2, pc : 45.00000000000000, pd : true }
     }
     print(x)
    }
  )");
  O(R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : 'hello', pb : 2, pc : 45.00000000000000, pd : true } })");
}

TEST_F(ObjectLocalTest, ObjectLocalTestDecUse2Assign) {
  I(R"(
     
     type parent = {
      pa:str,
      pb:int,
      pc:deci,
      pd:bool
     }

     type t1 = {
      a:str,
      b:int,
      c:deci,
      d:bool,
      p:parent
     }

    {
             var x:t1 = { 
       a:"hello",
       b:10,
       c:10.10,
       d:true,
       p:{ pa : "hello", pb : 2, pc : -1 * 45.10000000000000, pd : true }
     }
     var y:t1 = x
     print(y)
    }
  )");
  O(R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : 'hello', pb : 2, pc : -45.10000000000000, pd : true } })");
}

TEST_F(ObjectLocalTest, ObjectLocalTestDecUse2AssignMix) {
  I(R"(
     
     type parent = {
      pa:str,
      pb:int,
      pc:deci,
      pd:bool
     }

     type t1 = {
      a:str,
      b:int,
      c:deci,
      d:bool,
      p:parent
     }


             var x:t1 = { 
       a:"hello",
       b:10,
       c:10.10,
       d:true,
       p:{ pa : "hello", pb : 2, pc : -1 * 45.10000000000000, pd : true }
     }
    {
     var y:t1 = x
     print(y)
    }
  )");
  O(R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : 'hello', pb : 2, pc : -45.10000000000000, pd : true } })");
}

TEST_F(ObjectLocalTest, ObjectLocalTestDecUse2AssignMix2) {
  I(R"(
     
     type parent = {
      pa:str,
      pb:int,
      pc:deci,
      pd:bool
     }

     type t1 = {
      a:str,
      b:int,
      c:deci,
      d:bool,
      p:parent
     }


             var x:t1 = { 
       a:"hello",
       b:10,
       c:10.10,
       d:true,
       p:{ pa : "hello", pb : 2, pc : -1 * 45.10000000000000, pd : true }
     }

     var y:t1 = x
         {
            print(y)
         }
  )");
  O(R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : 'hello', pb : 2, pc : -45.10000000000000, pd : true } })");
}

TEST_F(ObjectLocalTest, ObjectLocalTestDecUse2NoDec) {
  I(R"(
     
     type parent = {
      pa:str,
      pb:int,
      pc:deci,
      pd:bool
     }

     type t1 = {
      a:str,
      b:int,
      c:deci,
      d:bool,
      p:parent
     }

    {
             var x:t1 = { 
       a:"hello",
       b:10,
       c:10.10,
       d:true,
     }
     print(x)
    }
  )");
  O(R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : '', pb : 0, pc : 0.00000000000000, pd : false } })");
}

TEST_F(ObjectLocalTest, ObjectLocalTestDecUse2NoDecAssign1) {
  I(R"(
     
     type parent = {
      pa:str,
      pb:int,
      pc:deci,
      pd:bool
     }

     type t1 = {
      a:str,
      b:int,
      c:deci,
      d:bool,
      p:parent
     }

    {
             var x:t1 = { 
       a:"hello",
       b:10,
       c:10.10,
       d:true,
     }
    var y:t1 = x

     print(y)
    }
  )");
  O(R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : '', pb : 0, pc : 0.00000000000000, pd : false } })");
}

TEST_F(ObjectLocalTest, ObjectLocalTestDecUse2NoDecAssign1Mix) {
  I(R"(
     
     type parent = {
      pa:str,
      pb:int,
      pc:deci,
      pd:bool
     }

     type t1 = {
      a:str,
      b:int,
      c:deci,
      d:bool,
      p:parent
     }

    {
             var x:t1 = { 
       a:"hello",
       b:10,
       c:10.10,
       d:true,
     }
    {
    var y:t1 = x

     print(y)
    }
    }
  )");
  O(R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : '', pb : 0, pc : 0.00000000000000, pd : false } })");
}

TEST_F(ObjectLocalTest, ObjectLoneInt) {
  I(R"(
      type t1 = {
        a:int
      }

    {
      var x:t1 = {
        a:1
      } 

      print(x)
    }
    
  )");
  O(R"({ a : 1 })");
}

TEST_F(ObjectLocalTest, ObjectLoneDec) {
  I(R"(
      type t1 = {
        a:deci
      }

    {
      var x:t1 = {
        a:1.0
      }

      print(x)
    }


  )");
  O(R"({ a : 1.00000000000000 })");
}

TEST_F(ObjectLocalTest, ObjectLoneBool) {
  I(R"(
      type t1 = {
        a:bool
      }

    {
     var x:t1 = {
        a:true
      }

      print(x)
    }


  )");
  O(R"({ a : true })");
}

TEST_F(ObjectLocalTest, ObjectLoneStr) {
  I(R"(
      type t1 = {
        a:str
      }

    {
              var x:t1 = {
        a:"hello"
      }

      print(x)
    }


  )");
  O(R"({ a : 'hello' })");
}

// Dec Use Fun Start

TEST_F(ObjectLocalTest, ObjectLocalTest1Fun) {
  I(R"(
     type t1 = {
      a:str,
      b:int,
      c:deci,
      d:bool
     }
     fun mainTest() -> t1{
           var x:t1 = { 
       a:"hello",
       b:10,
       c:10.10,
       d:true
     }

     return x
     }

    {
             var u:t1 = mainTest()
     print(u)
    }
  )");
  O(R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true })");
}

TEST_F(ObjectLocalTest, ObjectLocalTestDecFun) {
  I(R"(
     
     type parent = {
      pa:str,
      pb:int,
      pc:deci,
      pd:bool
     }

     type t1 = {
      a:str,
      b:int,
      c:deci,
      d:bool,
      p:parent
     }

     fun mainTest() -> t1 {
           var x:t1 = { 
       a:"hello",
       b:10,
       c:10.10,
       d:true
     }
     return x
     }

    {
    var y:t1 = mainTest()
     print(y)
    }
  )");
  O(R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : '', pb : 0, pc : 0.00000000000000, pd : false } })");
}

TEST_F(ObjectLocalTest, ObjectLocalTestDecUseFun) {
  I(R"(
     
     type parent = {
      pa:str,
      pb:int,
      pc:deci,
      pd:bool
     }

     type t1 = {
      a:str,
      b:int,
      c:deci,
      d:bool,
      p:parent
     }

    fun mainTest() -> t1 {
           var x:t1 = { 
       a:"hello",
       b:10,
       c:10.10,
       d:true,
       p:{ pa : "Hello" }
     }
     return x
    }
    {
    var y:t1 = mainTest()

     print(y)
    }
  )");
  O(R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : 'Hello', pb : 0, pc : 0.00000000000000, pd : false } })");
}

TEST_F(ObjectLocalTest, ObjectLocalTestDecUse2Fun) {
  I(R"(
     
     type parent = {
      pa:str,
      pb:int,
      pc:deci,
      pd:bool
     }

     type t1 = {
      a:str,
      b:int,
      c:deci,
      d:bool,
      p:parent
     }
    fun mainTest() -> t1 {
           var x:t1 = { 
       a:"hello",
       b:10,
       c:10.10,
       d:true,
       p:{ pa : "hello", pb : 2, pc : 45.00000000000000, pd : true }
     }
     return x
    }
    {
     var y:t1 = mainTest()
     print(y)
    }
  )");
  O(R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : 'hello', pb : 2, pc : 45.00000000000000, pd : true } })");
}

TEST_F(ObjectLocalTest, ObjectLocalTestDecUse2AssignFun) {
  I(R"(
     
     type parent = {
      pa:str,
      pb:int,
      pc:deci,
      pd:bool
     }

     type t1 = {
      a:str,
      b:int,
      c:deci,
      d:bool,
      p:parent
     }
    
    fun mainTest() -> t1 {
           var x:t1 = { 
       a:"hello",
       b:10,
       c:10.10,
       d:true,
       p:{ pa : "hello", pb : 2, pc : -1 * 45.10000000000000, pd : true }
     }
             var y:t1 = x
     return y
    }

    {
    var z:t1 = mainTest()
     print(z)
    }
  )");
  O(R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : 'hello', pb : 2, pc : -45.10000000000000, pd : true } })");
}

TEST_F(ObjectLocalTest, ObjectLocalTestDecUse2NoDecFun) {
  I(R"(
     
     type parent = {
      pa:str,
      pb:int,
      pc:deci,
      pd:bool
     }

     type t1 = {
      a:str,
      b:int,
      c:deci,
      d:bool,
      p:parent
     }

      var x:t1 = { 
       a:"hello",
       b:10,
       c:10.10,
       d:true,
     }

      fun mainTest() -> t1 {
        return x
      }

    {
     var y:t1 =  mainTest()
     print(y)
    }
  )");
  O(R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : '', pb : 0, pc : 0.00000000000000, pd : false } })");
}

TEST_F(ObjectLocalTest, ObjectLocalTestDecUse2NoDecAssign1Fun) {
  I(R"(
     
     type parent = {
      pa:str,
      pb:int,
      pc:deci,
      pd:bool
     }

     type t1 = {
      a:str,
      b:int,
      c:deci,
      d:bool,
      p:parent
     }

    fun mainTest() -> t1 {
          var x:t1 = { 
       a:"hello",
       b:10,
       c:10.10,
       d:true,
     }
    var y:t1 = x
    return y
    }

    {
     var z:t1 =  mainTest()
     print(z)
    }
  )");
  O(R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : '', pb : 0, pc : 0.00000000000000, pd : false } })");
}

TEST_F(ObjectLocalTest, ObjectLocalTestDecUse2NoDecAssign1AvdFun) {
  I(R"(
     
     type parent = {
      pa:str,
      pb:int,
      pc:deci,
      pd:bool
     }

     type t1 = {
      a:str,
      b:int,
      c:deci,
      d:bool,
      p:parent
     }

    fun mainTest() -> parent {
          var x:t1 = { 
       a:"hello",
       b:10,
       c:10.10,
       d:true,
       p: {pa:"s",pb:1,pc:1.1,pd:true}
     }
    var y:t1 = x
    return y.p
    }

    {
            var z:parent =  mainTest()
     print(z)
    }
  )");
  O(R"({ pa : 's', pb : 1, pc : 1.10000000000000, pd : true })");
}

TEST_F(ObjectLocalTest, ObjectLoneIntFun) {
  I(R"(
      type t1 = {
        a:int
      }
  
      fun mainTest() -> t1 {
        var x:t1 = {
          a:1
        }  
      return x
      }

    {
              var y:t1 = mainTest()
      print(y)
    }
    
  )");
  O(R"({ a : 1 })");
}

TEST_F(ObjectLocalTest, ObjectLoneDecFun) {
  I(R"(
      type t1 = {
        a:deci
      }

      fun mainTest() -> t1 {
              var x:t1 = {
        a:1.0
      }
      return x
      }

    {
              var y:t1 = mainTest()
      print(y)
    }

  )");
  O(R"({ a : 1.00000000000000 })");
}

TEST_F(ObjectLocalTest, ObjectLoneBoolFun) {
  I(R"(
      type t1 = {
        a:bool
      }

      fun mainTest() -> t1 {
           var x:t1 = {
        a:true
      }
      return x
      }

    
    {
              var y:t1 = mainTest()
      print(y)
    }


  )");
  O(R"({ a : true })");
}

TEST_F(ObjectLocalTest, ObjectLoneStrFun) {
  I(R"(
      type t1 = {
        a:str
      }

    fun mainTest() -> t1 {
          var x:t1 = {
        a:"hello"
      }
      return x
    }

    {
            var y:t1 = mainTest()
      print(y)
    }


  )");
  O(R"({ a : 'hello' })");
}

// Dec Use Fun End

// Assignment

TEST_F(ObjectLocalTest, ObjectLoneIntAssign) {
  I(R"(
{
          type t1 = {
        a:int
      }

      var x:t1 = {
        a:1
      }

      var y:t1 = {
        a:2
      }
      print(y)
      y = x 
      print(y)
}
    
  )");
  O(R"({ a : 2 }{ a : 1 })");
}

TEST_F(ObjectLocalTest, ObjectLoneIntAssignMix) {
  I(R"(

          type t1 = {
        a:int
      }

      var x:t1 = {
        a:1
      }
{
      var y:t1 = {
        a:2
      }
      print(y)
      y = x 
      print(y)
}
    
  )");
  O(R"({ a : 2 }{ a : 1 })");
}

TEST_F(ObjectLocalTest, ObjectLoneIntAssignMix2) {
  I(R"(

          type t1 = {
        a:int
      }

      var x:t1 = {
        a:1
      }

      var y:t1 = {
        a:2
      }
      {
      print(y)
      y = x 

}
      print(y)
    
  )");
  O(R"({ a : 2 }{ a : 1 })");
}
TEST_F(ObjectLocalTest, ObjectLoneDecAssign) {
  I(R"(
      type t1 = {
        a:deci
      }

      var x:t1 = {
        a:1.0
      }

    {
              var y:t1 = {
        a:2.0
      }
      print(y)
      y = x 
      print(y)
    }

  )");
  O(R"({ a : 2.00000000000000 }{ a : 1.00000000000000 })");
}

TEST_F(ObjectLocalTest, ObjectLoneDecAssignMix1) {
  I(R"(
      type t1 = {
        a:deci
      }

      var x:t1 = {
        a:1.0
      }


              var y:t1 = {
        a:2.0
      }
          {
      print(y)
      y = x 
      print(y)

    }
  )");
  O(R"({ a : 2.00000000000000 }{ a : 1.00000000000000 })");
}

TEST_F(ObjectLocalTest, ObjectLoneBoolAssign) {
  I(R"(
    {
              type t1 = {
        a:bool
      }

      var x:t1 = {
        a:true
      }

      var y:t1 = {
        a:false
      }
      print(y)
      y = x 
      print(y)
    }
  )");
  O(R"({ a : false }{ a : true })");
}

TEST_F(ObjectLocalTest, ObjectLoneStrAssign) {
  I(R"(
    {
              type t1 = {
        a:str
      }

      var x:t1 = {
        a:"hello"
      }

      var y:t1 = {
        a:"world"
      }
      print(y)
      y = x 
      print(y)
    }
  )");
  O(R"({ a : 'world' }{ a : 'hello' })");
}

TEST_F(ObjectLocalTest, ObjectLocalTest1Assign) {
  I(R"(
     type t1 = {
      a:str,
      b:int,
      c:deci,
      d:bool
     }

     var x:t1 = { 
       a:"hello",
       b:10,
       c:10.10,
       d:true
     }
    {
            var y:t1  = {
      a:"world",
      b:20,
      c:20.20,
      d:false
    }

    y.a = x.a
    y.b = x.b
    y.c = x.c
    y.d = x.d
     print(y)
    }
  )");
  O(R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true })");
}

TEST_F(ObjectLocalTest, ObjectLocalTestDecAssign) {
  I(R"(
     
     type parent = {
      pa:str,
      pb:int,
      pc:deci,
      pd:bool
     }

     type t1 = {
      a:str,
      b:int,
      c:deci,
      d:bool,
      p:parent
     }

    {
             var x:t1 = { 
       a:"hello",
       b:10,
       c:10.10,
       d:true
     }
     var y:t1  = {
       a:"world",
       b:20,
       c:20.20,
       d:false
     }

     y.a = x.a
     y.b = x.b
     y.c = x.c
     y.d = x.d
     print(y)
     y.p.pa = x.p.pa
     y.p.pb = x.p.pb
     y.p.pc = x.p.pc
     y.p.pd = x.p.pd
     print(y)
    }
  )");
  O(R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : '', pb : 0, pc : 0.00000000000000, pd : false } }{ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : '', pb : 0, pc : 0.00000000000000, pd : false } })");
}

TEST_F(ObjectLocalTest, ObjectLocalTestDecUseAssign) {
  I(R"(
     
     type parent = {
      pa:str,
      pb:int,
      pc:deci,
      pd:bool
     }

     type t1 = {
      a:str,
      b:int,
      c:deci,
      d:bool,
      p:parent
     }

     var x:t1 = { 
       a:"hello",
       b:10,
       c:10.10,
       d:true,
       p:{ pa : "Hello" }
     }

     print(x)
    {
             x.p.pa = "w"
     x.p.pb = 2
     x.p.pc = 45.00000000000000
     x.p.pd = true
     print(x)
    }
  )");
  O(R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : 'Hello', pb : 0, pc : 0.00000000000000, pd : false } }{ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : 'w', pb : 2, pc : 45.00000000000000, pd : true } })");
}

TEST_F(ObjectLocalTest, ObjectLocalTestDecUseAssign2) {
  I(R"(
     
     type parent = {
      pa:str,
      pb:int,
      pc:deci,
      pd:bool
     }

     type t1 = {
      a:str,
      b:int,
      c:deci,
      d:bool,
      p:parent
     }

     var x:t1 = { 
       a:"hello",
       b:10,
       c:10.10,
       d:true,
       p:{ pa : "Hello" }
     }

    {
             print(x)
     x.p = { pa : "w", pb : 2, pc : 45.00000000000000, pd : true }
     print(x)
    }
  )");
  O(R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : 'Hello', pb : 0, pc : 0.00000000000000, pd : false } }{ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : 'w', pb : 2, pc : 45.00000000000000, pd : true } })");
}

TEST_F(ObjectLocalTest, ObjectLocalTestDecUseAssign2Mix) {
  I(R"(
     
     type parent = {
      pa:str,
      pb:int,
      pc:deci,
      pd:bool
     }

     type t1 = {
      a:str,
      b:int,
      c:deci,
      d:bool,
      p:parent
     }

    {
     var x:t1 = { 
       a:"hello",
       b:10,
       c:10.10,
       d:true,
       p:{ pa : "Hello" }
     }

             print(x)
     x.p = { pa : "w", pb : 2, pc : 45.00000000000000, pd : true }
     print(x)
    }
  )");
  O(R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : 'Hello', pb : 0, pc : 0.00000000000000, pd : false } }{ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : 'w', pb : 2, pc : 45.00000000000000, pd : true } })");
}

TEST_F(ObjectLocalTest, ObjectLocalTestDecUseAssign3) {
  I(R"(
     
     type parent = {
      pa:str,
      pb:int,
      pc:deci,
      pd:bool
     }

     type t1 = {
      a:str,
      b:int,
      c:deci,
      d:bool,
      p:parent
     }

     var x:t1 = { 
       a:"hello",
       b:10,
       c:10.10,
       d:true,
       p:{ pa : "Hello" }
     }

    {
             print(x)
     x.p = { pa : "w", pb : 2, pc : 45.00000000000000, pd : true }
     print(x)
     var y:t1 = { a : "hello2", b : 110, c : 110.10, d : true , p : { pa : "wj", pb : 20, pc : 47.00000000000000, pd : false } }
     print(y)
     y.p = x.p
     print(y)
    }
  )");
  O(R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : 'Hello', pb : 0, pc : 0.00000000000000, pd : false } }{ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : 'w', pb : 2, pc : 45.00000000000000, pd : true } }{ a : 'hello2', b : 110, c : 110.09999999999999, d : true, p : { pa : 'wj', pb : 20, pc : 47.00000000000000, pd : false } }{ a : 'hello2', b : 110, c : 110.09999999999999, d : true, p : { pa : 'w', pb : 2, pc : 45.00000000000000, pd : true } })");
}
TEST_F(ObjectLocalTest, ObjectLocalTestDecUseAssign3Mix1) {
  I(R"(
     
     type parent = {
      pa:str,
      pb:int,
      pc:deci,
      pd:bool
     }

     type t1 = {
      a:str,
      b:int,
      c:deci,
      d:bool,
      p:parent
     }

     var x:t1 = { 
       a:"hello",
       b:10,
       c:10.10,
       d:true,
       p:{ pa : "Hello" }
     }


             print(x)
     x.p = { pa : "w", pb : 2, pc : 45.00000000000000, pd : true }
     print(x)
     {
     var y:t1 = { a : "hello2", b : 110, c : 110.10, d : true , p : { pa : "wj", pb : 20, pc : 47.00000000000000, pd : false } }
     print(y)
     y.p = x.p
     print(y)
    }
  )");
  O(R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : 'Hello', pb : 0, pc : 0.00000000000000, pd : false } }{ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : 'w', pb : 2, pc : 45.00000000000000, pd : true } }{ a : 'hello2', b : 110, c : 110.09999999999999, d : true, p : { pa : 'wj', pb : 20, pc : 47.00000000000000, pd : false } }{ a : 'hello2', b : 110, c : 110.09999999999999, d : true, p : { pa : 'w', pb : 2, pc : 45.00000000000000, pd : true } })");
}
TEST_F(ObjectLocalTest, ObjectLocalTestDecUse2Assign2) {
  I(R"(
     
    {
             type parent = {
      pa:str,
      pb:int,
      pc:deci,
      pd:bool
     }

     type t1 = {
      a:str,
      b:int,
      c:deci,
      d:bool,
      p:parent
     }

     var x:t1 = { 
       a:"hello",
       b:10,
       c:10.10,
       d:true,
       p:{ pa : "hello", pb : 2, pc : 45.00000000000000, pd : true }
     }

     print(x)
     x.p = { pa : "w", pb : 2, pc : 45.00000000000000, pd : true }
     x.p.pa = "g"
     x.p.pd = false
     x.p.pb = 1
     x.p.pc = -1 * 45.10000000000000
     print(x)
    }
  )");
  O(R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : 'hello', pb : 2, pc : 45.00000000000000, pd : true } }{ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : 'g', pb : 1, pc : -45.10000000000000, pd : false } })");
}
TEST_F(ObjectLocalTest, ObjectLocalTestDecUse2Assign2Mix1) {
  I(R"(
     
    {
             type parent = {
      pa:str,
      pb:int,
      pc:deci,
      pd:bool
     }

     type t1 = {
      a:str,
      b:int,
      c:deci,
      d:bool,
      p:parent
     }

     var x:t1 = { 
       a:"hello",
       b:10,
       c:10.10,
       d:true,
       p:{ pa : "hello", pb : 2, pc : 45.00000000000000, pd : true }
     }

     print(x)
    {
           x.p = { pa : "w", pb : 2, pc : 45.00000000000000, pd : true }
     x.p.pa = "g"
     x.p.pd = false
     x.p.pb = 1
     x.p.pc = -1 * 45.10000000000000
    }
     print(x)
    }
  )");
  O(R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : 'hello', pb : 2, pc : 45.00000000000000, pd : true } }{ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : 'g', pb : 1, pc : -45.10000000000000, pd : false } })");
}
TEST_F(ObjectLocalTest, ObjectLocalTestDecUse2AssignAssign) {
  I(R"(
     
    {
             type parent = {
      pa:str,
      pb:int,
      pc:deci,
      pd:bool
     }

     type t1 = {
      a:str,
      b:int,
      c:deci,
      d:bool,
      p:parent
     }

     var x:t1 = { 
       a:"hello",
       b:10,
       c:10.10,
       d:true,
       p:{ pa : "hello", pb : 2, pc : -1 * 45.10000000000000, pd : true }
     }
     var y:t1 = { a : "hello2", b : 110, c : 110.10, d : true , p : { pa : "wj", pb : 20, pc : 47.00000000000000, pd : false } }
     print(x)
     print(y)
     x.p = y.p
     print(x)
     y = x
     print(y)
    }
  )");
  O(R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : 'hello', pb : 2, pc : -45.10000000000000, pd : true } }{ a : 'hello2', b : 110, c : 110.09999999999999, d : true, p : { pa : 'wj', pb : 20, pc : 47.00000000000000, pd : false } }{ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : 'wj', pb : 20, pc : 47.00000000000000, pd : false } }{ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : 'wj', pb : 20, pc : 47.00000000000000, pd : false } })");
}

TEST_F(ObjectLocalTest, ObjectLocalTestDecUse2NoDecAssign2) {
  I(R"(
     
     type parent = {
      pa:str,
      pb:int,
      pc:deci,
      pd:bool
     }

     type t1 = {
      a:str,
      b:int,
      c:deci,
      d:bool,
      p:parent
     }

    {
             var x:t1 = { 
       a:"hello",
       b:10,
       c:10.10,
       d:true,
     }
     x.p = { pa : "x", pb : 10, pc : 1.00000000000000, pd : true }
     print(x)
    }
  )");
  O(R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : 'x', pb : 10, pc : 1.00000000000000, pd : true } })");
}

TEST_F(ObjectLocalTest, ObjectLocalTestDecUse2NoDecAssign) {
  I(R"(
     
     type parent = {
      pa:str,
      pb:int,
      pc:deci,
      pd:bool
     }

     type t1 = {
      a:str,
      b:int,
      c:deci,
      d:bool,
      p:parent
     }

     var x:t1 = { 
       a:"hello",
       b:10,
       c:10.10,
       d:true,
     }
    {
            var y:t1 = x
    y.a = "hello2"
    y.b = 110
    y.c = 110.10
    y.d = true
    y.p.pa = "wj"
    y.p.pb = 20
    y.p.pc = 47.00000000000000
    y.p.pd = false
     print(x)
     print(y)
    }
  )");
  O(R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : '', pb : 0, pc : 0.00000000000000, pd : false } }{ a : 'hello2', b : 110, c : 110.09999999999999, d : true, p : { pa : 'wj', pb : 20, pc : 47.00000000000000, pd : false } })");
}

TEST_F(ObjectLocalTest, ObjectLocalTestDecUse2NoDecAssignFunAllIn) {
  I(R"(
     
         type parent = {
      pa:str,
      pb:int,
      pc:deci,
      pd:bool
     }
     type t1 = {
      a:str,
      b:int,
      c:deci,
      d:bool,
      p:parent
     }

     var x:t1 = { 
       a:"hello",
       b:10,
       c:10.10,
       d:true,
       p: {pa:"b",pb:1,pc:1.1,pd:true}
     }


    fun mainTest(y:t1) -> t1 {

      print(y)
          y.a = "hello2"
    y.b = 110
    y.c = 110.10
    y.d = true
    y.p.pa = "wj"
    y.p.pb = 20
    y.p.pc = 47.00000000000000
    y.p.pd = false
print("\n")
    return y
    }

    {
            var z:t1 =  {a:"gog",b:1,c:1.1,d:true}
    print(z)
    print("\n")
    z = mainTest(x)
     print(z)
    }

  )");
  O(R"({ a : 'gog', b : 1, c : 1.10000000000000, d : true, p : { pa : '', pb : 0, pc : 0.00000000000000, pd : false } }
{ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : 'b', pb : 1, pc : 1.10000000000000, pd : true } }
{ a : 'hello2', b : 110, c : 110.09999999999999, d : true, p : { pa : 'wj', pb : 20, pc : 47.00000000000000, pd : false } })");
}

// Functions

TEST_F(ObjectLocalTest, ObjectFunReturnObject1) {
  I(R"(
     
type t1 = {
      a:str
}

fun get() -> t1 {
      var x:t1 = {
            a:"h"
      }
      
      return x
}
print(get())
  )");
  O(R"({ a : 'h' })");
}

TEST_F(ObjectLocalTest, ObjectFunReturnObject2) {
  I(R"(
     
type t1 = {
      a:str
}

fun get() -> t1 {
      var x:t1 = {
            a:"h"
      }
      
      return x
}
print(get())
  )");
  O(R"({ a : 'h' })");
}

TEST_F(ObjectLocalTest, ObjectFunReturnObjectFull) {
  I(R"(
     
type t1 = {
      a:str,
      b:int,
      c:bool,
      d:deci
}

fun get() -> t1 {
      var x:t1 = {
            a:"h",
            b:1,
            c:true,
            d:2.0
      }
      
      return x
}
print(get())
  )");
  O(R"({ a : 'h', b : 1, c : true, d : 2.00000000000000 })");
}

TEST_F(ObjectLocalTest, ObjectFunReturnObjectFullDefault) {
  I(R"(
type t1 = {
      a:str,
      b:int,
      c:bool,
      d:deci
}

fun get() -> t1 {
      var x:t1 = {
      }
      
      return x
}
print(get())

  )");
  O(R"({ a : '', b : 0, c : false, d : 0.00000000000000 })");
}

TEST_F(ObjectLocalTest, ObjectFunReturnObjectFullDefaultWithParent) {
  I(R"(
type parent ={
      pa:int,
      pb:str,
      pc:bool,
      pd:deci
}

type t1 = {
      a:str,
      b:int,
      c:bool,
      d:deci,
      par:parent
}

fun get() -> t1 {
      var x:t1 = {
      }
      
      return x
}
print(get())

  )");
  O(R"({ a : '', b : 0, c : false, d : 0.00000000000000, par : { pa : 0, pb : '', pc : false, pd : 0.00000000000000 } })");
}

TEST_F(ObjectLocalTest, ObjectFunReturnObjectFullWithParentFull) {
  I(R"(
type parent ={
      pa:int,
      pb:str,
      pc:bool,
      pd:deci
}

type t1 = {
      a:str,
      b:int,
      c:bool,
      d:deci,
      par:parent
}

fun get() -> t1 {
      var x:t1 = {
            a:"hello",
            b:100,
            c:true,
            d:2.0,
            par:{pa:100,pb:"hello",pc:true,pd:2.0}
      }
      
      return x
}
print(get())

  )");
  O(R"({ a : 'hello', b : 100, c : true, d : 2.00000000000000, par : { pa : 100, pb : 'hello', pc : true, pd : 2.00000000000000 } })");
}

TEST_F(ObjectLocalTest, ObjectFunReturnObjectFullWithParentHalf) {
  I(R"(

type parent ={
      pa:int,
      pb:str,
      pc:bool,
      pd:deci
}

type t1 = {
      a:str,
      b:int,
      c:bool,
      d:deci,
      par:parent
}

fun get() -> t1 {
      var x:t1 = {
            a:"hello",
            b:100,
            c:true,
            d:2.0,
      }
      
      return x
}
print(get())

  )");
  O(R"({ a : 'hello', b : 100, c : true, d : 2.00000000000000, par : { pa : 0, pb : '', pc : false, pd : 0.00000000000000 } })");
}

//

TEST_F(ObjectLocalTest, ObjectFunReturnObjectOutside) {
  I(R"(
     
type t1 = {
      a:str
}
      var x:t1 = {
            a:"h"
      }
      
fun get() -> t1 {
      return x
}
print(get())
  )");
  O(R"({ a : 'h' })");
}

TEST_F(ObjectLocalTest, ObjectFunReturnObjectOutput) {
  I(R"(
     
type t1 = {
      a:str
}
      var x:t1 = {
            a:"h"
      }
fun get() -> t1 {

      
      return x
}
print(get())
  )");
  O(R"({ a : 'h' })");
}

TEST_F(ObjectLocalTest, ObjectFunReturnObjectFullOut) {
  I(R"(
     
type t1 = {
      a:str,
      b:int,
      c:bool,
      d:deci
}
      var x:t1 = {
            a:"h",
            b:1,
            c:true,
            d:2.0
      }
fun get() -> t1 {

      
      return x
}
print(get())
  )");
  O(R"({ a : 'h', b : 1, c : true, d : 2.00000000000000 })");
}

TEST_F(ObjectLocalTest, ObjectFunReturnObjectFullDefaultOut) {
  I(R"(
type t1 = {
      a:str,
      b:int,
      c:bool,
      d:deci
}
      var x:t1 = {
      }
      
fun get() -> t1 {

      return x
}
print(get())

  )");
  O(R"({ a : '', b : 0, c : false, d : 0.00000000000000 })");
}

TEST_F(ObjectLocalTest, ObjectFunReturnObjectFullDefaultWithParentOut) {
  I(R"(
type parent ={
      pa:int,
      pb:str,
      pc:bool,
      pd:deci
}

type t1 = {
      a:str,
      b:int,
      c:bool,
      d:deci,
      par:parent
}
      var x:t1 = {
      }
      
fun get() -> t1 {

      return x
}
print(get())

  )");
  O(R"({ a : '', b : 0, c : false, d : 0.00000000000000, par : { pa : 0, pb : '', pc : false, pd : 0.00000000000000 } })");
}

TEST_F(ObjectLocalTest, ObjectFunReturnObjectFullWithParentFullOut) {
  I(R"(
type parent ={
      pa:int,
      pb:str,
      pc:bool,
      pd:deci
}

type t1 = {
      a:str,
      b:int,
      c:bool,
      d:deci,
      par:parent
}
      var x:t1 = {
            a:"hello",
            b:100,
            c:true,
            d:2.0,
            par:{pa:100,pb:"hello",pc:true,pd:2.0}
      }
fun get() -> t1 {

      
      return x
}
print(get())

  )");
  O(R"({ a : 'hello', b : 100, c : true, d : 2.00000000000000, par : { pa : 100, pb : 'hello', pc : true, pd : 2.00000000000000 } })");
}

TEST_F(ObjectLocalTest, ObjectFunReturnObjectFullWithParentHalfOut) {
  I(R"(

type parent ={
      pa:int,
      pb:str,
      pc:bool,
      pd:deci
}

type t1 = {
      a:str,
      b:int,
      c:bool,
      d:deci,
      par:parent
}
      var x:t1 = {
            a:"hello",
            b:100,
            c:true,
            d:2.0,
      }
fun get() -> t1 {

      
      return x
}
print(get())

  )");
  O(R"({ a : 'hello', b : 100, c : true, d : 2.00000000000000, par : { pa : 0, pb : '', pc : false, pd : 0.00000000000000 } })");
}

//

TEST_F(ObjectLocalTest, ObjectFunReturnObjectOutsideUpdate) {
  I(R"(
     
type t1 = {
      a:str
}
      var x:t1 = {
            a:"h"
      }
      
fun get() -> t1 {
      x.a = "hello"
      return x
}
print(get())
  )");
  O(R"({ a : 'hello' })");
}

TEST_F(ObjectLocalTest, ObjectFunReturnObjectFullOutUpdate) {
  I(R"(
type t1 = {
      a:str,
      b:int,
      c:bool,
      d:deci
}
      var x:t1 = {
            a:"h",
            b:1,
            c:true,
            d:2.0
      }
fun get() -> t1 {
      x.a = "hello"
      x.b = 100
      x.c = false
      x.d = 100.0
      
      return x
}
print(get())
  )");
  O(R"({ a : 'hello', b : 100, c : false, d : 100.00000000000000 })");
}

TEST_F(ObjectLocalTest, ObjectFunReturnObjectFullOutUpdate2) {
  I(R"(
type t1 = {
      a:str,
      b:int,
      c:bool,
      d:deci
}
      var x:t1 = {
            a:"h",
            b:1,
            c:true,
            d:2.0
      }
fun get() -> t1 {
      var x:t1 = {
            a:"h3",
            b:12,
            c:false,
            d:3.0
      }
      
      return x
}
print(get())
  )");
  O(R"({ a : 'h3', b : 12, c : false, d : 3.00000000000000 })");
}

TEST_F(ObjectLocalTest, ObjectFunReturnObjectFullDefaultOutUpdate) {
  I(R"(
type t1 = {
      a:str,
      b:int,
      c:bool,
      d:deci
}
      var x:t1 = {
      }
      
fun get() -> t1 {
      x.a = "hello"
      x.b = 100
      x.c = true
      x.d = 10.0
      return x
}
print(get())

  )");
  O(R"({ a : 'hello', b : 100, c : true, d : 10.00000000000000 })");
}

TEST_F(ObjectLocalTest, ObjectFunReturnObjectFullDefaultWithParentOutUpdate) {
  I(R"(
type parent ={
      pa:int,
      pb:str,
      pc:bool,
      pd:deci
}

type t1 = {
      a:str,
      b:int,
      c:bool,
      d:deci,
      par:parent
}
      var x:t1 = {
      }
      
fun get() -> t1 {

      x.a = "hello"
      x.b = 100
      x.c = true
      x.d = 10.0
      x.par = {pa:1,pb:"hello",pc:true,pd:10.0}
      return x
}
print(get())
  )");
  O(R"({ a : 'hello', b : 100, c : true, d : 10.00000000000000, par : { pa : 1, pb : 'hello', pc : true, pd : 10.00000000000000 } })");
}

TEST_F(ObjectLocalTest, ObjectFunReturnObjectFullWithParentFullOutUpdate) {
  I(R"(
type parent ={
      pa:int,
      pb:str,
      pc:bool,
      pd:deci
}

type t1 = {
      a:str,
      b:int,
      c:bool,
      d:deci,
      par:parent
}
      var x:t1 = {
            a:"hello",
            b:100,
            c:true,
            d:2.0,
            par:{pa:100,pb:"hello",pc:true,pd:2.0}
      }
fun get() -> t1 {
      x.b = 200
      x.c = false
      x.d = 3.0
      x.par.pc = false
      x.par.pd = 3.0
      x.par.pa = 200
      
      return x
}
print(get())

  )");
  O(R"({ a : 'hello', b : 200, c : false, d : 3.00000000000000, par : { pa : 200, pb : 'hello', pc : false, pd : 3.00000000000000 } })");
}

TEST_F(ObjectLocalTest, ObjectFunReturnObjectFullWithParentHalfOutUpdate) {
  I(R"(
type parent ={
      pa:int,
      pb:str,
      pc:bool,
      pd:deci
}

type t1 = {
      a:str,
      b:int,
      c:bool,
      d:deci,
      par:parent
}
      var x:t1 = {
            a:"hello",
            b:100,
            c:true,
            d:2.0,
      }
fun get() -> t1 {
      x = {a:"hello",b:100,c:true,d:2.0,par:{pa:100,pb:"hello",pc:true,pd:2.0}}
      return x
}
print(get())
  )");
  O(R"({ a : 'hello', b : 100, c : true, d : 2.00000000000000, par : { pa : 100, pb : 'hello', pc : true, pd : 2.00000000000000 } })");
}

TEST_F(ObjectLocalTest, ObjectFunReturnObjectFullWithParentHalfOutUpdate5) {
  I(R"(
type parent ={
      pa:int,
      pb:str,
      pc:bool,
      pd:deci
}

type t1 = {
      a:str,
      b:int,
      c:bool,
      d:deci,
      par:parent
}
      var x:t1 = {
            a:"hello",
            b:100,
            c:true,
            d:2.0,
      }
fun get() -> t1 {
      x = {a:"hello",b:100,c:true,d:2.0,par:{pa:100,pb:"hello",pc:true,pd:2.0}}
      return x
}
print(get())
  )");
  O(R"({ a : 'hello', b : 100, c : true, d : 2.00000000000000, par : { pa : 100, pb : 'hello', pc : true, pd : 2.00000000000000 } })");
}

TEST_F(ObjectLocalTest, ObjectFunReturnObjectFullWithParentHalfOutUpdate5One) {
  I(R"(
type parent ={
      pa:int,
      pb:str,
      pc:bool,
      pd:deci
}

type t1 = {
      a:str,
      b:int,
      c:bool,
      d:deci,
      par:parent
}
fun get(y:t1) -> t1 {

      return y
}
var  x:t1 = {a:"hello",b:100,c:true,d:2.0,par:{pa:200,pb:"fso",pc:true,pd:3.0}}
print(get(x))
  )");
  O(R"({ a : 'hello', b : 100, c : true, d : 2.00000000000000, par : { pa : 200, pb : 'fso', pc : true, pd : 3.00000000000000 } })");
}

TEST_F(ObjectLocalTest,
       ObjectFunReturnObjectFullWithParentHalfOutUpdate5TwoUpdate5) {
  I(R"(
type parent ={
      pa:int,
      pb:str,
      pc:bool,
      pd:deci
}

type t1 = {
      a:str,
      b:int,
      c:bool,
      d:deci,
      par:parent
}
fun get(y:t1) -> t1 {
      y.par.pa = 545
      y.par.pb = "llo"
      y.par.pc = true
      return y
}
var  x:t1 = {a:"hello",b:100,c:true,d:2.0,par:{pa:200,pb:"fso",pc:true,pd:3.0}}
print(get(x))
  )");
  O(R"({ a : 'hello', b : 100, c : true, d : 2.00000000000000, par : { pa : 545, pb : 'llo', pc : true, pd : 3.00000000000000 } })");
}

TEST_F(ObjectLocalTest,
       ObjectFunReturnObjectFullWithParentHalfOutUpdate5TwoUpdate5Assign) {
  I(R"(
type parent ={
      pa:int,
      pb:str,
      pc:bool,
      pd:deci
}

type t1 = {
      a:str,
      b:int,
      c:bool,
      d:deci,
      par:parent
}
fun get(y:t1) -> t1 {
      y.par.pa = 545
      y.par.pb = "llo"
      y.par.pc = true
      return y
}
var  x:t1 = {a:"hello",b:100,c:true,d:2.0,par:{pa:200,pb:"fso",pc:true,pd:3.0}}
var z:t1 = get(x)
print(z)
  )");
  O(R"({ a : 'hello', b : 100, c : true, d : 2.00000000000000, par : { pa : 545, pb : 'llo', pc : true, pd : 3.00000000000000 } })");
}

TEST_F(ObjectLocalTest,
       ObjectFunReturnObjectFullWithParentHalfOutUpdate5TwoUpdate5AssignRe) {
  I(R"(
type parent ={
      pa:int,
      pb:str,
      pc:bool,
      pd:deci
}

type t1 = {
      a:str,
      b:int,
      c:bool,
      d:deci,
      par:parent
}
fun get(y:t1) -> t1 {
      y.par.pa = 545
      y.par.pb = "llo"
      y.par.pc = true
      return y
}
var  x:t1 = {a:"hello",b:100,c:true,d:2.0,par:{pa:200,pb:"fso",pc:true,pd:3.0}}
var z:t1 = {a:"string",b:500,c:true,d:5.0,par:{pa:700,pb:"fdso",pc:true,pd:4.0}}
print(z)
z = get(x)
print(z)
  )");
  O(R"({ a : 'string', b : 500, c : true, d : 5.00000000000000, par : { pa : 700, pb : 'fdso', pc : true, pd : 4.00000000000000 } }{ a : 'hello', b : 100, c : true, d : 2.00000000000000, par : { pa : 545, pb : 'llo', pc : true, pd : 3.00000000000000 } })");
}

#endif