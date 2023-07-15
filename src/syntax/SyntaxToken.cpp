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
  case SyntaxKindUtils::SyntaxKind::PlusToken:
  case SyntaxKindUtils::SyntaxKind::MinusToken:
  case SyntaxKindUtils::SyntaxKind::BangToken:
    return 10;
  default:
    return 0;
  }
}

int SyntaxToken::getBinaryOperatorPrecedence() {
  switch (this->kind) {
  case SyntaxKindUtils::SyntaxKind::StarToken:
  case SyntaxKindUtils::SyntaxKind::SlashToken:
  case SyntaxKindUtils::SyntaxKind::PercentToken:
    return 9;
  case SyntaxKindUtils::SyntaxKind::PlusToken:
  case SyntaxKindUtils::SyntaxKind::MinusToken:
    return 8;

  case SyntaxKindUtils::SyntaxKind::LessToken:
  case SyntaxKindUtils::SyntaxKind::LessOrEqualsToken:
  case SyntaxKindUtils::SyntaxKind::GreaterToken:
  case SyntaxKindUtils::SyntaxKind::GreaterOrEqualsToken:
    return 7;
  case SyntaxKindUtils::SyntaxKind::EqualsEqualsToken:
  case SyntaxKindUtils::SyntaxKind::BangEqualsToken:
    return 6;
  case SyntaxKindUtils::SyntaxKind::AmpersandToken:
    return 5;
  case SyntaxKindUtils::SyntaxKind::CaretToken:
    return 4;
  case SyntaxKindUtils::SyntaxKind::PipeToken:
    return 3;

  case SyntaxKindUtils::SyntaxKind::AmpersandAmpersandToken:
    return 2;
  case SyntaxKindUtils::SyntaxKind::PipePipeToken:
    return 1;
  default:
    return 0;
  }
}

std::vector<SyntaxNode *> SyntaxToken::getChildren() { return children; }
