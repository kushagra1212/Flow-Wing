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
    for (auto &entry : this->_entryExpressions) {
      _children.push_back(entry.get());
    }
  }

  return _children;
}

/*
  Setters
*/

void BoundContainerStatement::setEntryExpression(
    std::unique_ptr<BoundExpression> entryExpression) {
  this->_entryExpressions.push_back(std::move(entryExpression));
}

void BoundContainerStatement::setContainerSizeExpression(
    std::unique_ptr<BoundExpression> containerSizeExpression) {
  this->_containerSizeExpression = std::move(containerSizeExpression);
}

/*
  Getters
*/
auto BoundContainerStatement::getVariableNameRef() const
    -> const std::string & {
  return this->_variableName;
}

auto BoundContainerStatement::getEntryExpressionsRef() const
    -> const std::vector<std::unique_ptr<BoundExpression>> & {
  return this->_entryExpressions;
}

auto BoundContainerStatement::getContainerTypeRef() const
    -> const Utils::type & {
  return this->_type;
}

auto BoundContainerStatement::getContainerSizeExpressionRef() const
    -> const std::unique_ptr<BoundExpression> & {
  return this->_containerSizeExpression;
}