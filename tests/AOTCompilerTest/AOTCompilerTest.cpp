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
