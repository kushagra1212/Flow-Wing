#pragma once
#include "../../utils/Utils.h"
#include "../BinderKindUtils.h"
#include "../BoundExpression.h"
#include "../BoundSourceLocation/BoundSourceLocation.h"

class BoundTypeExpression : public BoundExpression {
 private:
  SyntaxKindUtils::SyntaxKind _type;

 public:
  BoundTypeExpression(const DiagnosticUtils::SourceLocation &location,
                      const SyntaxKindUtils::SyntaxKind &type);

  const std::type_info &getType() override;
  virtual BinderKindUtils::BoundNodeKind getKind() const override;
  virtual std::vector<BoundNode *> getChildren() override;

  inline auto getSyntaxType() const -> const SyntaxKindUtils::SyntaxKind & {
    return _type;
  }
};