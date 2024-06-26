#pragma once

#include "../BoundTypeExpression.h"

class BoundArrayTypeExpression : public BoundTypeExpression {
  std::vector<std::unique_ptr<BoundExpression>> _dimensions;
  SyntaxKindUtils::SyntaxKind _elementType;
  std::unique_ptr<BoundTypeExpression> _boundNonTrivialElementType;
  bool _isTrivialType = false;

public:
  BoundArrayTypeExpression(const DiagnosticUtils::SourceLocation &location,
                           const SyntaxKindUtils::SyntaxKind &type);

  std::vector<BoundNode *> getChildren() override;

  BinderKindUtils::BoundNodeKind getKind() const override;

  // Setters
  inline void setElementType(const SyntaxKindUtils::SyntaxKind &type) {
    _isTrivialType = true;
    _elementType = type;
  }

  inline void setNonTrivialElementType(
      std::unique_ptr<BoundTypeExpression> boundNonTrivialElementType) {
    _boundNonTrivialElementType = std::move(boundNonTrivialElementType);
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

  inline auto getNonTrivialElementType() const
      -> const std::unique_ptr<BoundTypeExpression> & {
    return _boundNonTrivialElementType;
  }

  inline bool isTrivialType() const { return _isTrivialType; }
};