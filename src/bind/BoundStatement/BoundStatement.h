#include "../BoundNode.h"
#include "BinderKindUtils.h"
class BoundStatement : public BoundNode {
public:
  virtual BinderKindUtils::BoundNodeKind getKind() = 0;
};