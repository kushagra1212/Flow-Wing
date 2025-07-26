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

#include "ParserContext.h"
#include "src/ASTBuilder/CodeFormatter/CodeFormatter.h"
#include "src/SourceTokenizer/SourceTokenizer.h"
#include "src/diagnostics/Diagnostic/Diagnostic.h"
#include "src/diagnostics/Diagnostic/DiagnosticCodeData.h"
#include "src/diagnostics/DiagnosticHandler/DiagnosticHandler.h"
#include "src/syntax/SyntaxKindUtils.h"
#include "src/syntax/SyntaxToken.h"
#include "src/utils/Utils.h"

ParserContext::ParserContext(
    FlowWing::DiagnosticHandler *diagnosticHandler,
    const std::unordered_map<std::string, int8_t> &dependencyPathsMap)
    : _diagnosticHandler(diagnosticHandler),
      _codeFormatter(std::make_unique<CodeFormatter>(this)),
      _dependencyPathsMap(dependencyPathsMap) {}

ParserContext::~ParserContext() {
  for (auto &token : _tokens) {
    token.reset();
  }
  _tokens.clear();
}

/*
  ////?  __START__ Syntax Token Methods ////
*/

SyntaxToken<std::any> *ParserContext::peek(const int &offset) {
  const int index = _position + offset;
  if (index >= _tokens.size()) {
    return _tokens[_tokens.size() - 1].get();
  }
  return _tokens[index].get();
}

SyntaxToken<std::any> *ParserContext::getCurrent() { return peek(0); }

std::unique_ptr<SyntaxToken<std::any>> ParserContext::nextToken() {
  if (_position == _tokens.size()) {
    return std::unique_ptr<SyntaxToken<std::any>>(
        _tokens[_tokens.size() - 1].release());
  } else {
    return std::unique_ptr<SyntaxToken<std::any>>(
        _tokens[_position++].release());
  }
}

SyntaxKindUtils::SyntaxKind ParserContext::getKind() {
  while (getCurrent()->getKind() == SyntaxKindUtils::CommentStatement) {

    if (getCurrent()->getText().find_first_of(NEW_LINE) == 0) {

      getCurrent()->setText(NEW_LINE + _codeFormatter->getIndentAmount() +
                            getCurrent()->getText().substr(
                                1, getCurrent()->getText().length() - 1));

    } else {

      getCurrent()->setText(_codeFormatter->getIndentAmount() +
                            getCurrent()->getText());
    }

    _codeFormatter->append(getCurrent()->getText());

    nextToken();
  }

  return getCurrent()->getKind();
}

std::unique_ptr<SyntaxToken<std::any>>
ParserContext::match(const SyntaxKindUtils::SyntaxKind &kind) {

  _codeFormatter->append(getCurrent()->getText());

  if (getKind() == kind) {
    return std::move(nextToken());
  }
  _diagnosticHandler->addDiagnostic(Diagnostic(
      DiagnosticUtils::DiagnosticLevel::Error,
      DiagnosticUtils::DiagnosticType::Syntactic,
      {SyntaxKindUtils::to_string(getKind()), SyntaxKindUtils::to_string(kind)},
      Utils::getSourceLocation(getCurrent()),
      FLOW_WING::DIAGNOSTIC::DiagnosticCode::UnexpectedToken));
  if (getKind() != SyntaxKindUtils::SyntaxKind::EndOfFileToken) {
    return std::move(nextToken());
  } else {

    return std::make_unique<SyntaxToken<std::any>>(
        getCurrent()->getAbsoluteFilePath(), getCurrent()->getLineNumber(),
        SyntaxKindUtils::SyntaxKind::BadToken, getCurrent()->getColumnNumber(),
        getCurrent()->getText(), getCurrent()->getValue());
  }
}

/*
  ////?  __END__ Syntax Token Methods ////
*/

//? Code Formatter Methods

const std::unique_ptr<CodeFormatter> &ParserContext::getCodeFormatterRef() {
  return _codeFormatter;
}

//? Parser Methods

//? Getters

const std::vector<std::unique_ptr<SyntaxToken<std::any>>> &
ParserContext::getTokenListRef() {
  return _tokens;
}

const std::string &ParserContext::getCurrentModuleName() {
  return _currentModuleName;
}

FlowWing::DiagnosticHandler *ParserContext::getDiagnosticHandler() {
  return _diagnosticHandler;
}

const bool ParserContext::getIsInsideCallExpression() const {
  return _isInsideCallExpression;
}
const bool ParserContext::getIsInsideIndexExpression() const {
  return _isInsideIndexExpression;
}
const bool ParserContext::getIsInsideContainerExpression() const {
  return _isInsideContainerExpression;
}
const bool ParserContext::getIsInsideReturnStatement() const {
  return _isInsideReturnStatement;
}

const int8_t ParserContext::getDependencyFileCount(const std::string &path) {
  return _dependencyPathsMap[path];
}

//? Setters

void ParserContext::setCurrentModuleName(const std::string &name) {
  _currentModuleName = name;
}

void ParserContext::setIsInsideCallExpression(const bool value) {
  _isInsideCallExpression = value;
}

void ParserContext::setIsInsideIndexExpression(const bool value) {
  _isInsideIndexExpression = value;
}

void ParserContext::setIsInsideContainerExpression(const bool value) {
  _isInsideContainerExpression = value;
}

void ParserContext::setIsInsideReturnStatement(const bool value) {
  _isInsideReturnStatement = value;
}

void ParserContext::updateDependencyCount(const std::string &path,
                                          const int8_t count) {
  _dependencyPathsMap[path] += count;
}

const std::unordered_map<std::string, int8_t> &
ParserContext::getDependencyPathsMap() {
  return _dependencyPathsMap;
}

//? Builder Methods

void ParserContext::buildTokenList(SourceTokenizer *lexer) {
  SyntaxKindUtils::SyntaxKind _kind =
      SyntaxKindUtils::SyntaxKind::EndOfFileToken;
  bool isEncounteredEndOfLineBefore = false;

  do {
    std::unique_ptr<SyntaxToken<std::any>> token =
        std::move(lexer->nextToken());
    _kind = token->getKind();

    handleDiagnosticsForBadToken(token.get());
    handleFormatCommentToken(token.get(), isEncounteredEndOfLineBefore);

    if (_kind != SyntaxKindUtils::SyntaxKind::WhitespaceToken &&
        _kind != SyntaxKindUtils::SyntaxKind::EndOfLineToken) {
      this->_tokens.emplace_back(std::move(token));
    } else {
      token.reset();
    }

  } while (_kind != SyntaxKindUtils::SyntaxKind::EndOfFileToken);

#if (defined(DEBUG) && defined(JIT_MODE)) ||                                   \
    (defined(DEBUG) && defined(AOT_MODE))

  Utils::prettyPrint(this->_tokens);

#endif
}

void ParserContext::handleDiagnosticsForBadToken(SyntaxToken<std::any> *token) {
  if (token->getKind() == SyntaxKindUtils::SyntaxKind::BadToken) {
    this->_diagnosticHandler->addDiagnostic(
        Diagnostic(DiagnosticUtils::DiagnosticLevel::Error,
                   DiagnosticUtils::DiagnosticType::Syntactic,
                   {token->getText()}, Utils::getSourceLocation(token),
                   FLOW_WING::DIAGNOSTIC::DiagnosticCode::UnexpectedCharacter));
  }
}
void ParserContext::handleFormatCommentToken(
    SyntaxToken<std::any> *token, bool &isEncounteredEndOfLineBefore) {
  if (token->getKind() == SyntaxKindUtils::SyntaxKind::CommentStatement) {
    if (isEncounteredEndOfLineBefore)
      token->setText(NEW_LINE + token->getText());
    else
      token->setText(TWO_SPACES + token->getText());
  }

  if (token->getKind() == SyntaxKindUtils::SyntaxKind::EndOfLineToken) {
    isEncounteredEndOfLineBefore = true;
  } else if (token->getKind() != SyntaxKindUtils::SyntaxKind::WhitespaceToken) {
    isEncounteredEndOfLineBefore = false;
  }
}
