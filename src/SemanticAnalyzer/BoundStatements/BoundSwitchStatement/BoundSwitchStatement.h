#pragma once

#include "../../BoundExpressions/BoundExpression/BoundExpression.h"
#include "../../BoundSourceLocation/BoundSourceLocation.h"
#include "../../BoundStatements/BoundBlockStatement/BoundBlockStatement.h"
#include "../../BoundStatements/BoundCaseStatement/BoundCaseStatement.h"
#include "../../BoundStatements/BoundStatement/BoundStatement.h"
#include <memory>
#include <vector>

class BoundSwitchStatement : public BoundStatement, public BoundSourceLocation {
  std::unique_ptr<BoundExpression> _switchExpression;
  std::vector<std::unique_ptr<BoundCaseStatement>> _boundCaseStatements;
  std::unique_ptr<BoundCaseStatement> _defaultCaseStatement;
  uint64_t _defaultCasesCount = 0;

public:
  BoundSwitchStatement(const DiagnosticUtils::SourceLocation &location);

  /*
    Overrides
  */
  BinderKindUtils::BoundNodeKind getKind() const override;
  std::vector<BoundNode *> getChildren() override;

  /*
    Setters
  */
  inline auto
  setSwitchExpression(std::unique_ptr<BoundExpression> switchExpression)
      -> void {
    this->_switchExpression = std::move(switchExpression);
  }

  inline auto
  addCaseStatement(std::unique_ptr<BoundCaseStatement> boundCaseStatement)
      -> void {

    if (boundCaseStatement->getIsDefaultCase()) {
      this->_defaultCasesCount++;
      _defaultCaseStatement = std::move(boundCaseStatement);
      return;
    }

    this->_boundCaseStatements.emplace_back(std::move(boundCaseStatement));
  }

  /*
    Getters
  */

  inline auto getSwitchExpressionRef() const
      -> const std::unique_ptr<BoundExpression> & {
    return this->_switchExpression;
  }

  inline auto getCaseStatementsRef() const
      -> const std::vector<std::unique_ptr<BoundCaseStatement>> & {
    return this->_boundCaseStatements;
  }

  inline auto getHasNoDefaultCase() const -> bool {
    return this->_defaultCasesCount == 0;
  }

  inline auto getHasMoreThanOneDefaultCase() const -> bool {
    return this->_defaultCasesCount > 1;
  }

  inline auto getDefaultCaseStatementRef() const
      -> const std::unique_ptr<BoundCaseStatement> & {
    return this->_defaultCaseStatement;
  }

  inline auto getHasAtLeastOneCaseStatement() const -> bool {
    return this->_boundCaseStatements.size() > 0;
  }
};
