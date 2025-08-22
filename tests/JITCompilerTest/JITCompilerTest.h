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


#ifndef JIT_COMPILER_TEST_H
#define JIT_COMPILER_TEST_H

#include "../../src/compiler/JITCompiler/JITCompiler.h"
#include "../BaseTest/BaseTest.h"

class JITCompilerTest : public BaseTest {
public:
  JITCompilerTest();
  void SetUp(bool captureStderr = false);
  void TearDown();
  void setInput(const std::string &input);
  void runEvaluator(std::istream &inputStream = std::cin,
                    std::ostream &outputStream = std::cout);
  std::string getOutput() const;
  std::string getErrorOutput() const;

  std::unique_ptr<JITCompiler> jit_compiler;
};

#endif // JIT_COMPILER_TEST_H