#pragma once

#include "../../Common.h"

class IOHandler {

public:
  IOHandler() : _test(std::move(Tests::FlowWing::getTest())) {}

  virtual inline void setInput(const std::string &input) {
    _test->setInput(input);
  }

  virtual inline std::string getOutput() const { return _test->getOutput(); }

  virtual inline void runEvaluator() { _test->runEvaluator(); }

  virtual inline auto I(const std::string input) -> void {
    setInput(input);
    runEvaluator();
  }

  std::unique_ptr<BaseTest> _test;
};