#include "JITCompilerTest.h"

JITCompilerTest::JITCompilerTest() {
  jit_compiler = std::make_unique<JITCompiler>();
}

void JITCompilerTest::SetUp() { testing::internal::CaptureStdout(); }
void JITCompilerTest::TearDown() {}

void JITCompilerTest::setInput(const std::string &input) {

  jit_compiler->text.push_back(input);
}

std::string JITCompilerTest::getOutput() const {
  return testing::internal::GetCapturedStdout();
}
void JITCompilerTest::runEvaluator() {
  jit_compiler->runTests(std::cin, std::cout);
}
