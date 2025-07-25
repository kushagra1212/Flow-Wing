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


#ifndef CALL_EXPRESSION_SYNTAX_H
#define CALL_EXPRESSION_SYNTAX_H

#include "../../SyntaxKindUtils.h"
#include "../../SyntaxNode.h"
#include "../../SyntaxToken.h"
#include "../ExpressionSyntax.h"
#include "../LiteralExpressionSyntax.h"

class CallExpressionSyntax : public ExpressionSyntax {
private:
  std::unique_ptr<LiteralExpressionSyntax<std::any>> _identifier;
  std::unique_ptr<SyntaxToken<std::any>> _openParenthesisToken;
  std::vector<std::unique_ptr<ExpressionSyntax>> _arguments;
  std::vector<std::unique_ptr<SyntaxToken<std::any>>> _separators;
  std::unique_ptr<SyntaxToken<std::any>> _closeParenthesisToken;
  std::unique_ptr<SyntaxToken<std::any>> _newKeyword;
  bool _hasNewKeyword = false;

public:
  CallExpressionSyntax(
      std::unique_ptr<LiteralExpressionSyntax<std::any>> identifier);

  std::unique_ptr<LiteralExpressionSyntax<std::any>> getIdentifier();
  std::unique_ptr<SyntaxToken<std::any>> getOpenParenthesisToken();
  std::unique_ptr<SyntaxToken<std::any>> getCloseParenthesisToken();

  void addArgument(std::unique_ptr<ExpressionSyntax> argument);
  void addSeparator(std::unique_ptr<SyntaxToken<std::any>> separator);
  void setOpenParenthesisToken(
      std::unique_ptr<SyntaxToken<std::any>> openParenthesisToken);
  void setCloseParenthesisToken(
      std::unique_ptr<SyntaxToken<std::any>> closeParenthesisToken);

  inline auto setNewKeyword(std::unique_ptr<SyntaxToken<std::any>> newKeyword) {
    _newKeyword = std::move(newKeyword);
    _hasNewKeyword = true;
  }

  inline auto hasNewKeyword() { return _hasNewKeyword; }

  const SyntaxKindUtils::SyntaxKind getKind() const override;
  const std::vector<SyntaxNode *> &getChildren() override;
  const DiagnosticUtils::SourceLocation getSourceLocation() const override;

  std::vector<std::unique_ptr<ExpressionSyntax>> &getArguments();
  std::vector<std::unique_ptr<SyntaxToken<std::any>>> &getSeparators();
  std::unique_ptr<LiteralExpressionSyntax<std::any>> &getIdentifierPtr();
  std::unique_ptr<SyntaxToken<std::any>> &getOpenParenthesisTokenPtr();
  std::unique_ptr<SyntaxToken<std::any>> &getCloseParenthesisTokenPtr();
};

#endif // CALL_EXPRESSION_SYNTAX_H
