#include "BinaryOperationTest.h"

BinaryOperationTest::BinaryOperationTest() { repl = std::make_unique<Repl>(); }

void BinaryOperationTest::SetUp() {
  saved_cout_buf = std::cout.rdbuf(output_stream.rdbuf());
}
void BinaryOperationTest::TearDown() { std::cout.rdbuf(saved_cout_buf); }

void BinaryOperationTest::setInput(const std::string &input) {
  input_stream.str(input);
}

std::string BinaryOperationTest::getOutput() const {
  return output_stream.str();
}
void BinaryOperationTest::runEvaluator() {

  repl->runTests(input_stream, output_stream);
}