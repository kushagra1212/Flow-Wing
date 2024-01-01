#pragma once
#include "../../utils/Utils.h"
#include "../BinderKindUtils.h"
#include "../BoundExpression.h"
#include "../BoundSourceLocation/BoundSourceLocation.h"

class BoundTypeExpression : public BoundExpression {
private:
  Utils::type _type;

public:
  BoundTypeExpression(const DiagnosticUtils::SourceLocation &location,
                      Utils::type type);

  const std::type_info &getType() override;
  virtual BinderKindUtils::BoundNodeKind getKind() const;
  virtual std::vector<BoundNode *> getChildren() override;

  inline auto getUtilsType() const -> const Utils::type & { return _type; }
};