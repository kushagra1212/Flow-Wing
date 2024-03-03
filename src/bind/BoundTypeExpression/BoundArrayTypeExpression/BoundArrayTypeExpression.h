#pragma once

#include "../BoundTypeExpression.h"

class BoundArrayTypeExpression : public BoundTypeExpression {
  std::vector<std::unique_ptr<BoundExpression>> _dimensions;
  SyntaxKindUtils::SyntaxKind _elementType;

 public:
  BoundArrayTypeExpression(const DiagnosticUtils::SourceLocation &location,
                           const SyntaxKindUtils::SyntaxKind &type);

  std::vector<BoundNode *> getChildren() override;

  BinderKindUtils::BoundNodeKind getKind() const override;

  // Setters
  inline void setElementType(const SyntaxKindUtils::SyntaxKind &type) {
    _elementType = type;
  }

  inline void addDimension(std::unique_ptr<BoundExpression> dimension) {
    _dimensions.push_back(std::move(dimension));
  }

  // Getters

  inline auto getDimensions() const
      -> const std::vector<std::unique_ptr<BoundExpression>> & {
    return _dimensions;
  }

  inline auto getElementType() const -> const SyntaxKindUtils::SyntaxKind & {
    return _elementType;
  }
};