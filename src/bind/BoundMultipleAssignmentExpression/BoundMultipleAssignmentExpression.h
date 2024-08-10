#ifndef __BOUND_MULTIPLE_ASSIGNMENT_EXPRESSION_H__
#define __BOUND_MULTIPLE_ASSIGNMENT_EXPRESSION_H__

#include "../BoundAssignmentExpression/BoundAssignmentExpression.h"

class BoundMultipleAssignmentExpression : public BoundExpression {
  std::vector<std::unique_ptr<BoundAssignmentExpression>> _assignmentList;

public:
  BoundMultipleAssignmentExpression(
      const DiagnosticUtils::SourceLocation &location);

  /*
    Overrides
  */

  BinderKindUtils::BoundNodeKind getKind() const override;
  std::vector<BoundNode *> getChildren() override;

  inline virtual const std::type_info &getType() override {
    return typeid(BoundMultipleAssignmentExpression);
  }
  /*
    Setters
  */

  inline auto
  addAssignment(std::unique_ptr<BoundAssignmentExpression> assignment) -> void {
    _assignmentList.push_back(std::move(assignment));
  }

  /*
    Getters
  */

  inline auto getAssignmentListRef() const
      -> const std::vector<std::unique_ptr<BoundAssignmentExpression>> & {
    return _assignmentList;
  }
};

#endif