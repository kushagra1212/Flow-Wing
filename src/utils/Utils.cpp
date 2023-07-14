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
    std::cout << " " << (((LiteralExpressionSyntax<int> *)node)->getValue());
  }
  std::cout << "\n";
  std::vector<SyntaxNode *> children = node->getChildren();
  for (int i = 0; i < children.size(); i++) {
    Utils::prettyPrint(children[i], indent, i == children.size() - 1);
  }
}
