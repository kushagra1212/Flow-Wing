#ifndef __FLOW__WING__ARRAYTYPEEXPRESSIONSYNTAX_H__
#define __FLOW__WING__ARRAYTYPEEXPRESSIONSYNTAX_H__

#include "../TypeExpressionSyntax.h"

class ArrayTypeExpressionSyntax : public TypeExpressionSyntax {
 private:
  std::vector<std::unique_ptr<ExpressionSyntax>> _dimensions;
  std::unique_ptr<SyntaxToken<std::any>> _elementType;

 public:
  virtual SyntaxKindUtils::SyntaxKind getKind() const override;
  virtual std::vector<SyntaxNode *> getChildren() override;
  virtual DiagnosticUtils::SourceLocation getSourceLocation() const override;

  ArrayTypeExpressionSyntax(std::unique_ptr<SyntaxToken<std::any>> type);

  // Setters
  inline void setElementType(std::unique_ptr<SyntaxToken<std::any>> type) {
    _elementType = std::move(type);
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
};

#endif  // __FLOW__WING__ARRAYTYPEEXPRESSIONSYNTAX_H__
