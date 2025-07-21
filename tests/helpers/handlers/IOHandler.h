#pragma once

#include "../../Common.h"
using namespace FLOW_WING::DIAGNOSTIC;
class IOHandler {

public:
  IOHandler() : _test(std::move(Tests::FlowWing::getTest())) {}

  virtual inline void setInput(const std::string &input) {
    _test->setInput(input);
  }

  virtual inline std::string getOutput() const { return _test->getOutput(); }

  virtual inline std::string getErrorOutput() const {
    return _test->getErrorOutput();
  }

  virtual inline void runEvaluator(std::istream &inputStream = std::cin,
                                   std::ostream &outputStream = std::cout) {
    _test->runEvaluator(inputStream, outputStream);
  }

  virtual inline auto I(const std::string input) -> void {
    setInput(input);
    runEvaluator();
  }

  virtual inline auto IE(const std::string input) -> void {
    setInput(input);
    runEvaluator(std::cin, std::cerr);
  }

  virtual inline auto EXPECT_ERROR_CODE(const DiagnosticCode &errorCode)
      -> void {

    EXPECT_TRUE(getErrorOutput().find(getErrorCode(errorCode)) !=
                std::string::npos);
  }

  std::unique_ptr<BaseTest> _test;
};