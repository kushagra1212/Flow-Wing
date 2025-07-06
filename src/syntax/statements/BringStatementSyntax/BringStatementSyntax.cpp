#include "BringStatementSyntax.h"

void BringStatementSyntax::addExpression(
    std::unique_ptr<LiteralExpressionSyntax<std::any>> expression) {
  expressions.push_back(std::move(expression));
}
void BringStatementSyntax::setAbsoluteFilePath(
    const std::string &absoluteFilePath) {
  this->absoluteFilePath = absoluteFilePath;
}
void BringStatementSyntax::setDiagnosticHandler(
    std::unique_ptr<FlowWing::DiagnosticHandler> diagnosticHandler) {
  this->diagnosticHandler = std::move(diagnosticHandler);
}

void BringStatementSyntax::setRelativeFilePath(
    const std::string &relativeFilePath) {
  this->relativeFilePath = relativeFilePath;
}

void BringStatementSyntax::setCompilationUnit(
    std::unique_ptr<CompilationUnitSyntax> compilationUnit) {
  this->_compilationUnit = std::move(compilationUnit);
}

void BringStatementSyntax::addBringKeyword(
    std::unique_ptr<SyntaxToken<std::any>> bringKeyword) {
  this->_bringKeyword = std::move(bringKeyword);
}

void BringStatementSyntax::addPathToken(
    std::unique_ptr<SyntaxToken<std::any>> pathToken) {

  this->_pathToken = std::move(pathToken);
}

const std::string &BringStatementSyntax::getAbsoluteFilePath() const {
  return absoluteFilePath;
}

const SyntaxKindUtils::SyntaxKind BringStatementSyntax::getKind() const {
  return SyntaxKindUtils::SyntaxKind::BringStatementSyntax;
}
const std::vector<SyntaxNode *> &BringStatementSyntax::getChildren() {
  if (_children.empty()) {
    this->_children.push_back(_bringKeyword.get());

    if (_pathToken)
      this->_children.push_back(_pathToken.get());

    for (const auto &expression : expressions) {
      this->_children.push_back(expression.get());
    }
    for (const auto &member : _compilationUnit->getMembers()) {
      this->_children.push_back(member.get());
    }
  }
  return _children;
}
const DiagnosticUtils::SourceLocation
BringStatementSyntax::getSourceLocation() const {

  if (_pathToken) {
    return _pathToken->getSourceLocation();
  }

  if (_openBraceToken) {
    return _openBraceToken->getSourceLocation();
  }

  return _bringKeyword->getSourceLocation();
}

const std::vector<std::unique_ptr<LiteralExpressionSyntax<std::any>>> &
BringStatementSyntax::getExpressionsPtr() {
  return expressions;
}

const bool BringStatementSyntax::getIsChoosyImportPtr() {
  return this->_openBraceToken != nullptr;
}
const std::string &BringStatementSyntax::getAbsoluteFilePathPtr() {
  return absoluteFilePath;
}
const std::string &BringStatementSyntax::getRelativeFilePathPtr() {
  return relativeFilePath;
}

std::unique_ptr<FlowWing::DiagnosticHandler> &
BringStatementSyntax::getDiagnosticHandlerPtr() {
  return diagnosticHandler;
}

const std::unique_ptr<SyntaxToken<std::any>> &
BringStatementSyntax::getBringKeywordPtr() {
  return _bringKeyword;
}

const std::unique_ptr<CompilationUnitSyntax> &
BringStatementSyntax::getCompilationUnitPtr() {
  return _compilationUnit;
}

const std::unique_ptr<SyntaxToken<std::any>> &
BringStatementSyntax::getPathTokenPtr() {
  return _pathToken;
}

void BringStatementSyntax::addOpenBraceToken(
    std::unique_ptr<SyntaxToken<std::any>> openBraceToken) {
  this->_openBraceToken = std::move(openBraceToken);
}