#pragma once
#include "BinderKindUtils.h"
class MemoryNode {
public:
  virtual ~MemoryNode() = default;
  virtual BinderKindUtils::MemoryKind getMemoryKind() const = 0;
};