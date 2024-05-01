#ifndef REPL_TEST_H
#define REPL_TEST_H

#include "../../src/REPL/Repl.h"
#include "../BaseTest/BaseTest.h"

class ReplTest : public BaseTest {
public:
  ReplTest();
  void SetUp();
  void TearDown();
  void setInput(const std::string &input);
  void runEvaluator();
  std::string getOutput() const;

  std::unique_ptr<Repl> repl;
};

#endif // REPL_TEST_H