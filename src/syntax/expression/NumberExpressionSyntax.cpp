#include "../SyntaxToken.cpp"
#include "ExpressionSyntax.h"
class NumberExpressionSyntax : public ExpressionSyntax {

private:
  SyntaxToken *numberToken;

public:
  std::vector<SyntaxNode *> children;
  NumberExpressionSyntax(SyntaxToken *numberToken) {

    this->numberToken = numberToken;

    children.push_back(this->numberToken);
  }

public:
  SyntaxKindUtils::SyntaxKind getKind() {
    return SyntaxKindUtils::NumberExpression;
  }

public:
  std::string getKindText() {
    return SyntaxKindUtils::enum_to_string_map[this->getKind()];
  }

public:
  SyntaxToken *getNumberToken() { return this->numberToken; }

public:
  std::vector<SyntaxNode *> getChildren() { return children; }
};