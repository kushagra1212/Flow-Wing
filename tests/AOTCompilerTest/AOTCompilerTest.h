#ifndef AOT_COMPILER_TEST_H
#define AOT_COMPILER_TEST_H

#include "../../src/compiler/AOTCompiler/AOTCompiler.h"
#include "../BaseTest/BaseTest.h"

class AOTCompilerTest : public BaseTest {
public:
  AOTCompilerTest();
  void SetUp();
  void TearDown();
  void setInput(const std::string &input);
  void runEvaluator();
  std::string getOutput() const;

  std::unique_ptr<AOTCompiler> compiler;
};

#endif // JIT_COMPILER_TEST_H