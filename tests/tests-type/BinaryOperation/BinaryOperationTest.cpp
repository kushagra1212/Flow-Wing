#include "BinaryOperationTest.h"

BinaryOperationTest::BinaryOperationTest() {
  _test = std::move(FlowWing::getTest());
}

void BinaryOperationTest::SetUp() { _test->SetUp(); }

void BinaryOperationTest::TearDown() { _test->TearDown(); }

void BinaryOperationTest::setInput(const std::string &input) {

  std::string latestInput = "";

#if defined(JIT_TEST_MODE) || defined(AOT_TEST_MODE)
  latestInput = ("print(" + input + ")");
#endif

#ifdef REPL_TEST_MODE
  latestInput = input;
#endif

  _test->setInput(latestInput);
}

std::string BinaryOperationTest::getOutput() const {
  return _test->getOutput();
}

void BinaryOperationTest::runEvaluator() { _test->runEvaluator(); }
