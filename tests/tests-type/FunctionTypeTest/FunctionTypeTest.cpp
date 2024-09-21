#include "FunctionTypeTest.h"

void FunctionTypeTest::SetUp() { _test->SetUp(); }

void FunctionTypeTest::TearDown() { _test->TearDown(); }

TEST_F(FunctionTypeTest, BasicTest) {
  I(R"(
fun printX(x: int) -> nthg {
    print("Printing X",x)
  }


fun main(f:[(int)-> nthg]) -> nthg {
f(2)
}


  main(printX)
    )");

  EXPECT_EQ(getOutput(), "Printing X2");
}
TEST_F(FunctionTypeTest, BasicWithPrimitiveType) {
  I(R"(
fun printX(x: int,y:deci,p:str,u:bool,ano:[(str)->nthg]) -> nthg {
    print("Printing X",x)
    print(y,p,u)
    ano("Hehe")
  }
fun printS(x: str) -> nthg {
  print("\n from printS",x)
}

fun main(f:[(int,deci,str,bool,[(str)->nthg])-> nthg]) -> nthg {
f(2,2.2,"Sss",false,printS)
}


  main(printX)
    )");

  EXPECT_EQ(getOutput(), R"(Printing X22.20000000000000Sssfalse
 from printSHehe)");
}

TEST_F(FunctionTypeTest, BasicWithPrimitiveType2) {
  I(R"(
fun printX(x: int,y:deci,p:str,u:bool,ano:[(str)->nthg]) -> nthg {
    print("Printing X",x)
    print(y,p,u)
    ano("Hehe")
  }
fun printS(x: str) -> nthg {
  print("\n from printS",x)
}

fun getDeci(y:int,j:str) -> deci  {
    print("\ny",y,"\nj",j)

    return 3.5
  }

fun main(f:[(int,deci,str,bool,[(str)->nthg])-> nthg] , c: [(int,str)->deci]) -> int {
f(2,2.2,"Sss",false,printS)c(23,"getDeci")
return 2
}


  main(printX,getDeci)
    )");

  EXPECT_EQ(getOutput(), R"(Printing X22.20000000000000Sssfalse
 from printSHehe
y23
jgetDeci)");
}
TEST_F(FunctionTypeTest, BasicWithPrimitiveType3) {
  I(R"(
fun printX(x: int,y:deci,p:str,u:bool,ano:[(str)->nthg],d:deci ) -> nthg {
    print("Printing X",x)
    print(y,p,u)
    ano("Hehe")
    print("D",d)
  }
fun printS(x: str) -> nthg {
  print("\n from printS",x)
}

fun getDeci(y:int,j:str) -> deci  {
    print("\ny",y,"\nj",j)

    return 3.5
  }

fun main(f:[(int,deci,str,bool,[(str)->nthg],deci)-> nthg] , c: [(int,str)->deci]) -> int {
f(2,2.2,"Sss",false,printS,c(23,"getDeci"))return 2
}


  main(printX,getDeci)
    )");

  EXPECT_EQ(getOutput(), R"(
y23
jgetDeciPrinting X22.20000000000000Sssfalse
 from printSHeheD3.50000000000000)");
}