#ifndef __FLOW__WING__OBJECT_TYPEEXPRESSIONSYNTAX_H__
#define __FLOW__WING__OBJECT_TYPEEXPRESSIONSYNTAX_H__

#include "../TypeExpressionSyntax.h"

class ObjectTypeExpressionSyntax : public TypeExpressionSyntax {
private:
  std::unique_ptr<LiteralExpressionSyntax<std::any>> _objectTypeIdentifier;

public:
  ObjectTypeExpressionSyntax(Utils::type type);

  virtual SyntaxKindUtils::SyntaxKind getKind() const override;
  virtual std::vector<SyntaxNode *> getChildren() override;

  inline auto setObjectTypeIdentifier(
      std::unique_ptr<LiteralExpressionSyntax<std::any>> objectTypeIdentifier)
      -> void {
    this->_objectTypeIdentifier = std::move(objectTypeIdentifier);
  }

  inline auto getObjectTypeIdentifierRef()
      -> const std::unique_ptr<LiteralExpressionSyntax<std::any>> & {
    return this->_objectTypeIdentifier;
  }
};

#endif // __FLOW__WING__OBJECT_TYPEEXPRESSIONSYNTAX_H__
