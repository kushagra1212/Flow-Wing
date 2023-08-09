#pragma once
#include "BinderKindUtils.h"
class BoundNode {
public:
  virtual BinderKindUtils::BoundNodeKind getKind() = 0;

  virtual std::vector<BoundNode *> getChildren() = 0;
};