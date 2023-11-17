#ifndef __BOUND_CONTAINER_STATEMENT_H__
#define __BOUND_CONTAINER_STATEMENT_H__
#include "../../utils/Utils.h"
#include "../BinderKindUtils.h"
#include "../BoundExpression.h"
#include "../BoundLiteralExpression/BoundLiteralExpression.h"
#include "../BoundNode.h"
#include "../BoundSourceLocation/BoundSourceLocation.h"

class BoundContainerStatement : public BoundStatement,
                                public BoundSourceLocation {
private:
  Utils::type _type;
  std::unique_ptr<BoundLiteralExpression<std::any>> _identifierExpression;
  std::vector<std::unique_ptr<BoundExpression>> _entryExpressions;

public:
  BoundContainerStatement(
      const DiagnosticUtils::SourceLocation &location, Utils::type type,
      std::unique_ptr<BoundLiteralExpression<std::any>> identifierExpression);

  BinderKindUtils::BoundNodeKind getKind() const override;

  std::vector<BoundNode *> getChildren() override;

  void addEntryExpression(std::unique_ptr<BoundExpression> entryExpression);

  std::unique_ptr<BoundLiteralExpression<std::any>> &getIdentifierExpression();
  std::vector<std::unique_ptr<BoundExpression>> &getEntryExpressions();
  Utils::type getContainerType() const;
};

#endif //  __BOUND_CONTAINER_STATEMENT_H__