#pragma once
#include "BinderKindUtils.h"
class BoundNode {

public:
  std::string _lineAndColumn;
  std::vector<BoundNode *> _children;
  virtual BinderKindUtils::BoundNodeKind getKind() const = 0;

  virtual std::vector<BoundNode *> getChildren() = 0;

  virtual std::string getLineNumberAndColumn() = 0;
};