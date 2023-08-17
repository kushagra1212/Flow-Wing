#include "ReplTest.h"

void ReplTest::SetUp() {
  // Set up common objects or resources here
  // For example, initialize your REPL instance
  repl = std::make_unique<Repl>(true);
}

void ReplTest::TearDown() {
  // Clean up common objects or resources
  repl.reset();
}

std::string ReplTest::runReplWithInput(const std::string &input) {
  std::stringstream captured_output;
  std::streambuf *cout_backup = std::cout.rdbuf();
  std::cout.rdbuf(captured_output.rdbuf());

  repl->addTextString(input);
  std::string output = repl->runForTest(std::cin, std::cout);

  std::cout.rdbuf(cout_backup);

  return output;
}
