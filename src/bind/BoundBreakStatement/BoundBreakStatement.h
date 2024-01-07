#ifndef BOUDBREAKSTATEMENT_H
#define BOUDBREAKSTATEMENT_H

#include "../BoundSourceLocation/BoundSourceLocation.h"
#include "../BoundStatement/BoundStatement.h"

class BoundBreakStatement : public BoundStatement, public BoundSourceLocation {
 public:
  BoundBreakStatement(const DiagnosticUtils::SourceLocation &location);

  BinderKindUtils::BoundNodeKind getKind() const;

  std::vector<BoundNode *> getChildren() override;
};

#endif  // BOUDBREAKSTATEMENT_H