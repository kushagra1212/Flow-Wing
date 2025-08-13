/*
 * FlowWing Compiler
 * Copyright (C) 2023-2025 Kushagra Rathore
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include "Utils.h"
#include "src/SemanticAnalyzer/BoundExpressions/BoundLiteralExpression/BoundLiteralExpression.h"
#include "src/SemanticAnalyzer/BoundStatements/BoundStatement/BoundStatement.h"
#include "src/diagnostics/DiagnosticUtils/DiagnosticUtils.h"
#include "src/interpreter/InterpreterUtils/InterpreterConversions/InterpreterConversion.h"
#include "src/syntax/CompilationUnitSyntax.h"
#include "src/syntax/SyntaxKindUtils.h"
#include "src/syntax/SyntaxNode.h"
#include "src/syntax/SyntaxToken.h"
#include <algorithm>
#include <cstdint>
#include <dirent.h>
#include <fstream>
#include <iostream>
#include <queue>
#include <random>
#include <regex>
#include <sstream>
#include <sys/stat.h>

#if defined(__linux__) || defined(__APPLE__)
#include <unistd.h>
#endif

#ifdef _WIN32
#include <windows.h>
std::string Utils::getTempDir() {
#if defined(DEBUG)
  return "";
#endif
  char tempPath[MAX_PATH];
  DWORD pathLen = GetTempPath(MAX_PATH, tempPath);
  if (pathLen > 0 && pathLen < MAX_PATH) {
    return std::string(tempPath);
  }
  return "";
}
#else
#include <cstdlib>
std::string Utils::getTempDir() {
#if defined(DEBUG)
  return "";
#endif

  const char *tempDir = std::getenv("TMPDIR");
  if (!tempDir) {
    tempDir = "/tmp/";
  }
  return std::string(tempDir);
}
#endif

void Utils::split(const std::string &str, const std::string &delim,
                  std::vector<std::string> &tokens) {
  size_t prev = 0, pos = 0;
  do {
    pos = str.find(delim, prev);
    if (pos == std::string::npos)
      pos = str.length();
    std::string token = str.substr(prev, pos - prev);
    if (!token.empty())
      tokens.push_back(token);

    prev = pos + delim.length();
  } while (pos < str.length() && prev < str.length());

  // std::vector<std::string> tokens;
}

std::string Utils::CE(const std::string &str) {
  std::string res = "";

  res += YELLOW + str + RESET + RED_TEXT;
  res += "";
  return res;
}

void Utils::prettyPrint(SyntaxNode *node, std::string indent, bool isLast) {
  if (!node) {
    std::cout << "Node is null\n";
    return;
  }
  std::cout << indent;
  std::string prevIndent = indent;
  if (isLast) {
    std::cout << RED_TEXT << "└──" << RESET;
    indent += "    ";
  } else {
    std::cout << GREEN_TEXT << "├──" << RESET;
    indent += GREEN_TEXT;
    indent += "├   ";
    indent += RESET;
  }

  std::cout << "Node kind: " << SyntaxKindUtils::to_string(node->getKind());
  if (Utils::isSyntaxToken(node)) {
    std::string value = ((SyntaxToken<std::any> *)node)->getText();
    std::cout << " { Node value: '" << PINK_TEXT << value << RESET << "' }";
  }
  std::vector<SyntaxNode *> children = node->getChildren();

  std::string GRAY_TEXT = "\033[1;30m";
  std::cout << GRAY_TEXT;

  if (children.size())
    std::cout << " { Childrens = [ " << children.size() << " ] } ";
  for (size_t i = 0; i < children.size(); i++) {
    // std::cout << "\n"
    //           << prevIndent << "    "
    //           << "├"
    //           << "Printing child " << i;
    std::cout << "\n";
    std::cout << RESET;
    Utils::prettyPrint(children[i], indent, i == children.size() - 1);
  }
}

void Utils::prettyPrint(CompilationUnitSyntax *compilationUnit,
                        std::string indent, bool isLast) {
  if (!compilationUnit) {
    std::cout << "Compilation unit is null\n";
    return;
  }
  std::cout << indent;
  std::string prevIndent = indent;
  if (isLast) {
    std::cout << RED_TEXT << "└──" << RESET;
    indent += "    ";
  } else {
    std::cout << GREEN_TEXT << "├──" << RESET;
    indent += "|   ";
  }
  std::string GRAY_TEXT = "\033[1;30m";

  std::cout << "Compilation unit kind: "
            << SyntaxKindUtils::to_string(compilationUnit->getKind()) << '\n';
  std::cout << GRAY_TEXT;
  std::cout << prevIndent << "    "
            << "Number of children in compilation unit: "
            << compilationUnit->getChildren().size() << "\n";
  for (size_t i = 0; i < compilationUnit->getChildren().size(); i++) {
    std::cout << prevIndent << "    "
              << " { Printing child [ " << i << " ] of compilation unit }\n";

    std::cout << RESET;
    Utils::prettyPrint(compilationUnit->getChildren()[i], indent, true);
  }

  std::cout << "\n";
}

void Utils::prettyPrint(BoundNode *node, std::string indent, bool isLast) {
  if (!node) {
    // std::cout << "null\n";
    return;
  }
  std::cout << indent;
  if (isLast) {
    std::cout << RED_TEXT << "└──" << RESET;
    indent += "    ";
  } else {
    std::cout << GREEN_TEXT << "├──" << RESET;
    indent += "├   ";
  }

  std::cout << BinderKindUtils::to_string(node->getKind());
  if (node->getKind() == BinderKindUtils::LiteralExpression) {
    std::any value = ((BoundLiteralExpression<std::any> *)node)->getValue();

    std::cout << " "
              << InterpreterConversion::explicitConvertAnyToString(value);
  }
  std::cout << "\n";
  std::vector<BoundNode *> children = node->getChildren();
  for (size_t i = 0; i < children.size(); i++) {
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

  std::cout << BLUE_TEXT << indent << RESET
            << BinderKindUtils::to_string(statement->getKind()) << '\n';
  for (size_t i = 0; i < statement->getChildren().size(); i++) {
    Utils::prettyPrint(statement->getChildren()[i], indent,
                       i == statement->getChildren().size() - 1);
  }
}

JSON Utils::outJSON(BoundNode *node, [[maybe_unused]] bool isLast) {
  if (!node) {
    return JSON();
  }

  JSON jsonObject;

  if (node->getKind() == BinderKindUtils::LiteralExpression) {
    std::any value = ((BoundLiteralExpression<std::any> *)node)->getValue();
    jsonObject[BinderKindUtils::to_string(node->getKind())] =
        InterpreterConversion::explicitConvertAnyToString(value);
  }

  std::vector<BoundNode *> children = node->getChildren();
  for (size_t i = 0; i < children.size(); i++) {
    jsonObject[BinderKindUtils::to_string(node->getKind())].push_back(
        Utils::outJSON(children[i], i == children.size() - 1));
  }

  return jsonObject;
}

JSON Utils::outJSON(BoundStatement *statement, [[maybe_unused]] bool isLast) {
  if (!statement) {
    return JSON();
  }

  JSON jsonObject;

  for (size_t i = 0; i < statement->getChildren().size(); i++) {
    jsonObject[BinderKindUtils::to_string(statement->getKind())].push_back(
        Utils::outJSON(statement->getChildren()[i],
                       i == statement->getChildren().size() - 1));
  }

  return jsonObject;
}

JSON Utils::outJSON(SyntaxNode *node) {
  if (!node) {
    return JSON();
  }

  JSON jsonObject;
  if (Utils::isSyntaxToken(node)) {

    jsonObject[SyntaxKindUtils::to_string(node->getKind())] = {
        {"value", ((SyntaxToken<std::any> *)node)->getText()},
        {"lineNumber", node->getSourceLocation().lineNumber},
        {"columnNumber", node->getSourceLocation().columnNumber}};
  }
  std::vector<SyntaxNode *> children = node->getChildren();

  for (size_t i = 0; i < children.size(); i++) {
    jsonObject[SyntaxKindUtils::to_string(node->getKind())].push_back(
        Utils::outJSON(children[i]));
  }

  return jsonObject;
}

JSON Utils::outJSON(CompilationUnitSyntax *compilationUnit) {
  if (!compilationUnit) {
    return JSON();
  }
  JSON jsonObject;

  for (size_t i = 0; i < compilationUnit->getChildren().size(); i++) {
    jsonObject[SyntaxKindUtils::to_string(compilationUnit->getKind())]
        .push_back(Utils::outJSON(compilationUnit->getChildren()[i]));
  }

  return jsonObject;
}

JSON Utils::outJSON(
    const std::vector<std::unique_ptr<SyntaxToken<std::any>>> &tokens) {

  JSON jsonObject;

  for (auto &token : tokens) {
    jsonObject.push_back(
        {{"value", token->getText()},
         {"lineNumber", token->getSourceLocation().lineNumber},
         {"columnNumber", token->getSourceLocation().columnNumber}});
  }

  return jsonObject;
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
  for (size_t i = 0; i < children.size(); i++) {
    if (children[i]) {
      bool has = include;

      has = has || (children[i]->getKind() ==
                    SyntaxKindUtils::SyntaxKind::FunctionDeclarationSyntax);

      code += Utils::getSourceCode(children[i], has);
    }
  }
  return code;
}

void Utils::prettyPrint(
    const std::vector<std::unique_ptr<SyntaxToken<std::any>>> &tokens) {
  const int kindTextWidth = 20;
  const int textWidth = 20;

  // Print headers
  std::cout << GREEN_TEXT << std::left << std::setw(kindTextWidth) << "Kind"
            << std::left << std::setw(textWidth) << "Text" << RESET << "\n";
  std::cout << std::string(kindTextWidth + textWidth, '-') << "\n";

  // Print token data
  for (auto &token : tokens) {
    std::cout << YELLOW_TEXT << std::left << std::setw(kindTextWidth)
              << token->getKindText() << std::left << RESET
              << std::setw(textWidth) << token->getText() << "\n";
  }

  std::cout << std::string(kindTextWidth + textWidth, '-') << "\n";
}

std::string Utils::getSourceCode(CompilationUnitSyntax *compilationUnit) {
  if (!compilationUnit) {
    return "";
  }
  std::string code = "";

  for (size_t i = 0; i < compilationUnit->getChildren().size(); i++) {
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

SyntaxKindUtils::SyntaxKind Utils::getTypeFromAny(const std::any &value) {
  if (value.type() == typeid(int)) {
    return SyntaxKindUtils::SyntaxKind::Int32Keyword;
  } else if (value.type() == typeid(double)) {
    return SyntaxKindUtils::SyntaxKind::DeciKeyword;
  } else if (value.type() == typeid(std::string)) {
    return SyntaxKindUtils::SyntaxKind::StrKeyword;
  } else if (value.type() == typeid(bool)) {
    return SyntaxKindUtils::SyntaxKind::BoolKeyword;
  } else {
    return SyntaxKindUtils::SyntaxKind::NthgKeyword;
  }
}

void Utils::printErrors(const std::vector<std::string> &errors,
                        std::ostream &outputStream, bool isWarning) {
  outputStream << "\n";
  for (const std::string &error : errors) {
    if (isWarning)
      outputStream << YELLOW_TEXT << error << RESET << "\n";
    else
      outputStream << RED_TEXT << error << RESET << "\n";
  }
}

std::string Utils::getAbsoluteFilePath(std::string relativeFilePath) {
  std::filesystem::path basePath = std::filesystem::current_path();

  // Create an absolute path by combining the base path and the relative path
  std::filesystem::path absolutePath = basePath / relativeFilePath;

  return absolutePath.string();
}

const std::string Utils::getFileName(const std::string &filePath) {
  std::filesystem::path path(filePath);
  return path.filename().string();
}

const std::string Utils::getNameExtension(const std::string &filePath) {
  if (filePath.empty())
    return "";

  std::filesystem::path path(filePath);
  return path.stem().string();
}
const std::string Utils::getExtension(const std::string &filePath) {

  return std::filesystem::path(filePath).extension().string();
}

bool Utils::isSubstring(const std::string &s1, const std::string &s2) {
  size_t M = s1.length();
  size_t N = s2.length();

  /* A loop to slide pat[] one by one */
  for (size_t i = 0; i <= N - M; i++) {
    size_t j;

    /* For current index i, check for
    pattern match */
    for (j = 0; j < M; j++)
      if (s2[i + j] != s1[j])
        break;

    if (j == M)
      return true; // or print index of the pattern
  }

  return false;
}
const std::string
Utils::removeExtensionFromString(const std::string &filePath) {
  std::filesystem::path path(filePath);
  return path.replace_extension("").string();
}

DiagnosticUtils::SourceLocation
Utils::getSourceLocation(SyntaxToken<std::any> *token) {
  return DiagnosticUtils::SourceLocation(
      token->getLineNumber(), token->getColumnNumber(),
      token->getText().length(), token->getAbsoluteFilePath());
}

Utils::type Utils::toContainerType(Utils::type basicType) {
  switch (basicType) {
  case Utils::type::INT8:
    return Utils::type::INT8_CONTAINER;
  case Utils::type::INT16:
    return Utils::type::INT16_CONTAINER;
  case Utils::type::INT32:
    return Utils::type::INT32_CONTAINER;
  case Utils::type::INT64:
    return Utils::type::INT64_CONTAINER;
  case Utils::type::DECIMAL:
    return Utils::type::DECIMAL_CONTAINER;
  case Utils::type::BOOL:
    return Utils::type::BOOL_CONTAINER;
  case Utils::type::STRING:
    return Utils::type::STRING_CONTAINER;
  case Utils::type::UNKNOWN:
    return Utils::type::UNKNOWN_CONTAINER;
  default:
    // Handle error: basicType is not a basic Utils::type
    throw std::invalid_argument("Invalid basic Utils::type");
  }
}

Utils::type Utils::toContainerElementType(Utils::type containerType) {
  switch (containerType) {
  case Utils::type::INT8_CONTAINER:
    return Utils::type::INT8;
  case Utils::type::INT16_CONTAINER:
    return Utils::type::INT16;
  case Utils::type::INT32_CONTAINER:
    return Utils::type::INT32;
  case Utils::type::INT64_CONTAINER:
    return Utils::type::INT64;
  case Utils::type::DECIMAL_CONTAINER:
    return Utils::type::DECIMAL;
  case Utils::type::DECIMAL32_CONTAINER:
    return Utils::type::DECIMAL32;
  case Utils::type::BOOL_CONTAINER:
    return Utils::type::BOOL;
  case Utils::type::STRING_CONTAINER:
    return Utils::type::STRING;
  case Utils::type::UNKNOWN_CONTAINER:
    return Utils::type::UNKNOWN;
  default:
    // Handle error: containerType is not a container Utils::type
    throw std::invalid_argument("Invalid container Utils::type");
  }
}

auto Utils::isStaticTypedPrimitiveType(Utils::type type) -> bool {
  switch (type) {
  case Utils::type::INT8:
  case Utils::type::INT16:
  case Utils::type::INT32:
  case Utils::type::INT64:
  case Utils::type::DECIMAL:
  case Utils::type::DECIMAL32:
  case Utils::type::BOOL:
  case Utils::type::STRING:
    return true;
  default:
    return false;
  }
}
auto Utils::isDynamicTypedPrimitiveType(Utils::type type) -> bool {
  return type == Utils::type::UNKNOWN;
}

auto Utils::isContainerType(Utils::type type) -> bool {
  return isStaticTypedContainerType(type) || isDynamicTypedContainerType(type);
}

auto Utils::isStaticTypedType(Utils::type type) -> bool {
  return isStaticTypedPrimitiveType(type) || isStaticTypedContainerType(type);
}
auto Utils::isDynamicTypedType(Utils::type type) -> bool {
  return isDynamicTypedPrimitiveType(type) || isDynamicTypedContainerType(type);
}

auto Utils::isStaticTypedContainerType(Utils::type type) -> bool {
  switch (type) {
  case Utils::type::INT8_CONTAINER:
  case Utils::type::INT16_CONTAINER:
  case Utils::type::INT32_CONTAINER:
  case Utils::type::INT64_CONTAINER:
  case Utils::type::DECIMAL_CONTAINER:
  case Utils::type::BOOL_CONTAINER:
  case Utils::type::STRING_CONTAINER:
    return true;
  default:
    return false;
  }
  return false;
}

auto Utils::isDynamicTypedContainerType(Utils::type type) -> bool {
  return type == Utils::type::UNKNOWN_CONTAINER;
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

auto Utils::typeToString(SyntaxKindUtils::SyntaxKind type) -> std::string {
  switch (type) {
  case SyntaxKindUtils::SyntaxKind::Int32Keyword:
    return "Int32";
  case SyntaxKindUtils::SyntaxKind::Int8Keyword:
    return "Int8";
  case SyntaxKindUtils::SyntaxKind::Int64Keyword:
    return "Int64";
  case SyntaxKindUtils::SyntaxKind::DeciKeyword:
    return "Decimal";
  case SyntaxKindUtils::SyntaxKind::StrKeyword:
    return "String";
  case SyntaxKindUtils::SyntaxKind::BoolKeyword:
    return "Bool";
  case SyntaxKindUtils::SyntaxKind::NthgKeyword:
    return "Nothing";
  case SyntaxKindUtils::SyntaxKind::NBU_UNKNOWN_TYPE:
    return "Unknown";

  default:
    break;
  }
  return "Not a type";
}

std::vector<std::string> Utils::readLines(std::string absoluteFilePath) {
  std::ifstream file;

  file.open(absoluteFilePath);
  if (!file.is_open()) {
    Utils::printErrors(
        {
            "Error: Unable to open file: " + absoluteFilePath,
        },
        std::cerr);

    file.close();
    return std::vector<std::string>();
  }

  std::string line;
  std::vector<std::string> lines = std::vector<std::string>();
  while (std::getline(file, line)) {
    lines.push_back(line);
  }
  file.close();
  return lines;
}

std::vector<std::string> Utils::readLinesFromText(const std::string &Code) {
  std::vector<std::string> lines = std::vector<std::string>();
  std::string line;
  std::istringstream stream(Code);
  while (std::getline(stream, line)) {
    lines.push_back(line);
  }
  return lines;
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
  std::string str("0123456789ABCDEF");

  std::random_device rd;
  std::mt19937 generator(rd());

  std::shuffle(str.begin(), str.end(), generator);

  // append time to the end of the string

  std::string time = std::to_string(
      std::chrono::system_clock::now().time_since_epoch().count());

  str += time;

  return str.substr(0, 10);
}

std::string Utils::generateUniqueString() {
  // Get the current time since epoch
  auto now = std::chrono::system_clock::now();
  auto duration = now.time_since_epoch();
  auto milliseconds =
      std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();

  // Convert the timestamp to a string
  return std::to_string(milliseconds);
}

std::vector<std::string> Utils::getAllFilesInDirectoryWithExtension(
    std::string directoryPath, std::string extension, bool recursive) {
  std::vector<std::string> files = std::vector<std::string>();

  for (const auto &entry : std::filesystem::directory_iterator(directoryPath)) {
    if (entry.path().extension() == extension) {
      files.push_back(entry.path().string());
    }

    if (entry.is_directory() && recursive) {
      std::vector<std::string> subFiles = getAllFilesInDirectoryWithExtension(
          entry.path().string(), extension, recursive);
      files.insert(files.end(), subFiles.begin(), subFiles.end());
    }
  }
  return files;
}

void Utils::deleteFilesWithExtension(const std::string &directoryPath,
                                     const std::string &extension) {
  namespace fs = std::filesystem;
  for (const auto &entry : fs::directory_iterator(directoryPath)) {
    if (entry.path().extension() == extension) {
      fs::remove(entry.path());
    }
  }
}

void Utils::logJSON(JSON &jsonObject, std::string filePath) {
  std::ofstream outputFile(filePath);
  if (outputFile.is_open()) {
    outputFile << jsonObject.dump(1); // Pretty print with 1 spaces
    outputFile.close();
    Utils::print_log("JSON object has been written to " + filePath,
                     SUCCESS_COLOR);
  } else {
    Utils::print_log("Could not open output.json for writing\n", ERROR_COLOR);
  }
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
  case SyntaxKindUtils::SyntaxKind::OpenBracketToken:
  case SyntaxKindUtils::SyntaxKind::CloseBracketToken:
  case SyntaxKindUtils::SyntaxKind::HashToken:
  case SyntaxKindUtils::SyntaxKind::OpenParenthesisToken:
  case SyntaxKindUtils::SyntaxKind::CloseParenthesisToken:
  case SyntaxKindUtils::SyntaxKind::CaretToken:
  case SyntaxKindUtils::SyntaxKind::PercentToken:
  case SyntaxKindUtils::SyntaxKind::TildeToken:
  case SyntaxKindUtils::SyntaxKind::ColonToken:
  case SyntaxKindUtils::SyntaxKind::DotToken:
  case SyntaxKindUtils::SyntaxKind::AmpersandAmpersandToken:
  case SyntaxKindUtils::SyntaxKind::SlashSlashToken:
  case SyntaxKindUtils::SyntaxKind::AmpersandToken:
  case SyntaxKindUtils::SyntaxKind::SlashToken:
  case SyntaxKindUtils::SyntaxKind::PipePipeToken:
  case SyntaxKindUtils::SyntaxKind::PipeToken:
  case SyntaxKindUtils::SyntaxKind::EqualsEqualsToken:
  case SyntaxKindUtils::SyntaxKind::EqualsToken:
  case SyntaxKindUtils::SyntaxKind::BangEqualsToken:
  case SyntaxKindUtils::SyntaxKind::BangToken:
  case SyntaxKindUtils::SyntaxKind::AssignmentToken:
  case SyntaxKindUtils::SyntaxKind::LessOrEqualsToken:
  case SyntaxKindUtils::SyntaxKind::LessToken:
  case SyntaxKindUtils::SyntaxKind::GreaterOrEqualsToken:
  case SyntaxKindUtils::SyntaxKind::GreaterToken:
  case SyntaxKindUtils::SyntaxKind::EndOfLineToken:
  case SyntaxKindUtils::SyntaxKind::StringToken:

  case SyntaxKindUtils::SyntaxKind::Int32Keyword:
  case SyntaxKindUtils::SyntaxKind::Int8Keyword:
  case SyntaxKindUtils::SyntaxKind::Int64Keyword:
  case SyntaxKindUtils::SyntaxKind::DeciKeyword:
  case SyntaxKindUtils::SyntaxKind::StrKeyword:
  case SyntaxKindUtils::SyntaxKind::BoolKeyword:
  case SyntaxKindUtils::SyntaxKind::NthgKeyword:
  case SyntaxKindUtils::SyntaxKind::NBU_UNKNOWN_TYPE:
  case SyntaxKindUtils::SyntaxKind::ClassKeyword:
  case SyntaxKindUtils::SyntaxKind::Deci32Keyword:
  case SyntaxKindUtils::SyntaxKind::BringKeyword:
  case SyntaxKindUtils::SyntaxKind::ExposeKeyword:
  case SyntaxKindUtils::SyntaxKind::FromKeyword:
  case SyntaxKindUtils::SyntaxKind::FillKeyword:
  case SyntaxKindUtils::SyntaxKind::TypeKeyword:
  case SyntaxKindUtils::SyntaxKind::DeclKeyword:
  case SyntaxKindUtils::SyntaxKind::NewKeyword:
  case SyntaxKindUtils::SyntaxKind::InOutKeyword:
  case SyntaxKindUtils::SyntaxKind::ExtendsKeyword:
  case SyntaxKindUtils::SyntaxKind::AsKeyword:
  case SyntaxKindUtils::SyntaxKind::NBU_OBJECT_TYPE: {
    return true;
  }
  default:
    break;
  }

  return false;
}

std::filesystem::path Utils::findFile(const std::filesystem::path &directory,
                                      const std::string &filename) {
  std::queue<std::filesystem::path> directories;
  directories.push(directory);

  while (!directories.empty()) {
    std::filesystem::path currentDir = directories.front();
    directories.pop();

    for (const auto &entry : std::filesystem::directory_iterator(currentDir)) {
      if (entry.is_directory()) {
        directories.push(entry.path());
      } else if (entry.path().filename() == filename) {
        return entry.path();
      }
    }
  }

  return std::filesystem::path();
}

std::unordered_map<std::string, int> Utils::Node::fileMap =
    std::unordered_map<std::string, int>();

std::unordered_map<std::string, int> Utils::Node::visitedMap =
    std::unordered_map<std::string, int>();
