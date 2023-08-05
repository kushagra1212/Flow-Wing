#pragma once
#include "BoundNode.h"
class BoundExpression : public BoundNode {
public:
  virtual const std::type_info &getType() = 0;
  virtual std::vector<BoundNode *> getChildren() = 0;
};