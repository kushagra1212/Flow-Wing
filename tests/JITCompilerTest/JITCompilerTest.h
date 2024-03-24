#ifndef JIT_COMPILER_TEST_H
#define JIT_COMPILER_TEST_H

#include "../../src/just-in-time-compiler/JITCompiler.h"
#include "../BaseTest/BaseTest.h"

class JITCompilerTest : public BaseTest {
public:
  JITCompilerTest();
  void SetUp();
  void TearDown();
  void setInput(const std::string &input);
  void runEvaluator();
  std::string getOutput() const;

  std::unique_ptr<JITCompiler> jit_compiler;
};

#endif // JIT_COMPILER_TEST_H