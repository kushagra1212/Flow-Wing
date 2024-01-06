#ifndef __FLOW_BOUNDCUSTOMTYPESTATEMENT_H
#define __FLOW_BOUNDCUSTOMTYPESTATEMENT_H

#include "../BoundLiteralExpression/BoundLiteralExpression.h"
#include "../BoundSourceLocation/BoundSourceLocation.h"
#include "../BoundStatement/BoundStatement.h"
#include "../BoundTypeExpression/BoundTypeExpression.h"

class BoundCustomTypeStatement : public BoundStatement,
                                 public BoundSourceLocation {
  std::unique_ptr<BoundLiteralExpression<std::any>> _typeName;
  std::vector<std::pair<std::unique_ptr<BoundLiteralExpression<std::any>>,
                        std::unique_ptr<BoundTypeExpression>>>
      _key_type_pairs;

public:
  BoundCustomTypeStatement(const DiagnosticUtils::SourceLocation &location);

  /*
    Setters
  */

  inline auto
  setTypeName(std::unique_ptr<BoundLiteralExpression<std::any>> typeName)
      -> void {
    this->_typeName = std::move(typeName);
  }

  inline auto
  addKeyTypePair(std::unique_ptr<BoundLiteralExpression<std::any>> key,
                 std::unique_ptr<BoundTypeExpression> type) -> void {
    this->_key_type_pairs.push_back(
        std::make_pair(std::move(key), std::move(type)));
  }

  /*
    Getters
  */

  inline auto getTypeName()
      -> const std::unique_ptr<BoundLiteralExpression<std::any>> & {
    return this->_typeName;
  }
  inline auto getTypeNameAsString() -> const std::string {
    return std::any_cast<std::string>(this->_typeName->getValue());
  }

  inline auto getKeyPairs() -> const
      std::vector<std::pair<std::unique_ptr<BoundLiteralExpression<std::any>>,
                            std::unique_ptr<BoundTypeExpression>>> & {
    return this->_key_type_pairs;
  }

public:
  BinderKindUtils::BoundNodeKind getKind() const override;
  std::vector<BoundNode *> getChildren() override;
};

#endif // __FLOW_BOUNDCUSTOMTYPESTATEMENT_H
