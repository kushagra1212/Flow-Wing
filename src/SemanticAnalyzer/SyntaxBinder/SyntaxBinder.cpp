#include "SyntaxBinder.h"
#include "MemberBinder/MemberBinderFactory.h"

SyntaxBinder::SyntaxBinder(std::unique_ptr<BoundScope> scope,
                           FlowWing::DiagnosticHandler *diagnosticHandler)
    : _context(std::make_unique<SyntaxBinderContext>(std::move(scope),
                                                     diagnosticHandler)) {}

std::unique_ptr<SyntaxBinderContext> &SyntaxBinder::getContextRef() {
  return _context;
}

std::unique_ptr<BoundStatement>
SyntaxBinder::bind(CompilationUnitSyntax *syntax) {

  std::unique_ptr<BoundBlockStatement> globalBoundBlockStatement =
      std::make_unique<BoundBlockStatement>(DiagnosticUtils::SourceLocation(),
                                            true);

  std::vector<std::unique_ptr<MemberSyntax>> &members = syntax->getMembers();

  std::vector<size_t> functionsYetToDefine = {};
  for (size_t i = 0; i < members.size(); i++) {
    switch (members[i].get()->getKind()) {
    case SyntaxKindUtils::SyntaxKind::FunctionDeclarationSyntax: {
      FunctionDeclarationSyntax *functionDeclarationSyntax =
          static_cast<FunctionDeclarationSyntax *>(members[i].get());

      //? Declaring All Functions (whether defined or not)

      if (!functionDeclarationSyntax->isOnlyDeclared()) {
        functionDeclarationSyntax->setIsOnlyDeclared(true);
        functionsYetToDefine.emplace_back(i);
      }

      globalBoundBlockStatement->addStatement(std::move(
          MemberBinderFactory::create(functionDeclarationSyntax->getKind())
              ->bindMember(_context.get(), functionDeclarationSyntax)));
      break;
    }
    case SyntaxKindUtils::SyntaxKind::GlobalStatement: {

      globalBoundBlockStatement->addStatement(
          std::move(MemberBinderFactory::create(members[i]->getKind())
                        ->bindMember(_context.get(), members[i].get())));
      break;
    }
    default:
      throw "Unexpected global member";
      break;
    }
  }

  //? DEFINING FUNCTIONS
  for (int i = 0; i < functionsYetToDefine.size(); i++) {
    FunctionDeclarationSyntax *functionDeclarationSyntax =
        (FunctionDeclarationSyntax *)members[functionsYetToDefine[i]].get();

    //? Only Defining Functions
    functionDeclarationSyntax->setIsOnlyDeclared(false);

    std::unique_ptr<BoundStatement> _statement = std::move(std::move(
        MemberBinderFactory::create(functionDeclarationSyntax->getKind())
            ->bindMember(_context.get(), functionDeclarationSyntax)));

    globalBoundBlockStatement->addStatement(std::move(_statement));
  }

  return globalBoundBlockStatement;
}