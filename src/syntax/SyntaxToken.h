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

#include "src/syntax/SyntaxNode.h"

template <typename T> class SyntaxToken;

template <typename T> class SyntaxToken : public SyntaxNode {
private:
  SyntaxKindUtils::SyntaxKind kind;
  std::string text;
  T value;

public:
  SyntaxToken(const std::string &absoluteFilePath, const int &lineNumber,
              const SyntaxKindUtils::SyntaxKind &kind, const int &columnNumber,
              const std::string &text, const T &value);

  const int &getColumnNumber();

  const int &getLineNumber();

  const std::string &getAbsoluteFilePath() const;

  const std::string &getText();

  const T &getValue();

  std::string getKindText();

  int getUnaryOperatorPrecedence();

  int getBinaryOperatorPrecedence();

  SyntaxKindUtils::SyntaxKind getKind() const override;

  const DiagnosticUtils::SourceLocation getSourceLocation() const override;

  const std::vector<SyntaxNode *> &getChildren() override;

  inline auto setText(const std::string newText) -> void {
    this->text = newText;
  }
  inline auto setValue(const T &newValue) -> void { this->value = newValue; }
};
