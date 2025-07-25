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


#ifndef BASE_TEST_H
#define BASE_TEST_H

#include <gtest/gtest.h>

#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>

class BaseTest {
public:
  virtual ~BaseTest() {}

  virtual void SetUp(bool captureStderr = false) = 0;
  virtual void TearDown() = 0;
  virtual void setInput(const std::string &input) = 0;
  virtual void runEvaluator(std::istream &inputStream = std::cin,
                            std::ostream &outputStream = std::cout) = 0;
  virtual std::string getOutput() const = 0;
  virtual std::string getErrorOutput() const = 0;

  std::stringstream input_stream;
  std::stringstream output_stream;
  std::streambuf *saved_cout_buf;
};

#endif // BASE_TEST_H
