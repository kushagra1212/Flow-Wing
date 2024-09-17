#include "AOTCompilerTest.h"

AOTCompilerTest::AOTCompilerTest() {}

void AOTCompilerTest::SetUp() {
  compiler = std::make_unique<AOTCompiler>();
  testing::internal::CaptureStdout();
}
void AOTCompilerTest::TearDown() {}

void AOTCompilerTest::setInput(const std::string &input) {

  compiler->text.push_back(input);
}

std::string AOTCompilerTest::getOutput() const {
  return testing::internal::GetCapturedStdout();
}
void AOTCompilerTest::runEvaluator() {
  compiler->runTests(std::cin, std::cout);
}
