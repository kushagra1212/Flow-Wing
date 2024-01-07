#ifndef __FLOW__WING__BOUND_OBJECT_TYPEEXPRESSIONSYNTAX_H__
#define __FLOW__WING__BOUND_OBJECT_TYPEEXPRESSIONSYNTAX_H__

#include "../BoundTypeExpression.h"

class BoundObjectTypeExpression : public BoundTypeExpression {
 private:
  std::unique_ptr<BoundLiteralExpression<std::any>> _objectTypeIdentifier;

 public:
  BoundObjectTypeExpression(const DiagnosticUtils::SourceLocation &location,
                            const SyntaxKindUtils::SyntaxKind &type);

  virtual std::vector<BoundNode *> getChildren() override;
  virtual BinderKindUtils::BoundNodeKind getKind() const override;

  inline auto setObjectTypeIdentifier(
      std::unique_ptr<BoundLiteralExpression<std::any>> objectTypeIdentifier)
      -> void {
    this->_objectTypeIdentifier = std::move(objectTypeIdentifier);
  }

  inline auto getObjectTypeIdentifier()
      -> const std::unique_ptr<BoundLiteralExpression<std::any>> & {
    return this->_objectTypeIdentifier;
  }
};

#endif  // __FLOW__WING__BOUND_OBJECT_TYPEEXPRESSIONSYNTAX_H__
