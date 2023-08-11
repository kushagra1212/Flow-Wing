#include "Utils.h"

void Utils::prettyPrint(SyntaxNode *node, std::string indent, bool isLast) {
  if (!node) {
    // std::cout << "null\n";
    return;
  }
  std::cout << indent;
  if (isLast) {
    std::cout << RED_TEXT << "\\-" << RESET;
    indent += "  ";
  } else {
    std::cout << GREEN_TEXT << "|-" << RESET;
    indent += "| ";
  }

  std::cout << SyntaxKindUtils::to_string(node->getKind());
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

void Utils::prettyPrint(CompilationUnitSyntax *compilationUnit,
                        std::string indent, bool isLast) {
  if (!compilationUnit) {
    // std::cout << "null\n";
    return;
  }
  std::cout << indent;
  if (isLast) {
    std::cout << RED_TEXT << "\\-" << RESET;
    indent += "  ";
  } else {
    std::cout << GREEN_TEXT << "|-" << RESET;
    indent += "| ";
  }

  std::cout << SyntaxKindUtils::to_string(compilationUnit->getKind()) << '\n';
  for (int i = 0; i < compilationUnit->getMembers().size(); i++) {

    Utils::prettyPrint(
        dynamic_cast<SyntaxNode *>(compilationUnit->getMembers()[i]), indent,
        true);
  }
}

void Utils::prettyPrint(BoundNode *statement, std::string indent, bool isLast) {

  if (!statement) {
    // std::cout << "null\n";
    return;
  }

  std::cout << indent;
  if (isLast) {
    std::cout << RED_TEXT << "\\-" << RESET;
    indent += "  ";
  } else {
    std::cout << GREEN_TEXT << "|-" << RESET;
    indent += "| ";
  }

  std::cout << BinderKindUtils::to_string(statement->getKind()) << '\n';
  for (int i = 0; i < statement->getChildren().size(); i++) {

    Utils::prettyPrint(statement->getChildren()[i], indent,
                       i == statement->getChildren().size() - 1);
  }
}

std::string Utils::getLineNumberAndPosition(SyntaxToken<std::any> *token) {
  return "line " + std::to_string(token->getLineNumber() + 1) + ":" +
         std::to_string(token->getPosition() + 1) + " ";
}

std::string Utils::convertAnyToString(std::any value) {
  if (value.type() == typeid(std::string)) {
    return std::any_cast<std::string>(value);
  } else if (value.type() == typeid(int)) {
    return std::to_string(std::any_cast<int>(value));
  } else if (value.type() == typeid(double)) {
    return std::to_string(std::any_cast<double>(value));
  } else if (value.type() == typeid(float)) {
    return std::to_string(std::any_cast<float>(value));
  } else if (value.type() == typeid(bool)) {
    return std::to_string(std::any_cast<bool>(value));
  } else if (value.type() == typeid(std::nullptr_t)) {
    return "nullptr"; // Handle nullptr case explicitly
  } else {
    throw std::runtime_error("Unknown type");
  }
}

std::string Utils::getTypeString(const std::any &value) {
  if (value.type() == typeid(int)) {
    return "int";
  } else if (value.type() == typeid(double)) {
    return "double";
  } else if (value.type() == typeid(std::string)) {
    return "std::string";
  } else {
    return "unknown";
  }
}

void Utils::printErrors(const std::vector<std::string> &errors,
                        std::ostream &outputStream, bool isWarning) {
  for (const std::string &error : errors) {
    if (isWarning)
      outputStream << YELLOW << error << RESET << "\n";
    else
      outputStream << RED << error << RESET << "\n";
  }
}