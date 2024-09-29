#pragma once
#include "../../utils/Utils.h"
#include "../BinderKindUtils.h"
#include "../BoundExpression.h"
#include "../BoundSourceLocation/BoundSourceLocation.h"

class BoundTypeExpression : public BoundExpression {
private:
  SyntaxKindUtils::SyntaxKind _type;
  std::string _variableNameItBelongsTo = "";

public:
  BoundTypeExpression(const DiagnosticUtils::SourceLocation &location,
                      const SyntaxKindUtils::SyntaxKind &type);

  const std::type_info &getType() override;
  virtual BinderKindUtils::BoundNodeKind getKind() const override;
  virtual std::vector<BoundNode *> getChildren() override;

  inline auto setVariableNameitBelongsTo(std::string variableName) -> void {
    this->_variableNameItBelongsTo = variableName;
  }

  inline auto getSyntaxType() const -> const SyntaxKindUtils::SyntaxKind & {
    return _type;
  }

  inline auto getVariableNameItBelongsTo() -> std::string {
    return _variableNameItBelongsTo;
  }
};