#include "CompilationUnitSyntax.h"
class CompilationUnitSyntax {
private:
  ExpressionSyntax *expression;
  SyntaxToken *endOfFileToken;

public:
  std::vector<std::string> logs;
  CompilationUnitSyntax(std::vector<std::string> &logs,
                        ExpressionSyntax *expression,
                        SyntaxToken *endOfFileToken) {
    this->expression = expression;
    this->endOfFileToken = endOfFileToken;
    this->logs = logs;
  }

public:
  SyntaxKindUtils::SyntaxKind getKind() {
    return SyntaxKindUtils::SyntaxKind::CompilationUnit;
  }

public:
  ExpressionSyntax *getExpression() { return this->expression; }

public:
  SyntaxToken *getEndOfFileToken() { return this->endOfFileToken; }
};
