#ifndef GlobalStatementSyntax_H
#define GlobalStatementSyntax_H

#include "../../../Common.h"
#include "../../MemberSyntax.h"

#include "../StatementSyntax.h"
class GlobalStatementSyntax : public MemberSyntax {
private:
  std::unique_ptr<StatementSyntax> _statement;

public:
  GlobalStatementSyntax(std::unique_ptr<StatementSyntax> statement);

  std::unique_ptr<StatementSyntax> getStatement();

  SyntaxKindUtils::SyntaxKind getKind() const override;

  std::vector<SyntaxNode *> getChildren() override;

  std::string getLineNumberAndColumn() override;

  std::unique_ptr<StatementSyntax> &getStatementPtr();
};

#endif // GlobalStatementSyntax_H