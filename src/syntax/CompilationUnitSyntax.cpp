#include "CompilationUnitSyntax.h"

CompilationUnitSyntax::CompilationUnitSyntax(
    std::vector<std::shared_ptr<MemberSyntax>> members,
    std::shared_ptr<SyntaxToken<std::any>> endOfFileToken) {
  this->members = members;
  this->endOfFileToken = endOfFileToken;
}

SyntaxKindUtils::SyntaxKind CompilationUnitSyntax::getKind() {
  return SyntaxKindUtils::SyntaxKind::CompilationUnit;
}

std::vector<std::shared_ptr<MemberSyntax>> CompilationUnitSyntax::getMembers() {
  return this->members;
}

std::shared_ptr<SyntaxToken<std::any>>
CompilationUnitSyntax::getEndOfFileToken() {
  return this->endOfFileToken;
}

std::vector<std::shared_ptr<SyntaxNode>> CompilationUnitSyntax::getChildren() {
  std::vector<std::shared_ptr<SyntaxNode>> children = {};
  for (auto member : this->members) {
    children.push_back(member);
  }
  children.push_back(this->endOfFileToken);
  return children;
}
