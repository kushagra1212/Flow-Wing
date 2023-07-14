#include "SyntaxToken.h"

SyntaxToken::SyntaxToken(SyntaxKindUtils::SyntaxKind kind, int position,
                         std::string text, int *v) {
  this->kind = kind;
  this->position = position;
  this->text = text;
  if (v != nullptr)
    this->value = new int(*v);
}

SyntaxKindUtils::SyntaxKind SyntaxToken::getKind() { return this->kind; }

int SyntaxToken::getPosition() { return this->position; }

std::string SyntaxToken::getText() { return this->text; }

int SyntaxToken::getValue() { return *(this->value); }

std::string SyntaxToken::getKindText() {
  return SyntaxKindUtils::enum_to_string_map[this->kind];
}

int SyntaxToken::getUnaryOperatorPrecedence() {
  switch (this->kind) {
  case SyntaxKindUtils::PlusToken:
  case SyntaxKindUtils::MinusToken:
    return 3;
  default:
    return 0;
  }
}

int SyntaxToken::getBinaryOperatorPrecedence() {
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

std::vector<SyntaxNode *> SyntaxToken::getChildren() { return children; }
