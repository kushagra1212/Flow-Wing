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

#include "ReplTest.h"

ReplTest::ReplTest() { repl = std::make_unique<Repl>(); }

void ReplTest::SetUp([[maybe_unused]] bool captureStderr) {
  saved_cout_buf = std::cout.rdbuf(output_stream.rdbuf());
}
void ReplTest::TearDown() { std::cout.rdbuf(saved_cout_buf); }

void ReplTest::setInput(const std::string &input) { input_stream.str(input); }

std::string ReplTest::getOutput() const { return output_stream.str(); }
void ReplTest::runEvaluator(std::istream &inputStream,
                            std::ostream &outputStream) {
  repl->runTests(inputStream, outputStream);
}

#ifdef REPL_TEST_MODE

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

#endif