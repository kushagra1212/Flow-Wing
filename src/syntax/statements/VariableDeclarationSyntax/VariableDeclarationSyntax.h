#pragma once
#include "../../../common/Common.h"
#include "../../../utils/Utils.h"
#include "../../SyntaxKindUtils.h"
#include "../../SyntaxToken.h"
#include "../../expression/ExpressionSyntax.h"
#include "../../expression/TypeExpressionSyntax/TypeExpressionSyntax.h"
#include "../StatementSyntax.h"

class VariableDeclarationSyntax : public StatementSyntax {
private:
  std::unique_ptr<SyntaxToken<std::any>> _keyword;
  std::unique_ptr<SyntaxToken<std::any>> _inout_keyword;
  std::unique_ptr<SyntaxToken<std::any>> _identifier;
  std::unique_ptr<SyntaxToken<std::any>> _newKeyword;
  std::unique_ptr<SyntaxToken<std::any>> _exposeKeyword;
  std::unique_ptr<SyntaxToken<std::any>> _asKeyword;
  std::unique_ptr<ExpressionSyntax> _initializer;
  std::unique_ptr<TypeExpressionSyntax> _typeExpr;
  bool _hasNewKeyword = false;

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

  inline auto setAsKeyword(std::unique_ptr<SyntaxToken<std::any>> asKeyword) {
    _asKeyword = std::move(asKeyword);
  }

  inline auto
  setInoutKeyword(std::unique_ptr<SyntaxToken<std::any>> inoutKeyword) -> void {
    _inout_keyword = std::move(inoutKeyword);
  }
  inline void
  setExposeKeyword(std::unique_ptr<SyntaxToken<std::any>> exposeKeyword) {
    _exposeKeyword = std::move(exposeKeyword);
  }

  inline void setNewKeyword(std::unique_ptr<SyntaxToken<std::any>> newkeyword) {
    _hasNewKeyword = true;
    _newKeyword = std::move(newkeyword);
  }

  // Getters
  inline auto getIdentifierRef()
      -> const std::unique_ptr<SyntaxToken<std::any>> & {
    return _identifier;
  }

  inline auto getInoutKeywordRef()
      -> const std::unique_ptr<SyntaxToken<std::any>> & {
    return _inout_keyword;
  }

  inline auto getKeywordRef()
      -> const std::unique_ptr<SyntaxToken<std::any>> & {
    return _keyword;
  }

  inline auto getTypeRef() -> const std::unique_ptr<TypeExpressionSyntax> & {
    return _typeExpr;
  }

  inline auto getAsKeywordRef()
      -> const std::unique_ptr<SyntaxToken<std::any>> & {
    return _asKeyword;
  }

  inline auto getInitializerRef() -> std::unique_ptr<ExpressionSyntax> & {
    return _initializer;
  }
  inline auto getHasNewKeyWord() -> bool & { return _hasNewKeyword; }

  inline auto isExposed() -> bool { return _exposeKeyword != nullptr; }
};