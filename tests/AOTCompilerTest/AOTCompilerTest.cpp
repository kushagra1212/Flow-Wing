#include "AOTCompilerTest.h"

AOTCompilerTest::AOTCompilerTest() {
  compiler = std::make_unique<AOTCompiler>();
}

void AOTCompilerTest::SetUp(bool captureStderr) {
  if (captureStderr) {
    testing::internal::CaptureStderr();
  } else {
    testing::internal::CaptureStdout();
  }
}
void AOTCompilerTest::TearDown() {}

void AOTCompilerTest::setInput(const std::string &input) {

  compiler->text.push_back(input);
}

std::string AOTCompilerTest::getOutput() const {
  return testing::internal::GetCapturedStdout();
}
std::string AOTCompilerTest::getErrorOutput() const {
  return testing::internal::GetCapturedStderr();
}
void AOTCompilerTest::runEvaluator(std::istream &inputStream,
                                   std::ostream &outputStream) {
  compiler->runTests(inputStream, outputStream);
}
