#ifndef __FLOW__WING__ARRAYTYPEEXPRESSIONSYNTAX_H__
#define __FLOW__WING__ARRAYTYPEEXPRESSIONSYNTAX_H__

#include "../TypeExpressionSyntax.h"

class ArrayTypeExpressionSyntax : public TypeExpressionSyntax {
private:
  std::vector<std::unique_ptr<ExpressionSyntax>> _dimensions;

public:
  virtual SyntaxKindUtils::SyntaxKind getKind() const override;
  virtual std::vector<SyntaxNode *> getChildren() override;

  ArrayTypeExpressionSyntax(Utils::type type);
  inline void addDimension(std::unique_ptr<ExpressionSyntax> dimension) {
    _dimensions.push_back(std::move(dimension));
  }

  inline auto getDimensions() const
      -> const std::vector<std::unique_ptr<ExpressionSyntax>> & {
    return _dimensions;
  }
};

#endif // __FLOW__WING__ARRAYTYPEEXPRESSIONSYNTAX_H__
