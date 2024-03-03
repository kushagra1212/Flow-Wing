#pragma once
#include <any>
#include <iostream>
#include <typeinfo>

#include "../../utils/Utils.h"
#include "../BinderKindUtils.h"
#include "../BoundExpression.h"
#include "../BoundSourceLocation/BoundSourceLocation.h"

template <typename T>
class BoundLiteralExpression : public BoundExpression {
 private:
  T value;
  SyntaxKindUtils::SyntaxKind _syntaxKind;

 public:
  BoundLiteralExpression(const DiagnosticUtils::SourceLocation &location,
                         T value);

  BoundLiteralExpression(const DiagnosticUtils::SourceLocation &location,
                         T value, SyntaxKindUtils::SyntaxKind syntaxKind);

  const std::type_info &getType() override;

  T getValue();

  BinderKindUtils::BoundNodeKind getKind() const override;

  std::vector<BoundNode *> getChildren() override;
  SyntaxKindUtils::SyntaxKind getSyntaxKind();
};
