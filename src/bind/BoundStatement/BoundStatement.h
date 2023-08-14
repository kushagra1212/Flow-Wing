#pragma once
#include "../BinderKindUtils.h"
#include "../BoundNode.h"
class BoundStatement : public BoundNode {
public:
  virtual BinderKindUtils::BoundNodeKind getKind() = 0;
  virtual std::vector<std::shared_ptr<BoundNode>> getChildren() = 0;
  virtual std::string getLineNumberAndColumn() const = 0;
};