#pragma once
#include "../../../Common.h"
#include "../../../utils/Utils.h"
#include "../../SyntaxKindUtils.h"
#include "../../SyntaxToken.h"
#include "../../expression/ExpressionSyntax.h"
#include "../../expression/TypeExpressionSyntax/TypeExpressionSyntax.h"
#include "../StatementSyntax.h"

class VariableDeclarationSyntax : public StatementSyntax {
private:
  std::unique_ptr<SyntaxToken<std::any>> _keyword;
  std::unique_ptr<SyntaxToken<std::any>> _identifier;

  std::unique_ptr<SyntaxToken<std::any>> _exposeKeyword;
  std::unique_ptr<ExpressionSyntax> _initializer;
  std::unique_ptr<TypeExpressionSyntax> _typeExpr;

public:
  const SyntaxKindUtils::SyntaxKind getKind() const override;
  const std::vector<SyntaxNode *> &getChildren() override;
  const DiagnosticUtils::SourceLocation getSourceLocation() const override;

  // Setters
  inline void setKeyword(std::unique_ptr<SyntaxToken<std::any>> keyword) {
    _keyword = std::move(keyword);
  }

  inline void setIdentifier(std::unique_ptr<SyntaxToken<std::any>> identifier) {
    _identifier = std::move(identifier);
  }

  inline void setInitializer(std::unique_ptr<ExpressionSyntax> initializer) {
    _initializer = std::move(initializer);
  }

  inline void setTypeExpr(std::unique_ptr<TypeExpressionSyntax> typeExpr) {
    _typeExpr = std::move(typeExpr);
  }

  inline void
  setExposeKeyword(std::unique_ptr<SyntaxToken<std::any>> exposeKeyword) {
    _exposeKeyword = std::move(exposeKeyword);
  }

  // Getters
  inline auto getIdentifierRef()
      -> const std::unique_ptr<SyntaxToken<std::any>> & {
    return _identifier;
  }

  inline auto getKeywordRef()
      -> const std::unique_ptr<SyntaxToken<std::any>> & {
    return _keyword;
  }

  inline auto getTypeRef() -> const std::unique_ptr<TypeExpressionSyntax> & {
    return _typeExpr;
  }

  inline auto getInitializerRef() -> const std::unique_ptr<ExpressionSyntax> & {
    return _initializer;
  }

  inline auto isExposed() -> bool { return _exposeKeyword != nullptr; }
};