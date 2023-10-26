#ifndef BRING_STATEMENT_SYNTAX_H
#define BRING_STATEMENT_SYNTAX_H

#include "../../../diagnostics/DiagnosticHandler/DiagnosticHandler.h"
#include "../../SyntaxToken.h"
#include "../../statements/StatementSyntax.h"

class BringStatementSyntax : public StatementSyntax {

  std::vector<std::unique_ptr<SyntaxToken<std::any>>> expressions;
  std::unique_ptr<DiagnosticHandler> diagnosticHandler;
  std::string absoluteFilePath;
  std::string relativeFilePath;
  std::unique_ptr<SyntaxToken<std::any>> _bringKeyword;
  std::unique_ptr<CompilationUnitSyntax> _compilationUnit;

public:
  void addExpression(std::unique_ptr<SyntaxToken<std::any>> expression);
  void addBringKeyword(std::unique_ptr<SyntaxToken<std::any>> bringKeyword);
  void setAbsoluteFilePath(const std::string &absoluteFilePath);
  void
  setDiagnosticHandler(std::unique_ptr<DiagnosticHandler> diagnosticHandler);
  void setRelativeFilePath(const std::string &relativeFilePath);
  void
  setCompilationUnit(std::unique_ptr<CompilationUnitSyntax> compilationUnit);

  const std::string &getAbsoluteFilePath() const;

  SyntaxKindUtils::SyntaxKind getKind() const override;
  std::vector<SyntaxNode *> getChildren() override;
  DiagnosticUtils::SourceLocation getSourceLocation() const override;

  const std::vector<std::unique_ptr<SyntaxToken<std::any>>> &
  getExpressionsPtr();
  const std::unique_ptr<CompilationUnitSyntax> &getCompilationUnitPtr();

  const bool getIsChoosyImportPtr();
  const std::string &getAbsoluteFilePathPtr();
  std::unique_ptr<DiagnosticHandler> &getDiagnosticHandlerPtr();
  const std::string &getRelativeFilePathPtr();
  const std::unique_ptr<SyntaxToken<std::any>> &getBringKeywordPtr();
};

#endif // BRING_STATEMENT_SYNTAX_H
