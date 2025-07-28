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

#ifndef REPL_TEST_H
#define REPL_TEST_H

#include "../../src/REPL/Repl.h"
#include "../BaseTest/BaseTest.h"

class ReplTest : public BaseTest {
public:
  ReplTest();
  void SetUp(bool captureStderr = false);
  void TearDown();
  void setInput(const std::string &input);
  std::string getOutput() const;

  void runEvaluator(std::istream &inputStream = std::cin,
                    std::ostream &outputStream = std::cout);
  std::unique_ptr<Repl> repl;
};

#endif // REPL_TEST_H