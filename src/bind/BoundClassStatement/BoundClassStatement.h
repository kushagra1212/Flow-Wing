#ifndef __FLOW_WING_BOUND_CLASS_STATEMENT__
#define __FLOW_WING_BOUND_CLASS_STATEMENT__

#include "../../syntax/CompilationUnitSyntax.h"
#include "../Binder/BoundScopeGlobal/BoundScopeGlobal.h"
#include "../BoundSourceLocation/BoundSourceLocation.h"
#include "../BoundStatement/BoundStatement.h"

class BoundClassStatement : public BoundStatement, public BoundSourceLocation {
  std::string _className;
  std::vector<std::unique_ptr<BoundVariableDeclaration>> _memberVariables;
  std::vector<std::unique_ptr<BoundStatement>> _memberFunctions;
  std::vector<std::unique_ptr<BoundStatement>> _customTypes;
  std::vector<
      std::pair<BoundLiteralExpression<std::any> *, BoundTypeExpression *>>
      _key_type_pairs;

public:
  BoundClassStatement(const DiagnosticUtils::SourceLocation &location);

  BinderKindUtils::BoundNodeKind getKind() const override;
  std::vector<BoundNode *> getChildren() override;

  inline auto setClassName(std::string className) -> void {
    _className = className;
  }
  inline auto addMemberVariable(std::unique_ptr<BoundVariableDeclaration> var)
      -> void {
    _memberVariables.push_back(std::move(var));
  }

  inline auto addCustomType(std::unique_ptr<BoundStatement> type) -> void {
    _customTypes.push_back(std::move(type));
  }

  inline auto addMemberFunction(std::unique_ptr<BoundStatement> fun) -> void {
    _memberFunctions.push_back(std::move(fun));
  }

  inline auto addKeyTypePair(BoundLiteralExpression<std::any> *key,
                             BoundTypeExpression *type) -> void {
    _key_type_pairs.push_back(std::make_pair(key, type));
  }
  inline auto getCustomTypesRef()
      -> std::vector<std::unique_ptr<BoundStatement>> & {
    return _customTypes;
  }
  inline auto getClassName() -> std::string { return _className; }

  inline auto getMemberVariablesRef()
      -> std::vector<std::unique_ptr<BoundVariableDeclaration>> & {
    return _memberVariables;
  }

  inline auto getMemberFunctionsRef()
      -> std::vector<std::unique_ptr<BoundStatement>> & {
    return _memberFunctions;
  }

  inline auto getKeyPairsRef() -> std::vector<
      std::pair<BoundLiteralExpression<std::any> *, BoundTypeExpression *>> & {
    return _key_type_pairs;
  }

  inline auto getInitializerMemberFunction() -> BoundFunctionDeclaration * {
    for (auto &fun : _memberFunctions) {
      BoundFunctionDeclaration *fd =
          static_cast<BoundFunctionDeclaration *>(fun.get());
      if (fd->getFunctionNameRef() == _className + "_:" + "init")
        return fd;
    }
    return nullptr;
  }

  inline auto getMemberFunction(std::string functionName)
      -> BoundFunctionDeclaration * {
    for (auto &fun : _memberFunctions) {
      BoundFunctionDeclaration *fd =
          static_cast<BoundFunctionDeclaration *>(fun.get());
      if (fd->getFunctionNameRef() == functionName)
        return fd;
    }
    return nullptr;
  }
};

#endif // __FLOW_WING_BOUND_CLASS_STATEMENT__
