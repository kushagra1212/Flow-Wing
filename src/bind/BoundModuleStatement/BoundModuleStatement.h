#ifndef __BoundModuleStatement_H__
#define __BoundModuleStatement_H__

#include "../BoundSourceLocation/BoundSourceLocation.h"
#include "../BoundStatement/BoundStatement.h"
#include "../BoundVariableDeclaration/BoundVariableDeclaration.h"

class BoundModuleStatement : public BoundStatement, public BoundSourceLocation {

  std::unique_ptr<BoundLiteralExpression<std::any>> _moduleNameIdentifier;
  std::vector<std::unique_ptr<BoundVariableDeclaration>>
      _variableDeclarationStatements;
  std::vector<std::unique_ptr<BoundStatement>> _functionStatements;
  std::vector<std::unique_ptr<BoundStatement>> _customTypeStatements;
  std::vector<std::unique_ptr<BoundStatement>> _classStatements;

public:
  BoundModuleStatement(const DiagnosticUtils::SourceLocation &location);
  BinderKindUtils::BoundNodeKind getKind() const override;
  std::vector<BoundNode *> getChildren() override;

  inline auto addVariableStatement(
      std::unique_ptr<BoundVariableDeclaration> variableDeclarationStatement)
      -> void {
    _variableDeclarationStatements.push_back(
        std::move(variableDeclarationStatement));
  }

  inline auto addModuleNameIdentifier(
      std::unique_ptr<BoundLiteralExpression<std::any>> moduleNameIdentifier)
      -> void {
    _moduleNameIdentifier = std::move(moduleNameIdentifier);
  }

  inline auto
  addFunctionStatement(std::unique_ptr<BoundStatement> functionStatement)
      -> void {
    _functionStatements.push_back(std::move(functionStatement));
  }

  inline auto
  addCustomTypeStatement(std::unique_ptr<BoundStatement> typeStatement)
      -> void {
    _customTypeStatements.push_back(std::move(typeStatement));
  }

  inline auto addClassStatement(std::unique_ptr<BoundStatement> classStatement)
      -> void {

    _classStatements.push_back(std::move(classStatement));
  }

  inline auto getVariableDeclarationStatementsRef()
      -> std::vector<std::unique_ptr<BoundVariableDeclaration>> & {
    return _variableDeclarationStatements;
  }

  inline auto getFunctionStatementsRef()
      -> std::vector<std::unique_ptr<BoundStatement>> & {
    return _functionStatements;
  }

  inline auto getCustomTypeStatementsRef()
      -> std::vector<std::unique_ptr<BoundStatement>> & {
    return _customTypeStatements;
  }

  inline auto getModuleNameIdentifierRef()
      -> std::unique_ptr<BoundLiteralExpression<std::any>> & {
    return _moduleNameIdentifier;
  }

  inline auto getClassStatementsRef()
      -> std::vector<std::unique_ptr<BoundStatement>> & {
    return _classStatements;
  }
  inline auto getModuleName() -> std::string {
    return std::any_cast<std::string>(_moduleNameIdentifier->getValue());
  }
};

#endif