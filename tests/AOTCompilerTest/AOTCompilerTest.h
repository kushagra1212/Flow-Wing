#ifndef AOT_COMPILER_TEST_H
#define AOT_COMPILER_TEST_H

#include "../../src/compiler/AOTCompiler/AOTCompiler.h"
#include "../BaseTest/BaseTest.h"

class AOTCompilerTest : public BaseTest {
public:
  AOTCompilerTest();
  void SetUp(bool captureStderr = false);
  void TearDown();
  void setInput(const std::string &input);
  void runEvaluator(std::istream &inputStream = std::cin,
                    std::ostream &outputStream = std::cout);
  std::string getOutput() const;
  std::string getErrorOutput() const;

  std::unique_ptr<AOTCompiler> compiler;
};

#endif // JIT_COMPILER_TEST_H