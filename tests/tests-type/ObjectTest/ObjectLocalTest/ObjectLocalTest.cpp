#include "ObjectLocalTest.h"

void ObjectLocalTest::SetUp() { _test->SetUp(); }

void ObjectLocalTest::TearDown() { _test->TearDown(); }

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
  EXPECT_EQ(getOutput(),
            R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true })");
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
  EXPECT_EQ(getOutput(),
            R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true })");
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
  EXPECT_EQ(
      getOutput(),
      R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : '', pb : 0, pc : 0.00000000000000, pd : false } })");
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
  EXPECT_EQ(
      getOutput(),
      R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : 'Hello', pb : 0, pc : 0.00000000000000, pd : false } })");
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
  EXPECT_EQ(
      getOutput(),
      R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : 'hello', pb : 2, pc : 45.00000000000000, pd : true } })");
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
  EXPECT_EQ(
      getOutput(),
      R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : 'hello', pb : 2, pc : -45.10000000000000, pd : true } })");
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
  EXPECT_EQ(
      getOutput(),
      R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : 'hello', pb : 2, pc : -45.10000000000000, pd : true } })");
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
  EXPECT_EQ(
      getOutput(),
      R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : 'hello', pb : 2, pc : -45.10000000000000, pd : true } })");
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
  EXPECT_EQ(
      getOutput(),
      R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : '', pb : 0, pc : 0.00000000000000, pd : false } })");
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
  EXPECT_EQ(
      getOutput(),
      R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : '', pb : 0, pc : 0.00000000000000, pd : false } })");
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
  EXPECT_EQ(
      getOutput(),
      R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : '', pb : 0, pc : 0.00000000000000, pd : false } })");
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
  EXPECT_EQ(getOutput(), R"({ a : 1 })");
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
  EXPECT_EQ(getOutput(), R"({ a : 1.00000000000000 })");
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
  EXPECT_EQ(getOutput(), R"({ a : true })");
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
  EXPECT_EQ(getOutput(), R"({ a : 'hello' })");
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
  EXPECT_EQ(getOutput(),
            R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true })");
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
  EXPECT_EQ(
      getOutput(),
      R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : '', pb : 0, pc : 0.00000000000000, pd : false } })");
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
  EXPECT_EQ(
      getOutput(),
      R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : 'Hello', pb : 0, pc : 0.00000000000000, pd : false } })");
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
  EXPECT_EQ(
      getOutput(),
      R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : 'hello', pb : 2, pc : 45.00000000000000, pd : true } })");
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
  EXPECT_EQ(
      getOutput(),
      R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : 'hello', pb : 2, pc : -45.10000000000000, pd : true } })");
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
  EXPECT_EQ(
      getOutput(),
      R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : '', pb : 0, pc : 0.00000000000000, pd : false } })");
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
  EXPECT_EQ(
      getOutput(),
      R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : '', pb : 0, pc : 0.00000000000000, pd : false } })");
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
  EXPECT_EQ(getOutput(),
            R"({ pa : 's', pb : 1, pc : 1.10000000000000, pd : true })");
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
  EXPECT_EQ(getOutput(), R"({ a : 1 })");
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
  EXPECT_EQ(getOutput(), R"({ a : 1.00000000000000 })");
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
  EXPECT_EQ(getOutput(), R"({ a : true })");
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
  EXPECT_EQ(getOutput(), R"({ a : 'hello' })");
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
  EXPECT_EQ(getOutput(), R"({ a : 2 }{ a : 1 })");
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
  EXPECT_EQ(getOutput(), R"({ a : 2 }{ a : 1 })");
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
  EXPECT_EQ(getOutput(), R"({ a : 2 }{ a : 1 })");
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
  EXPECT_EQ(getOutput(), R"({ a : 2.00000000000000 }{ a : 1.00000000000000 })");
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
  EXPECT_EQ(getOutput(), R"({ a : 2.00000000000000 }{ a : 1.00000000000000 })");
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
  EXPECT_EQ(getOutput(), R"({ a : false }{ a : true })");
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
  EXPECT_EQ(getOutput(), R"({ a : 'world' }{ a : 'hello' })");
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
  EXPECT_EQ(getOutput(),
            R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true })");
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
  EXPECT_EQ(
      getOutput(),
      R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : '', pb : 0, pc : 0.00000000000000, pd : false } }{ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : '', pb : 0, pc : 0.00000000000000, pd : false } })");
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
  EXPECT_EQ(
      getOutput(),
      R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : 'Hello', pb : 0, pc : 0.00000000000000, pd : false } }{ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : 'w', pb : 2, pc : 45.00000000000000, pd : true } })");
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
  EXPECT_EQ(
      getOutput(),
      R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : 'Hello', pb : 0, pc : 0.00000000000000, pd : false } }{ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : 'w', pb : 2, pc : 45.00000000000000, pd : true } })");
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
  EXPECT_EQ(
      getOutput(),
      R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : 'Hello', pb : 0, pc : 0.00000000000000, pd : false } }{ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : 'w', pb : 2, pc : 45.00000000000000, pd : true } })");
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
  EXPECT_EQ(
      getOutput(),
      R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : 'Hello', pb : 0, pc : 0.00000000000000, pd : false } }{ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : 'w', pb : 2, pc : 45.00000000000000, pd : true } }{ a : 'hello2', b : 110, c : 110.09999999999999, d : true, p : { pa : 'wj', pb : 20, pc : 47.00000000000000, pd : false } }{ a : 'hello2', b : 110, c : 110.09999999999999, d : true, p : { pa : 'w', pb : 2, pc : 45.00000000000000, pd : true } })");
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
  EXPECT_EQ(
      getOutput(),
      R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : 'Hello', pb : 0, pc : 0.00000000000000, pd : false } }{ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : 'w', pb : 2, pc : 45.00000000000000, pd : true } }{ a : 'hello2', b : 110, c : 110.09999999999999, d : true, p : { pa : 'wj', pb : 20, pc : 47.00000000000000, pd : false } }{ a : 'hello2', b : 110, c : 110.09999999999999, d : true, p : { pa : 'w', pb : 2, pc : 45.00000000000000, pd : true } })");
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
  EXPECT_EQ(
      getOutput(),
      R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : 'hello', pb : 2, pc : 45.00000000000000, pd : true } }{ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : 'g', pb : 1, pc : -45.10000000000000, pd : false } })");
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
  EXPECT_EQ(
      getOutput(),
      R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : 'hello', pb : 2, pc : 45.00000000000000, pd : true } }{ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : 'g', pb : 1, pc : -45.10000000000000, pd : false } })");
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
  EXPECT_EQ(
      getOutput(),
      R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : 'hello', pb : 2, pc : -45.10000000000000, pd : true } }{ a : 'hello2', b : 110, c : 110.09999999999999, d : true, p : { pa : 'wj', pb : 20, pc : 47.00000000000000, pd : false } }{ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : 'wj', pb : 20, pc : 47.00000000000000, pd : false } }{ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : 'wj', pb : 20, pc : 47.00000000000000, pd : false } })");
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
  EXPECT_EQ(
      getOutput(),
      R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : 'x', pb : 10, pc : 1.00000000000000, pd : true } })");
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
  EXPECT_EQ(
      getOutput(),
      R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : '', pb : 0, pc : 0.00000000000000, pd : false } }{ a : 'hello2', b : 110, c : 110.09999999999999, d : true, p : { pa : 'wj', pb : 20, pc : 47.00000000000000, pd : false } })");
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
  EXPECT_EQ(
      getOutput(),
      R"({ a : 'gog', b : 1, c : 1.10000000000000, d : true, p : { pa : '', pb : 0, pc : 0.00000000000000, pd : false } }
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
  EXPECT_EQ(getOutput(), R"({ a : 'h' })");
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
  EXPECT_EQ(getOutput(), R"({ a : 'h' })");
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
  EXPECT_EQ(getOutput(),
            R"({ a : 'h', b : 1, c : true, d : 2.00000000000000 })");
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
  EXPECT_EQ(getOutput(),
            R"({ a : '', b : 0, c : false, d : 0.00000000000000 })");
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
  EXPECT_EQ(
      getOutput(),
      R"({ a : '', b : 0, c : false, d : 0.00000000000000, par : { pa : 0, pb : '', pc : false, pd : 0.00000000000000 } })");
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
  EXPECT_EQ(
      getOutput(),
      R"({ a : 'hello', b : 100, c : true, d : 2.00000000000000, par : { pa : 100, pb : 'hello', pc : true, pd : 2.00000000000000 } })");
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
  EXPECT_EQ(
      getOutput(),
      R"({ a : 'hello', b : 100, c : true, d : 2.00000000000000, par : { pa : 0, pb : '', pc : false, pd : 0.00000000000000 } })");
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
  EXPECT_EQ(getOutput(), R"({ a : 'h' })");
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
  EXPECT_EQ(getOutput(), R"({ a : 'h' })");
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
  EXPECT_EQ(getOutput(),
            R"({ a : 'h', b : 1, c : true, d : 2.00000000000000 })");
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
  EXPECT_EQ(getOutput(),
            R"({ a : '', b : 0, c : false, d : 0.00000000000000 })");
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
  EXPECT_EQ(
      getOutput(),
      R"({ a : '', b : 0, c : false, d : 0.00000000000000, par : { pa : 0, pb : '', pc : false, pd : 0.00000000000000 } })");
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
  EXPECT_EQ(
      getOutput(),
      R"({ a : 'hello', b : 100, c : true, d : 2.00000000000000, par : { pa : 100, pb : 'hello', pc : true, pd : 2.00000000000000 } })");
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
  EXPECT_EQ(
      getOutput(),
      R"({ a : 'hello', b : 100, c : true, d : 2.00000000000000, par : { pa : 0, pb : '', pc : false, pd : 0.00000000000000 } })");
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
  EXPECT_EQ(getOutput(), R"({ a : 'hello' })");
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
  EXPECT_EQ(getOutput(),
            R"({ a : 'hello', b : 100, c : false, d : 100.00000000000000 })");
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
  EXPECT_EQ(getOutput(),
            R"({ a : 'h3', b : 12, c : false, d : 3.00000000000000 })");
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
  EXPECT_EQ(getOutput(),
            R"({ a : 'hello', b : 100, c : true, d : 10.00000000000000 })");
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
  EXPECT_EQ(
      getOutput(),
      R"({ a : 'hello', b : 100, c : true, d : 10.00000000000000, par : { pa : 1, pb : 'hello', pc : true, pd : 10.00000000000000 } })");
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
  EXPECT_EQ(
      getOutput(),
      R"({ a : 'hello', b : 200, c : false, d : 3.00000000000000, par : { pa : 200, pb : 'hello', pc : false, pd : 3.00000000000000 } })");
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
  EXPECT_EQ(
      getOutput(),
      R"({ a : 'hello', b : 100, c : true, d : 2.00000000000000, par : { pa : 100, pb : 'hello', pc : true, pd : 2.00000000000000 } })");
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
  EXPECT_EQ(
      getOutput(),
      R"({ a : 'hello', b : 100, c : true, d : 2.00000000000000, par : { pa : 100, pb : 'hello', pc : true, pd : 2.00000000000000 } })");
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
  EXPECT_EQ(
      getOutput(),
      R"({ a : 'hello', b : 100, c : true, d : 2.00000000000000, par : { pa : 200, pb : 'fso', pc : true, pd : 3.00000000000000 } })");
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
  EXPECT_EQ(
      getOutput(),
      R"({ a : 'hello', b : 100, c : true, d : 2.00000000000000, par : { pa : 545, pb : 'llo', pc : true, pd : 3.00000000000000 } })");
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
  EXPECT_EQ(
      getOutput(),
      R"({ a : 'hello', b : 100, c : true, d : 2.00000000000000, par : { pa : 545, pb : 'llo', pc : true, pd : 3.00000000000000 } })");
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
  EXPECT_EQ(
      getOutput(),
      R"({ a : 'string', b : 500, c : true, d : 5.00000000000000, par : { pa : 700, pb : 'fdso', pc : true, pd : 4.00000000000000 } }{ a : 'hello', b : 100, c : true, d : 2.00000000000000, par : { pa : 545, pb : 'llo', pc : true, pd : 3.00000000000000 } })");
}

// Array Inside objects

TEST_F(ObjectLocalTest, ArrayInObjectPropertySingleDimensionExpressionIn) {
  I(R"(
{
       type t1 = {
       x:int[10]
     }
    var y:t1 = {
      x:[1,2,3,4,5,6,7,8,9]
    }

    print(y)    
}
  )");
  EXPECT_EQ(getOutput(), R"({ x : [1, 2, 3, 4, 5, 6, 7, 8, 9, 0] })");
}

TEST_F(ObjectLocalTest, ArrayInObjectPropertySingleDimensionExpressionInMix) {
  I(R"(

       type t1 = {
       x:int[10]
     }
     {
    var y:t1 = {
      x:[1,2,3,4,5,6,7,8,9]
    }

    print(y)    
}
  )");
  EXPECT_EQ(getOutput(), R"({ x : [1, 2, 3, 4, 5, 6, 7, 8, 9, 0] })");
}

TEST_F(ObjectLocalTest, ArrayInObjectPropertySingleDimensionExpressionMultiIn) {
  I(R"(
{
       type t1 = {
       x:int[10][5]
     }
    var y:t1 = {
      x:[1,2,3,4,5,6,7,8,9]
    }

    print(y)  
}   
  )");
  EXPECT_EQ(
      getOutput(),
      R"({ x : [[1, 0, 0, 0, 0], [2, 0, 0, 0, 0], [3, 0, 0, 0, 0], [4, 0, 0, 0, 0], [5, 0, 0, 0, 0], [6, 0, 0, 0, 0], [7, 0, 0, 0, 0], [8, 0, 0, 0, 0], [9, 0, 0, 0, 0], [0, 0, 0, 0, 0]] })");
}

TEST_F(ObjectLocalTest, ArrayInObjectPropertySingleDimensionFillExpressionIn) {
  I(R"(
{
       type t1 = {
       x:int[10]
     }
    var y:t1 = {
      x:[5 fill 5]
    }

    print(y)    
}
  )");
  EXPECT_EQ(getOutput(), R"({ x : [5, 5, 5, 5, 5, 0, 0, 0, 0, 0] })");
}

TEST_F(ObjectLocalTest, ArrayInObjectPropertySingleDimensionUsingVariableIn) {
  I(R"(
{
       type t1 = {
       x:int[10]
     }

    var z:int[10] = [1,2,3,4,5,6,7,8]
    
    var y:t1 = {
      x:z
    }

    print(y)    
}
  )");
  EXPECT_EQ(getOutput(), R"({ x : [1, 2, 3, 4, 5, 6, 7, 8, 0, 0] })");
}

TEST_F(ObjectLocalTest,
       ArrayInObjectPropertySingleDimensionUsingVariableMultiIn) {
  I(R"(
{
       type t1 = {
       x:int[10][5]
     }

    var z:int[10][5] = [5 fill 10]
    
    var y:t1 = {
      x:z
    }

    print(y)  
}  
  )");
  EXPECT_EQ(
      getOutput(),
      R"({ x : [[10, 10, 10, 10, 10], [0, 0, 0, 0, 0], [0, 0, 0, 0, 0], [0, 0, 0, 0, 0], [0, 0, 0, 0, 0], [0, 0, 0, 0, 0], [0, 0, 0, 0, 0], [0, 0, 0, 0, 0], [0, 0, 0, 0, 0], [0, 0, 0, 0, 0]] })");
}

TEST_F(ObjectLocalTest,
       ArrayInObjectPropertySingleDimensionUsingVariableMultiInMix) {
  I(R"(

       type t1 = {
       x:int[10][5]
     }

    var z:int[10][5] = [5 fill 10]
    {
    var y:t1 = {
      x:z
    }

    print(y)  
}  
  )");
  EXPECT_EQ(
      getOutput(),
      R"({ x : [[10, 10, 10, 10, 10], [0, 0, 0, 0, 0], [0, 0, 0, 0, 0], [0, 0, 0, 0, 0], [0, 0, 0, 0, 0], [0, 0, 0, 0, 0], [0, 0, 0, 0, 0], [0, 0, 0, 0, 0], [0, 0, 0, 0, 0], [0, 0, 0, 0, 0]] })");
}

TEST_F(ObjectLocalTest,
       ArrayInObjectPropertySingleDimensionUsingVariableMulti2In) {
  I(R"(
{
       type t1 = {
       x:int[10][5]
     }

    var z:int[10][5] = [1,2,3,4,5,6,7,8]
    
    var y:t1 = {
      x:z
    }

    print(y)   
} 
  )");
  EXPECT_EQ(
      getOutput(),
      R"({ x : [[1, 0, 0, 0, 0], [2, 0, 0, 0, 0], [3, 0, 0, 0, 0], [4, 0, 0, 0, 0], [5, 0, 0, 0, 0], [6, 0, 0, 0, 0], [7, 0, 0, 0, 0], [8, 0, 0, 0, 0], [0, 0, 0, 0, 0], [0, 0, 0, 0, 0]] })");
}

TEST_F(ObjectLocalTest,
       ArrayInObjectPropertySingleDimensionUsingVariableReturnFromFunctionIn) {
  I(R"(

       type t1 = {
       x:int[10]
     }

    fun get() -> int[10] {

    var z:int[10] = [1,2,3,4,5,6,7,8]
    return z
    }
    {
    var y:t1 = {
      x:get()
    }
    print(y)   
} 
  )");
  EXPECT_EQ(getOutput(), R"({ x : [1, 2, 3, 4, 5, 6, 7, 8, 0, 0] })");
}

TEST_F(
    ObjectLocalTest,
    ArrayInObjectPropertySingleDimensionUsingVariableReturnFromFunctionMultiIn) {
  I(R"(

       type t1 = {
       x:int[10][5]
     }

    fun get() -> int[10][5] {

    var z:int[10][5] = [1,2,3,4,5,6,7,8]
    return z
    }
    {
    var y:t1 = {
      x:get()
    }
    print(y)  
}
  )");
  EXPECT_EQ(
      getOutput(),
      R"({ x : [[1, 0, 0, 0, 0], [2, 0, 0, 0, 0], [3, 0, 0, 0, 0], [4, 0, 0, 0, 0], [5, 0, 0, 0, 0], [6, 0, 0, 0, 0], [7, 0, 0, 0, 0], [8, 0, 0, 0, 0], [0, 0, 0, 0, 0], [0, 0, 0, 0, 0]] })");
}

// Assignment

TEST_F(
    ObjectLocalTest,
    ArrayInObjectPropertySingleDimensionUsingVariableReturnFromFunctionCompleteIn) {
  I(R"(

       type t1 = {
       x:int[10]
     }

    fun get() -> int[10] {

    var z:int[10] = [1,2,3,4,5,6,7,8]
    return z
    }
    {
    var y:t1 = {
      x:[5 fill 2]
    }
    print(y)
    y = {x:get()}
    print(y) 
}
  )");
  EXPECT_EQ(
      getOutput(),
      R"({ x : [2, 2, 2, 2, 2, 0, 0, 0, 0, 0] }{ x : [1, 2, 3, 4, 5, 6, 7, 8, 0, 0] })");
}

TEST_F(
    ObjectLocalTest,
    ArrayInObjectPropertySingleDimensionUsingVariableReturnFromFunctionPartialAssignThroughFunctionIn) {
  I(R"(

       type t1 = {
       x:int[10]
     }

    fun get() -> int[10] {

    var z:int[10] = [1,2,3,4,5,6,7,8]
    return z
    }
    {
    var y:t1 = {
      x:[5 fill 2]
    }
    print(y)
    y.x = get()
    print(y) 
}
  )");
  EXPECT_EQ(
      getOutput(),
      R"({ x : [2, 2, 2, 2, 2, 0, 0, 0, 0, 0] }{ x : [1, 2, 3, 4, 5, 6, 7, 8, 0, 0] })");
}

TEST_F(
    ObjectLocalTest,
    ArrayInObjectPropertySingleDimensionUsingVariableReturnFromFunctionPartialAssignThroughFunctionMutliIn) {
  I(R"(

        type t1 = {
        x:int[10][5]
      }

      fun get() -> int[10][5] {

      var z:int[10][5] = [1,2,3,4,5,6,7,8]
      return z
      }
      {
      var y:t1 = {
        x:[5 fill 2]
      }
      print(y)
      y.x = get()
      print(y) 
}
  )");
  EXPECT_EQ(
      getOutput(),
      R"({ x : [[2, 2, 2, 2, 2], [0, 0, 0, 0, 0], [0, 0, 0, 0, 0], [0, 0, 0, 0, 0], [0, 0, 0, 0, 0], [0, 0, 0, 0, 0], [0, 0, 0, 0, 0], [0, 0, 0, 0, 0], [0, 0, 0, 0, 0], [0, 0, 0, 0, 0]] }{ x : [[1, 0, 0, 0, 0], [2, 0, 0, 0, 0], [3, 0, 0, 0, 0], [4, 0, 0, 0, 0], [5, 0, 0, 0, 0], [6, 0, 0, 0, 0], [7, 0, 0, 0, 0], [8, 0, 0, 0, 0], [0, 0, 0, 0, 0], [0, 0, 0, 0, 0]] })");
}

TEST_F(
    ObjectLocalTest,
    ArrayInObjectPropertySingleDimensionUsingVariableReturnFromFunctionPartialAssignThroughExpressionIn) {
  I(R"(

       type t1 = {
       x:int[10]
     }

    fun get() -> int[10] {

    var z:int[10] = [1,2,3,4,5,6,7,8]
    return z
    }
    {
    var y:t1 = {
      x:[5 fill 2]
    }
    print(y)
    y.x = [1 ,2 ,3]
    print(y) 
}
  )");
  EXPECT_EQ(
      getOutput(),
      R"({ x : [2, 2, 2, 2, 2, 0, 0, 0, 0, 0] }{ x : [1, 2, 3, 2, 2, 0, 0, 0, 0, 0] })");
}

TEST_F(
    ObjectLocalTest,
    ArrayInObjectPropertySingleDimensionUsingVariableReturnFromFunctionPartialAssignThroughFillExpressionIn) {
  I(R"(

       type t1 = {
       x:int[10]
     }

    fun get() -> int[10] {

    var z:int[10] = [1,2,3,4,5,6,7,8]
    return z
    }
    {
    var y:t1 = {
      x:[5 fill 2]
    }
    print(y)
    y.x = [4 fill 10]
    print(y) 
}
  )");
  EXPECT_EQ(
      getOutput(),
      R"({ x : [2, 2, 2, 2, 2, 0, 0, 0, 0, 0] }{ x : [10, 10, 10, 10, 2, 0, 0, 0, 0, 0] })");
}

TEST_F(
    ObjectLocalTest,
    ArrayInObjectPropertySingleDimensionUsingVariableReturnFromFunctionPartialAssignThroughVariableIn) {
  I(R"(

       type t1 = {
       x:int[10]
     }
         fun get() -> int[10] {

    var z:int[10] = [1,2,3,4,5,6,7,8]
    return z
    }
    
     {
    var z:int[10] = [1,2,3,4,5,6,7,8]

    var y:t1 = {
      x:[5 fill 2]
    }
    print(y)
    y.x = z
    print(y) 
}
  )");
  EXPECT_EQ(
      getOutput(),
      R"({ x : [2, 2, 2, 2, 2, 0, 0, 0, 0, 0] }{ x : [1, 2, 3, 4, 5, 6, 7, 8, 0, 0] })");
}

TEST_F(
    ObjectLocalTest,
    ArrayInObjectPropertySingleDimensionUsingVariableReturnFromPassingFunctionParamIn) {
  I(R"(

       type t1 = {
       x:int[10]
     }
    fun getPrint(u:t1) -> nthg {
      print(u)
    }
    
     {
    var z:int[10] = [1,2,3,4,5,6,7,8]

    var y:t1 = {
      x:[5 fill 2]
    }
    getPrint(y)
}
  )");
  EXPECT_EQ(getOutput(), R"({ x : [2, 2, 2, 2, 2, 0, 0, 0, 0, 0] })");
}

TEST_F(
    ObjectLocalTest,
    ArrayInObjectPropertySingleDimensionUsingVariableReturnFromPassingFunctionParamReturnIn) {
  I(R"(

       type t1 = {
       x:int[10]
     }
    fun getPrint(u:t1) ->  t1 {
      return u
    }
    
     {
    var z:int[10] = [1,2,3,4,5,6,7,8]

    var y:t1 = {
      x:[5 fill 2]
    }
    print(getPrint(y))
}
  )");
  EXPECT_EQ(getOutput(), R"({ x : [2, 2, 2, 2, 2, 0, 0, 0, 0, 0] })");
}

TEST_F(
    ObjectLocalTest,
    ArrayInObjectPropertySingleDimensionUsingVariableReturnFromPassingFunctionParamReturn2In) {
  I(R"(

       type t1 = {
       x:int[10]
     }    
        fun getPrint(u:t1) ->  t1 {

    var z:int[10] = [1,2,3,4,5,6,7,8]
      u  = {x:z}
      return u
    }

     {
    var z:int[10] = [1,2,3,4,5,6,7,8]
 
    var y:t1 = {
      x:[5 fill 2]
    }
    print(getPrint(y))
}
  )");
  EXPECT_EQ(getOutput(), R"({ x : [1, 2, 3, 4, 5, 6, 7, 8, 0, 0] })");
}

TEST_F(
    ObjectLocalTest,
    ArrayInObjectPropertySingleDimensionUsingVariableReturnFromPassingFunctionParamReturn3In) {
  I(R"(

       type t1 = {
       x:int[10]
     }
     
         fun getPrint(u:t1) ->  t1 {

    var z:int[10] = [1,2,3,4,5,6,7,8]
      u  = {x:z}
      return u
    }
     {

    
    var y:t1 = {
      x:[5 fill 2]
    }
    print(getPrint(y))
}
  )");
  EXPECT_EQ(getOutput(), R"({ x : [1, 2, 3, 4, 5, 6, 7, 8, 0, 0] })");
}

TEST_F(
    ObjectLocalTest,
    ArrayInObjectPropertySingleDimensionUsingVariableReturnFromPassingFunctionParamReturn4In) {
  I(R"(

       type t1 = {
       x:int[10]
     }

         fun getPrint(u:t1) ->  t1 {

      u  = {x:[1,2,3,4,5,6,7,8]}
      return u
    }
     {

    
    var y:t1 = {
      x:[5 fill 2]
    }
    print(getPrint(y))
}
  )");
  EXPECT_EQ(getOutput(), R"({ x : [1, 2, 3, 4, 5, 6, 7, 8, 0, 0] })");
}

TEST_F(
    ObjectLocalTest,
    ArrayInObjectPropertySingleDimensionUsingVariableReturnFromPassingFunctionParamReturn4MultiIn) {
  I(R"(

       type t1 = {
       x:int[10][5]
     }
    fun getPrint(u:t1) ->  t1 {

      u  = {x:[1,2,3,4,5,6,7,8]}
      return u
    }
    {
    var y:t1 = {
      x:[5 fill 2]
    }
    print(getPrint(y))
}
  )");
  EXPECT_EQ(
      getOutput(),
      R"({ x : [[1, 2, 2, 2, 2], [2, 0, 0, 0, 0], [3, 0, 0, 0, 0], [4, 0, 0, 0, 0], [5, 0, 0, 0, 0], [6, 0, 0, 0, 0], [7, 0, 0, 0, 0], [8, 0, 0, 0, 0], [0, 0, 0, 0, 0], [0, 0, 0, 0, 0]] })");
}

TEST_F(
    ObjectLocalTest,
    ArrayInObjectPropertySingleDimensionUsingVariableReturnFromPassingFunctionParamReturn4MultiInDefaultAssign) {
  I(R"(

    type obj = {
    i:int,
    s:str
  }
type k = {
  o: int,
  s: str,
  d: deci,
  i: int,
  ob:obj
}
type par = {
  u: str,
  g: k[2]
}
type t = {
  x: int,
  y: str,
  a: deci,
  b: bool,
  ar: par[1]
}
fun getGKA() -> k[2] {
  var gka: k  = {
  i:1022,
 o: 102,
  s: "sora"
  
}
var x:k[2] = [gka]

    return x
  }

fun getT()-> t{
  var tt:t = {y:"NO",b:true,ar:[{u:"eeet",g:getGKA()}]}
  return tt
  }

var u:t  = getT()

print(u)
print("\n")
u <- {}
  print(u)

  )");
  EXPECT_EQ(
      getOutput(),
      R"({ x : 0, y : 'NO', a : 0.00000000000000, b : true, ar : [{ u : 'eeet', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }
{ x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] })");
}

TEST_F(
    ObjectLocalTest,
    ArrayInObjectPropertySingleDimensionUsingVariableReturnFromPassingFunctionParamReturn4MultiInDefaultAssignWithout) {
  I(R"(

   type obj = {
    i:int,
    s:str
  }
type k = {
  o: int,
  s: str,
  d: deci,
  i: int,
  ob:obj
}
type par = {
  u: str,
  g: k[2]
}
type t = {
  x: int,
  y: str,
  a: deci,
  b: bool,
  ar: par[1]
}
fun getGKA() -> k[2] {
  var gka: k  = {
  i:1022,
 o: 102,
  s: "sora"
  
}
var x:k[2] = [gka]

    return x
  }

fun getT()-> t{
  var tt:t = {y:"NO",b:true,ar:[{u:"eeet",g:getGKA()}]}
  return tt
  }

var u:t  = getT()

print(u)
print("\n")
u = {}
  print(u)

  )");
  EXPECT_EQ(
      getOutput(),
      R"({ x : 0, y : 'NO', a : 0.00000000000000, b : true, ar : [{ u : 'eeet', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }
{ x : 0, y : 'NO', a : 0.00000000000000, b : true, ar : [{ u : 'eeet', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] })");
}

TEST_F(
    ObjectLocalTest,
    ArrayInObjectPropertySingleDimensionUsingVariableReturnFromPassingFunctionParamReturn4MultiInDefaultAssignWithArray) {
  I(R"(
type obj = {
    i:int,
    s:str
  }
type k = {
  o: int,
  s: str,
  d: deci,
  i: int,
  ob:obj
}
type par = {
  u: str,
  g: k[2]
}
type t = {
  x: int,
  y: str,
  a: deci,
  b: bool,
  ar: par[1]
}
fun getGKA() -> k[2] {
  var gka: k  = {
  i:1022,
 o: 102,
  s: "sora"
  
}
var x:k[2] = [gka]

    return x
  }

fun getT()-> t{
  var tt:t = {y:"NO",b:true,ar:[{u:"eeet",g:getGKA()}]}
  return tt
  }

fun getArr()-> t[2] {
var a:t[2] = [{x:2,y:"hello",a:3.3,b:true,ar:[{u:"get",g:getGKA()}]}]
return a
  }
{
  var arr:t[2] =[{x:300,y:"eee",a:4.3,b:true,ar:[{g:getGKA()}]}]
print(arr)
print("\n\n")
arr <- []
print(arr)
arr[0].ar[0].g = getGKA()
}

  )");
  EXPECT_EQ(
      getOutput(),
      R"([{ x : 300, y : 'eee', a : 4.30000000000000, b : true, ar : [{ u : '', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }]

[{ x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }])");
}

TEST_F(
    ObjectLocalTest,
    ArrayInObjectPropertySingleDimensionUsingVariableReturnFromPassingFunctionParamReturn4MultiInDefaultAssignWithArrayWithSomeValue) {
  I(R"(
type obj = {
    i:int,
    s:str
  }
type k = {
  o: int,
  s: str,
  d: deci,
  i: int,
  ob:obj
}
type par = {
  u: str,
  g: k[2]
}
type t = {
  x: int,
  y: str,
  a: deci,
  b: bool,
  ar: par[1]
}
fun getGKA() -> k[2] {
  var gka: k  = {
  i:1022,
 o: 102,
  s: "sora"
  
}
var x:k[2] = [gka]

    return x
  }

fun getT()-> t{
  var tt:t = {y:"NO",b:true,ar:[{u:"eeet",g:getGKA()}]}
  return tt
  }

fun getArr()-> t[2] {
var a:t[2] = [{x:2,y:"hello",a:3.3,b:true,ar:[{u:"get",g:getGKA()}]}]
return a
  }
{
  var arr:t[2] =[{x:300,y:"eee",a:4.3,b:true,ar:[{g:getGKA()}]}]
print(arr)
print("\n\n")
arr <- [{x:2}]
print(arr)
arr[0].ar[0].g = getGKA()
}

  )");
  EXPECT_EQ(
      getOutput(),
      R"([{ x : 300, y : 'eee', a : 4.30000000000000, b : true, ar : [{ u : '', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }]

[{ x : 2, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }])");
}

TEST_F(
    ObjectLocalTest,
    ArrayInObjectPropertySingleDimensionUsingVariableReturnFromPassingFunctionParamReturn4MultiInDefaultAssignWithArrayWithSomeValueGlobal) {
  I(R"(
type obj = {
    i:int,
    s:str
  }
type k = {
  o: int,
  s: str,
  d: deci,
  i: int,
  ob:obj
}
type par = {
  u: str,
  g: k[2]
}
type t = {
  x: int,
  y: str,
  a: deci,
  b: bool,
  ar: par[1]
}
fun getGKA() -> k[2] {
  var gka: k  = {
  i:1022,
 o: 102,
  s: "sora"
  
}
var x:k[2] = [gka]

    return x
  }

fun getT()-> t{
  var tt:t = {y:"NO",b:true,ar:[{u:"eeet",g:getGKA()}]}
  return tt
  }

fun getArr()-> t[2] {
var a:t[2] = [{x:2,y:"hello",a:3.3,b:true,ar:[{u:"get",g:getGKA()}]}]
return a
  }
  var arr:t[2] =[{x:300,y:"eee",a:4.3,b:true,ar:[{g:getGKA()}]}]
print(arr)
print("\n\n")
arr <- [{x:2}]
print(arr)
arr[0].ar[0].g = getGKA()


  )");
  EXPECT_EQ(
      getOutput(),
      R"([{ x : 300, y : 'eee', a : 4.30000000000000, b : true, ar : [{ u : '', g : [{ o : 102, s : 'sora', d : 0.00000000000000, i : 1022, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }]

[{ x : 2, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }, { x : 0, y : '', a : 0.00000000000000, b : false, ar : [{ u : '', g : [{ o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }, { o : 0, s : '', d : 0.00000000000000, i : 0, ob : { i : 0, s : '' } }] }] }])");
}
TEST_F(
    ObjectLocalTest,
    ArrayInObjectPropertySingleDimensionUsingVariableReturnFromPassingFunctionParamIn1) {
  I(R"(

  type T = {
      x:int 
    }
    fun  getC() -> T {
      return  {x:2}
    }

    fun setC(x:T) -> nthg {
      print(x)
    }
setC(getC())
print(getC())
/#
    fun  getC() -> int {
      return  3
    }

    fun setC(x:int) -> nthg {
      print(x)
      }
setC(getC())
  )");
  EXPECT_EQ(getOutput(), R"({ x : 2 }{ x : 2 })");
}

#endif