#include "Utils.h"

void Utils::prettyPrint(SyntaxNode *node, std::string indent, bool isLast) {
  std::cout << indent;
  if (isLast) {
    std::cout << "\\-";
    indent += "  ";
  } else {
    std::cout << "|-";
    indent += "| ";
  }
  std::cout << SyntaxKindUtils::enum_to_string_map[node->getKind()];
  if (node->getKind() == SyntaxKindUtils::LiteralExpression) {

    std::any value = ((LiteralExpressionSyntax<std::any> *)node)->getValue();
    if (value.type() == typeid(int)) {
      std::cout << " " << std::any_cast<int>(value);
    } else if (value.type() == typeid(bool)) {
      std::cout << " " << std::any_cast<bool>(value);
    } else if (value.type() == typeid(std::string)) {
      std::cout << " " << std::any_cast<std::string>(value);
    } else {
      std::cout << " " << std::any_cast<double>(value);
    }
  }
  std::cout << "\n";
  std::vector<SyntaxNode *> children = node->getChildren();
  for (int i = 0; i < children.size(); i++) {
    Utils::prettyPrint(children[i], indent, i == children.size() - 1);
  }
}

std::string Utils::getLineNumberAndPosition(SyntaxToken<std::any> *token) {
  return "line " + std::to_string(token->getLineNumber() + 1) + ":" +
         std::to_string(token->getPosition() + 1) + " ";
}

Utils::Variable::Variable(std::any value, bool isConst) {

  this->value = value;
  this->isConst = isConst;
}
