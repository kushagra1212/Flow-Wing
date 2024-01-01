#ifndef __FLOW__WING__TYPEEXPRESSIONSYNTAX_H__
#define __FLOW__WING__TYPEEXPRESSIONSYNTAX_H__
#include "../../../Common.h"
#include "../../../utils/Utils.h"
#include "../../SyntaxToken.h"
#include "../ExpressionSyntax.h"
#include "../LiteralExpressionSyntax.h"

class TypeExpressionSyntax : public ExpressionSyntax {
private:
  Utils::type _type;

public:
  TypeExpressionSyntax(Utils::type type);
  virtual SyntaxKindUtils::SyntaxKind getKind() const override;
  virtual std::vector<SyntaxNode *> getChildren() override;
  DiagnosticUtils::SourceLocation getSourceLocation() const override;

  inline auto getType() const -> const Utils::type & { return _type; }

  inline void setType(const Utils::type &type) { _type = type; }
};

#endif // __FLOW__WING__TYPEEXPRESSIONSYNTAX_H__
