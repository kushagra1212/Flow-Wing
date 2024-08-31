#include "BinaryOperationTest.h"

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
