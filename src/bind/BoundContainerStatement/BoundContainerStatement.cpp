#include "BoundContainerStatement.h"

BoundContainerStatement::BoundContainerStatement(
    const DiagnosticUtils::SourceLocation &location, const Utils::type &type,
    std::string variableName)
    : BoundSourceLocation(location), _type(type),
      _variableName(std::move(variableName)) {}

/*
  Overrides
*/

BinderKindUtils::BoundNodeKind BoundContainerStatement::getKind() const {
  return BinderKindUtils::BoundNodeKind::ContainerStatement;
}

std::vector<BoundNode *> BoundContainerStatement::getChildren() {
  if (_children.size() == 0) {

    for (const auto &exp : this->_containerSizeExpressions) {
      _children.push_back(exp.get());
    }
    _children.push_back(_containerExpression.get());
  }

  return _children;
}

/*
  Setters
*/

void BoundContainerStatement::setBracketedExpression(
    std::unique_ptr<BoundExpression> containerExpression) {
  this->_containerExpression = std::move(containerExpression);
}

/*
  Getters
*/
auto BoundContainerStatement::getVariableNameRef() const
    -> const std::string & {
  return this->_variableName;
}

auto BoundContainerStatement::getContainerTypeRef() const
    -> const Utils::type & {
  return this->_type;
}

auto BoundContainerStatement::getBracketedExpressionRef() const
    -> const std::unique_ptr<BoundExpression> & {
  return this->_containerExpression;
}