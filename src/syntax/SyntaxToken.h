
#ifndef SYNTAXTOKEN_H
#define SYNTAXTOKEN_H
#include "SyntaxNode.h"

template <typename T> class SyntaxToken : public SyntaxNode {
private:
  SyntaxKindUtils::SyntaxKind kind;
  std::string text;
  T value;

public:
  SyntaxToken(const std::string absoluteFilePath, int lineNumber,
              SyntaxKindUtils::SyntaxKind kind, int columnNumber,
              std::string text, T value);

  int getColumnNumber();

  int getLineNumber();

  const std::string &getAbsoluteFilePath() const;

  std::string getText();

  T getValue();

  std::string getKindText();

  int getUnaryOperatorPrecedence();

  int getBinaryOperatorPrecedence();

  SyntaxKindUtils::SyntaxKind getKind() const override;

  DiagnosticUtils::SourceLocation getSourceLocation() const override;

  std::vector<SyntaxNode *> getChildren() override;
};
#endif