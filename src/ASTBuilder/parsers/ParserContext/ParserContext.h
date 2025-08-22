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

#include "src/ASTBuilder/CodeFormatter/CodeFormatter.h"
#include "src/syntax/SyntaxToken.h"
#include <any>
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

class SourceTokenizer;

namespace FlowWing {
class DiagnosticHandler;
}

namespace SyntaxKindUtils {
enum SyntaxKind : int;
}

class ParserContext {

public:
  ParserContext(
      FlowWing::DiagnosticHandler *diagnosticHandler,
      const std::unordered_map<std::string, int8_t> &dependencyPathsMap =
          std::unordered_map<std::string, int8_t>());

  ~ParserContext();

  //? Syntax Token Methods

  std::unique_ptr<SyntaxToken<std::any>>
  match(const SyntaxKindUtils::SyntaxKind &kind);
  SyntaxToken<std::any> *peek(const int &offset);
  SyntaxToken<std::any> *getCurrent();
  std::unique_ptr<SyntaxToken<std::any>> nextToken();
  SyntaxKindUtils::SyntaxKind getKind();
  //? Build Token List
  void buildTokenList(SourceTokenizer *lexer);

  //? Code Formatter Methods

  const std::unique_ptr<CodeFormatter> &getCodeFormatterRef();

  //? Parser Methods

  //? Getters
  const std::string &getCurrentModuleName();
  FlowWing::DiagnosticHandler *getDiagnosticHandler();
  bool getIsInsideCallExpression() const;
  bool getIsInsideIndexExpression() const;
  bool getIsInsideContainerExpression() const;
  bool getIsInsideReturnStatement() const;
  int8_t getDependencyFileCount(const std::string &path);
  const std::vector<std::unique_ptr<SyntaxToken<std::any>>> &getTokenListRef();

  //? Setters

  void setCurrentModuleName(const std::string &name);
  void setIsInsideCallExpression(const bool value);
  void setIsInsideIndexExpression(const bool value);
  void setIsInsideContainerExpression(const bool value);
  void setIsInsideReturnStatement(const bool value);
  void updateDependencyCount(const std::string &path, const int8_t count);
  const std::unordered_map<std::string, int8_t> &getDependencyPathsMap();

private:
  void handleDiagnosticsForBadToken(SyntaxToken<std::any> *token);
  void handleFormatCommentToken(SyntaxToken<std::any> *token,
                                bool &isEncounteredEndOfLineBefore);

  FlowWing::DiagnosticHandler *_diagnosticHandler = nullptr;
  std::vector<std::unique_ptr<SyntaxToken<std::any>>> _tokens = {};
  std::unique_ptr<CodeFormatter> _codeFormatter = nullptr;
  std::unordered_map<std::string, int8_t> _dependencyPathsMap =
      std::unordered_map<std::string, int8_t>();
  size_t _position = 0;
  std::string _currentModuleName = "";
  bool _isInsideCallExpression = false;
  bool _isInsideIndexExpression = false;
  bool _isInsideContainerExpression = false;
  bool _isInsideReturnStatement = false;
};
