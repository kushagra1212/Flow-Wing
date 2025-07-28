/*
 * FlowWing Compiler
 * Copyright (C) 2023-2025 Kushagra Rathore
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#pragma once

#include "src/diagnostics/Diagnostic/DiagnosticCodeData.h"
#include "tests/Common.h"
#include <iostream>

using namespace FLOW_WING::DIAGNOSTIC;
class IOHandler {

public:
  IOHandler() : _test((Tests::FlowWing::getTest())) {}

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