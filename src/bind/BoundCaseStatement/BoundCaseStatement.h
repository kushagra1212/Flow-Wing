#pragma once

#include "../BoundBlockStatement/BoundBlockStatement.h"
#include "../BoundExpression.h"
#include "../BoundSourceLocation/BoundSourceLocation.h"
#include "../BoundStatement/BoundStatement.h"

class BoundCaseStatement : public BoundStatement, public BoundSourceLocation {
  bool _isDefaultCase = false;
  std::unique_ptr<BoundExpression> _caseExpression;
  std::unique_ptr<BoundStatement> _bodyStatement;

public:
  BoundCaseStatement(const DiagnosticUtils::SourceLocation &location);

  /*
    Overrides
  */
  BinderKindUtils::BoundNodeKind getKind() const override;
  std::vector<BoundNode *> getChildren() override;

  /*
    Setters
  */
  inline auto setIsDefaultCase(const bool &isDefaultCase) -> void {
    this->_isDefaultCase = isDefaultCase;
  }
  inline auto setCaseExpression(std::unique_ptr<BoundExpression> caseExpression)
      -> void {
    this->_caseExpression = std::move(caseExpression);
  }
  inline auto setBodyStatement(std::unique_ptr<BoundStatement> bodyStatement)
      -> void {
    this->_bodyStatement = std::move(bodyStatement);
  }

  /*
    Getters
  */

  inline auto getIsDefaultCase() const -> const bool & {
    return this->_isDefaultCase;
  }
  inline auto getCaseExpressionRef() const
      -> const std::unique_ptr<BoundExpression> & {
    return this->_caseExpression;
  }
  inline auto getBodyStatementRef() const
      -> const std::unique_ptr<BoundStatement> & {
    return this->_bodyStatement;
  }
};
