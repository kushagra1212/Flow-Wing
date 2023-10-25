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

    std::cout << " "
              << InterpreterConversion::explicitConvertAnyToString(value);
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
  for (int i = 0; i < compilationUnit->getChildren().size(); i++) {

    Utils::prettyPrint(compilationUnit->getChildren()[i], indent, true);
  }
}

void Utils::prettyPrint(BoundNode *node, std::string indent, bool isLast) {
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

  std::cout << BinderKindUtils::to_string(node->getKind());
  if (node->getKind() == BinderKindUtils::LiteralExpression) {

    std::any value = ((BoundLiteralExpression<std::any> *)node)->getValue();

    std::cout << " "
              << InterpreterConversion::explicitConvertAnyToString(value);
  }
  std::cout << "\n";
  std::vector<BoundNode *> children = node->getChildren();
  for (int i = 0; i < children.size(); i++) {
    Utils::prettyPrint(children[i], indent, i == children.size() - 1);
  }
}

void Utils::prettyPrint(BoundStatement *statement, std::string indent,
                        bool isLast) {

  if (!statement) {
    std::cout << "null\n";
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

std::string Utils::getSourceCode(SyntaxNode *node, bool include) {
  if (!node) {
    // std::cout << "null\n";
    return "";
  }
  std::string code = "";

  if (node->getKind() == SyntaxKindUtils::SyntaxKind::EndOfFileToken ||
      node->getKind() == SyntaxKindUtils::SyntaxKind::EndOfLineToken) {
    return code;
  }

  if (!include &&
      (node->getKind() == SyntaxKindUtils::SyntaxKind::CommentStatement)) {
    return code;
  }

  if (isSyntaxToken(node)) {

    if (node->getKind() != SyntaxKindUtils::SyntaxKind::StringToken)
      code += ((SyntaxToken<std::any> *)node)->getText() + " ";
    else
      code += "\"" + ((SyntaxToken<std::any> *)node)->getText() + "\" ";
  }
  std::vector<SyntaxNode *> children = node->getChildren();
  for (int i = 0; i < children.size(); i++) {

    if (children[i]) {
      bool has = include;

      has = has || (children[i]->getKind() ==
                    SyntaxKindUtils::SyntaxKind::FunctionDeclarationSyntax);

      code += Utils::getSourceCode(children[i], has);
    }
  }
  return code;
}

std::string Utils::getSourceCode(CompilationUnitSyntax *compilationUnit) {
  if (!compilationUnit) {
    return "";
  }
  std::string code = "";

  for (int i = 0; i < compilationUnit->getChildren().size(); i++) {

    if (compilationUnit->getChildren()[i])
      code += Utils::getSourceCode(
          compilationUnit->getChildren()[i],
          compilationUnit->getChildren()[i]->getKind() ==
              SyntaxKindUtils::SyntaxKind::FunctionDeclarationSyntax);
  }

  return code;
}

std::string Utils::getTypeString(const std::any &value) {
  return Utils::typeToString(Utils::getTypeFromAny(value));
}

Utils::type Utils::getTypeFromAny(const std::any &value) {
  if (value.type() == typeid(int)) {
    return Utils::type::INT32;
  } else if (value.type() == typeid(double)) {
    return Utils::type::DECIMAL;
  } else if (value.type() == typeid(std::string)) {
    return Utils::type::STRING;
  } else if (value.type() == typeid(bool)) {
    return Utils::type::BOOL;
  } else {
    return Utils::type::NOTHING;
  }
}

void Utils::printErrors(const std::vector<std::string> &errors,
                        std::ostream &outputStream, bool isWarning) {
  outputStream << "\n";
  for (const std::string &error : errors) {
    if (isWarning)
      outputStream << YELLOW << error << RESET << "\n";
    else
      outputStream << RED << error << RESET << "\n";
  }
}

const std::string Utils::concatErrors(const std::vector<std::string> &errors,
                                      std::ostream &outputStream,
                                      bool isWarning) {
  std::string res = "";

  for (const std::string &error : errors) {
    res += error + "\n";
  }
  return res;
}

std::string Utils::getAbsoluteFilePath(std::string relativeFilePath) {
  std::filesystem::path basePath = std::filesystem::current_path();

  // Create an absolute path by combining the base path and the relative path
  std::filesystem::path absolutePath = basePath / relativeFilePath;

  return absolutePath.string();
}

DiagnosticUtils::SourceLocation
Utils::getSourceLocation(SyntaxToken<std::any> *token) {
  return DiagnosticUtils::SourceLocation(token->getLineNumber(),
                                         token->getColumnNumber(),
                                         token->getAbsoluteFilePath());
}

bool Utils::isInteger(const std::string &str) {
  // Pattern for integers (optional sign followed by digits)
  std::regex intPattern("^[-+]?[0-9]+$");
  return std::regex_match(str, intPattern);
}

bool Utils::isDouble(const std::string &str) {
  // Pattern for doubles (optional sign, digits, optional decimal, optional
  // exponent)
  std::regex doublePattern("^[-+]?[0-9]*\\.?[0-9]+([eE][-+]?[0-9]+)?$");
  return std::regex_match(str, doublePattern);
}

auto Utils::typeToString(Utils::type type) -> std::string {
  switch (type) {
  case Utils::type::INT32:
    return "Integer";
  case Utils::type::DECIMAL:
    return "Decimal";
  case Utils::type::STRING:
    return "String";
  case Utils::type::BOOL:
    return "Boolean";
  case Utils::type::NOTHING:
    return "Nothing";
  default:
    break;
  }

  return "Unknown";
}

auto Utils::getFileContent(const std::string &filePath) -> std::string {
  std::ifstream file(filePath);
  std::string content((std::istreambuf_iterator<char>(file)),
                      (std::istreambuf_iterator<char>()));
  return content;
}

auto Utils::getSourceCodeFromFilePath(const std::string &filePath)
    -> std::vector<std::string> {

  std::ifstream file;

  file.open(Utils::getAbsoluteFilePath(filePath));

  // Check if the file was opened successfully
  if (!file.is_open()) {
    //   std::cerr << "Could not open the file." << std::endl;
    return std::vector<std::string>();
  }

  std::string line;
  std::vector<std::string> text = std::vector<std::string>();
  while (std::getline(file, line)) {
    text.push_back(line);
  }
  file.close();

  return text;
}

auto Utils::getStrongRandomString() -> std::string {
  std::string str(
      "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");

  std::random_device rd;
  std::mt19937 generator(rd());

  std::shuffle(str.begin(), str.end(), generator);

  return str.substr(0, 32); // assumes 32 < number of characters in str
}

auto Utils::isSyntaxToken(SyntaxNode *node) -> bool {
  switch (node->getKind()) {
  case SyntaxKindUtils::SyntaxKind::BadToken:
  case SyntaxKindUtils::SyntaxKind::NumberToken:
  case SyntaxKindUtils::SyntaxKind::TrueKeyword:
  case SyntaxKindUtils::SyntaxKind::FalseKeyword:
  case SyntaxKindUtils::SyntaxKind::VarKeyword:
  case SyntaxKindUtils::SyntaxKind::IfKeyword:
  case SyntaxKindUtils::SyntaxKind::OrKeyword:
  case SyntaxKindUtils::SyntaxKind::ElseKeyword:
  case SyntaxKindUtils::SyntaxKind::WhileKeyword:
  case SyntaxKindUtils::SyntaxKind::ForKeyword:
  case SyntaxKindUtils::SyntaxKind::FunctionKeyword:
  case SyntaxKindUtils::SyntaxKind::ToKeyword:
  case SyntaxKindUtils::SyntaxKind::ContinueKeyword:
  case SyntaxKindUtils::SyntaxKind::BreakKeyword:
  case SyntaxKindUtils::SyntaxKind::ReturnKeyword:
  case SyntaxKindUtils::SyntaxKind::ConstKeyword:
  case SyntaxKindUtils::SyntaxKind::IdentifierToken:
  case SyntaxKindUtils::SyntaxKind::WhitespaceToken:
  case SyntaxKindUtils::SyntaxKind::EndOfFileToken:
  case SyntaxKindUtils::SyntaxKind::CommentStatement:
  case SyntaxKindUtils::SyntaxKind::PlusToken:
  case SyntaxKindUtils::SyntaxKind::MinusToken:
  case SyntaxKindUtils::SyntaxKind::StarToken:
  case SyntaxKindUtils::SyntaxKind::SemiColonToken:
  case SyntaxKindUtils::SyntaxKind::CommaToken:
  case SyntaxKindUtils::SyntaxKind::OpenBraceToken:
  case SyntaxKindUtils::SyntaxKind::CloseBraceToken:
  case SyntaxKindUtils::SyntaxKind::HashToken:
  case SyntaxKindUtils::SyntaxKind::OpenParenthesisToken:
  case SyntaxKindUtils::SyntaxKind::CloseParenthesisToken:
  case SyntaxKindUtils::SyntaxKind::CaretToken:
  case SyntaxKindUtils::SyntaxKind::PercentToken:
  case SyntaxKindUtils::SyntaxKind::TildeToken:
  case SyntaxKindUtils::SyntaxKind::ColonToken:
  case SyntaxKindUtils::SyntaxKind::AmpersandAmpersandToken:
  case SyntaxKindUtils::SyntaxKind::AmpersandToken:
  case SyntaxKindUtils::SyntaxKind::SlashToken:
  case SyntaxKindUtils::SyntaxKind::PipePipeToken:
  case SyntaxKindUtils::SyntaxKind::PipeToken:
  case SyntaxKindUtils::SyntaxKind::EqualsEqualsToken:
  case SyntaxKindUtils::SyntaxKind::EqualsToken:
  case SyntaxKindUtils::SyntaxKind::BangEqualsToken:
  case SyntaxKindUtils::SyntaxKind::BangToken:
  case SyntaxKindUtils::SyntaxKind::LessOrEqualsToken:
  case SyntaxKindUtils::SyntaxKind::LessToken:
  case SyntaxKindUtils::SyntaxKind::GreaterOrEqualsToken:
  case SyntaxKindUtils::SyntaxKind::GreaterToken:
  case SyntaxKindUtils::SyntaxKind::EndOfLineToken:
  case SyntaxKindUtils::SyntaxKind::StringToken: {
    return true;
  }
  default:
    break;
  }

  return false;
}

std::unordered_map<std::string, int> Utils::Node::fileMap =
    std::unordered_map<std::string, int>();

std::unordered_map<std::string, int> Utils::Node::visitedMap =
    std::unordered_map<std::string, int>();
