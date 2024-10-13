#include "BoundCustomTypeStatement.h"

BoundCustomTypeStatement::BoundCustomTypeStatement(
    const DiagnosticUtils::SourceLocation &location, bool isExposed)
    : BoundSourceLocation(location), _isExposed(isExposed) {}

BinderKindUtils::BoundNodeKind BoundCustomTypeStatement::getKind() const {
  return BinderKindUtils::BoundNodeKind::CustomTypeStatement;
}

std::vector<BoundNode *> BoundCustomTypeStatement::getChildren() {
  if (_children.size() > 0) {
    return _children;
  }

  _children.push_back(_typeName.get());

  for (auto &keyTypePair : _key_type_pairs) {
    _children.push_back(keyTypePair.first.get());
    _children.push_back(keyTypePair.second.get());
  }

  return _children;
}
