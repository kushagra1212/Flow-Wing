#pragma once
#include "BinderKindUtils.h"
class BoundNode {
public:
  virtual BinderKindUtils::BoundNodeKind getKind() = 0;
};