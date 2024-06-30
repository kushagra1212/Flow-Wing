#include "ObjectTest.h"

ObjectTest::ObjectTest() { _test = std::move(Tests::FlowWing::getTest()); }

void ObjectTest::SetUp() { _test->SetUp(); }

void ObjectTest::TearDown() { _test->TearDown(); }

void ObjectTest::setInput(const std::string &input) { _test->setInput(input); }

std::string ObjectTest::getOutput() const { return _test->getOutput(); }

void ObjectTest::runEvaluator() { _test->runEvaluator(); }

#if defined(JIT_TEST_MODE) || defined(AOT_TEST_MODE)

TEST_F(ObjectTest, DefineCustomType) {
  I(R"(
        type my = {
            name: str,
            age: int,
            height: deci,
            weight: deci,
            isEmployed: bool,
        }

    )");

  O("");
}

TEST_F(ObjectTest, DefineCustomTypeUse) {
  I(R"(
        type my = {
            name: str,
            age: int,
            height: deci,
            weight: deci,
            isEmployed: bool,
        }

        var a:my = {
            name: "Kushagra",
            age: 30,
            height: 5.10,
            weight: 50.5,
        }

        print(a)

    )");

  O("{ name : 'Kushagra', age : 30, height : 5.10000000000000, weight : "
    "50.50000000000000, isEmployed : false }");
}

TEST_F(ObjectTest, DefineCustomTypeUseDefaultValues) {
  I(R"(
        type my = {
            name: str,
            age: int,
            height: deci,
            weight: deci,
            isEmployed: bool,
        }

        var a:my = {}

        print(a)

    )");

  O("{ name : '', age : 0, height : 0.00000000000000, weight : "
    "0.00000000000000, isEmployed : false }");
}

TEST_F(ObjectTest, DefineCustomTypeUseDefaultValues2) {
  I(R"(
        type my = {
            name: str,
            age: int,
            height: deci,
            weight: deci,
            isEmployed: bool,
        }

        var a:my = {
            name: "Kushagra",
        }

        print(a)

    )");

  O("{ name : 'Kushagra', age : 0, height : 0.00000000000000, weight : "
    "0.00000000000000, isEmployed : false }");
}

TEST_F(ObjectTest, DefineCustomTypeUseDefaultValuesCompletePropertyPrint) {
  I(R"(
        type my = {
            name: str,
            age: int,
            height: deci,
            weight: deci,
            isEmployed: bool,
        }

        var a:my = {
            name: "Kushagra",
            age: 30,
            height: 5.10,
            weight: 50.5,
            isEmployed: true
        }

        print(a.name)
        print(a.age)
        print(a.height)
        print(a.weight)
        print(a.isEmployed)

    )");

  O("Kushagra305.1000000000000050.50000000000000true");
}

TEST_F(ObjectTest, MultipleCustomTypes) {
  I(R"(
        type obj = {
            height: deci,
            weight: deci,
            isEmployed: bool,
        }

        type my2 = {
            name: str,
            age: int,
            obj: obj,
        }

        var a:my2 = {
            name: "Kushagra",
            age: 30,
            obj: {
                height: 5.10,
                weight: 50.5,
                isEmployed: true
            }
        }

        print(a)

    )");

  O("{ name : 'Kushagra', age : 30, obj : { height : 5.10000000000000, weight "
    ": 50.50000000000000, isEmployed : true } }");
}

TEST_F(ObjectTest, PartialFill) {
  I(R"(
        type my = {
            name: str,
            age: int,
            height: deci,
            weight: deci,
            isEmployed: bool,
        } 


        var a:my = {
            name: "Kushagra",
        }

        print(a)

    )");

  O("{ name : 'Kushagra', age : 0, height : 0.00000000000000, weight : "
    "0.00000000000000, isEmployed : false }");
}

// TEST_F(ObjectTest, SelfType) {
//   I(R"(
//         type par = {
//           name : string
//         }

//         type type1 = {
//             name: str,
//             age: int,
//             height: deci,
//             type1: par,
//         }

//         var a:type1 = {
//             name: "Kushagra",
//             age: 30,
//             height: 5.10,
//             type1: {
//                 name: "Rathore",
//             }
//         }

//         print(a)

//     )");

//   O("{ name : 'Kushagra', age : 30, height : 5.10000000000000, type1 : { name
//   "
//     ": 'Rathore', age : 0, height : 0.00000000000000, type1 :  } }");
// }

// Inside Scope

TEST_F(ObjectTest, DefineCustomTypeScoped) {
  I(R"(
        {
                  type my = {
            name: str,
            age: int,
            height: deci,
            weight: deci,
            isEmployed: bool,
        }
        }

    )");

  O("");
}

TEST_F(ObjectTest, DefineCustomTypeUseScoped) {
  I(R"(
        {
           type my = {
            name: str,
            age: int,
            height: deci,
            weight: deci,
            isEmployed: bool,
        }

        var a:my = {
            name: "Kushagra",
            age: 30,
            height: 5.10,
            weight: 50.5,
            isEmployed:false
        }

        print(a)
        }

    )");

  O("{ name : 'Kushagra', age : 30, height : 5.10000000000000, weight : "
    "50.50000000000000, isEmployed : false }");
}

TEST_F(ObjectTest, DefineCustomTypeUseDefaultValuesScoped) {
  I(R"(
       {
         type my = {
            name: str,
            age: int,
            height: deci,
            weight: deci,
            isEmployed: bool,
        }

        var a:my = {}

        print(a)
       }

    )");

  O("{ name : '', age : 0, height : 0.00000000000000, weight : "
    "0.00000000000000, isEmployed : false }");
}

TEST_F(ObjectTest, DefineCustomTypeUseDefaultValues2Scoped) {
  I(R"(
       {
         type my = {
            name: str,
            age: int,
            height: deci,
            weight: deci,
            isEmployed: bool,
        }

        var a:my = {
            name: "Kushagra",
        }

        print(a)
       }

    )");

  O("{ name : 'Kushagra', age : 0, height : 0.00000000000000, weight : "
    "0.00000000000000, isEmployed : false }");
}

TEST_F(ObjectTest,
       DefineCustomTypeUseDefaultValuesCompletePropertyPrintScoped) {
  I(R"(
       {
         type my = {
            name: str,
            age: int,
            height: deci,
            weight: deci,
            isEmployed: bool,
        }

        var a:my = {
            name: "Kushagra",
            age: 30,
            height: 5.10,
            weight: 50.5,
            isEmployed: true
        }

        print(a.name)
        print(a.age)
        print(a.height)
        print(a.weight)
        print(a.isEmployed)
       }

    )");

  O("Kushagra305.1000000000000050.50000000000000true");
}

TEST_F(ObjectTest, MultipleCustomTypesScoped) {
  I(R"(
       {
         type obj = {
            height: deci,
            weight: deci,
            isEmployed: bool,
        }

        type my2 = {
            name: str,
            age: int,
            obj: obj,
        }

        var a:my2 = {
            name: "Kushagra",
            age: 30,
            obj: {
                height: 5.10,
                weight: 50.5,
                isEmployed: true
            }
        }

        print(a)
       }

    )");

  O("{ name : 'Kushagra', age : 30, obj : { height : 5.10000000000000, weight "
    ": 50.50000000000000, isEmployed : true } }");
}

TEST_F(ObjectTest, PartialFillScoped) {
  I(R"(
       {
         type my = {
            name: str,
            age: int,
            height: deci,
            weight: deci,
            isEmployed: bool,
        } 


        var a:my = {
            name: "Kushagra",
        }

        print(a)
       }

    )");

  O("{ name : 'Kushagra', age : 0, height : 0.00000000000000, weight : "
    "0.00000000000000, isEmployed : false }");
}

// TEST_F(ObjectTest, SelfTypeScoped) {
//   I(R"(
//        {
//          type type1 = {
//             name: str,
//             age: int,
//             height: deci,
//             type1: type1,
//         }

//         var a:type1 = {
//             name: "Kushagra",
//             age: 30,
//             height: 5.10,
//             type1: {
//                 name: "Rathore",
//             }
//         }

//         print(a)
//        }

//     )");

//   O("{ name : 'Kushagra', age : 30, height : 5.10000000000000, type1 : { name
//   "
//     ": 'Rathore', age : 0, height : 0.00000000000000, type1 :  } }");
// }

TEST_F(ObjectTest, MultipleCustomTypesPrintSubobjectScoped) {
  I(R"(
       {
         type obj = {
            height: deci,
            weight: deci,
            isEmployed: bool,
        }

        type my2 = {
            name: str,
            age: int,
            obj: obj,
        }

        var a:my2 = {
            name: "Kushagra",
            age: 30,
            obj: {
                height: 5.10,
                weight: 50.5,
                isEmployed: true
            }
        }

        print(a)
        print(a.obj)
       }

    )");

  O("{ name : 'Kushagra', age : 30, obj : { height : 5.10000000000000, weight "
    ": 50.50000000000000, isEmployed : true } }{ height : 5.10000000000000, "
    "weight : 50.50000000000000, isEmployed : true }");
}

TEST_F(ObjectTest, MultipleCustomTypesPrintSubobject) {
  I(R"(
         type obj = {
            height: deci,
            weight: deci,
            isEmployed: bool,
        }

        type my2 = {
            name: str,
            age: int,
            obj: obj,
        }

        var a:my2 = {
            name: "Kushagra",
            age: 30,
            obj: {
                height: 5.10,
                weight: 50.5,
                isEmployed: true
            }
        }

        print(a)
        print(a.obj)

    )");

  O("{ name : 'Kushagra', age : 30, obj : { height : 5.10000000000000, weight "
    ": 50.50000000000000, isEmployed : true } }{ height : 5.10000000000000, "
    "weight : 50.50000000000000, isEmployed : true }");
}

TEST_F(ObjectTest, AssignObjectSimple) {
  I(R"(
         type obj = {
          a:int,
          b:deci,
          c:bool,
          d:str
        }
        var x:obj = { 
          a:1,
          b:2.0,
          c:true,
          d:"hello"
        }
        print(x)
        x = {
          a:100,
          b:200.0,
          c:false,
          d:"world"
        }

        print(x)

    )");

  O("{ a : 1, b : 2.00000000000000, c : true, d : 'hello' }{ a : 100, b : "
    "200.00000000000000, c : false, d : 'world' }");
}

TEST_F(ObjectTest, AssignObjectSimpleNested1) {
  I(R"(
{

         type obj = {
          a:int,
          b:deci,
          c:bool,
          d:str
        }
        var x:obj = { 
          a:1,
          b:2.0,
          c:true,
          d:"hello"
        }
        print(x)
        x = {
          a:100,
          b:200.0,
          c:false,
          d:"world"
        }

        print(x)

}

    )");

  O("{ a : 1, b : 2.00000000000000, c : true, d : 'hello' }{ a : 100, b : "
    "200.00000000000000, c : false, d : 'world' }");
}

TEST_F(ObjectTest, AssignObjectSimpleNested2) {
  I(R"(
         type obj = {
          a:int,
          b:deci,
          c:bool,
          d:str
        }

{


        var x:obj = { 
          a:1,
          b:2.0,
          c:true,
          d:"hello"
        }
        print(x)
        x = {
          a:100,
          b:200.0,
          c:false,
          d:"world"
        }

        print(x)

}

    )");

  O("{ a : 1, b : 2.00000000000000, c : true, d : 'hello' }{ a : 100, b : "
    "200.00000000000000, c : false, d : 'world' }");
}

TEST_F(ObjectTest, AssignObjectSimpleNested3) {
  I(R"(
         type obj = {
          a:int,
          b:deci,
          c:bool,
          d:str
        }
        var x:obj = { 
          a:1,
          b:2.0,
          c:true,
          d:"hello"
        }
{



        print(x)
        x = {
          a:100,
          b:200.0,
          c:false,
          d:"world"
        }

        print(x)

}

    )");

  O("{ a : 1, b : 2.00000000000000, c : true, d : 'hello' }{ a : 100, b : "
    "200.00000000000000, c : false, d : 'world' }");
}

TEST_F(ObjectTest, AssignObjectSimpleNested4) {
  I(R"(
         type obj = {
          a:int,
          b:deci,
          c:bool,
          d:str
        }
        var x:obj = { 
          a:1,
          b:2.0,
          c:true,
          d:"hello"
        }
{



        print(x)
        x = {
          a:100,
          b:200.0,
          c:false,
          d:"world"
        }


}
        print(x)

    )");

  O("{ a : 1, b : 2.00000000000000, c : true, d : 'hello' }{ a : 100, b : "
    "200.00000000000000, c : false, d : 'world' }");
}

TEST_F(ObjectTest, AssignValueSimple) {
  I(R"(
         type obj = {
          a:int,
          b:deci,
          c:bool,
          d:str
        }
        var x:obj = { 
          a:1,
          b:2.0,
          c:true,
          d:"hello"
        }



        print(x)
        x.a = 100
        x.b = 200.0
        x.c = false
        x.d = "world"
        print(x)

    )");

  O("{ a : 1, b : 2.00000000000000, c : true, d : 'hello' }{ a : 100, b : "
    "200.00000000000000, c : false, d : 'world' }");
}

TEST_F(ObjectTest, AssignValueSimpleScope) {
  I(R"(
{         type obj = {
          a:int,
          b:deci,
          c:bool,
          d:str
        }
        var x:obj = { 
          a:1,
          b:2.0,
          c:true,
          d:"hello"
        }



        print(x)
        x.a = 100
        x.b = 200.0
        x.c = false
        x.d = "world"
        print(x)
        
      }

    )");

  O("{ a : 1, b : 2.00000000000000, c : true, d : 'hello' }{ a : 100, b : "
    "200.00000000000000, c : false, d : 'world' }");
}

TEST_F(ObjectTest, AssignValueSimpleObject) {
  I(R"(
        type Parent = {
          a:int
        }

         type obj = {
          a:int,
          b:deci,
          c:bool,
          d:str,
          p:Parent
        }
        var x:obj = { 
          a:1,
          b:2.0,
          c:true,
          d:"hello",
          p:{ a : 100 }
        }
        print(x)
        x.a = 100
        x.b = 200.0
        x.c = false
        x.d = "world"
        x.p.a = 400
        print(x)

    )");

  O("{ a : 1, b : 2.00000000000000, c : true, d : 'hello', p : { a : 100 } }{ "
    "a : 100, b : 200.00000000000000, c : false, d : 'world', p : { a : 400 } "
    "}");
}
TEST_F(ObjectTest, AssignValueSimpleObject2) {
  I(R"(
        type Parent = {
          a:int
        }

         type obj = {
          a:int,
          b:deci,
          c:bool,
          d:str,
          p:Parent
        }
        var x:obj = { 
          a:1,
          b:2.0,
          c:true,
          d:"hello",
          p:{ a : 100 }
        }
        print(x)
        x.a = 100
        x.b = 200.0
        x.c = false
        x.d = "world"
        x.p = { a : 400 }
        print(x)

    )");

  O("{ a : 1, b : 2.00000000000000, c : true, d : 'hello', p : { a : 100 } }{ "
    "a : 100, b : 200.00000000000000, c : false, d : 'world', p : { a : 400 } "
    "}");
}
TEST_F(ObjectTest, AssignValueSimpleObject2Constant) {
  I(R"(
  type Position = {
  x: int,
  y: int
}

const screenWidth: int  = 1000
const screenHeight: int = 500
const side: int = 10

fun getN() -> int {
  return 2
}
  var pos: Position = { 
    x: getN(), 
    y: getN()
  }
  print(pos.x)
  pos.x =  pos.x -  pos.x % side
  pos.y = pos.y - pos.y % side
    )");

  O("2");
}
// TEST_F(ObjectTest, AssignCompleteObject) {
//   I(R"(
//         type type1 = {
//             name: str,
//             age: int,
//             height: deci,
//             is:bool,
//             type1: type1,
//         }

//         var a:type1 = {
//             name: "Kushagra",
//             age: 30,
//             height: 5.10,
//             is:false,
//             type1: {
//                 name: "Rathore",
//             }
//         }
//         var b:type1 = {}
//         print(b)
//         b = {
//             name: "Kushagra",
//             age: 30,
//             height: 5.10,
//             is:true,
//             type1: {
//                 name: "Rathore",
//             }
//         }
//         print(b)

//     )");

//   O("{ name : '', age : 0, height : 0.00000000000000, is : false, type1 :  }{
//   "
//     "name : 'Kushagra', age : 30, height : 5.10000000000000, is : true, type1
//     "
//     ": { name : 'Rathore', age : 0, height : 0.00000000000000, is : false, "
//     "type1 :  } }");
// }

// TEST_F(ObjectTest, AssignCompleteObjectScope) {
//   I(R"(
// {
//           type type1 = {
//             name: str,
//             age: int,
//             height: deci,
//             is:bool,
//             type1: type1,
//         }

//         var a:type1 = {
//             name: "Kushagra",
//             age: 30,
//             height: 5.10,
//             is:false,
//             type1: {
//                 name: "Rathore",
//             }
//         }
//         var b:type1 = {}
//         print(b)
//         b = {
//             name: "Kushagra",
//             age: 30,
//             height: 5.10,
//             is:true,
//             type1: {
//                 name: "Rathore",
//             }
//         }
//         print(b)
// }

//     )");

//   O("{ name : '', age : 0, height : 0.00000000000000, is : false, type1 :  }{
//   "
//     "name : 'Kushagra', age : 30, height : 5.10000000000000, is : true, type1
//     "
//     ": { name : 'Rathore', age : 0, height : 0.00000000000000, is : false, "
//     "type1 :  } }");
// }

// TEST_F(ObjectTest, AssignCompleteObjectScopeInnerandOuter) {
//   I(R"(
//       type type1 = {
//             name: str,
//             age: int,
//             height: deci,
//             is:bool,
//             type1: type1,
//         }

//         var a:type1 = {
//             name: "Kushagra",
//             age: 30,
//             height: 5.10,
//             is:false,
//             type1: {
//                 name: "Rathore",
//             }
//         }
//         var b:type1 = {}
//         print(b)
//       {
//               b = {
//             name: "Kushagra",
//             age: 30,
//             height: 5.10,
//             is:true,
//             type1: {
//                 name: "Rathore",
//             }
//         }
//         print(b)}

//     )");

//   O("{ name : '', age : 0, height : 0.00000000000000, is : false, type1 :  }{
//   "
//     "name : 'Kushagra', age : 30, height : 5.10000000000000, is : true, type1
//     "
//     ": { name : 'Rathore', age : 0, height : 0.00000000000000, is : false, "
//     "type1 :  } }");
// }

// TEST_F(ObjectTest, AssignCompleteObjectScopeInnerandOuter2) {
//   I(R"(
//       type type1 = {
//             name: str,
//             age: int,
//             height: deci,
//             is:bool,
//             type1: type1,
//         }

//         var a:type1 = {
//             name: "Kushagra",
//             age: 30,
//             height: 5.10,
//             is:false,
//             type1: {
//                 name: "Rathore",
//             }
//         }
//         var b:type1 = {}
//         print(b)
//       {
//               b = {
//             name: "Kushagra",
//             age: 30,
//             height: 5.10,
//             is:true,
//             type1: {
//                 name: "Rathore",
//             }
//         }
//         }

//         print(b)

//     )");

//   O("{ name : '', age : 0, height : 0.00000000000000, is : false, type1 :  }{
//   "
//     "name : 'Kushagra', age : 30, height : 5.10000000000000, is : true, type1
//     "
//     ": { name : 'Rathore', age : 0, height : 0.00000000000000, is : false, "
//     "type1 :  } }");
// }

// TEST_F(ObjectTest, AssignCompleteObjectPartial) {
//   I(R"(
//       type type1 = {
//             name: str,
//             age: int,
//             height: deci,
//             is:bool,
//             type1: type1,
//         }

//         var a:type1 = {
//             name: "Kushagra",
//             age: 30,
//             height: 5.10,
//             is:false,
//             type1: {
//                 name: "Rathore",
//             }
//         }
//         var b:type1 = {}
//         print(b)
//         b.type1 = {
//             name: "Rathore",
//         }
//         print(b)

//     )");

//   O("{ name : '', age : 0, height : 0.00000000000000, is : false, type1 :  }{
//   "
//     "name : '', age : 0, height : 0.00000000000000, is : false, type1 : {
//     name "
//     ": 'Rathore', age : 0, height : 0.00000000000000, is : false, type1 :  }
//     "
//     "}");
// }

// TEST_F(ObjectTest, AssignCompleteObjectPartialScoped) {
//   I(R"(
// {      type type1 = {
//             name: str,
//             age: int,
//             height: deci,
//             is:bool,
//             type1: type1,
//         }

//         var a:type1 = {
//             name: "Kushagra",
//             age: 30,
//             height: 5.10,
//             is:false,
//             type1: {
//                 name: "Rathore",
//             }
//         }
//         var b:type1 = {}
//         print(b)
//         b.type1 = {
//             name: "Rathore",
//         }
//         print(b)}

//     )");

//   O("{ name : '', age : 0, height : 0.00000000000000, is : false, type1 :  }{
//   "
//     "name : '', age : 0, height : 0.00000000000000, is : false, type1 : {
//     name "
//     ": 'Rathore', age : 0, height : 0.00000000000000, is : false, type1 :  }
//     "
//     "}");
// }

// TEST_F(ObjectTest, AssignCompleteObjectPartialScopedInnerandouter) {
//   I(R"(
//       type type1 = {
//             name: str,
//             age: int,
//             height: deci,
//             is:bool,
//             type1: type1,
//         }

//         var a:type1 = {
//             name: "Kushagra",
//             age: 30,
//             height: 5.10,
//             is:false,
//             type1: {
//                 name: "Rathore",
//             }
//         }
//         var b:type1 = {}
//         print(b)
//         {
//         b.type1 = {
//             name: "Rathore",
//         }
//         }
//         print(b)

//     )");

//   O("{ name : '', age : 0, height : 0.00000000000000, is : false, type1 :  }{
//   "
//     "name : '', age : 0, height : 0.00000000000000, is : false, type1 : {
//     name "
//     ": 'Rathore', age : 0, height : 0.00000000000000, is : false, type1 :  }
//     "
//     "}");
// }

// TEST_F(ObjectTest, AssignCompleteObjectPartialScopedInnerandouter2) {
//   I(R"(
//       type type1 = {
//             name: str,
//             age: int,
//             height: deci,
//             is:bool,
//             type1: type1,
//         }

//         var a:type1 = {
//             name: "Kushagra",
//             age: 30,
//             height: 5.10,
//             is:false,
//             type1: {
//                 name: "Rathore",
//             }
//         }
//         var b:type1 = {}
//         print(b)
//         {
//         b.type1 = {
//             name: "Rathore",
//         }

//         print(b)
//         }

//     )");

//   O("{ name : '', age : 0, height : 0.00000000000000, is : false, type1 :  }{
//   "
//     "name : '', age : 0, height : 0.00000000000000, is : false, type1 : {
//     name "
//     ": 'Rathore', age : 0, height : 0.00000000000000, is : false, type1 :  }
//     "
//     "}");
// }

// TEST_F(ObjectTest, AssignFromVariableComplete) {
//   I(R"(
//       type type1 = {
//             name: str,
//             age: int,
//             height: deci,
//             is:bool,
//             type1: type1,
//         }

//         var a:type1 = {
//             name: "Kushagra",
//             age: 30,
//             height: 5.10,
//             is:false,
//             type1: {
//                 name: "Rathore",
//             }
//         }
//         var b:type1 = {}
//         print(b)
//         b = a
//         print(b)

//     )");

//   O("{ name : '', age : 0, height : 0.00000000000000, is : false, type1 :  }{
//   "
//     "name : 'Kushagra', age : 30, height : 5.10000000000000, is : false,
//     type1 "
//     ": { name : 'Rathore', age : 0, height : 0.00000000000000, is : false, "
//     "type1 :  } }");
// }

// TEST_F(ObjectTest, AssignFromVariableCompleteScoped) {
//   I(R"(
// {
//         type type1 = {
//             name: str,
//             age: int,
//             height: deci,
//             is:bool,
//             type1: type1,
//         }

//         var a:type1 = {
//             name: "Kushagra",
//             age: 30,
//             height: 5.10,
//             is:false,
//             type1: {
//                 name: "Rathore",
//             }
//         }
//         var b:type1 = {}
//         print(b)
//         b = a
//         print(b)
// }

//     )");

//   O("{ name : '', age : 0, height : 0.00000000000000, is : false, type1 :  }{
//   "
//     "name : 'Kushagra', age : 30, height : 5.10000000000000, is : false,
//     type1 "
//     ": { name : 'Rathore', age : 0, height : 0.00000000000000, is : false, "
//     "type1 :  } }");
// }

// TEST_F(ObjectTest, AssignFromVariableCompleteScopedInnerOuter) {
//   I(R"(
//             type type1 = {
//             name: str,
//             age: int,
//             height: deci,
//             is:bool,
//             type1: type1,
//         }

//         var a:type1 = {
//             name: "Kushagra",
//             age: 30,
//             height: 5.10,
//             is:false,
//             type1: {
//                 name: "Rathore",
//             }
//         }
// {
//         var b:type1 = {}
//         print(b)
//         b = a
//         print(b)
// }
//     )");

//   O("{ name : '', age : 0, height : 0.00000000000000, is : false, type1 :  }{
//   "
//     "name : 'Kushagra', age : 30, height : 5.10000000000000, is : false,
//     type1 "
//     ": { name : 'Rathore', age : 0, height : 0.00000000000000, is : false, "
//     "type1 :  } }");
// }
// TEST_F(ObjectTest, AssignFromVariableCompleteScopedInnerOuter2) {
//   I(R"(
//             type type1 = {
//             name: str,
//             age: int,
//             height: deci,
//             is:bool,
//             type1: type1,
//         }

//         var a:type1 = {
//             name: "Kushagra",
//             age: 30,
//             height: 5.10,
//             is:false,
//             type1: {
//                 name: "Rathore",
//             }
//         }

//         var b:type1 = {}
//         print(b)
// {
//           b = a
//         print(b)
// }
//     )");

//   O("{ name : '', age : 0, height : 0.00000000000000, is : false, type1 :  }{
//   "
//     "name : 'Kushagra', age : 30, height : 5.10000000000000, is : false,
//     type1 "
//     ": { name : 'Rathore', age : 0, height : 0.00000000000000, is : false, "
//     "type1 :  } }");
// }
// TEST_F(ObjectTest, AssignFromVariableCompleteScopedInnerOuter3) {
//   I(R"(
//             type type1 = {
//             name: str,
//             age: int,
//             height: deci,
//             is:bool,
//             type1: type1,
//         }

//         var a:type1 = {
//             name: "Kushagra",
//             age: 30,
//             height: 5.10,
//             is:false,
//             type1: {
//                 name: "Rathore",
//             }
//         }

//         var b:type1 = {}
//         print(b)
// {
//           b = a
// }
//         print(b)
//     )");

//   O("{ name : '', age : 0, height : 0.00000000000000, is : false, type1 :  }{
//   "
//     "name : 'Kushagra', age : 30, height : 5.10000000000000, is : false,
//     type1 "
//     ": { name : 'Rathore', age : 0, height : 0.00000000000000, is : false, "
//     "type1 :  } }");
// }

// TEST_F(ObjectTest, AssignFromVariablePartialCompleteScopedInnerOuter) {
//   I(R"(
//             type type1 = {
//             name: str,
//             age: int,
//             height: deci,
//             is:bool,
//             type1: type1,
//         }

//         var a:type1 = {
//             name: "Kushagra",
//             age: 30,
//             height: 5.10,
//             is:false,
//             type1: {
//                 name: "Rathore",
//             }
//         }

//         var b:type1 = {}
//         print(b)
//           b.name = a.name
//           b.age = a.age
//           b.height = a.height
//           b.is = a.is
//           b.type1 = a.type1
//         print(b)
//     )");

//   O("{ name : '', age : 0, height : 0.00000000000000, is : false, type1 :  }{
//   "
//     "name : 'Kushagra', age : 30, height : 5.10000000000000, is : false,
//     type1 "
//     ": { name : 'Rathore', age : 0, height : 0.00000000000000, is : false, "
//     "type1 :  } }");
// }

// TEST_F(ObjectTest, AssignFromVariablePartialCompleteScopedInnerOuter2) {
//   I(R"(
// {
//               type type1 = {
//             name: str,
//             age: int,
//             height: deci,
//             is:bool,
//             type1: type1,
//         }

//         var a:type1 = {
//             name: "Kushagra",
//             age: 30,
//             height: 5.10,
//             is:false,
//             type1: {
//                 name: "Rathore",
//             }
//         }

//         var b:type1 = {}
//         print(b)
//           b.name = a.name
//           b.age = a.age
//           b.height = a.height
//           b.is = a.is
//           b.type1 = a.type1
//         print(b)
// }
//     )");

//   O("{ name : '', age : 0, height : 0.00000000000000, is : false, type1 :  }{
//   "
//     "name : 'Kushagra', age : 30, height : 5.10000000000000, is : false,
//     type1 "
//     ": { name : 'Rathore', age : 0, height : 0.00000000000000, is : false, "
//     "type1 :  } }");
// }

// TEST_F(ObjectTest, AssignFromVariablePartialCompleteScopedInnerOuter3) {
//   I(R"(
//             type type1 = {
//             name: str,
//             age: int,
//             height: deci,
//             is:bool,
//             type1: type1,
//         }

//         var a:type1 = {
//             name: "Kushagra",
//             age: 30,
//             height: 5.10,
//             is:false,
//             type1: {
//                 name: "Rathore",
//             }
//         }

//         var b:type1 = {}
//         print(b)
// {
//                 b.name = a.name
//           b.age = a.age
//           b.height = a.height
//           b.is = a.is
//           b.type1 = a.type1
// }
//         print(b)
//     )");

//   O("{ name : '', age : 0, height : 0.00000000000000, is : false, type1 :  }{
//   "
//     "name : 'Kushagra', age : 30, height : 5.10000000000000, is : false,
//     type1 "
//     ": { name : 'Rathore', age : 0, height : 0.00000000000000, is : false, "
//     "type1 :  } }");
// }

// TEST_F(ObjectTest, AssignFromVariablePartialCompleteScopedInnerOuter4) {
//   I(R"(
//             type type1 = {
//             name: str,
//             age: int,
//             height: deci,
//             is:bool,
//             type1: type1,
//         }

//         var a:type1 = {
//             name: "Kushagra",
//             age: 30,
//             height: 5.10,
//             is:false,
//             type1: {
//                 name: "Rathore",
//             }
//         }

//         var b:type1 = {}
//         print(b)
// {
//                 b.name = a.name
//           b.age = a.age
//           b.height = a.height
//           b.is = a.is
//           b.type1 = a.type1
//         print(b)
// }
//     )");

//   O("{ name : '', age : 0, height : 0.00000000000000, is : false, type1 :  }{
//   "
//     "name : 'Kushagra', age : 30, height : 5.10000000000000, is : false,
//     type1 "
//     ": { name : 'Rathore', age : 0, height : 0.00000000000000, is : false, "
//     "type1 :  } }");
// }

#endif