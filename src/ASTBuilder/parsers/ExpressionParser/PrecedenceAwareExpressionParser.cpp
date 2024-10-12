#include "PrecedenceAwareExpressionParser.h"
#include "TernaryExpressionParser/TernaryExpressionParser.h"
#include <memory>

std::unique_ptr<ExpressionSyntax>
PrecedenceAwareExpressionParser::parse(ParserContext *ctx,
                                       const int &parentPrecedence) {
  std::unique_ptr<ExpressionSyntax> left = nullptr;
  size_t unaryOperatorPrecedence =
      ctx->getCurrent()->getUnaryOperatorPrecedence();

  if (unaryOperatorPrecedence != 0 &&
      unaryOperatorPrecedence >= parentPrecedence) {
    std::unique_ptr<SyntaxToken<std::any>> operatorToken =
        std::move(ctx->match(ctx->getKind()));
    std::unique_ptr<ExpressionSyntax> operand = std::move(
        PrecedenceAwareExpressionParser::parse(ctx, unaryOperatorPrecedence));
    left = std::make_unique<UnaryExpressionSyntax>(std::move(operatorToken),
                                                   std::move(operand));

  } else {
    left =
        std::move(PrimaryExpressionParserFactory::createPrimaryExpressionParser(
                      ctx->getKind()))
            ->parseExpression(ctx);
  }

  while (true) {
    int precedence = ctx->getCurrent()->getBinaryOperatorPrecedence();
    if (precedence == 0 || precedence <= parentPrecedence) {
      break;
    }
    ctx->getCodeFormatterRef()->appendWithSpace();
    std::unique_ptr<SyntaxToken<std::any>> operatorToken =
        std::move(ctx->match(ctx->getKind()));
    ctx->getCodeFormatterRef()->appendWithSpace();

    std::unique_ptr<ExpressionSyntax> right =
        std::move(PrecedenceAwareExpressionParser::parse(ctx, precedence));

    left = std::make_unique<BinaryExpressionSyntax>(
        std::move(left), std::move(operatorToken), std::move(right));
  }

  if (ctx->getKind() == SyntaxKindUtils::SyntaxKind::QuestionToken) {
    auto ternaryExpression = std::move(
        std::make_unique<TernaryExpressionParser>()->parseExpression(ctx));

    static_cast<TernaryExpressionSyntax *>(ternaryExpression.get())
        ->addConditionExpression(std::move(left));

    left = std::move(ternaryExpression);
  }

  return std::move(left);
}