#pragma once
#include "BinderKindUtils.h"
class BoundNode {
 public:
    virtual ~BoundNode() = default; 
  std::vector<BoundNode *> _children;
  virtual BinderKindUtils::BoundNodeKind getKind() const = 0;

  virtual std::vector<BoundNode *> getChildren() = 0;
};