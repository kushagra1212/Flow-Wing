#pragma once

#include "../../SyntaxToken.h"
#include "../../expression/ExpressionSyntax.h"
#include "../CaseStatementSyntax/CaseStatementSyntax.h"
#include "../StatementSyntax.h"
#include <memory>

class SwitchStatementSyntax : public StatementSyntax {
  std::unique_ptr<SyntaxToken<std::any>> _switchToken;
  std::unique_ptr<ExpressionSyntax> _switchExpression;
  std::unique_ptr<SyntaxToken<std::any>> _openCurlyToken;
  std::vector<std::unique_ptr<CaseStatementSyntax>> _caseStatements;
  std::unique_ptr<SyntaxToken<std::any>> _closeCurlyToken;

public:
  /*
    Overrides
  */

  const std::vector<SyntaxNode *> &getChildren() override;
  const SyntaxKindUtils::SyntaxKind getKind() const override;
  const DiagnosticUtils::SourceLocation getSourceLocation() const override;

  /*
    Setters
  */

  inline auto
  setSwitchToken(std::unique_ptr<SyntaxToken<std::any>> switchToken) {
    _switchToken = std::move(switchToken);
  }

  inline auto
  setSwitchExpression(std::unique_ptr<ExpressionSyntax> switchExpression) {
    _switchExpression = std::move(switchExpression);
  }

  inline auto
  setOpenCurlyToken(std::unique_ptr<SyntaxToken<std::any>> openCurlyToken) {
    _openCurlyToken = std::move(openCurlyToken);
  }

  inline auto
  addCaseStatement(std::unique_ptr<CaseStatementSyntax> caseStatement) {
    _caseStatements.emplace_back(std::move(caseStatement));
  }

  inline auto
  setCloseCurlyToken(std::unique_ptr<SyntaxToken<std::any>> closeCurlyToken) {
    _closeCurlyToken = std::move(closeCurlyToken);
  }

  /*
    Getters
  */

  inline auto getSwitchExpressionRef() const
      -> const std::unique_ptr<ExpressionSyntax> & {
    return _switchExpression;
  }

  inline auto getCaseStatementsRef() const
      -> const std::vector<std::unique_ptr<CaseStatementSyntax>> & {
    return _caseStatements;
  }
};
