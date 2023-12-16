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
  std::vector<std::unique_ptr<BoundExpression>> _entryExpressions;
  std::string _variableName;
  std::unique_ptr<BoundExpression> _containerSizeExpression;

public:
  BoundContainerStatement(const DiagnosticUtils::SourceLocation &location,
                          const Utils::type &type, std::string variableName);

  /*
    Overrides
  */
  BinderKindUtils::BoundNodeKind getKind() const override;
  std::vector<BoundNode *> getChildren() override;

  /*
    Setters
  */
  void setEntryExpression(std::unique_ptr<BoundExpression> entryExpression);
  void setContainerSizeExpression(
      std::unique_ptr<BoundExpression> containerSizeExpression);

  /*
    Getters
  */
  auto getVariableNameRef() const -> const std::string &;
  auto getEntryExpressionsRef() const
      -> const std::vector<std::unique_ptr<BoundExpression>> &;
  auto getContainerTypeRef() const -> const Utils::type &;
  auto getContainerSizeExpressionRef() const
      -> const std::unique_ptr<BoundExpression> &;
};

#endif //  __BOUND_CONTAINER_STATEMENT_H__