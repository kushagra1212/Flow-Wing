#include "ReplTest.h"

ReplTest::ReplTest() { repl = std::make_unique<Repl>(); }

void ReplTest::SetUp() {
  saved_cout_buf = std::cout.rdbuf(output_stream.rdbuf());
}
void ReplTest::TearDown() { std::cout.rdbuf(saved_cout_buf); }

void ReplTest::setInput(const std::string &input) { input_stream.str(input); }

std::string ReplTest::getOutput() const { return output_stream.str(); }
void ReplTest::runEvaluator() { repl->runTests(input_stream, output_stream); }

#ifdef REPL_TEST_MODE

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

#endif