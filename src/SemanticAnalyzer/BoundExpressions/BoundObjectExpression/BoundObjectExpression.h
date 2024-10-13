#ifndef __FLOW_BoundObjectExpression_H
#define __FLOW_BoundObjectExpression_H

#include "../BoundExpression/BoundExpression.h"
#include "../BoundLiteralExpression/BoundLiteralExpression.h"

class BoundObjectExpression : public BoundExpression {
  std::vector<std::pair<std::unique_ptr<BoundLiteralExpression<std::any>>,
                        std::unique_ptr<BoundExpression>>>
      _key_value_pairs;

public:
  BoundObjectExpression(const DiagnosticUtils::SourceLocation &location);

  /*
    Overrides
  */

  BinderKindUtils::BoundNodeKind getKind() const override;
  std::vector<BoundNode *> getChildren() override;
  inline virtual const std::type_info &getType() override {
    return typeid(BoundObjectExpression);
  }
  /*
    Setters
  */

  inline auto
  addKeyValuePair(std::unique_ptr<BoundLiteralExpression<std::any>> key,
                  std::unique_ptr<BoundExpression> value) -> void {
    this->_key_value_pairs.push_back(
        std::make_pair(std::move(key), std::move(value)));
  }

  /*
    Getters
  */

  inline auto getKeyValuePairs() -> const
      std::vector<std::pair<std::unique_ptr<BoundLiteralExpression<std::any>>,
                            std::unique_ptr<BoundExpression>>> & {
    return this->_key_value_pairs;
  }
};

#endif // __FLOW_BoundObjectExpression_H
