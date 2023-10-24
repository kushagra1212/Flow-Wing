#include "BringStatementSyntax.h"

void BringStatementSyntax::addExpression(
    std::unique_ptr<SyntaxToken<std::any>> expression) {
  expressions.push_back(std::move(expression));
}
void BringStatementSyntax::setAbsoluteFilePath(
    const std::string &absoluteFilePath) {
  this->absoluteFilePath = absoluteFilePath;
}
void BringStatementSyntax::setDiagnosticHandler(
    std::unique_ptr<DiagnosticHandler> diagnosticHandler) {
  this->diagnosticHandler = std::move(diagnosticHandler);
}

void BringStatementSyntax::setRelativeFilePath(
    const std::string &relativeFilePath) {
  this->relativeFilePath = relativeFilePath;
}

void BringStatementSyntax::addBringKeyword(
    std::unique_ptr<SyntaxToken<std::any>> bringKeyword) {
  _bringKeyword = std::move(bringKeyword);
}

const std::string &BringStatementSyntax::getAbsoluteFilePath() const {
  return absoluteFilePath;
}

SyntaxKindUtils::SyntaxKind BringStatementSyntax::getKind() const {
  return SyntaxKindUtils::SyntaxKind::BringStatementSyntax;
}
std::vector<SyntaxNode *> BringStatementSyntax::getChildren() {
  std::vector<SyntaxNode *> children;
  for (auto &expression : expressions) {
    children.push_back(expression.get());
  }
  return children;
}
DiagnosticUtils::SourceLocation
BringStatementSyntax::getSourceLocation() const {
  return _bringKeyword->getSourceLocation();
}

const std::vector<std::unique_ptr<SyntaxToken<std::any>>> &
BringStatementSyntax::getExpressionsPtr() {
  return expressions;
}
const bool BringStatementSyntax::getIsChoosyImportPtr() {
  return this->expressions.size() > 0;
}
const std::string &BringStatementSyntax::getAbsoluteFilePathPtr() {
  return absoluteFilePath;
}
const std::string &BringStatementSyntax::getRelativeFilePathPtr() {
  return relativeFilePath;
}

std::unique_ptr<DiagnosticHandler> &
BringStatementSyntax::getDiagnosticHandlerPtr() {
  return diagnosticHandler;
}

const std::unique_ptr<SyntaxToken<std::any>> &
BringStatementSyntax::getBringKeywordPtr() {
  return _bringKeyword;
}