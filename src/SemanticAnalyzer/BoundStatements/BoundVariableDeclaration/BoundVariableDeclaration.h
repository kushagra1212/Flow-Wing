#pragma once

#include "../../../Common.h"
#include "../../../syntax/expression/ExpressionSyntax.h"
#include "../../../utils/Utils.h"
#include "../../BinderKindUtils.h"
#include "../../BoundExpressions/BoundTypeExpression/BoundTypeExpression.h"
#include "../../BoundSourceLocation/BoundSourceLocation.h"
#include "../../BoundStatements/BoundStatement/BoundStatement.h"
#include "../../MemoryNode.h"
#include "llvm/IR/DerivedTypes.h"

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
  bool _hasAsKeyword = false;
  std::string _classItBelongsTo;
  BinderKindUtils::MemoryKind _memoryKind = BinderKindUtils::MemoryKind::None;
  std::pair<llvm::Value *, llvm::Type *> _llvmVariable;

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

  inline auto getTypeExpression() -> std::unique_ptr<BoundTypeExpression> & {
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

  inline auto setHasAsKeyword(bool hasAsKeyword) {
    _hasAsKeyword = hasAsKeyword;
  }

  inline auto
  setLLVMVariable(std::pair<llvm::Value *, llvm::Type *> llvmVariable) {
    _llvmVariable = (llvmVariable);
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

  inline auto getHasAsKeyword() -> bool { return _hasAsKeyword; }

  inline auto getLLVMVariable() -> std::pair<llvm::Value *, llvm::Type *> {
    return _llvmVariable;
  }

  inline auto setIsConst(bool isConst) { _isConst = isConst; }

  inline auto setIsExposed(bool isExposed) { _isExposed = isExposed; }
};
