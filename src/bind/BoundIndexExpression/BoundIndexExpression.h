#ifndef __BIND_INDEX_EXPRESSION_H__
#define __BIND_INDEX_EXPRESSION_H__

#include "../BinderKindUtils.h"
#include "../BoundExpression.h"
#include "../BoundLiteralExpression/BoundLiteralExpression.h"
#include "../BoundSourceLocation/BoundSourceLocation.h"
class BoundIndexExpression : public BoundExpression {
 private:
  std::unique_ptr<BoundLiteralExpression<std::any>> _boundIdentifierExpression;
  std::vector<std::unique_ptr<BoundExpression>> _boundIndexExpressions;

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

  // Setters

  inline void addBoundIndexExpression(
      std::unique_ptr<BoundExpression> boundIndexExpression) {
    this->_boundIndexExpressions.push_back(std::move(boundIndexExpression));
  }
};

#endif  // __BIND_INDEX_EXPRESSION_H__