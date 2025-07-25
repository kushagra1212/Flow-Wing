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


#ifndef __FLOW__WING__COMPILER__H__
#define __FLOW__WING__COMPILER__H__

#if defined(AOT_TEST_MODE) || defined(JIT_TEST_MODE)
#include <gtest/gtest.h>
#endif

#include <fstream>
#include <iostream>

#include "../ASTBuilder/ASTBuilder.h"
#include "../IR/IRGenerator.h"
#include "../IR/utils/fileSaver/ll-file/LLFileSaveStrategy.h"
#include "../SemanticAnalyzer/SemanticAnalyzer.h"
#include "../common/commandLineOptions/commandLineOptions.h"
#include "../utils/Utils.h"
#include "CompilerUtils.h"

class Compiler {
public:
  Compiler(std::string filePath = "");

  void compile(std::vector<std::string> &text, std::ostream &outputStream);

  void runTests(std::istream &inputStream, std::ostream &outputStream);

  virtual void execute() = 0;

  std::string _filePath;
  std::string _outputFilePath;
  std::unique_ptr<LLFileSaveStrategy> llFileSaveStrategy;
  std::vector<std::string> text = std::vector<std::string>();
  std::string executable_directory_string;
  std::unique_ptr<FlowWing::DiagnosticHandler> _currentDiagnosticHandler;
  llvm::ExecutionEngine *executionEngine;
  std::filesystem::path _executable_path = std::filesystem::current_path();
};

#endif // __FLOW__WING__COMPILER__H__