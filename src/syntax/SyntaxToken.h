
#ifndef SYNTAXTOKEN_H
#define SYNTAXTOKEN_H
#include "SyntaxNode.h"
class SyntaxToken : public SyntaxNode {
private:
  SyntaxKindUtils::SyntaxKind kind;

private:
  int position;

private:
  std::string text;

private:
  int *value = nullptr;

public:
  SyntaxToken(SyntaxKindUtils::SyntaxKind kind, int position, std::string text,
              int *v);

public:
  SyntaxKindUtils::SyntaxKind getKind();

public:
  int getPosition();

public:
  std::string getText();

public:
  int getValue();

public:
  std::string getKindText();

public:
  int getUnaryOperatorPrecedence();

public:
  int getBinaryOperatorPrecedence();

public:
public:
  std::vector<SyntaxNode *> children;
  std::vector<SyntaxNode *> getChildren();
};
#endif