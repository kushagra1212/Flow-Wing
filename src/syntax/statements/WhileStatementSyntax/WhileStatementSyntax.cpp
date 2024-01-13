#include "WhileStatementSyntax.h"

WhileStatementSyntax::WhileStatementSyntax(
    std::unique_ptr<SyntaxToken<std::any>> whileKeyword,
    std::unique_ptr<ExpressionSyntax> condition,
    std::unique_ptr<BlockStatementSyntax> body) {
  this->_whileKeyword = std::move(whileKeyword);
  this->_condition = std::move(condition);
  this->_body = std::move(body);
}

std::unique_ptr<SyntaxToken<std::any>> WhileStatementSyntax::getWhileKeyword() {
  return std::move(_whileKeyword);
}

std::unique_ptr<ExpressionSyntax> WhileStatementSyntax::getCondition() {
  return std::move(_condition);
}

std::unique_ptr<BlockStatementSyntax> WhileStatementSyntax::getBody() {
  return std::move(_body);
}

const SyntaxKindUtils::SyntaxKind WhileStatementSyntax::getKind() const {
  return SyntaxKindUtils::SyntaxKind::WhileStatement;
}

const std::vector<SyntaxNode *> &WhileStatementSyntax::getChildren() {
  if (_children.empty()) {
    // Add children
    _children.push_back(_whileKeyword.get());
    _children.push_back(_condition.get());
    _children.push_back(_body.get());
  }
  return this->_children;
}

const DiagnosticUtils::SourceLocation WhileStatementSyntax::getSourceLocation()
    const {
  return this->_whileKeyword->getSourceLocation();
}

std::unique_ptr<SyntaxToken<std::any>> &
WhileStatementSyntax::getWhileKeywordPtr() {
  return this->_whileKeyword;
}

std::unique_ptr<ExpressionSyntax> &WhileStatementSyntax::getConditionPtr() {
  return this->_condition;
}

std::unique_ptr<BlockStatementSyntax> &WhileStatementSyntax::getBodyPtr() {
  return this->_body;
}