#include "CompilationUnitSyntax.h"

CompilationUnitSyntax::CompilationUnitSyntax(
    std::vector<std::string> &logs, std::vector<MemberSyntax *> members,
    SyntaxToken<std::any> *endOfFileToken) {
  this->members = members;
  this->endOfFileToken = endOfFileToken;
  this->logs = logs;
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
