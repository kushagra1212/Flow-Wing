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
