#ifndef __FLOW_WING_BOUND_CLASS_STATEMENT__
#define __FLOW_WING_BOUND_CLASS_STATEMENT__

#include "../../syntax/CompilationUnitSyntax.h"
#include "../Binder/BoundScopeGlobal/BoundScopeGlobal.h"
#include "../BoundSourceLocation/BoundSourceLocation.h"
#include "../BoundStatement/BoundStatement.h"

class BoundClassStatement : public BoundStatement, public BoundSourceLocation {
  std::string _className;
  std::string _parentClassName;
  BoundClassStatement *_parentClass = nullptr;
  std::vector<std::unique_ptr<BoundVariableDeclaration>> _memberVariables;

  std::vector<BoundVariableDeclaration *> _allMemberVariables;

  std::vector<std::string> _allFunctionNames;
  std::unordered_map<std::string, uint64_t> _allFunctionNamesMap;

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

  inline auto setParentClassName(std::string parentClassName) -> void {
    _parentClassName = parentClassName;
  }

  inline auto setParentClass(BoundClassStatement *parentClass) -> void {
    _parentClass = parentClass;
  }

  inline auto addMemberVariable(std::unique_ptr<BoundVariableDeclaration> var)
      -> void {
    _memberVariables.push_back(std::move(var));
  }

  inline auto addMemberVariablePtr(BoundVariableDeclaration *var) -> void {

    for (auto &v : _allMemberVariables) {
      if (v->getVariableName() == var->getVariableName()) {
        v = var;
        return;
      }
    }

    _allMemberVariables.push_back(var);
  }

  inline auto addFunctionName(std::string name) -> void {

    for (auto &v : _allFunctionNames) {
      if (v == name) {
        return;
      }
    }
    _allFunctionNamesMap[name] = _allFunctionNames.size();
    _allFunctionNames.push_back(name);
  }

  inline auto hasFunctionName(std::string name) -> bool {
    return _allFunctionNamesMap.find(name) != _allFunctionNamesMap.end();
  }

  inline auto addCustomType(std::unique_ptr<BoundStatement> type) -> void {

    _customTypes.push_back(std::move(type));
  }

  inline auto addMemberFunction(std::unique_ptr<BoundStatement> fun) -> void {
    _memberFunctions.push_back(std::move(fun));
  }

  inline auto addKeyTypePair(BoundLiteralExpression<std::any> *key,
                             BoundTypeExpression *type) -> void {

    for (auto &v : _key_type_pairs) {
      if (v.first == key) {
        v.second = type;
        return;
      }
    }

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

  inline auto getAllFunctionNamesRef() -> std::vector<std::string> & {
    return _allFunctionNames;
  }

  inline auto getParentClass() -> BoundClassStatement * { return _parentClass; }

  inline auto getAllMemberVariablesRef()
      -> std::vector<BoundVariableDeclaration *> & {
    return _allMemberVariables;
  }

  inline auto tryGetCustomLocalType(std::string typeName)
      -> BoundCustomTypeStatement * {
    for (auto &v : _customTypes) {
      BoundCustomTypeStatement *customType =
          dynamic_cast<BoundCustomTypeStatement *>(v.get());

      if (customType->getTypeNameAsString().substr(
              0, customType->getTypeNameAsString().find(".")) == typeName) {
        return customType;
      }
    }
    return nullptr;
  }

  inline auto tryGetCustomType(std::string typeName)
      -> BoundCustomTypeStatement * {

    auto type = this->tryGetCustomLocalType(typeName);
    if (type) {
      return type;
    }

    if (this->_parentClass) {

      return this->_parentClass->tryGetCustomType(typeName);
    }

    return nullptr;
  }

  inline auto getMemberFunctionsRef()
      -> std::vector<std::unique_ptr<BoundStatement>> & {
    return _memberFunctions;
  }

  inline auto getKeyPairsRef() -> std::vector<
      std::pair<BoundLiteralExpression<std::any> *, BoundTypeExpression *>> & {
    return _key_type_pairs;
  }

  inline auto getParentClassName() -> std::string { return _parentClassName; }

  inline auto getInitializerMemberFunction() -> BoundFunctionDeclaration * {
    for (auto &fun : _memberFunctions) {
      BoundFunctionDeclaration *fd =
          static_cast<BoundFunctionDeclaration *>(fun.get());
      if (fd->getFunctionNameRef() ==
          _className + FLOWWING::UTILS::CONSTANTS::MEMBER_FUN_PREFIX + "init")
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

  inline auto getActualFunctionNameIfExists(std::string functionName)
      -> std::string {

    for (auto &fun : this->getMemberFunctionsRef()) {
      BoundFunctionDeclaration *fd =
          static_cast<BoundFunctionDeclaration *>(fun.get());

      if (fd->getFunctionNameRef().substr(
              fd->getFunctionNameRef().find(
                  FLOWWING::UTILS::CONSTANTS::MEMBER_FUN_PREFIX) +
              1) == functionName) {
        return this->_className +
               FLOWWING::UTILS::CONSTANTS::MEMBER_FUN_PREFIX + functionName;
      }
    }
    if (this->_parentClass) {
      return this->_parentClass->getActualFunctionNameIfExists(functionName);
    }
    return "";
  }
};

#endif // __FLOW_WING_BOUND_CLASS_STATEMENT__
