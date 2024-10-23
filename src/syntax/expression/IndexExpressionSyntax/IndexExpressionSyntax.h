#ifndef INDEXEXPRESSIONSYNTAX_H
#define INDEXEXPRESSIONSYNTAX_H
#include "../../../common/Common.h"
#include "../../SyntaxToken.h"
#include "../ExpressionSyntax.h"
#include "../LiteralExpressionSyntax.h"

class IndexExpressionSyntax : public ExpressionSyntax {
private:
  std::unique_ptr<LiteralExpressionSyntax<std::any>> _identifierExpression;
  std::vector<std::unique_ptr<ExpressionSyntax>> _indexExpressions;
  std::unique_ptr<ExpressionSyntax> _variableExpression;
  std::unique_ptr<SyntaxToken<std::any>> _selfKeyword;
  bool _isObject = false;

public:
  IndexExpressionSyntax(
      std::unique_ptr<LiteralExpressionSyntax<std::any>> identifierExpression);

  inline auto addIndexExpression(std::unique_ptr<ExpressionSyntax> item)
      -> void {
    this->_indexExpressions.push_back(std::move(item));
  }

  inline auto
  addVariableExpression(std::unique_ptr<ExpressionSyntax> variableExpression)
      -> void {
    _isObject = true;
    _variableExpression = std::move(variableExpression);
  }

  inline auto addSelfKeyword(std::unique_ptr<SyntaxToken<std::any>> selfKeyword)
      -> void {
    _selfKeyword = std::move(selfKeyword);
  }

  inline auto getIndexExpressionsRef() const
      -> const std::vector<std::unique_ptr<ExpressionSyntax>> & {
    return this->_indexExpressions;
  }

  inline auto getVariableExpressionRef() const
      -> const std::unique_ptr<ExpressionSyntax> & {
    return _variableExpression;
  }

  inline auto getIsSelf() -> bool { return _selfKeyword != nullptr; }

  inline auto isObject() const -> bool { return _isObject; }

  std::unique_ptr<LiteralExpressionSyntax<std::any>> &
  getIndexIdentifierExpressionRef();

  const SyntaxKindUtils::SyntaxKind getKind() const override;
  const std::vector<SyntaxNode *> &getChildren() override;
  const DiagnosticUtils::SourceLocation getSourceLocation() const override;
};

#endif // INDEXEXPRESSIONSYNTAX_H
