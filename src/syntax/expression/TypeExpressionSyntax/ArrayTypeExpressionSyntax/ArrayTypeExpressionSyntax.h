#ifndef __FLOW__WING__ARRAYTYPEEXPRESSIONSYNTAX_H__
#define __FLOW__WING__ARRAYTYPEEXPRESSIONSYNTAX_H__

#include "../TypeExpressionSyntax.h"

class ArrayTypeExpressionSyntax : public TypeExpressionSyntax {
private:
  std::vector<std::unique_ptr<ExpressionSyntax>> _dimensions;
  std::unique_ptr<SyntaxToken<std::any>> _elementType;
  std::unique_ptr<TypeExpressionSyntax> _nonTrivialElementType;
  bool _isTrivial = false;

public:
  const virtual SyntaxKindUtils::SyntaxKind getKind() const override;
  const virtual std::vector<SyntaxNode *> &getChildren() override;
  const virtual DiagnosticUtils::SourceLocation
  getSourceLocation() const override;

  ArrayTypeExpressionSyntax(std::unique_ptr<SyntaxToken<std::any>> type);

  // Setters
  inline void setElementType(std::unique_ptr<SyntaxToken<std::any>> type) {
    _isTrivial = true;
    _elementType = std::move(type);
  }

  inline void
  setNonTrivialElementType(std::unique_ptr<TypeExpressionSyntax> type) {
    _nonTrivialElementType = std::move(type);
  }

  inline void addDimension(std::unique_ptr<ExpressionSyntax> dimension) {
    _dimensions.push_back(std::move(dimension));
  }

  // Getters
  inline auto getDimensions() const
      -> const std::vector<std::unique_ptr<ExpressionSyntax>> & {
    return _dimensions;
  }

  inline auto getElementTypeRef()
      -> const std::unique_ptr<SyntaxToken<std::any>> & {
    return _elementType;
  }

  inline auto getNonTrivialElementTypeRef()
      -> const std::unique_ptr<TypeExpressionSyntax> & {
    return _nonTrivialElementType;
  }

  inline bool isTrivial() const { return _isTrivial; }
};

#endif // __FLOW__WING__ARRAYTYPEEXPRESSIONSYNTAX_H__
