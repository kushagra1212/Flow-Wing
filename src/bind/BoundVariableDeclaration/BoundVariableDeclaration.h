#pragma once
#include "../../Common.h"
#include "../../syntax/expression/ExpressionSyntax.h"
#include "../../utils/Utils.h"
#include "../BinderKindUtils.h"
#include "../BoundExpression.h"
#include "../BoundSourceLocation/BoundSourceLocation.h"
#include "../BoundStatement/BoundStatement.h"
#include "../BoundTypeExpression/BoundTypeExpression.h"
#include "../MemoryNode.h"
class BoundVariableDeclaration : public BoundStatement,
                                 public BoundSourceLocation,
                                 public MemoryNode {
private:
  std::string _variableName;
  std::unique_ptr<BoundExpression> _initializer;
  std::unique_ptr<BoundLiteralExpression<std::any>> _identifier;
  bool _isConst;
  std::unique_ptr<BoundTypeExpression> _typeExp;
  bool _isExposed;
  bool _hasInOutKeyword = false;
  std::string _classItBelongsTo;
  BinderKindUtils::MemoryKind _memoryKind = BinderKindUtils::MemoryKind::None;

public:
  BoundVariableDeclaration(const DiagnosticUtils::SourceLocation &location,
                           const std::string &variableName, bool isConst,
                           bool isExposed);

  BinderKindUtils::MemoryKind getMemoryKind() const override;

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

  inline auto setHasInOutKeyword(bool hasInOutKeyword) {
    _hasInOutKeyword = hasInOutKeyword;
  }

  inline auto setMemoryKind(BinderKindUtils::MemoryKind memoryKind) {
    _memoryKind = memoryKind;
  }

  inline auto setClassItBelongsTo(const std::string &classItBelongsTo) {
    _classItBelongsTo = classItBelongsTo;
  }
  inline auto
  setIdentifier(std::unique_ptr<BoundLiteralExpression<std::any>> identifier) {
    _identifier = std::move(identifier);
  }
  inline auto setTypeExpression(std::unique_ptr<BoundTypeExpression> typeExp) {
    _typeExp = std::move(typeExp);
  }

  inline auto getHasInOutKeyword() -> bool { return _hasInOutKeyword; }

  inline auto getIdentifierRef()
      -> std::unique_ptr<BoundLiteralExpression<std::any>> & {
    return _identifier;
  }

  inline auto getClassItBelongsTo() -> const std::string & {
    return _classItBelongsTo;
  }
};
