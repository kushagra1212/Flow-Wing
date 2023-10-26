#include "BringStatementSyntax.h"

void BringStatementSyntax::addExpression(
    std::unique_ptr<SyntaxToken<std::any>> expression) {
  this->_children.push_back(expression.get());
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

void BringStatementSyntax::setCompilationUnit(
    std::unique_ptr<CompilationUnitSyntax> compilationUnit) {

  for (const auto &member : compilationUnit->getMembers()) {
    this->_children.push_back(member.get());
  }
  this->_compilationUnit = std::move(compilationUnit);
}

void BringStatementSyntax::addBringKeyword(
    std::unique_ptr<SyntaxToken<std::any>> bringKeyword) {
  this->_children.push_back(bringKeyword.get());
  this->_bringKeyword = std::move(bringKeyword);
}

const std::string &BringStatementSyntax::getAbsoluteFilePath() const {
  return absoluteFilePath;
}

SyntaxKindUtils::SyntaxKind BringStatementSyntax::getKind() const {
  return SyntaxKindUtils::SyntaxKind::BringStatementSyntax;
}
std::vector<SyntaxNode *> BringStatementSyntax::getChildren() {
  return _children;
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

const std::unique_ptr<CompilationUnitSyntax> &
BringStatementSyntax::getCompilationUnitPtr() {
  return _compilationUnit;
}