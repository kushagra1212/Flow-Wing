#include "BinaryOperationTest.h"

BinaryOperationTest::BinaryOperationTest() {
#ifdef JIT_TEST_MODE
  _test = std::make_unique<JITCompilerTest>();
#endif

#ifdef REPL_TEST_MODE
  _test = std::make_unique<ReplTest>();
#endif
}

void BinaryOperationTest::SetUp() { _test->SetUp(); }

void BinaryOperationTest::TearDown() { _test->TearDown(); }

void BinaryOperationTest::setInput(const std::string &input) {
#ifdef JIT_TEST_MODE
  _test->setInput("print(" + input + ")");
#endif

#ifdef REPL_TEST_MODE
  _test->setInput(input);
#endif
}

std::string BinaryOperationTest::getOutput() const {
  return _test->getOutput();
}

void BinaryOperationTest::runEvaluator() { _test->runEvaluator(); }
