#ifndef GlobalStatementSyntax_H
#define GlobalStatementSyntax_H

#include "../../../Common.h"
#include "../../MemberSyntax.h"

#include "../StatementSyntax.h"
class GlobalStatementSyntax : public MemberSyntax {
private:
  std::shared_ptr<StatementSyntax> _statement;

public:
  GlobalStatementSyntax(std::shared_ptr<StatementSyntax> statement);

  std::shared_ptr<StatementSyntax> getStatement() const;

  SyntaxKindUtils::SyntaxKind getKind() override;

  std::vector<std::shared_ptr<SyntaxNode>> getChildren() override;

  std::string getLineNumberAndColumn() const override;
};

#endif // GlobalStatementSyntax_H