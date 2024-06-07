#include "FunctionTest.h"

FunctionTest::FunctionTest() { _test = std::move(FlowWing::getTest()); }

void FunctionTest::SetUp() { _test->SetUp(); }

void FunctionTest::TearDown() { _test->TearDown(); }

void FunctionTest::setInput(const std::string &input) {
  _test->setInput(input);
}

std::string FunctionTest::getOutput() const { return _test->getOutput(); }

void FunctionTest::runEvaluator() { _test->runEvaluator(); }
#if defined(JIT_TEST_MODE) || defined(AOT_TEST_MODE)

// TEST_F(FunctionTest, F) {
//   I(R"(
// fun gS() -> str  {
//   return "Something"
// }

// fun gI() -> int   {
//   return 11
// }
// {
//     var x:deci = Decimal(input(gS()))
// print("x: ",x+2)
// var y:int =  Int32(input(gI()))
// print("y :",y+2)

//   }

// var x:deci = Decimal(input("Enter"))
// print("x: ",x+2)
// var y:int =  Int32(input("Enter"))
// print("y :",y+2)
// var z:bool = Bool(input("Enter Bool: "))
// print("z :",z+2)
// var s:str = input("Enter")
// print("s: ",s+2)
// var ss:str =  String(input("Enter String: "))
// print("ss: ",ss+2)
//     )");

//   O(R"(22222222)");
// }

#endif