#ifndef __MULTIPLE_ASSIGNMENT_EXPRESSION_SYNTAX_H__
#define __MULTIPLE_ASSIGNMENT_EXPRESSION_SYNTAX_H__

#include "../AssignmentExpressionSyntax.h"
#include "../ExpressionSyntax.h"

class MultipleAssignmentExpressionSyntax : public ExpressionSyntax {
  std::vector<std::unique_ptr<AssignmentExpressionSyntax>> _assignmentExprList;

public:
  MultipleAssignmentExpressionSyntax();
  /*
    MultipleAssignmentExpressionSyntax
  */
  const SyntaxKindUtils::SyntaxKind getKind() const override;
  const std::vector<SyntaxNode *> &getChildren() override;
  const DiagnosticUtils::SourceLocation getSourceLocation() const override;

  /*
    Setters
  */

  inline auto addAssignmentExpression(
      std::unique_ptr<AssignmentExpressionSyntax> assignmentExpr) -> void {
    _assignmentExprList.push_back(std::move(assignmentExpr));
  }

  /*
    Getters
  */

  inline auto getAssignmentExprListRef() const
      -> const std::vector<std::unique_ptr<AssignmentExpressionSyntax>> & {
    return _assignmentExprList;
  }
};

#endif