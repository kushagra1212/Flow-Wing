
#include "MultipleVariableDeclarationBinder.h"
#include <memory>

std::unique_ptr<BoundStatement>
MultipleVariableDeclarationBinder::bindStatement(SyntaxBinderContext *ctx,
                                                 StatementSyntax *statement) {

  MultipleVariableDeclarationSyntax *multipleVariableDeclaration =
      static_cast<MultipleVariableDeclarationSyntax *>(statement);

  std::unique_ptr<BoundMultipleVariableDeclaration>
      boundMultipleVariableDeclaration =
          std::make_unique<BoundMultipleVariableDeclaration>(
              multipleVariableDeclaration->getSourceLocation());

  for (auto &variableDeclaration :
       multipleVariableDeclaration->getVariableDeclarationListRef()) {

    std::unique_ptr<BoundVariableDeclaration> boundVarDec(
        static_cast<BoundVariableDeclaration *>(
            StatementBinderFactory::create(variableDeclaration->getKind())
                ->bindStatement(ctx, variableDeclaration.get())
                .release()));

    boundMultipleVariableDeclaration->addVariableDeclaration(
        std::move(boundVarDec));
  }

  auto firstVariableDeclaration =
      boundMultipleVariableDeclaration->getVariableDeclarationListRef()[0]
          .get();

  for (auto i = 1;
       i <
       boundMultipleVariableDeclaration->getVariableDeclarationListRef().size();
       i++) {
    boundMultipleVariableDeclaration->getVariableDeclarationListRef()[i]
        ->setIsConst(firstVariableDeclaration->isConst());

    boundMultipleVariableDeclaration->getVariableDeclarationListRef()[i]
        ->setHasAsKeyword(firstVariableDeclaration->getHasAsKeyword());

    boundMultipleVariableDeclaration->getVariableDeclarationListRef()[i]
        ->setHasInOutKeyword(firstVariableDeclaration->getHasInOutKeyword());

    boundMultipleVariableDeclaration->getVariableDeclarationListRef()[i]
        ->setMemoryKind(firstVariableDeclaration->getMemoryKind());

    boundMultipleVariableDeclaration->getVariableDeclarationListRef()[i]
        ->setIsExposed(firstVariableDeclaration->isExposed());
  }

  return std::move(boundMultipleVariableDeclaration);
}