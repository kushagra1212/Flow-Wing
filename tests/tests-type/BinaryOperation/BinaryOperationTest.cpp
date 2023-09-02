#include "BinaryOperationTest.h"

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
  std::unique_ptr<Repl> repl = std::make_unique<Repl>();
  repl->runForTest(input_stream, output_stream);
}
