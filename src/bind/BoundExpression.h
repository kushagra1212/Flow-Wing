#pragma once
#include "BoundNode.h"
#include "BoundSourceLocation/BoundSourceLocation.h"

class BoundExpression : public BoundNode, public BoundSourceLocation {
 public:
  inline BoundExpression(DiagnosticUtils::SourceLocation location)
      : BoundSourceLocation(location){};

  virtual const std::type_info &getType() = 0;
};