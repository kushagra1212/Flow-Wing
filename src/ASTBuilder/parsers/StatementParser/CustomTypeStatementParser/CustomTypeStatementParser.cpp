#include "CustomTypeStatementParser.h"

std::unique_ptr<StatementSyntax>
CustomTypeStatementParser::parseStatement(ParserContext *ctx) {
  std::unique_ptr<CustomTypeStatementSyntax> customTypeStatement =
      std::make_unique<CustomTypeStatementSyntax>();

  if (ctx->getKind() == SyntaxKindUtils::SyntaxKind::ExposeKeyword) {
    customTypeStatement->setExposeKeyword(
        std::move(ctx->match(SyntaxKindUtils::SyntaxKind::ExposeKeyword)));
    ctx->getCodeFormatterRef()->appendWithSpace();
  }
  ctx->match(SyntaxKindUtils::SyntaxKind::TypeKeyword);
  ctx->getCodeFormatterRef()->appendWithSpace();

  std::any val = "";
  std::unique_ptr<SyntaxToken<std::any>> typeToken =
      std::move(ctx->match(SyntaxKindUtils::SyntaxKind::IdentifierToken));
  ctx->getCodeFormatterRef()->appendWithSpace();

  std::string MODULE_PREFIX = "";

  if (ctx->getCurrentModuleName() != "") {

    MODULE_PREFIX =
        ctx->getCurrentModuleName() + FLOWWING::UTILS::CONSTANTS::MODULE_PREFIX;
  }

  if (typeToken->getValue().type() == typeid(std::string)) {
    const std::string PREFIX =
        MODULE_PREFIX + std::any_cast<std::string>(typeToken->getValue());
    val = PREFIX + FLOWWING::UTILS::CONSTANTS::MEMBER_FUN_PREFIX +
          IDGenerator::CustomTypeIDGenerator::instance()->nextString();
    //! CHECK
    typeToken->setValue(val);
    typeToken->setText(std::any_cast<std::string>(val));
  }
  DEBUG_LOG("Declared Type: " + std::any_cast<std::string>(val));
  std::unique_ptr<LiteralExpressionSyntax<std::any>> typeNameExp =
      std::make_unique<LiteralExpressionSyntax<std::any>>(std::move(typeToken),
                                                          val);

  customTypeStatement->setTypeName(std::move(typeNameExp));

  ctx->match(SyntaxKindUtils::SyntaxKind::EqualsToken);
  ctx->getCodeFormatterRef()->appendWithSpace();
  ctx->match(SyntaxKindUtils::SyntaxKind::OpenBraceToken);
  ctx->getCodeFormatterRef()->appendNewLine();
  ctx->getCodeFormatterRef()->appendIndentAmount(TAB_SPACE);
  while (ctx->getKind() != SyntaxKindUtils::SyntaxKind::CloseBraceToken &&
         ctx->getKind() != SyntaxKindUtils::SyntaxKind::EndOfFileToken) {

    ctx->getCodeFormatterRef()->append(
        ctx->getCodeFormatterRef()->getIndentAmount());

    std::unique_ptr<SyntaxToken<std::any>> idenfierToken =
        std::move(ctx->match(SyntaxKindUtils::SyntaxKind::IdentifierToken));

    std::any val = idenfierToken->getValue();

    std::unique_ptr<LiteralExpressionSyntax<std::any>> idenfierExp =
        std::make_unique<LiteralExpressionSyntax<std::any>>(
            std::move(idenfierToken), val);

    ctx->match(SyntaxKindUtils::SyntaxKind::ColonToken);
    ctx->getCodeFormatterRef()->appendWithSpace();

    std::unique_ptr<TypeExpressionSyntax> typeExpression(
        static_cast<TypeExpressionSyntax *>(
            std::make_unique<TypeExpressionParser>()
                ->parseExpression(ctx)
                .release()));

    customTypeStatement->addKeyTypePair(std::move(idenfierExp),
                                        std::move(typeExpression));

    if (ctx->getKind() != SyntaxKindUtils::SyntaxKind::CloseBraceToken) {
      ctx->match(SyntaxKindUtils::SyntaxKind::CommaToken);
    }
    ctx->getCodeFormatterRef()->appendNewLine();
  }

  ctx->getCodeFormatterRef()->setIndentAmount(
      ctx->getCodeFormatterRef()->getIndentAmount().substr(
          0, ctx->getCodeFormatterRef()->getIndentAmount().length() -
                 (sizeof(TAB_SPACE) - 1)));

  ctx->getCodeFormatterRef()->append(
      ctx->getCodeFormatterRef()->getIndentAmount());

  ctx->match(SyntaxKindUtils::SyntaxKind::CloseBraceToken);
  return std::move(customTypeStatement);
}
