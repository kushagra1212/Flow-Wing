#ifndef __FLOW__WING__CUSTOM_TYPE_STATEMENT_SYNTAX_H__
#define __FLOW__WING__CUSTOM_TYPE_STATEMENT_SYNTAX_H__
#include "../../../Common.h"
#include "../../../utils/Utils.h"
#include "../../SyntaxToken.h"
#include "../../expression/LiteralExpressionSyntax.h"
#include "../../expression/TypeExpressionSyntax/TypeExpressionSyntax.h"
#include "../StatementSyntax.h"

class CustomTypeStatementSyntax : public StatementSyntax {
private:
  std::unique_ptr<LiteralExpressionSyntax<std::any>> _typeName;
  std::vector<std::pair<std::unique_ptr<LiteralExpressionSyntax<std::any>>,
                        std::unique_ptr<TypeExpressionSyntax>>>
      _key_type_pairs;

public:
  virtual SyntaxKindUtils::SyntaxKind getKind() const override;
  virtual std::vector<SyntaxNode *> getChildren() override;
  DiagnosticUtils::SourceLocation getSourceLocation() const override;

  /*
      Setters
  */

  inline auto
  setTypeName(std::unique_ptr<LiteralExpressionSyntax<std::any>> typeName)
      -> void {
    this->_typeName = std::move(typeName);
  }

  inline auto
  addKeyTypePair(std::unique_ptr<LiteralExpressionSyntax<std::any>> key,
                 std::unique_ptr<TypeExpressionSyntax> type) -> void {
    this->_key_type_pairs.push_back(
        std::make_pair(std::move(key), std::move(type)));
  }

  /*
    Getters
  */

  inline auto getTypeNameRef()
      -> const std::unique_ptr<LiteralExpressionSyntax<std::any>> & {
    return this->_typeName;
  }

  inline auto getKeyTypePairsRef() -> const
      std::vector<std::pair<std::unique_ptr<LiteralExpressionSyntax<std::any>>,
                            std::unique_ptr<TypeExpressionSyntax>>> & {
    return this->_key_type_pairs;
  }
};

#endif // __FLOW__WING__CUSTOM_TYPE_STATEMENT_SYNTAX_H__
