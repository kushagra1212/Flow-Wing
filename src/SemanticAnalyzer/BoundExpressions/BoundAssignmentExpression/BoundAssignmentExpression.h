#ifndef ASSIGNMENT_EXPRESSION_H
#define ASSIGNMENT_EXPRESSION_H

#include "../../BoundStatements/BoundVariableDeclaration/BoundVariableDeclaration.h"
#include "../BoundExpression/BoundExpression.h"

class BoundAssignmentExpression : public BoundExpression {
private:
  BinderKindUtils::BoundBinaryOperatorKind _op;
  std::unique_ptr<BoundExpression> _left;
  std::unique_ptr<BoundExpression> _right;
  BoundVariableDeclaration *_variable;
  bool _needDefaultInitialization;

public:
  BoundAssignmentExpression(const DiagnosticUtils::SourceLocation &location,
                            BoundVariableDeclaration *variable,
                            std::unique_ptr<BoundExpression> left,
                            BinderKindUtils::BoundBinaryOperatorKind op,
                            std::unique_ptr<BoundExpression> right,
                            bool needDefaultInitialization = false);

  BinderKindUtils::BoundBinaryOperatorKind getOperator();

  const std::type_info &getType() override;

  BinderKindUtils::BoundNodeKind getKind() const override;

  std::vector<BoundNode *> getChildren() override;

  std::unique_ptr<BoundExpression> &getLeftPtr();

  std::unique_ptr<BoundExpression> &getRightPtr();

  BoundVariableDeclaration *getVariable();

  inline bool getNeedDefaultInitialization() {
    return _needDefaultInitialization;
  }
};

#endif // ASSIGNMENT_EXPRESSION_H