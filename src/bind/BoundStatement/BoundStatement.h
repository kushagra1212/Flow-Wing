#pragma once
#include "../BinderKindUtils.h"
#include "../BoundNode.h"
class BoundStatement : public BoundNode {
public:
  virtual BinderKindUtils::BoundNodeKind getKind() = 0;
  virtual std::vector<BoundNode *> getChildren() = 0;
};