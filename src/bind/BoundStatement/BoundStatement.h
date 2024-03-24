#pragma once
#include "../BinderKindUtils.h"
#include "../BoundNode.h"
class BoundStatement : public BoundNode {
     public:
    virtual ~BoundStatement() = default; 
};