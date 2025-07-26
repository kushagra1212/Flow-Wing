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

#include "SyntaxToken.h"
#include "src/diagnostics/DiagnosticUtils/SourceLocation.h"
#include "src/syntax/SyntaxKindUtils.h"
#include <any>

template <typename T>
SyntaxToken<T>::SyntaxToken(const std::string &absoluteFilePath,
                            const int &lineNumber,
                            const SyntaxKindUtils::SyntaxKind &kind,
                            const int &columnNumber, const std::string &text,
                            const T &value) {
  this->kind = kind;
  this->text = text;
  this->value = value;
  this->lineNumber = lineNumber;
  this->columnNumber = columnNumber;
  this->absoluteFilePath = absoluteFilePath;
  this->length = text.length();
}

template <typename T>
const SyntaxKindUtils::SyntaxKind SyntaxToken<T>::getKind() const {
  return this->kind;
}
template <typename T> const int &SyntaxToken<T>::getColumnNumber() {
  return this->columnNumber;
}

template <typename T> const int &SyntaxToken<T>::getLineNumber() {
  return this->lineNumber;
}

template <typename T> const std::string &SyntaxToken<T>::getText() {
  return this->text;
}

template <typename T>
const std::string &SyntaxToken<T>::getAbsoluteFilePath() const {
  return this->absoluteFilePath;
}

template <typename T> const T &SyntaxToken<T>::getValue() {
  return (this->value);
}
template <typename T> std::string SyntaxToken<T>::getKindText() {
  return SyntaxKindUtils::to_string(this->kind);
}
template <typename T> const int SyntaxToken<T>::getUnaryOperatorPrecedence() {
  switch (this->kind) {
  case SyntaxKindUtils::SyntaxKind::PlusToken:
  case SyntaxKindUtils::SyntaxKind::MinusToken:
  case SyntaxKindUtils::SyntaxKind::BangToken:
  case SyntaxKindUtils::SyntaxKind::TildeToken:
    return 10;
  default:
    return 0;
  }
}
template <typename T> const int SyntaxToken<T>::getBinaryOperatorPrecedence() {
  switch (this->kind) {
  case SyntaxKindUtils::SyntaxKind::StarToken:
  case SyntaxKindUtils::SyntaxKind::SlashSlashToken:
  case SyntaxKindUtils::SyntaxKind::SlashToken:
  case SyntaxKindUtils::SyntaxKind::PercentToken:
    return 9;
  case SyntaxKindUtils::SyntaxKind::PlusToken:
  case SyntaxKindUtils::SyntaxKind::MinusToken:
    return 8;
  case SyntaxKindUtils::SyntaxKind::LessToken:
  case SyntaxKindUtils::SyntaxKind::LessOrEqualsToken:
  case SyntaxKindUtils::SyntaxKind::GreaterToken:
  case SyntaxKindUtils::SyntaxKind::GreaterOrEqualsToken:
    return 7;
  case SyntaxKindUtils::SyntaxKind::EqualsEqualsToken:
  case SyntaxKindUtils::SyntaxKind::BangEqualsToken:
    return 6;
  case SyntaxKindUtils::SyntaxKind::AmpersandToken:
    return 5;
  case SyntaxKindUtils::SyntaxKind::CaretToken:
    return 4;
  case SyntaxKindUtils::SyntaxKind::PipeToken:
    return 3;
  case SyntaxKindUtils::SyntaxKind::AmpersandAmpersandToken:
    return 2;
  case SyntaxKindUtils::SyntaxKind::PipePipeToken:
  case SyntaxKindUtils::SyntaxKind::EqualsToken:
    return 1;
  default:
    return 0;
  }
}
template <typename T>
const std::vector<SyntaxNode *> &SyntaxToken<T>::getChildren() {
  return _children;
}

template <typename T>
const DiagnosticUtils::SourceLocation
SyntaxToken<T>::getSourceLocation() const {
  return DiagnosticUtils::SourceLocation(this->lineNumber, this->columnNumber,
                                         this->length, this->absoluteFilePath);
}

// Explicit template instantiations - must come after all method definitions
template class SyntaxToken<std::any>;
template class SyntaxToken<int>;
template class SyntaxToken<double>;
template class SyntaxToken<bool>;
template class SyntaxToken<std::string>;
template class SyntaxToken<char>;
