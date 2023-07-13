#include "SyntaxNode.h"
#ifndef SYNTAXTOKEN_H
#define SYNTAXTOKEN_H
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
              int *v) {
    this->kind = kind;
    this->position = position;
    this->text = text;
    if (v != nullptr)
      this->value = new int(*v);
  }

public:
  SyntaxKindUtils::SyntaxKind getKind() { return this->kind; }

public:
  int getPosition() { return this->position; }

public:
  std::string getText() { return this->text; }

public:
  int getValue() { return *(this->value); }

public:
  std::string getKindText() {
    return SyntaxKindUtils::enum_to_string_map[this->kind];
  }

public:
  int getUnaryOperatorPrecedence() {
    switch (this->kind) {
    case SyntaxKindUtils::PlusToken:
    case SyntaxKindUtils::MinusToken:
      return 3;
    default:
      return 0;
    }
  }

public:
  int getBinaryOperatorPrecedence() {
    switch (this->kind) {
    case SyntaxKindUtils::StarToken:
    case SyntaxKindUtils::SlashToken:
      return 2;
    case SyntaxKindUtils::PlusToken:
    case SyntaxKindUtils::MinusToken:
      return 1;
    default:
      return 0;
    }
  }

public:
public:
  std::vector<SyntaxNode *> children;
  std::vector<SyntaxNode *> getChildren() { return children; }
};
#endif