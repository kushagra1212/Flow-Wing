#include "ExpressionStatementParser.h"

std::unique_ptr<StatementSyntax>
ExpressionStatementParser::parseStatement(ParserContext *ctx) {
  std::unique_ptr<ExpressionSyntax> expression =
      std::move(PrecedenceAwareExpressionParser::parse(ctx));

  return std::make_unique<ExpressionStatementSyntax>(std::move(expression));
}
