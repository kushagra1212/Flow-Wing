#ifndef CALL_EXPRESSION_SYNTAX_H
#define CALL_EXPRESSION_SYNTAX_H

#include "../../SyntaxKindUtils.h"
#include "../../SyntaxNode.h"
#include "../../SyntaxToken.h"
#include "../ExpressionSyntax.h"
#include "../LiteralExpressionSyntax.h"

class CallExpressionSyntax : public ExpressionSyntax {
private:
  std::unique_ptr<LiteralExpressionSyntax<std::any>> _identifier;
  std::unique_ptr<SyntaxToken<std::any>> _openParenthesisToken;
  std::vector<std::unique_ptr<ExpressionSyntax>> _arguments;
  std::vector<std::unique_ptr<SyntaxToken<std::any>>> _separators;
  std::unique_ptr<SyntaxToken<std::any>> _closeParenthesisToken;

public:
  CallExpressionSyntax(
      std::unique_ptr<LiteralExpressionSyntax<std::any>> identifier);

  std::unique_ptr<LiteralExpressionSyntax<std::any>> getIdentifier();
  std::unique_ptr<SyntaxToken<std::any>> getOpenParenthesisToken();
  std::unique_ptr<SyntaxToken<std::any>> getCloseParenthesisToken();

  void addArgument(std::unique_ptr<ExpressionSyntax> argument);
  void addSeparator(std::unique_ptr<SyntaxToken<std::any>> separator);
  void setOpenParenthesisToken(
      std::unique_ptr<SyntaxToken<std::any>> openParenthesisToken);
  void setCloseParenthesisToken(
      std::unique_ptr<SyntaxToken<std::any>> closeParenthesisToken);

  SyntaxKindUtils::SyntaxKind getKind() const override;
  std::vector<SyntaxNode *> getChildren() override;
  DiagnosticUtils::SourceLocation getSourceLocation() const override;

  std::vector<std::unique_ptr<ExpressionSyntax>> &getArguments();
  std::vector<std::unique_ptr<SyntaxToken<std::any>>> &getSeparators();
  std::unique_ptr<LiteralExpressionSyntax<std::any>> &getIdentifierPtr();
  std::unique_ptr<SyntaxToken<std::any>> &getOpenParenthesisTokenPtr();
  std::unique_ptr<SyntaxToken<std::any>> &getCloseParenthesisTokenPtr();
};

#endif // CALL_EXPRESSION_SYNTAX_H
