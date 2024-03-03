
#ifndef SYNTAXTOKEN_H
#define SYNTAXTOKEN_H
#include "SyntaxNode.h"

template <typename T>
class SyntaxToken : public SyntaxNode {
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
};
#endif