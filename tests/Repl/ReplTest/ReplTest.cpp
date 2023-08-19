#include "ReplTest.h"

ReplTest::ReplTest() { repl = std::make_unique<Repl>(true); }

void ReplTest::SetUp() {}

void ReplTest::TearDown() {}

std::string ReplTest::runReplWithInput(const std::string &input) {
  cout_backup = std::cout.rdbuf();
  std::cout.rdbuf(captured_output.rdbuf());
  repl->addTextString(input);
  repl->runForTest(std::cin, std::cout);
  std::cout.rdbuf(cout_backup);
  return captured_output.str();
}
std::string ReplTest::runReplWithInputPrint(const std::string &input) {

  testing::internal::CaptureStdout();

  const std::string &output = runReplWithInput(input);

  return testing::internal::GetCapturedStdout();
}
