#ifndef __BOUND_CONTAINER_STATEMENT_H__
#define __BOUND_CONTAINER_STATEMENT_H__
#include "../../utils/Utils.h"
#include "../BinderKindUtils.h"
#include "../BoundContainerExpression/BoundContainerExpression.h"
#include "../BoundExpression.h"
#include "../BoundLiteralExpression/BoundLiteralExpression.h"
#include "../BoundNode.h"
#include "../BoundSourceLocation/BoundSourceLocation.h"
class BoundContainerStatement : public BoundStatement,
                                public BoundSourceLocation {
private:
  Utils::type _type;
  std::string _variableName;
  std::unique_ptr<BoundExpression> _containerSizeExpression;
  std::unique_ptr<BoundExpression> _containerExpression;

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
  void setContainerSizeExpression(
      std::unique_ptr<BoundExpression> containerSizeExpression);

  void
  setBracketedExpression(std::unique_ptr<BoundExpression> containerExpression);

  /*
    Getters
  */
  auto getVariableNameRef() const -> const std::string &;
  auto getContainerTypeRef() const -> const Utils::type &;
  auto getBracketedExpressionRef() const
      -> const std::unique_ptr<BoundExpression> &;
  auto getContainerSizeExpressionRef() const
      -> const std::unique_ptr<BoundExpression> &;
};

#endif //  __BOUND_CONTAINER_STATEMENT_H__