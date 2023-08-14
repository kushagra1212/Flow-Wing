#pragma once
#include "BinderKindUtils.h"
class BoundNode {

public:
  std::string _lineAndColumn;
  virtual BinderKindUtils::BoundNodeKind getKind() = 0;

  virtual std::vector<std::shared_ptr<BoundNode>> getChildren() = 0;

  virtual std::string getLineNumberAndColumn() const = 0;
};