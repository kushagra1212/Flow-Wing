#ifndef BOUNDCONTINUESTATEMENT_H
#define BOUNDCONTINUESTATEMENT_H

#include "../BoundSourceLocation/BoundSourceLocation.h"
#include "../BoundStatement/BoundStatement.h"

class BoundContinueStatement : public BoundStatement,
                               public BoundSourceLocation {

public:
  BoundContinueStatement(const DiagnosticUtils::SourceLocation &location);

public:
  BinderKindUtils::BoundNodeKind getKind() const;

  std::vector<BoundNode *> getChildren() override;
};

#endif // BOUNDCONTINUESTATEMENT_H