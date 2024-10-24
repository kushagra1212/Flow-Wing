#ifndef BRING_STATEMENT_SYNTAX_H
#define BRING_STATEMENT_SYNTAX_H

#include "../../../diagnostics/DiagnosticHandler/DiagnosticHandler.h"
#include "../../SyntaxToken.h"
#include "../../statements/StatementSyntax.h"

class BringStatementSyntax : public StatementSyntax {
  std::vector<std::unique_ptr<LiteralExpressionSyntax<std::any>>> expressions;
  std::unique_ptr<FlowWing::DiagnosticHandler> diagnosticHandler;
  std::unique_ptr<SyntaxToken<std::any>> _openBraceToken;
  std::unique_ptr<SyntaxToken<std::any>> _pathToken;
  std::string absoluteFilePath;
  std::string relativeFilePath;
  std::unique_ptr<SyntaxToken<std::any>> _bringKeyword;
  std::unique_ptr<CompilationUnitSyntax> _compilationUnit;
  bool _isModuleImport = false;
  std::string _moduleName = "";

public:
  void
  addExpression(std::unique_ptr<LiteralExpressionSyntax<std::any>> expression);
  void addBringKeyword(std::unique_ptr<SyntaxToken<std::any>> bringKeyword);

  void addOpenBraceToken(std::unique_ptr<SyntaxToken<std::any>> openBraceToken);
  void addPathToken(std::unique_ptr<SyntaxToken<std::any>> pathToken);
  void setAbsoluteFilePath(const std::string &absoluteFilePath);
  void setDiagnosticHandler(
      std::unique_ptr<FlowWing::DiagnosticHandler> diagnosticHandler);
  void setRelativeFilePath(const std::string &relativeFilePath);
  void
  setCompilationUnit(std::unique_ptr<CompilationUnitSyntax> compilationUnit);

  const std::string &getAbsoluteFilePath() const;

  const SyntaxKindUtils::SyntaxKind getKind() const override;
  const std::vector<SyntaxNode *> &getChildren() override;
  const DiagnosticUtils::SourceLocation getSourceLocation() const override;

  const std::vector<std::unique_ptr<LiteralExpressionSyntax<std::any>>> &
  getExpressionsPtr();
  const std::unique_ptr<CompilationUnitSyntax> &getCompilationUnitPtr();

  inline auto setModuleName(const std::string &moduleName) -> void {
    _moduleName = moduleName;
  }

  const bool getIsChoosyImportPtr();
  const std::string &getAbsoluteFilePathPtr();
  std::unique_ptr<FlowWing::DiagnosticHandler> &getDiagnosticHandlerPtr();
  const std::string &getRelativeFilePathPtr();
  const std::unique_ptr<SyntaxToken<std::any>> &getBringKeywordPtr();

  const std::unique_ptr<SyntaxToken<std::any>> &getPathTokenPtr();

  inline auto setIsModuleImport(const bool &isModuleImport) -> void {
    _isModuleImport = isModuleImport;
  }

  inline auto getIsModuleImport() -> bool { return _isModuleImport; }

  inline auto getModuleName() -> std::string { return _moduleName; }
};

#endif // BRING_STATEMENT_SYNTAX_H
