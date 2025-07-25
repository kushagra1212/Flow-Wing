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



#ifndef REPL_H
#define REPL_H

#include "../ASTBuilder/ASTBuilder.h"
#include "../SemanticAnalyzer/SyntaxBinder/BoundGlobalScope/BoundGlobalScope.h"
#include "../common/Common.h"
#include "../diagnostics/DiagnosticHandler/DiagnosticHandler.h"
#include "../interpreter/Interpreter.h"

class Repl {
public:
  Repl();
  Repl(const bool &isTest);
  ~Repl();

  // Run the REPL with default input/output streams
  void run();

  void runWithStream(std::istream &inputStream, std::ostream &outputStream);
  void runTests(std::istream &inputStream, std::ostream &outputStream);
  bool isSyntaxTreeVisible() const;
  bool isBoundTreeVisible() const;
  // Helper functions
  void printWelcomeMessage(std::ostream &outputStream);
  bool handleSpecialCommands(const std::string &line);
  int countBraces(const std::string &line, char brace);

  void
  compileAndEvaluate(std::ostream &outputStream,
                     std::unique_ptr<CompilationUnitSyntax> compilationUnit);
  void runIfNotInTest(std::function<void()> f);
  void toggleExit();

  void addTextString(const std::string &textString);

private: // Data members
  bool showSyntaxTree = false, showBoundTree = false, exit = false;
  std::vector<std::string> text = std::vector<std::string>();

  std::unique_ptr<FlowWing::DiagnosticHandler> _diagnosticHandler = nullptr;
  std::unique_ptr<BoundGlobalScope> _previousGlobalScope = nullptr;
  std::vector<std::string> previousText;

  // For testing
  bool isTest = false;
};

#endif // REPL_H