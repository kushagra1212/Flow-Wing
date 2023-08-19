#include "ReplTest.h"

ReplTest::ReplTest() { repl = std::make_unique<Repl>(true); }

void ReplTest::SetUp() {
  cout_backup = std::cout.rdbuf();
  std::cout.rdbuf(captured_output.rdbuf());
}

void ReplTest::TearDown() { std::cout.rdbuf(cout_backup); }

std::string ReplTest::runReplWithInput(const std::string &input) {

  repl->addTextString(input);
  std::string output = repl->runForTest(std::cin, std::cout);
  return output;
}
