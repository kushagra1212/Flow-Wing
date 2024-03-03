#include "CompilationUnitSyntax.h"

const SyntaxKindUtils::SyntaxKind CompilationUnitSyntax::getKind() {
  return SyntaxKindUtils::SyntaxKind::CompilationUnit;
}

std::vector<std::unique_ptr<MemberSyntax>> &
CompilationUnitSyntax::getMembers() {
  return this->_members;
}

void CompilationUnitSyntax::addMember(std::unique_ptr<MemberSyntax> member) {
  this->_members.push_back(std::move(member));
}

void CompilationUnitSyntax::setEndOfFileToken(
    std::unique_ptr<SyntaxToken<std::any>> endOfFileToken) {
  this->_endOfFileToken = std::move(endOfFileToken);
}

const std::vector<SyntaxNode *> &CompilationUnitSyntax::getChildren() {
  if (this->_children.empty()) {
    // Add Children
    for (const auto &member : this->_members) {
      _children.push_back((SyntaxNode *)(member.get()));
    }
    _children.push_back(this->_endOfFileToken.get());
  }
  return this->_children;
}

const std::unique_ptr<SyntaxToken<std::any>> &
CompilationUnitSyntax::getEndOfFileTokenRef() {
  return this->_endOfFileToken;
}
