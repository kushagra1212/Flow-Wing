#include "SyntaxToken.h"

SyntaxToken::SyntaxToken(SyntaxKindUtils::SyntaxKind kind, int position,
                         std::string text, std::shared_ptr<void> value) {
  this->kind = kind;
  this->position = position;
  this->text = text;
  if (value != nullptr)
    this->value = std::move(value);
}

SyntaxKindUtils::SyntaxKind SyntaxToken::getKind() { return this->kind; }

int SyntaxToken::getPosition() { return this->position; }

std::string SyntaxToken::getText() { return this->text; }

std::shared_ptr<void> SyntaxToken::getValue() { return (this->value); }

std::string SyntaxToken::getKindText() {
  return SyntaxKindUtils::enum_to_string_map[this->kind];
}

int SyntaxToken::getUnaryOperatorPrecedence() {
  switch (this->kind) {
  case SyntaxKindUtils::PlusToken:
  case SyntaxKindUtils::MinusToken:
    return 5;
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
