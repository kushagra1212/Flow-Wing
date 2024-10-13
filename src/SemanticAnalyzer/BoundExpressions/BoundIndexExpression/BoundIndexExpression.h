#ifndef __BIND_INDEX_EXPRESSION_H__
#define __BIND_INDEX_EXPRESSION_H__

#include "../BoundExpression/BoundExpression.h"
#include "../BoundLiteralExpression/BoundLiteralExpression.h"

class BoundIndexExpression : public BoundExpression {
private:
  std::unique_ptr<BoundLiteralExpression<std::any>> _boundIdentifierExpression;
  std::vector<std::unique_ptr<BoundExpression>> _boundIndexExpressions;
  std::unique_ptr<BoundExpression> _variableExpression;
  bool _isObject = false;
  bool _isSelf = false;

public:
  BoundIndexExpression(const DiagnosticUtils::SourceLocation &location,
                       std::unique_ptr<BoundLiteralExpression<std::any>>
                           boundIdentifierExpression);

  // Getters
  const std::type_info &getType() override;
  BinderKindUtils::BoundNodeKind getKind() const override;
  std::vector<BoundNode *> getChildren() override;

  std::unique_ptr<BoundLiteralExpression<std::any>> &
  getBoundIdentifierExpression();

  inline const std::vector<std::unique_ptr<BoundExpression>> &
  getBoundIndexExpressions() const {
    return this->_boundIndexExpressions;
  }

  inline auto getVariableExpression() const
      -> const std::unique_ptr<BoundExpression> & {
    return _variableExpression;
  }

  inline auto isObject() const -> const bool { return _isObject; }
  inline auto isSelf() const -> const bool { return _isSelf; }

  // Setters

  inline void addBoundIndexExpression(
      std::unique_ptr<BoundExpression> boundIndexExpression) {
    this->_boundIndexExpressions.push_back(std::move(boundIndexExpression));
  }

  inline auto
  addVariableExpression(std::unique_ptr<BoundExpression> variableExpression)
      -> void {
    _isObject = true;
    _variableExpression = std::move(variableExpression);
  }

  inline void setIsSelf(bool isSelf) { _isSelf = isSelf; }
};

#endif // __BIND_INDEX_EXPRESSION_H__