#include "IndexTest.h"

void IndexTest::SetUp() { _test->SetUp(); }

void IndexTest::TearDown() { _test->TearDown(); }

TEST_F(IndexTest, IndexTestAssignmentBasicInsideClassUsingSelf) {
  I(R"(
class A{
    var x:int[2]
  

    init(x:int[2]) -> nthg {
      self.x[1] = x[1]
    }


  }


  var a: A = new A([2,3])


  print(a.x)
    )");

  EXPECT_EQ(getOutput(), R"([0, 3])");
}
TEST_F(IndexTest, IndexTestAssignmentBasicInsideClassUsingSelfObject) {
  I(R"(

class A{ 

  type T = {
      a:int 
    }
    var x:T[2]
  

    init(x:T[2]) -> nthg {
      self.x[1] = x[1]
    }


  }


  var a: A = new A([{},{a:10}])


  print(a.x)
    )");

  EXPECT_EQ(getOutput(), R"([{ a : 0 }, { a : 10 }])");
}