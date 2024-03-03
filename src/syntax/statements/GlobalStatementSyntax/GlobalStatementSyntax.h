#ifndef GlobalStatementSyntax_H
#define GlobalStatementSyntax_H

#include "../../../Common.h"
#include "../../MemberSyntax.h"
#include "../StatementSyntax.h"
class GlobalStatementSyntax : public MemberSyntax {
 private:
  std::unique_ptr<StatementSyntax> _statement;

 public:
  GlobalStatementSyntax(const bool &isExposed,
                        std::unique_ptr<StatementSyntax> statement);

  std::unique_ptr<StatementSyntax> getStatement();

  const SyntaxKindUtils::SyntaxKind getKind() const override;
  const std::vector<SyntaxNode *> &getChildren() override;
  const DiagnosticUtils::SourceLocation getSourceLocation() const override;

  std::unique_ptr<StatementSyntax> &getStatementPtr();
};

#endif  // GlobalStatementSyntax_H