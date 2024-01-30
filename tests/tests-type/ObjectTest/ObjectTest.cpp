#include "ObjectTest.h"

ObjectTest::ObjectTest() {
#ifdef JIT_TEST_MODE
  _test = std::make_unique<JITCompilerTest>();
#endif

#ifdef REPL_TEST_MODE
  _test = std::make_unique<ReplTest>();
#endif
}

void ObjectTest::SetUp() { _test->SetUp(); }

void ObjectTest::TearDown() { _test->TearDown(); }

void ObjectTest::setInput(const std::string &input) { _test->setInput(input); }

std::string ObjectTest::getOutput() const { return _test->getOutput(); }

void ObjectTest::runEvaluator() { _test->runEvaluator(); }

#ifdef JIT_TEST_MODE

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

TEST_F(ObjectTest, SelfType) {
  I(R"(
        type type1 = {
            name: str,
            age: int,
            height: deci,
            type1: type1,
        }

        var a:type1 = {
            name: "Kushagra",
            age: 30,
            height: 5.10,
            type1: {
                name: "Rathore",
            }
        }

        print(a)

    )");

  O("{ name : 'Kushagra', age : 30, height : 5.10000000000000, type1 : { name "
    ": 'Rathore', age : 0, height : 0.00000000000000, type1 :  } }");
}

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

TEST_F(ObjectTest, SelfTypeScoped) {
  I(R"(
       {
         type type1 = {
            name: str,
            age: int,
            height: deci,
            type1: type1,
        }

        var a:type1 = {
            name: "Kushagra",
            age: 30,
            height: 5.10,
            type1: {
                name: "Rathore",
            }
        }

        print(a)
       }

    )");

  O("{ name : 'Kushagra', age : 30, height : 5.10000000000000, type1 : { name "
    ": 'Rathore', age : 0, height : 0.00000000000000, type1 :  } }");
}

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

#endif