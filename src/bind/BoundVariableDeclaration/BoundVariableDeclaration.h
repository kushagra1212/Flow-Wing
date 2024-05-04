#pragma once
#include "../../Common.h"
#include "../../syntax/expression/ExpressionSyntax.h"
#include "../../utils/Utils.h"
#include "../BinderKindUtils.h"
#include "../BoundExpression.h"
#include "../BoundSourceLocation/BoundSourceLocation.h"
#include "../BoundStatement/BoundStatement.h"
#include "../BoundTypeExpression/BoundTypeExpression.h"

class BoundVariableDeclaration : public BoundStatement,
                                 public BoundSourceLocation {
private:
  std::string _variableName;
  std::unique_ptr<BoundExpression> _initializer;
  bool _isConst;
  std::unique_ptr<BoundTypeExpression> _typeExp;
  bool _isExposed;
  bool _hasNewKeyword;

public:
  BoundVariableDeclaration(const DiagnosticUtils::SourceLocation &location,
                           const std::string &variableName, bool isConst,
                           bool isExposed);

  std::unique_ptr<BoundExpression> getInitializer();

  std::vector<BoundNode *> getChildren() override;

  BinderKindUtils::BoundNodeKind getKind() const override;

  bool isConst() const;

  std::unique_ptr<BoundExpression> &getInitializerPtr();

  const std::string &getVariableName() const;

  inline auto getTypeExpression() const
      -> const std::unique_ptr<BoundTypeExpression> & {
    return _typeExp;
  }

  inline auto isExposed() const -> bool { return _isExposed; }

  // Setters
  inline auto setInitializer(std::unique_ptr<BoundExpression> initializer)
      -> void {
    _initializer = std::move(initializer);
  }

  inline auto setTypeExpression(std::unique_ptr<BoundTypeExpression> typeExp) {
    _typeExp = std::move(typeExp);
  }

  inline auto setHasNewKeyword(bool hasNewKeyword) {
    _hasNewKeyword = hasNewKeyword;
  }

  inline auto getHasNewKeyword() -> bool { return _hasNewKeyword; }
};
