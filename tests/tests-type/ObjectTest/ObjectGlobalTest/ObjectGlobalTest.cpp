#include "ObjectGlobalTest.h"

void ObjectGlobalTest::SetUp() { _test->SetUp(); }

void ObjectGlobalTest::TearDown() { _test->TearDown(); }

#if defined(JIT_TEST_MODE) || defined(AOT_TEST_MODE)

// Declarations

TEST_F(ObjectGlobalTest, ObjectGlobalTest1) {
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
     print(x)
  )");
  EXPECT_EQ(getOutput(),
            R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true })");
}

TEST_F(ObjectGlobalTest, ObjectGlobalTestDec) {
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
       d:true
     }
     print(x)
  )");
  EXPECT_EQ(
      getOutput(),
      R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : '', pb : 0, pc : 0.00000000000000, pd : false } })");
}

TEST_F(ObjectGlobalTest, ObjectGlobalTestDecUse) {
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
  )");
  EXPECT_EQ(
      getOutput(),
      R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : 'Hello', pb : 0, pc : 0.00000000000000, pd : false } })");
}

TEST_F(ObjectGlobalTest, ObjectGlobalTestDecUse2) {
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
       p:{ pa : "hello", pb : 2, pc : 45.00000000000000, pd : true }
     }
     print(x)
  )");
  EXPECT_EQ(
      getOutput(),
      R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : 'hello', pb : 2, pc : 45.00000000000000, pd : true } })");
}

TEST_F(ObjectGlobalTest, ObjectGlobalTestDecUse2Assign) {
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
     print(y)
  )");
  EXPECT_EQ(
      getOutput(),
      R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : 'hello', pb : 2, pc : -45.10000000000000, pd : true } })");
}

TEST_F(ObjectGlobalTest, ObjectGlobalTestDecUse2NoDec) {
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
     print(x)
  )");
  EXPECT_EQ(
      getOutput(),
      R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : '', pb : 0, pc : 0.00000000000000, pd : false } })");
}

TEST_F(ObjectGlobalTest, ObjectGlobalTestDecUse2NoDecAssign1) {
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
    var y:t1 = x

     print(y)
  )");
  EXPECT_EQ(
      getOutput(),
      R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : '', pb : 0, pc : 0.00000000000000, pd : false } })");
}

TEST_F(ObjectGlobalTest, ObjectLoneInt) {
  I(R"(
      type t1 = {
        a:int
      }

      var x:t1 = {
        a:1
      } 

      print(x)
    
  )");
  EXPECT_EQ(getOutput(), R"({ a : 1 })");
}

TEST_F(ObjectGlobalTest, ObjectLoneDec) {
  I(R"(
      type t1 = {
        a:deci
      }

      var x:t1 = {
        a:1.0
      }

      print(x)


  )");
  EXPECT_EQ(getOutput(), R"({ a : 1.00000000000000 })");
}

TEST_F(ObjectGlobalTest, ObjectLoneBool) {
  I(R"(
      type t1 = {
        a:bool
      }

      var x:t1 = {
        a:true
      }

      print(x)


  )");
  EXPECT_EQ(getOutput(), R"({ a : true })");
}

TEST_F(ObjectGlobalTest, ObjectLoneStr) {
  I(R"(
      type t1 = {
        a:str
      }

      var x:t1 = {
        a:"hello"
      }

      print(x)


  )");
  EXPECT_EQ(getOutput(), R"({ a : 'hello' })");
}

// Dec Use Fun Start

TEST_F(ObjectGlobalTest, ObjectGlobalTest1Fun) {
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

     var u:t1 = mainTest()
     print(u)
  )");
  EXPECT_EQ(getOutput(),
            R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true })");
}

TEST_F(ObjectGlobalTest, ObjectGlobalTestDecFun) {
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

     var y:t1 = mainTest()
     print(y)
  )");
  EXPECT_EQ(
      getOutput(),
      R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : '', pb : 0, pc : 0.00000000000000, pd : false } })");
}

TEST_F(ObjectGlobalTest, ObjectGlobalTestDecUseFun) {
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
    var y:t1 = mainTest()

     print(y)
  )");
  EXPECT_EQ(
      getOutput(),
      R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : 'Hello', pb : 0, pc : 0.00000000000000, pd : false } })");
}

TEST_F(ObjectGlobalTest, ObjectGlobalTestDecUse2Fun) {
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
    var y:t1 = mainTest()
     print(y)
  )");
  EXPECT_EQ(
      getOutput(),
      R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : 'hello', pb : 2, pc : 45.00000000000000, pd : true } })");
}

TEST_F(ObjectGlobalTest, ObjectGlobalTestDecUse2AssignFun) {
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
    var z:t1 = mainTest()
     print(z)
  )");
  EXPECT_EQ(
      getOutput(),
      R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : 'hello', pb : 2, pc : -45.10000000000000, pd : true } })");
}

TEST_F(ObjectGlobalTest, ObjectGlobalTestDecUse2NoDecFun) {
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

      var y:t1 =  mainTest()
     print(y)
  )");
  EXPECT_EQ(
      getOutput(),
      R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : '', pb : 0, pc : 0.00000000000000, pd : false } })");
}

TEST_F(ObjectGlobalTest, ObjectGlobalTestDecUse2NoDecAssign1Fun) {
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

    var z:t1 =  mainTest()
     print(z)
  )");
  EXPECT_EQ(
      getOutput(),
      R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : '', pb : 0, pc : 0.00000000000000, pd : false } })");
}

TEST_F(ObjectGlobalTest, ObjectGlobalTestDecUse2NoDecAssign1AvdFun) {
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

    var z:parent =  mainTest()
     print(z)
  )");
  EXPECT_EQ(getOutput(),
            R"({ pa : 's', pb : 1, pc : 1.10000000000000, pd : true })");
}

TEST_F(ObjectGlobalTest, ObjectLoneIntFun) {
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

      var y:t1 = mainTest()
      print(y)
    
  )");
  EXPECT_EQ(getOutput(), R"({ a : 1 })");
}

TEST_F(ObjectGlobalTest, ObjectLoneDecFun) {
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

      var y:t1 = mainTest()
      print(y)

  )");
  EXPECT_EQ(getOutput(), R"({ a : 1.00000000000000 })");
}

TEST_F(ObjectGlobalTest, ObjectLoneBoolFun) {
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

    
      var y:t1 = mainTest()
      print(y)


  )");
  EXPECT_EQ(getOutput(), R"({ a : true })");
}

TEST_F(ObjectGlobalTest, ObjectLoneStrFun) {
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

    var y:t1 = mainTest()
      print(y)


  )");
  EXPECT_EQ(getOutput(), R"({ a : 'hello' })");
}

// Dec Use Fun End

// Assignment

TEST_F(ObjectGlobalTest, ObjectLoneIntAssign) {
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
      print(y)
      y = x 
      print(y)
    
  )");
  EXPECT_EQ(getOutput(), R"({ a : 2 }{ a : 1 })");
}

TEST_F(ObjectGlobalTest, ObjectLoneDecAssign) {
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
      print(y)
      y = x 
      print(y)

  )");
  EXPECT_EQ(getOutput(), R"({ a : 2.00000000000000 }{ a : 1.00000000000000 })");
}

TEST_F(ObjectGlobalTest, ObjectLoneBoolAssign) {
  I(R"(
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
  )");
  EXPECT_EQ(getOutput(), R"({ a : false }{ a : true })");
}

TEST_F(ObjectGlobalTest, ObjectLoneStrAssign) {
  I(R"(
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
  )");
  EXPECT_EQ(getOutput(), R"({ a : 'world' }{ a : 'hello' })");
}

TEST_F(ObjectGlobalTest, ObjectGlobalTest1Assign) {
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
  )");
  EXPECT_EQ(getOutput(),
            R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true })");
}

TEST_F(ObjectGlobalTest, ObjectGlobalTestDecAssign) {
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
  )");
  EXPECT_EQ(
      getOutput(),
      R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : '', pb : 0, pc : 0.00000000000000, pd : false } }{ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : '', pb : 0, pc : 0.00000000000000, pd : false } })");
}

TEST_F(ObjectGlobalTest, ObjectGlobalTestDecUseAssign) {
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
     x.p.pa = "w"
     x.p.pb = 2
     x.p.pc = 45.00000000000000
     x.p.pd = true
     print(x)
  )");
  EXPECT_EQ(
      getOutput(),
      R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : 'Hello', pb : 0, pc : 0.00000000000000, pd : false } }{ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : 'w', pb : 2, pc : 45.00000000000000, pd : true } })");
}

TEST_F(ObjectGlobalTest, ObjectGlobalTestDecUseAssign2) {
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
  )");
  EXPECT_EQ(
      getOutput(),
      R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : 'Hello', pb : 0, pc : 0.00000000000000, pd : false } }{ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : 'w', pb : 2, pc : 45.00000000000000, pd : true } })");
}

TEST_F(ObjectGlobalTest, ObjectGlobalTestDecUseAssign3) {
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
     var y:t1 = { a : "hello2", b : 110, c : 110.10, d : true , p : { pa : "wj", pb : 20, pc : 47.00000000000000, pd : false } }
     print(y)
     y.p = x.p
     print(y)
  )");
  EXPECT_EQ(
      getOutput(),
      R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : 'Hello', pb : 0, pc : 0.00000000000000, pd : false } }{ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : 'w', pb : 2, pc : 45.00000000000000, pd : true } }{ a : 'hello2', b : 110, c : 110.09999999999999, d : true, p : { pa : 'wj', pb : 20, pc : 47.00000000000000, pd : false } }{ a : 'hello2', b : 110, c : 110.09999999999999, d : true, p : { pa : 'w', pb : 2, pc : 45.00000000000000, pd : true } })");
}

TEST_F(ObjectGlobalTest, ObjectGlobalTestDecUse2Assign2) {
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
       p:{ pa : "hello", pb : 2, pc : 45.00000000000000, pd : true }
     }

     print(x)
     x.p = { pa : "w", pb : 2, pc : 45.00000000000000, pd : true }
     x.p.pa = "g"
     x.p.pd = false
     x.p.pb = 1
     x.p.pc = -1 * 45.10000000000000
     print(x)
  )");
  EXPECT_EQ(
      getOutput(),
      R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : 'hello', pb : 2, pc : 45.00000000000000, pd : true } }{ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : 'g', pb : 1, pc : -45.10000000000000, pd : false } })");
}

TEST_F(ObjectGlobalTest, ObjectGlobalTestDecUse2AssignAssign) {
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
     var y:t1 = { a : "hello2", b : 110, c : 110.10, d : true , p : { pa : "wj", pb : 20, pc : 47.00000000000000, pd : false } }
     print(x)
     print(y)
     x.p = y.p
     print(x)
     y = x
     print(y)
  )");
  EXPECT_EQ(
      getOutput(),
      R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : 'hello', pb : 2, pc : -45.10000000000000, pd : true } }{ a : 'hello2', b : 110, c : 110.09999999999999, d : true, p : { pa : 'wj', pb : 20, pc : 47.00000000000000, pd : false } }{ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : 'wj', pb : 20, pc : 47.00000000000000, pd : false } }{ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : 'wj', pb : 20, pc : 47.00000000000000, pd : false } })");
}

TEST_F(ObjectGlobalTest, ObjectGlobalTestDecUse2NoDecAssign2) {
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
     x.p = { pa : "x", pb : 10, pc : 1.00000000000000, pd : true }
     print(x)
  )");
  EXPECT_EQ(
      getOutput(),
      R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : 'x', pb : 10, pc : 1.00000000000000, pd : true } })");
}

TEST_F(ObjectGlobalTest, ObjectGlobalTestDecUse2NoDecAssign) {
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
  )");
  EXPECT_EQ(
      getOutput(),
      R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : '', pb : 0, pc : 0.00000000000000, pd : false } }{ a : 'hello2', b : 110, c : 110.09999999999999, d : true, p : { pa : 'wj', pb : 20, pc : 47.00000000000000, pd : false } })");
}

TEST_F(ObjectGlobalTest, ObjectGlobalTestDecUse2NoDecAssignFunAllIn) {
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

    var z:t1 =  {a:"gog",b:1,c:1.1,d:true}
    print(z)
    print("\n")
    z = mainTest(x)
     print(z)

  )");
  EXPECT_EQ(
      getOutput(),
      R"({ a : 'gog', b : 1, c : 1.10000000000000, d : true, p : { pa : '', pb : 0, pc : 0.00000000000000, pd : false } }
{ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : 'b', pb : 1, pc : 1.10000000000000, pd : true } }
{ a : 'hello2', b : 110, c : 110.09999999999999, d : true, p : { pa : 'wj', pb : 20, pc : 47.00000000000000, pd : false } })");
}

TEST_F(ObjectGlobalTest, ArrayInObjectPropertySingleDimensionExpression) {
  I(R"(
     type t1 = {
       x:int[10]
     }
    var y:t1 = {
      x:[1,2,3,4,5,6,7,8,9]
    }

    print(y)    
  )");
  EXPECT_EQ(getOutput(), R"({ x : [1, 2, 3, 4, 5, 6, 7, 8, 9, 0] })");
}

TEST_F(ObjectGlobalTest, ArrayInObjectPropertySingleDimensionExpressionMulti) {
  I(R"(
     type t1 = {
       x:int[10][5]
     }
    var y:t1 = {
      x:[1,2,3,4,5,6,7,8,9]
    }

    print(y)     
  )");
  EXPECT_EQ(
      getOutput(),
      R"({ x : [[1, 0, 0, 0, 0], [2, 0, 0, 0, 0], [3, 0, 0, 0, 0], [4, 0, 0, 0, 0], [5, 0, 0, 0, 0], [6, 0, 0, 0, 0], [7, 0, 0, 0, 0], [8, 0, 0, 0, 0], [9, 0, 0, 0, 0], [0, 0, 0, 0, 0]] })");
}

TEST_F(ObjectGlobalTest, ArrayInObjectPropertySingleDimensionFillExpression) {
  I(R"(
     type t1 = {
       x:int[10]
     }
    var y:t1 = {
      x:[5 fill 5]
    }

    print(y)    
  )");
  EXPECT_EQ(getOutput(), R"({ x : [5, 5, 5, 5, 5, 0, 0, 0, 0, 0] })");
}

TEST_F(ObjectGlobalTest, ArrayInObjectPropertySingleDimensionUsingVariable) {
  I(R"(
     type t1 = {
       x:int[10]
     }

    var z:int[10] = [1,2,3,4,5,6,7,8]
    
    var y:t1 = {
      x:z
    }

    print(y)    
  )");
  EXPECT_EQ(getOutput(), R"({ x : [1, 2, 3, 4, 5, 6, 7, 8, 0, 0] })");
}

TEST_F(ObjectGlobalTest,
       ArrayInObjectPropertySingleDimensionUsingVariableMulti) {
  I(R"(
     type t1 = {
       x:int[10][5]
     }

    var z:int[10][5] = [5 fill 10]
    
    var y:t1 = {
      x:z
    }

    print(y)    
  )");
  EXPECT_EQ(
      getOutput(),
      R"({ x : [[10, 10, 10, 10, 10], [0, 0, 0, 0, 0], [0, 0, 0, 0, 0], [0, 0, 0, 0, 0], [0, 0, 0, 0, 0], [0, 0, 0, 0, 0], [0, 0, 0, 0, 0], [0, 0, 0, 0, 0], [0, 0, 0, 0, 0], [0, 0, 0, 0, 0]] })");
}

TEST_F(ObjectGlobalTest,
       ArrayInObjectPropertySingleDimensionUsingVariableMulti2) {
  I(R"(
     type t1 = {
       x:int[10][5]
     }

    var z:int[10][5] = [1,2,3,4,5,6,7,8]
    
    var y:t1 = {
      x:z
    }

    print(y)    
  )");
  EXPECT_EQ(
      getOutput(),
      R"({ x : [[1, 0, 0, 0, 0], [2, 0, 0, 0, 0], [3, 0, 0, 0, 0], [4, 0, 0, 0, 0], [5, 0, 0, 0, 0], [6, 0, 0, 0, 0], [7, 0, 0, 0, 0], [8, 0, 0, 0, 0], [0, 0, 0, 0, 0], [0, 0, 0, 0, 0]] })");
}

TEST_F(ObjectGlobalTest,
       ArrayInObjectPropertySingleDimensionUsingVariableReturnFromFunction) {
  I(R"(
     type t1 = {
       x:int[10]
     }

    fun get() -> int[10] {

    var z:int[10] = [1,2,3,4,5,6,7,8]
    return z
    }
    
    var y:t1 = {
      x:get()
    }
    print(y)    
  )");
  EXPECT_EQ(getOutput(), R"({ x : [1, 2, 3, 4, 5, 6, 7, 8, 0, 0] })");
}

TEST_F(
    ObjectGlobalTest,
    ArrayInObjectPropertySingleDimensionUsingVariableReturnFromFunctionMulti) {
  I(R"(
     type t1 = {
       x:int[10][5]
     }

    fun get() -> int[10][5] {

    var z:int[10][5] = [1,2,3,4,5,6,7,8]
    return z
    }
    
    var y:t1 = {
      x:get()
    }
    print(y)  
  )");
  EXPECT_EQ(
      getOutput(),
      R"({ x : [[1, 0, 0, 0, 0], [2, 0, 0, 0, 0], [3, 0, 0, 0, 0], [4, 0, 0, 0, 0], [5, 0, 0, 0, 0], [6, 0, 0, 0, 0], [7, 0, 0, 0, 0], [8, 0, 0, 0, 0], [0, 0, 0, 0, 0], [0, 0, 0, 0, 0]] })");
}

// Assignment

TEST_F(
    ObjectGlobalTest,
    ArrayInObjectPropertySingleDimensionUsingVariableReturnFromFunctionComplete) {
  I(R"(
     type t1 = {
       x:int[10]
     }

    fun get() -> int[10] {

    var z:int[10] = [1,2,3,4,5,6,7,8]
    return z
    }
    
    var y:t1 = {
      x:[5 fill 2]
    }
    print(y)
    y = {x:get()}
    print(y) 
  )");
  EXPECT_EQ(
      getOutput(),
      R"({ x : [2, 2, 2, 2, 2, 0, 0, 0, 0, 0] }{ x : [1, 2, 3, 4, 5, 6, 7, 8, 0, 0] })");
}

TEST_F(
    ObjectGlobalTest,
    ArrayInObjectPropertySingleDimensionUsingVariableReturnFromFunctionPartialAssignThroughFunction) {
  I(R"(
     type t1 = {
       x:int[10]
     }

    fun get() -> int[10] {

    var z:int[10] = [1,2,3,4,5,6,7,8]
    return z
    }
    
    var y:t1 = {
      x:[5 fill 2]
    }
    print(y)
    y.x = get()
    print(y) 
  )");
  EXPECT_EQ(
      getOutput(),
      R"({ x : [2, 2, 2, 2, 2, 0, 0, 0, 0, 0] }{ x : [1, 2, 3, 4, 5, 6, 7, 8, 0, 0] })");
}

TEST_F(
    ObjectGlobalTest,
    ArrayInObjectPropertySingleDimensionUsingVariableReturnFromFunctionPartialAssignThroughFunctionMutli) {
  I(R"(
      type t1 = {
        x:int[10][5]
      }

      fun get() -> int[10][5] {

      var z:int[10][5] = [1,2,3,4,5,6,7,8]
      return z
      }
      
      var y:t1 = {
        x:[5 fill 2]
      }
      print(y)
      y.x = get()
      print(y) 
  )");
  EXPECT_EQ(
      getOutput(),
      R"({ x : [[2, 2, 2, 2, 2], [0, 0, 0, 0, 0], [0, 0, 0, 0, 0], [0, 0, 0, 0, 0], [0, 0, 0, 0, 0], [0, 0, 0, 0, 0], [0, 0, 0, 0, 0], [0, 0, 0, 0, 0], [0, 0, 0, 0, 0], [0, 0, 0, 0, 0]] }{ x : [[1, 0, 0, 0, 0], [2, 0, 0, 0, 0], [3, 0, 0, 0, 0], [4, 0, 0, 0, 0], [5, 0, 0, 0, 0], [6, 0, 0, 0, 0], [7, 0, 0, 0, 0], [8, 0, 0, 0, 0], [0, 0, 0, 0, 0], [0, 0, 0, 0, 0]] })");
}

TEST_F(
    ObjectGlobalTest,
    ArrayInObjectPropertySingleDimensionUsingVariableReturnFromFunctionPartialAssignThroughExpression) {
  I(R"(
     type t1 = {
       x:int[10]
     }

    fun get() -> int[10] {

    var z:int[10] = [1,2,3,4,5,6,7,8]
    return z
    }
    
    var y:t1 = {
      x:[5 fill 2]
    }
    print(y)
    y.x = [1 ,2 ,3]
    print(y) 
  )");
  EXPECT_EQ(
      getOutput(),
      R"({ x : [2, 2, 2, 2, 2, 0, 0, 0, 0, 0] }{ x : [1, 2, 3, 2, 2, 0, 0, 0, 0, 0] })");
}

TEST_F(
    ObjectGlobalTest,
    ArrayInObjectPropertySingleDimensionUsingVariableReturnFromFunctionPartialAssignThroughFillExpression) {
  I(R"(
     type t1 = {
       x:int[10]
     }

    fun get() -> int[10] {

    var z:int[10] = [1,2,3,4,5,6,7,8]
    return z
    }
    
    var y:t1 = {
      x:[5 fill 2]
    }
    print(y)
    y.x = [4 fill 10]
    print(y) 
  )");
  EXPECT_EQ(
      getOutput(),
      R"({ x : [2, 2, 2, 2, 2, 0, 0, 0, 0, 0] }{ x : [10, 10, 10, 10, 2, 0, 0, 0, 0, 0] })");
}

TEST_F(
    ObjectGlobalTest,
    ArrayInObjectPropertySingleDimensionUsingVariableReturnFromFunctionPartialAssignThroughVariable) {
  I(R"(
     type t1 = {
       x:int[10]
     }
    var z:int[10] = [1,2,3,4,5,6,7,8]
    fun get() -> int[10] {

    var z:int[10] = [1,2,3,4,5,6,7,8]
    return z
    }
    
    var y:t1 = {
      x:[5 fill 2]
    }
    print(y)
    y.x = z
    print(y) 
  )");
  EXPECT_EQ(
      getOutput(),
      R"({ x : [2, 2, 2, 2, 2, 0, 0, 0, 0, 0] }{ x : [1, 2, 3, 4, 5, 6, 7, 8, 0, 0] })");
}

TEST_F(
    ObjectGlobalTest,
    ArrayInObjectPropertySingleDimensionUsingVariableReturnFromPassingFunctionParam) {
  I(R"(
     type t1 = {
       x:int[10]
     }
    var z:int[10] = [1,2,3,4,5,6,7,8]
    fun getPrint(u:t1) -> nthg {
      print(u)
    }
    
    var y:t1 = {
      x:[5 fill 2]
    }
    getPrint(y)
  )");
  EXPECT_EQ(getOutput(), R"({ x : [2, 2, 2, 2, 2, 0, 0, 0, 0, 0] })");
}

TEST_F(
    ObjectGlobalTest,
    ArrayInObjectPropertySingleDimensionUsingVariableReturnFromPassingFunctionParamReturn) {
  I(R"(
     type t1 = {
       x:int[10]
     }
    var z:int[10] = [1,2,3,4,5,6,7,8]
    fun getPrint(u:t1) ->  t1 {
      return u
    }
    
    var y:t1 = {
      x:[5 fill 2]
    }
    print(getPrint(y))
  )");
  EXPECT_EQ(getOutput(), R"({ x : [2, 2, 2, 2, 2, 0, 0, 0, 0, 0] })");
}

TEST_F(
    ObjectGlobalTest,
    ArrayInObjectPropertySingleDimensionUsingVariableReturnFromPassingFunctionParamReturn2) {
  I(R"(
     type t1 = {
       x:int[10]
     }
    var z:int[10] = [1,2,3,4,5,6,7,8]
    fun getPrint(u:t1) ->  t1 {
      u  = {x:z}
      return u
    }
    
    var y:t1 = {
      x:[5 fill 2]
    }
    print(getPrint(y))
  )");
  EXPECT_EQ(getOutput(), R"({ x : [1, 2, 3, 4, 5, 6, 7, 8, 0, 0] })");
}

TEST_F(
    ObjectGlobalTest,
    ArrayInObjectPropertySingleDimensionUsingVariableReturnFromPassingFunctionParamReturn3) {
  I(R"(
     type t1 = {
       x:int[10]
     }
    fun getPrint(u:t1) ->  t1 {

    var z:int[10] = [1,2,3,4,5,6,7,8]
      u  = {x:z}
      return u
    }
    
    var y:t1 = {
      x:[5 fill 2]
    }
    print(getPrint(y))
  )");
  EXPECT_EQ(getOutput(), R"({ x : [1, 2, 3, 4, 5, 6, 7, 8, 0, 0] })");
}

TEST_F(
    ObjectGlobalTest,
    ArrayInObjectPropertySingleDimensionUsingVariableReturnFromPassingFunctionParamReturn4) {
  I(R"(
     type t1 = {
       x:int[10]
     }
    fun getPrint(u:t1) ->  t1 {

      u  = {x:[1,2,3,4,5,6,7,8]}
      return u
    }
    
    var y:t1 = {
      x:[5 fill 2]
    }
    print(getPrint(y))
  )");
  EXPECT_EQ(getOutput(), R"({ x : [1, 2, 3, 4, 5, 6, 7, 8, 0, 0] })");
}

TEST_F(
    ObjectGlobalTest,
    ArrayInObjectPropertySingleDimensionUsingVariableReturnFromPassingFunctionParamReturn4Multi) {
  I(R"(
     type t1 = {
       x:int[10][5]
     }
    fun getPrint(u:t1) ->  t1 {

      u  = {x:[1,2,3,4,5,6,7,8]}
      return u
    }
    
    var y:t1 = {
      x:[5 fill 2]
    }
    print(getPrint(y))
  )");
  EXPECT_EQ(
      getOutput(),
      R"({ x : [[1, 2, 2, 2, 2], [2, 0, 0, 0, 0], [3, 0, 0, 0, 0], [4, 0, 0, 0, 0], [5, 0, 0, 0, 0], [6, 0, 0, 0, 0], [7, 0, 0, 0, 0], [8, 0, 0, 0, 0], [0, 0, 0, 0, 0], [0, 0, 0, 0, 0]] })");
}

#endif