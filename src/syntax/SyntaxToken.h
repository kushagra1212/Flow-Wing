
#ifndef SYNTAXTOKEN_H
#define SYNTAXTOKEN_H
#include "SyntaxNode.h"

template <typename T> class SyntaxToken : public SyntaxNode {
private:
  SyntaxKindUtils::SyntaxKind kind;
  std::string text;
  T value;

public:
  SyntaxToken(int lineNumber, SyntaxKindUtils::SyntaxKind kind, int position,
              std::string text, T value);

  int getPosition();

  int getLineNumber();

  std::string getText();

  T getValue();

  std::string getKindText();

  int getUnaryOperatorPrecedence();

  int getBinaryOperatorPrecedence();

  SyntaxKindUtils::SyntaxKind getKind() const override;

  std::string getLineNumberAndColumn() override;

  std::vector<SyntaxNode *> getChildren() override;
};
#endif