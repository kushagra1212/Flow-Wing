#include "ModuleIdentifierExpressionParser.h"
#include <memory>

std::unique_ptr<ExpressionSyntax>
ModuleIdentifierExpressionParser::parseExpression(ParserContext *ctx) {
  std::unique_ptr<SyntaxToken<std::any>> moduleIdentifier =
      std::move(ctx->match(SyntaxKindUtils::SyntaxKind::IdentifierToken));

  ctx->match(SyntaxKindUtils::SyntaxKind::ColonToken);
  ctx->match(SyntaxKindUtils::SyntaxKind::ColonToken);

  std::unique_ptr<ExpressionSyntax> member = std::move(
      std::make_unique<IdentifierExpressionParser>()->parseExpression(ctx));

  std::unique_ptr<TypeExpressionSyntax> typeExpression =
      std::make_unique<TypeExpressionSyntax>(
          std::make_unique<SyntaxToken<std::any>>(
              ctx->getDiagnosticHandler()->getAbsoluteFilePath(), 0,
              SyntaxKindUtils::SyntaxKind::NBU_UNKNOWN_TYPE, 0,
              "NBU_UNKNOWN_TYPE", "NBU_UNKNOWN_TYPE"));

  std::any value = moduleIdentifier->getValue();

  std::unique_ptr<VariableExpressionSyntax> variExp =
      std::make_unique<VariableExpressionSyntax>(
          std::make_unique<LiteralExpressionSyntax<std::any>>(
              std::move(moduleIdentifier), value),
          false, std::move(typeExpression));
  const std::string PREFIX = std::any_cast<std::string>(value) +
                             FLOWWING::UTILS::CONSTANTS::MODULE_PREFIX;

  if (member->getKind() ==
      SyntaxKindUtils::SyntaxKind::VariableExpressionSyntax) {

    VariableExpressionSyntax *memberExp =
        static_cast<VariableExpressionSyntax *>(member.get());
    memberExp->getIdentifierTokenRef()->setValue(
        PREFIX + (memberExp->getVariableName()));
    memberExp->getIdentifierTokenRef()->setText(std::any_cast<std::string>(
        memberExp->getIdentifierTokenRef()->getValue()));
  } else if (member->getKind() ==
             SyntaxKindUtils::SyntaxKind::AssignmentExpression) {

    AssignmentExpressionSyntax *assignExpr =
        static_cast<AssignmentExpressionSyntax *>(member.get());

    if (assignExpr->getLeftPtr()->getKind() ==
        SyntaxKindUtils::SyntaxKind::VariableExpressionSyntax) {

      VariableExpressionSyntax *memberExp =
          static_cast<VariableExpressionSyntax *>(
              assignExpr->getLeftPtr().get());
      memberExp->getIdentifierTokenRef()->setValue(
          PREFIX + (memberExp->getVariableName()));
      memberExp->getIdentifierTokenRef()->setText(std::any_cast<std::string>(
          memberExp->getIdentifierTokenRef()->getValue()));

    } else if (assignExpr->getLeftPtr()->getKind() ==
               SyntaxKindUtils::SyntaxKind::IndexExpression) {
      IndexExpressionSyntax *memberExp =
          static_cast<IndexExpressionSyntax *>(assignExpr->getLeftPtr().get());
      //! TODO:
      memberExp->getIndexIdentifierExpressionPtr()->setValue(
          PREFIX +
          std::any_cast<std::string>(
              memberExp->getIndexIdentifierExpressionPtr()->getValue()));
      memberExp->getIndexIdentifierExpressionPtr()->setText(
          std::any_cast<std::string>(
              memberExp->getIndexIdentifierExpressionPtr()->getValue()));
    }
  } else if (member->getKind() == SyntaxKindUtils::SyntaxKind::CallExpression) {

    CallExpressionSyntax *callExp =
        static_cast<CallExpressionSyntax *>(member.get());

    callExp->getIdentifierPtr()->setValue(
        PREFIX +
        std::any_cast<std::string>((callExp->getIdentifierPtr()->getValue())));

    callExp->getIdentifierPtr()->setText(
        std::any_cast<std::string>(callExp->getIdentifierPtr()->getValue()));
  }

  variExp->setModuleNameorCallExpression(std::move(member));

  return std::move(variExp);
}