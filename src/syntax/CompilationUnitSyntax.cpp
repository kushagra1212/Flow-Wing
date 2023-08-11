#include "CompilationUnitSyntax.h"

CompilationUnitSyntax::CompilationUnitSyntax(
    std::vector<MemberSyntax *> members,
    SyntaxToken<std::any> *endOfFileToken) {
  this->members = members;
  this->endOfFileToken = endOfFileToken;
}

SyntaxKindUtils::SyntaxKind CompilationUnitSyntax::getKind() {
  return SyntaxKindUtils::SyntaxKind::CompilationUnit;
}

std::vector<MemberSyntax *> CompilationUnitSyntax::getMembers() {
  return this->members;
}

SyntaxToken<std::any> *CompilationUnitSyntax::getEndOfFileToken() {
  return this->endOfFileToken;
}

std::vector<SyntaxNode *> CompilationUnitSyntax::getChildren() {
  std::vector<SyntaxNode *> children = {};
  for (auto member : this->members) {
    children.push_back(member);
  }
  children.push_back(this->endOfFileToken);
  return children;
}

CompilationUnitSyntax::~CompilationUnitSyntax() {
  for (auto member : this->members) {
    if (member != nullptr) {
      delete member;
      member = nullptr;
    }
  }
  this->members.clear();

  if (this->endOfFileToken != nullptr) {
    delete this->endOfFileToken;
    this->endOfFileToken = nullptr;
  }
}
