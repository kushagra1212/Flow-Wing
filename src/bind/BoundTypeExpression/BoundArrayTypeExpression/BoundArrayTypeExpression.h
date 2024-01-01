#pragma once

#include "../BoundTypeExpression.h"

class BoundArrayTypeExpression : public BoundTypeExpression {

  std::vector<std::unique_ptr<BoundExpression>> _dimensions;

public:
  BoundArrayTypeExpression(const DiagnosticUtils::SourceLocation &location,
                           Utils::type type);

  std::vector<BoundNode *> getChildren() override;

  BinderKindUtils::BoundNodeKind getKind() const;

  inline void addDimension(std::unique_ptr<BoundExpression> dimension) {
    _dimensions.push_back(std::move(dimension));
  }

  inline auto getDimensions() const
      -> const std::vector<std::unique_ptr<BoundExpression>> & {
    return _dimensions;
  }
};