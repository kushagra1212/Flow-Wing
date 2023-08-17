#include "CompilationUnitSyntax.h"

SyntaxKindUtils::SyntaxKind CompilationUnitSyntax::getKind() {
  return SyntaxKindUtils::SyntaxKind::CompilationUnit;
}

std::vector<std::unique_ptr<MemberSyntax>> &
CompilationUnitSyntax::getMembers() {
  return this->_members;
}

std::unique_ptr<SyntaxToken<std::any>>
CompilationUnitSyntax::getEndOfFileToken() {
  return std::move(this->_endOfFileToken);
}

void CompilationUnitSyntax::addMember(std::unique_ptr<MemberSyntax> member) {
  this->_members.push_back(std::move(member));
}

void CompilationUnitSyntax::setEndOfFileToken(
    std::unique_ptr<SyntaxToken<std::any>> endOfFileToken) {
  this->_endOfFileToken = std::move(endOfFileToken);
}

std::vector<SyntaxNode *> CompilationUnitSyntax::getChildren() {
  if (this->_children.empty()) {
    // Add Children
    for (const auto &member : this->_members) {
      _children.push_back((member.get()));
    }
    _children.push_back(this->_endOfFileToken.get());
  }
  return this->_children;
}

std::unique_ptr<SyntaxToken<std::any>> &
CompilationUnitSyntax::getEndOfFileTokenPtr() {
  return this->_endOfFileToken;
}

const std::vector<std::string> &CompilationUnitSyntax::getLogs() {
  return this->_logs;
}

void CompilationUnitSyntax::addLogs(const std::vector<std::string> &logs) {
  this->_logs.insert(this->_logs.end(), logs.begin(), logs.end());
}
