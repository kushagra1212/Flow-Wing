#include "ObjectGlobalTest.h"

ObjectGlobalTest::ObjectGlobalTest() {
#ifdef JIT_TEST_MODE
  _test = std::make_unique<JITCompilerTest>();
#endif

#ifdef REPL_TEST_MODE
  _test = std::make_unique<ReplTest>();
#endif
}

void ObjectGlobalTest::SetUp() { _test->SetUp(); }

void ObjectGlobalTest::TearDown() { _test->TearDown(); }

void ObjectGlobalTest::setInput(const std::string &input) {
  _test->setInput(input);
}

std::string ObjectGlobalTest::getOutput() const { return _test->getOutput(); }

void ObjectGlobalTest::runEvaluator() { _test->runEvaluator(); }

#ifdef JIT_TEST_MODE

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
  O(R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true })");
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
  O(R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : '', pb : 0, pc : 0.00000000000000, pd : false } })");
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
  O(R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : 'Hello', pb : 0, pc : 0.00000000000000, pd : false } })");
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
  O(R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : 'hello', pb : 2, pc : 45.00000000000000, pd : true } })");
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
  O(R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : 'hello', pb : 2, pc : -45.10000000000000, pd : true } })");
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
  O(R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : '', pb : 0, pc : 0.00000000000000, pd : false } })");
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
  O(R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : '', pb : 0, pc : 0.00000000000000, pd : false } })");
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
  O(R"({ a : 1 })");
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
  O(R"({ a : 1.00000000000000 })");
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
  O(R"({ a : true })");
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
  O(R"({ a : 'hello' })");
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
     fun main() -> t1{
           var x:t1 = { 
       a:"hello",
       b:10,
       c:10.10,
       d:true
     }

     return x
     }

     var u:t1 = main()
     print(u)
  )");
  O(R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true })");
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

     fun main() -> t1 {
           var x:t1 = { 
       a:"hello",
       b:10,
       c:10.10,
       d:true
     }
     return x
     }

     var y:t1 = main()
     print(y)
  )");
  O(R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : '', pb : 0, pc : 0.00000000000000, pd : false } })");
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

    fun main() -> t1 {
           var x:t1 = { 
       a:"hello",
       b:10,
       c:10.10,
       d:true,
       p:{ pa : "Hello" }
     }
     return x
    }
    var y:t1 = main()

     print(y)
  )");
  O(R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : 'Hello', pb : 0, pc : 0.00000000000000, pd : false } })");
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
    fun main() -> t1 {
           var x:t1 = { 
       a:"hello",
       b:10,
       c:10.10,
       d:true,
       p:{ pa : "hello", pb : 2, pc : 45.00000000000000, pd : true }
     }
     return x
    }
    var y:t1 = main()
     print(y)
  )");
  O(R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : 'hello', pb : 2, pc : 45.00000000000000, pd : true } })");
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
    
    fun main() -> t1 {
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
    var z:t1 = main()
     print(z)
  )");
  O(R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : 'hello', pb : 2, pc : -45.10000000000000, pd : true } })");
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

      fun main() -> t1 {
        return x
      }

      var y:t1 =  main()
     print(y)
  )");
  O(R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : '', pb : 0, pc : 0.00000000000000, pd : false } })");
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

    fun main() -> t1 {
          var x:t1 = { 
       a:"hello",
       b:10,
       c:10.10,
       d:true,
     }
    var y:t1 = x
    return y
    }

    var z:t1 =  main()
     print(z)
  )");
  O(R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : '', pb : 0, pc : 0.00000000000000, pd : false } })");
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

    fun main() -> parent {
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

    var z:parent =  main()
     print(z)
  )");
  O(R"({ pa : 's', pb : 1, pc : 1.10000000000000, pd : true })");
}

TEST_F(ObjectGlobalTest, ObjectLoneIntFun) {
  I(R"(
      type t1 = {
        a:int
      }
  
      fun main() -> t1 {
        var x:t1 = {
          a:1
        }  
      return x
      }

      var y:t1 = main()
      print(y)
    
  )");
  O(R"({ a : 1 })");
}

TEST_F(ObjectGlobalTest, ObjectLoneDecFun) {
  I(R"(
      type t1 = {
        a:deci
      }

      fun main() -> t1 {
              var x:t1 = {
        a:1.0
      }
      return x
      }

      var y:t1 = main()
      print(y)

  )");
  O(R"({ a : 1.00000000000000 })");
}

TEST_F(ObjectGlobalTest, ObjectLoneBoolFun) {
  I(R"(
      type t1 = {
        a:bool
      }

      fun main() -> t1 {
           var x:t1 = {
        a:true
      }
      return x
      }

    
      var y:t1 = main()
      print(y)


  )");
  O(R"({ a : true })");
}

TEST_F(ObjectGlobalTest, ObjectLoneStrFun) {
  I(R"(
      type t1 = {
        a:str
      }

    fun main() -> t1 {
          var x:t1 = {
        a:"hello"
      }
      return x
    }

    var y:t1 = main()
      print(y)


  )");
  O(R"({ a : 'hello' })");
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
  O(R"({ a : 2 }{ a : 1 })");
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
  O(R"({ a : 2.00000000000000 }{ a : 1.00000000000000 })");
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
  O(R"({ a : false }{ a : true })");
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
  O(R"({ a : 'world' }{ a : 'hello' })");
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
  O(R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true })");
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
  O(R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : '', pb : 0, pc : 0.00000000000000, pd : false } }{ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : '', pb : 0, pc : 0.00000000000000, pd : false } })");
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
  O(R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : 'Hello', pb : 0, pc : 0.00000000000000, pd : false } }{ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : 'w', pb : 2, pc : 45.00000000000000, pd : true } })");
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
  O(R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : 'Hello', pb : 0, pc : 0.00000000000000, pd : false } }{ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : 'w', pb : 2, pc : 45.00000000000000, pd : true } })");
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
  O(R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : 'Hello', pb : 0, pc : 0.00000000000000, pd : false } }{ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : 'w', pb : 2, pc : 45.00000000000000, pd : true } }{ a : 'hello2', b : 110, c : 110.09999999999999, d : true, p : { pa : 'wj', pb : 20, pc : 47.00000000000000, pd : false } }{ a : 'hello2', b : 110, c : 110.09999999999999, d : true, p : { pa : 'w', pb : 2, pc : 45.00000000000000, pd : true } })");
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
  O(R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : 'hello', pb : 2, pc : 45.00000000000000, pd : true } }{ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : 'g', pb : 1, pc : -45.10000000000000, pd : false } })");
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
  O(R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : 'hello', pb : 2, pc : -45.10000000000000, pd : true } }{ a : 'hello2', b : 110, c : 110.09999999999999, d : true, p : { pa : 'wj', pb : 20, pc : 47.00000000000000, pd : false } }{ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : 'wj', pb : 20, pc : 47.00000000000000, pd : false } }{ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : 'wj', pb : 20, pc : 47.00000000000000, pd : false } })");
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
  O(R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : 'x', pb : 10, pc : 1.00000000000000, pd : true } })");
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
  O(R"({ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : '', pb : 0, pc : 0.00000000000000, pd : false } }{ a : 'hello2', b : 110, c : 110.09999999999999, d : true, p : { pa : 'wj', pb : 20, pc : 47.00000000000000, pd : false } })");
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


    fun main(y:t1) -> t1 {

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
    z = main(x)
     print(z)

  )");
  O(R"({ a : 'gog', b : 1, c : 1.10000000000000, d : true, p : { pa : '', pb : 0, pc : 0.00000000000000, pd : false } }
{ a : 'hello', b : 10, c : 10.10000000000000, d : true, p : { pa : 'b', pb : 1, pc : 1.10000000000000, pd : true } }
{ a : 'hello2', b : 110, c : 110.09999999999999, d : true, p : { pa : 'wj', pb : 20, pc : 47.00000000000000, pd : false } })");
}

#endif