#include "JITCompilerTest.h"
#include "gtest/gtest.h"

JITCompilerTest::JITCompilerTest() {
  jit_compiler = std::make_unique<JITCompiler>();
}

void JITCompilerTest::SetUp(bool captureStderr) {
  if (captureStderr) {
    testing::internal::CaptureStderr();
  } else {
    testing::internal::CaptureStdout();
  }
}
void JITCompilerTest::TearDown() {}

void JITCompilerTest::setInput(const std::string &input) {
  jit_compiler->text.push_back(input);
}

std::string JITCompilerTest::getOutput() const {
  return testing::internal::GetCapturedStdout();
}
std::string JITCompilerTest::getErrorOutput() const {
  return testing::internal::GetCapturedStderr();
}
void JITCompilerTest::runEvaluator(std::istream &inputStream,
                                   std::ostream &outputStream) {
  jit_compiler->runTests(inputStream, outputStream);
}
