
#ifndef SYNTAXTOKEN_H
#define SYNTAXTOKEN_H
#include "SyntaxNode.h"

template <typename T> class SyntaxToken : public SyntaxNode {
private:
  SyntaxKindUtils::SyntaxKind kind;
  std::string text;
  T value;

public:
  SyntaxToken(const std::string &absoluteFilePath, const int &lineNumber,
              const SyntaxKindUtils::SyntaxKind &kind, const int &columnNumber,
              const std::string &text, const T &value);

  const int &getColumnNumber();

  const int &getLineNumber();

  const std::string &getAbsoluteFilePath() const;

  const std::string &getText();

  const T &getValue();

  std::string getKindText();

  const int getUnaryOperatorPrecedence();

  const int getBinaryOperatorPrecedence();

  const SyntaxKindUtils::SyntaxKind getKind() const override;

  const DiagnosticUtils::SourceLocation getSourceLocation() const override;

  const std::vector<SyntaxNode *> &getChildren() override;

  inline auto setText(const std::string text) -> void { this->text = text; }
  inline auto setValue(const T &value) -> void { this->value = value; }
};

template <typename T>
SyntaxToken<T>::SyntaxToken(const std::string &absoluteFilePath,
                            const int &lineNumber,
                            const SyntaxKindUtils::SyntaxKind &kind,
                            const int &columnNumber, const std::string &text,
                            const T &value) {
  this->kind = kind;
  this->text = text;
  this->value = value;
  this->lineNumber = lineNumber;
  this->columnNumber = columnNumber;
  this->absoluteFilePath = absoluteFilePath;
}

template <typename T>
const SyntaxKindUtils::SyntaxKind SyntaxToken<T>::getKind() const {
  return this->kind;
}
template <typename T> const int &SyntaxToken<T>::getColumnNumber() {
  return this->columnNumber;
}

template <typename T> const int &SyntaxToken<T>::getLineNumber() {
  return this->lineNumber;
}

template <typename T> const std::string &SyntaxToken<T>::getText() {
  return this->text;
}

template <typename T>
const std::string &SyntaxToken<T>::getAbsoluteFilePath() const {
  return this->absoluteFilePath;
}

template <typename T> const T &SyntaxToken<T>::getValue() {
  return (this->value);
}
template <typename T> std::string SyntaxToken<T>::getKindText() {
  return SyntaxKindUtils::to_string(this->kind);
}
template <typename T> const int SyntaxToken<T>::getUnaryOperatorPrecedence() {
  switch (this->kind) {
  case SyntaxKindUtils::SyntaxKind::PlusToken:
  case SyntaxKindUtils::SyntaxKind::MinusToken:
  case SyntaxKindUtils::SyntaxKind::BangToken:
  case SyntaxKindUtils::SyntaxKind::TildeToken:
    return 10;
  default:
    return 0;
  }
}
template <typename T> const int SyntaxToken<T>::getBinaryOperatorPrecedence() {
  switch (this->kind) {
  case SyntaxKindUtils::SyntaxKind::StarToken:
  case SyntaxKindUtils::SyntaxKind::SlashSlashToken:
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
  case SyntaxKindUtils::SyntaxKind::EqualsToken:
    return 1;
  default:
    return 0;
  }
}
template <typename T>
const std::vector<SyntaxNode *> &SyntaxToken<T>::getChildren() {
  return _children;
}

template <typename T>
const DiagnosticUtils::SourceLocation
SyntaxToken<T>::getSourceLocation() const {
  return DiagnosticUtils::SourceLocation(this->lineNumber, this->columnNumber,
                                         this->absoluteFilePath);
}

#endif