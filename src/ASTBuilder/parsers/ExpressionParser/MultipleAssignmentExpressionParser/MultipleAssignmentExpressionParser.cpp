#include "MultipleAssignmentExpressionParser.h"
#include <memory>

std::unique_ptr<ExpressionSyntax>
MultipleAssignmentExpressionParser::parseExpression(ParserContext *ctx) {
  std::unique_ptr<MultipleAssignmentExpressionSyntax>
      multipleAssignmentExpression =
          std::make_unique<MultipleAssignmentExpressionSyntax>();

  std::vector<std::unique_ptr<VariableExpressionSyntax>>
      variableExpressionsList;
  do {

    if (ctx->getKind() == SyntaxKindUtils::SyntaxKind::CommaToken) {
      ctx->match(SyntaxKindUtils::SyntaxKind::CommaToken);
      ctx->getCodeFormatterRef()->appendWithSpace();
    }

    std::unique_ptr<VariableExpressionSyntax> variableExpression(
        static_cast<VariableExpressionSyntax *>(
            std::make_unique<VariableExpressionParser>()
                ->parseExpression(ctx)
                .release()));

    variableExpressionsList.push_back(std::move(variableExpression));

  } while (ctx->getKind() == SyntaxKindUtils::SyntaxKind::CommaToken);

  ctx->getCodeFormatterRef()->appendWithSpace();

  bool needDefaultInitialize = false;
  std::unique_ptr<SyntaxToken<std::any>> operatorToken = nullptr;
  if (ctx->getKind() == SyntaxKindUtils::SyntaxKind::EqualsToken) {
    operatorToken =
        std::move(ctx->match(SyntaxKindUtils::SyntaxKind::EqualsToken));
  } else if (ctx->getKind() == SyntaxKindUtils::SyntaxKind::AssignmentToken) {
    operatorToken =
        std::move(ctx->match(SyntaxKindUtils::SyntaxKind::AssignmentToken));
    needDefaultInitialize = true;
  } else {
    ctx->match(SyntaxKindUtils::SyntaxKind::EqualsToken);
    return std::move(multipleAssignmentExpression);
  }

  uint64_t index = 0;
  ctx->getCodeFormatterRef()->appendWithSpace();
  do {
    if (ctx->getKind() == SyntaxKindUtils::SyntaxKind::CommaToken) {
      ctx->match(SyntaxKindUtils::SyntaxKind::CommaToken);
      ctx->getCodeFormatterRef()->appendWithSpace();
    }

    if (ctx->getKind() == SyntaxKindUtils::SyntaxKind::NewKeyword) {
      variableExpressionsList[index]->setNewKeyword(
          std::move(ctx->match(SyntaxKindUtils::SyntaxKind::NewKeyword)));
      ctx->getCodeFormatterRef()->appendWithSpace();
    }
    std::unique_ptr<ExpressionSyntax> right =
        std::move(PrecedenceAwareExpressionParser::parse(ctx));

    multipleAssignmentExpression->addAssignmentExpression(
        std::make_unique<AssignmentExpressionSyntax>(
            std::move(variableExpressionsList[index]), operatorToken->getKind(),
            std::move(right), needDefaultInitialize));
    index++;
  } while (ctx->getKind() == SyntaxKindUtils::SyntaxKind::CommaToken);

  for (; index < variableExpressionsList.size(); index++) {

    multipleAssignmentExpression->addAssignmentExpression(
        std::make_unique<AssignmentExpressionSyntax>(
            std::move(variableExpressionsList[index]), operatorToken->getKind(),
            nullptr, needDefaultInitialize));
  }

  ctx->getCodeFormatterRef()->appendWithSpace();

  return std::move(multipleAssignmentExpression);
}