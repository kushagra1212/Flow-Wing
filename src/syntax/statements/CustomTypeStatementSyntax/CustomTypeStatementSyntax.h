#ifndef __FLOW__WING__CUSTOM_TYPE_STATEMENT_SYNTAX_H__
#define __FLOW__WING__CUSTOM_TYPE_STATEMENT_SYNTAX_H__
#include "../../../Common.h"
#include "../../../utils/Utils.h"
#include "../../SyntaxToken.h"
#include "../../expression/AttributeExpressionSyntax/AttributeExpressionSyntax.h"
#include "../../expression/LiteralExpressionSyntax.h"
#include "../../expression/TypeExpressionSyntax/TypeExpressionSyntax.h"
#include "../StatementSyntax.h"

class CustomTypeStatementSyntax : public StatementSyntax {
 private:
  std::unique_ptr<LiteralExpressionSyntax<std::any>> _typeName;
  std::vector<std::unique_ptr<AttributeExpressionSyntax>> _key_type_pairs;

 public:
  const virtual SyntaxKindUtils::SyntaxKind getKind() const override;
  const virtual std::vector<SyntaxNode *> &getChildren() override;
  const DiagnosticUtils::SourceLocation getSourceLocation() const override;

  /*
      Setters
  */

  inline auto setTypeName(
      std::unique_ptr<LiteralExpressionSyntax<std::any>> typeName) -> void {
    this->_typeName = std::move(typeName);
  }

  inline auto addKeyTypePair(
      std::unique_ptr<LiteralExpressionSyntax<std::any>> key,
      std::unique_ptr<TypeExpressionSyntax> type) -> void {
    std::unique_ptr<AttributeExpressionSyntax> key_type_pair =
        std::make_unique<AttributeExpressionSyntax>();

    key_type_pair->setAttribute(std::move(key), std::move(type));

    this->_key_type_pairs.push_back(std::move(key_type_pair));
  }

  /*
    Getters
  */

  inline auto getTypeNameRef()
      -> const std::unique_ptr<LiteralExpressionSyntax<std::any>> & {
    return this->_typeName;
  }

  inline auto getKeyTypePairsRef()
      -> const std::vector<std::unique_ptr<AttributeExpressionSyntax>> & {
    return this->_key_type_pairs;
  }
};

#endif  // __FLOW__WING__CUSTOM_TYPE_STATEMENT_SYNTAX_H__
