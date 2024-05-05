#ifndef __FLOW_WING_CLASS_STATEMENT_SYNTAX_H
#define __FLOW_WING_CLASS_STATEMENT_SYNTAX_H
#include "../../SyntaxToken.h"
#include "../FunctionDeclarationSyntax/FunctionDeclarationSyntax.h"
#include "../StatementSyntax.h"
#include "../VariableDeclarationSyntax/VariableDeclarationSyntax.h"

class ClassStatementSyntax : public StatementSyntax {
private:
  std::unique_ptr<SyntaxToken<std::any>> _classKeyword;
  std::unique_ptr<SyntaxToken<std::any>> _classNameIdentifier;
  std::vector<std::unique_ptr<VariableDeclarationSyntax>> _classDataMembers;
  std::vector<std::unique_ptr<FunctionDeclarationSyntax>> _classMemberFunctions;
  bool _isExposed = false;

public:
  ClassStatementSyntax();
  const SyntaxKindUtils::SyntaxKind getKind() const override;
  const std::vector<SyntaxNode *> &getChildren() override;
  const DiagnosticUtils::SourceLocation getSourceLocation() const override;

  inline auto
  setClassKeyword(std::unique_ptr<SyntaxToken<std::any>> classKeyword) -> void {
    _classKeyword = std::move(classKeyword);
  }
  inline auto
  setClassNameIdentifier(std::unique_ptr<SyntaxToken<std::any>> classNameIden)
      -> void {
    _classNameIdentifier = std::move(classNameIden);
  }
  inline auto
  addClassDataMember(std::unique_ptr<VariableDeclarationSyntax> member)
      -> void {
    _classDataMembers.push_back(std::move(member));
  }

  inline auto
  addClassMemberFunction(std::unique_ptr<FunctionDeclarationSyntax> function)
      -> void {
    _classMemberFunctions.push_back(std::move(function));
  }

  inline auto setIsExposed(bool isExposed) -> void {
    this->_isExposed = isExposed;
  }

  inline auto isExposed() -> bool { return _isExposed; }

  inline auto getClassNameIdentifierRef()
      -> std::unique_ptr<SyntaxToken<std::any>> & {
    return _classNameIdentifier;
  }
  inline auto getDataMembersRef()
      -> std::vector<std::unique_ptr<VariableDeclarationSyntax>> & {
    return _classDataMembers;
  }

  inline auto getClassMemberFunctionsRef()
      -> std::vector<std::unique_ptr<FunctionDeclarationSyntax>> & {
    return _classMemberFunctions;
  }
};

#endif