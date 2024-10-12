#include "ObjectTypeExpressionParser.h"

std::unique_ptr<ExpressionSyntax>
ObjectTypeExpressionParser::parseExpression(ParserContext *ctx) {
  std::unique_ptr<ObjectTypeExpressionSyntax> objectTypeExpression =
      std::make_unique<ObjectTypeExpressionSyntax>(
          std::make_unique<SyntaxToken<std::any>>(
              ctx->getDiagnosticHandler()->getAbsoluteFilePath(), 0,
              SyntaxKindUtils::SyntaxKind::NBU_OBJECT_TYPE, 0,
              "NBU_OBJECT_TYPE", "NBU_OBJECT_TYPE"));

  std::unique_ptr<SyntaxToken<std::any>> iden =
      std::move(ctx->match(SyntaxKindUtils::SyntaxKind::IdentifierToken));

  std::any value = iden->getValue();

  std::unique_ptr<LiteralExpressionSyntax<std::any>> literalExp =
      std::make_unique<LiteralExpressionSyntax<std::any>>(std::move(iden),
                                                          value);

  objectTypeExpression->setObjectTypeIdentifier(std::move(literalExp));

  return std::move(objectTypeExpression);
}