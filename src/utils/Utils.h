#ifndef UTILS_H
#define UTILS_H
#include <filesystem>
#include <regex>
#include <typeinfo>

#include "../Common.h"
#include "../bind/BinderKindUtils.h"
#include "../bind/BoundLiteralExpression/BoundLiteralExpression.h"
#include "../bind/BoundNode.h"
#include "../bind/BoundStatement/BoundStatement.h"
#include "../diagnostics/DiagnosticUtils/DiagnosticUtils.h"
#include "../interpreter/InterpreterUtils/InterpreterConversions/InterpreterConversion.h"
#include "../syntax/CompilationUnitSyntax.h"
#include "../syntax/MemberSyntax.h"
#include "../syntax/SyntaxNode.h"
#include "../syntax/expression/LiteralExpressionSyntax.h"
#include "../syntax/statements/GlobalStatementSyntax/GlobalStatementSyntax.h"
// Implementation function
// Implementation of the debug log function
template <typename... Args>
void DEBUG_LOG_IMPL(const std::string &type, const std::string &file, int line,
                    const std::string &func, const std::string &format,
                    Args &&...args) {
  std::stringstream ss;
  ((ss << std::forward<Args>(args)), ...);

  std::cout << BOLD << "[DEBUG]" << BLUE_TEXT
            << (type.empty() ? "" : "[" + type + "]") << BLACK_TEXT << " ("
            << file << ":" << line << " in " << func << "): " << GREEN_TEXT
            << format << YELLOW_TEXT << ss.str() << RESET << std::endl;
}

// Macro to expand the variadic arguments correctly
#ifdef DEBUG
#define DEBUG_LOG(format, ...)                                                 \
  DEBUG_LOG_IMPL("", __FILE__, __LINE__, __func__, format, ##__VA_ARGS__)

// Macro for general info logs
#define INFO_DEBUG_LOG(format, ...)                                            \
  DEBUG_LOG_IMPL("INFO", __FILE__, __LINE__, __func__, format, ##__VA_ARGS__)

// Macro for lexer logs
#define LEXER_DEBUG_LOG(format, ...)                                           \
  DEBUG_LOG_IMPL("LEXER", __FILE__, __LINE__, __func__, format, ##__VA_ARGS__)

// Macro for parser logs
#define PARSER_DEBUG_LOG(format, ...)                                          \
  DEBUG_LOG_IMPL("PARSER", __FILE__, __LINE__, __func__, format, ##__VA_ARGS__)

// Macro for code generation logs
#define CODEGEN_DEBUG_LOG(format, ...)                                         \
  DEBUG_LOG_IMPL("CODEGEN", __FILE__, __LINE__, __func__, format, ##__VA_ARGS__)
#else
#define DEBUG_LOG(format, ...) // No-op in release builds
#define INFO_DEBUG_LOG(format, ...)
#define LEXER_DEBUG_LOG(format, ...)
#define PARSER_DEBUG_LOG(format, ...)
#define CODEGEN_DEBUG_LOG(format, ...)
#endif

namespace Utils {
enum type {
  INT8,
  INT16,
  INT32,
  INT64,
  DECIMAL,
  BOOL,
  STRING,
  NOTHING,
  ARRAY,
  OBJECT,
  UNKNOWN,

  // Container Types

  INT8_CONTAINER,
  INT16_CONTAINER,
  INT32_CONTAINER,
  INT64_CONTAINER,
  DECIMAL_CONTAINER,
  BOOL_CONTAINER,
  STRING_CONTAINER,
  UNKNOWN_CONTAINER,
};
void prettyPrint(SyntaxNode *node, std::string indent = "", bool isLast = true);

void prettyPrint(CompilationUnitSyntax *compilationUnit,
                 std::string indent = "", bool isLast = true);

void prettyPrint(BoundStatement *statement, std::string indent = "",
                 bool isLast = true);
void prettyPrint(BoundNode *statement, std::string indent = "",
                 bool isLast = true);
void prettyPrint(
    const std::vector<std::unique_ptr<SyntaxToken<std::any>>> &tokens);
void printErrors(const std::vector<std::string> &errors,
                 std::ostream &outputStream, bool isWarning = false);

JSON outJSON(BoundNode *node, bool isLast);
JSON outJSON(BoundStatement *statement, bool isLast);
JSON outJSON(SyntaxNode *node);
JSON outJSON(CompilationUnitSyntax *compilationUnit);
JSON outJSON(const std::vector<std::unique_ptr<SyntaxToken<std::any>>> &tokens);

void logJSON(JSON &jsonObject, std::string filePath);

const std::string getFileName(const std::string &filePath);

const std::string concatErrors(const std::vector<std::string> &errors,
                               std::ostream &outputStream,
                               bool isWarning = false);
auto getStrongRandomString() -> std::string;
std::string generateUniqueString();
std::string getTypeString(const std::any &value);
SyntaxKindUtils::SyntaxKind getTypeFromAny(const std::any &value);
std::string getSourceCode(CompilationUnitSyntax *node);
std::string getSourceCode(SyntaxNode *node, bool include);
std::string CE(const std::string &str);

Utils::type toContainerType(Utils::type type);
Utils::type toContainerElementType(Utils::type type);
auto isContainerType(Utils::type type) -> const bool;
auto isStaticTypedContainerType(Utils::type type) -> const bool;
auto isDynamicTypedContainerType(Utils::type type) -> const bool;
auto isStaticTypedPrimitiveType(Utils::type type) -> const bool;
auto isDynamicTypedPrimitiveType(Utils::type type) -> const bool;

auto isStaticTypedType(Utils::type type) -> const bool;
auto isDynamicTypedType(Utils::type type) -> const bool;

auto getFileContent(const std::string &filePath) -> std::string;
auto getSourceCodeFromFilePath(const std::string &filePath)
    -> std::vector<std::string>;
std::string getAbsoluteFilePath(std::string relativeFilePath);
std::vector<std::string> readLines(std::string absoluteFilePath);
std::vector<std::string> readLinesFromText(const std::string &Code);
void split(const std::string &s, const std::string &delim,
           std::vector<std::string> &tokens);

bool isInteger(const std::string &str);

bool isDouble(const std::string &str);
auto isSyntaxToken(SyntaxNode *node) -> bool;
auto typeToString(SyntaxKindUtils::SyntaxKind type) -> std::string;
std::filesystem::path findFile(const std::filesystem::path &directory,
                               const std::string &filename);

inline auto getActualTypeName(const std::string &typeName) -> std::string {
  return typeName.substr(0, typeName.find("."));
}

inline auto isClassInit(const std::string &name) -> bool {
  return name.find(".init") != std::string::npos;
}

inline std::string print_log(const std::string &str, const std::string &color) {
  std::string res = "";

  res += color + str + RESET;
  return res;
}

std::vector<std::string>
getAllFilesInDirectoryWithExtension(std::string directoryPath,
                                    std::string extension, bool recursive);

void deleteFilesWithExtension(const std::string &directoryPath,
                              const std::string &extension);
bool isSubstring(const std::string &s1, const std::string &s2);
enum class SymbolKind {
  Variable,
  Function,
  Parameter,
  Type,
  Namespace,
  Label,
  None
};
const std::string getExtension(const std::string &filePath);
const std::string removeExtensionFromString(const std::string &filePath);
DiagnosticUtils::SourceLocation getSourceLocation(SyntaxToken<std::any> *token);

const std::string getNameExtension(const std::string &filePath);
const std::string getRelativePath(const std::string &filePath);
struct Variable {
  Utils::type type;
  std::any value;
  bool isConst;
  SymbolKind kind;
  Variable() = default;
  Variable(std::any value, bool isConst,
           Utils::type type = Utils::type::UNKNOWN) {
    this->value = value;
    this->isConst = isConst;
    this->kind = SymbolKind::Variable;
    this->type = type;
  }
};

class Node {
  static std::unordered_map<std::string, int> fileMap;
  static std::unordered_map<std::string, int> visitedMap;

public:
  static void addPath(std::string path) {
    fileMap[(path)]++;
    visitedMap[(path)]++;
  }

  static bool isPathVisited(std::string path) {
    return visitedMap.find((path)) != visitedMap.end();
  }

  static bool isPathAdded(std::string path) {
    return fileMap.find((path)) != fileMap.end();
  }

  static void clear() { fileMap.clear(); }

  static void removePath(std::string path) { fileMap.erase((path)); }

  static bool isPathExists(std::string path) {
    return std::filesystem::exists((path));
  }

  static bool isPathDirectory(std::string path) {
    return std::filesystem::is_directory((path));
  }

  static bool isPathRegularFile(std::string path) {
    return std::filesystem::is_regular_file((path));
  }

  static bool isPathSymlink(std::string path) {
    return std::filesystem::is_symlink((path));
  }

  static bool isPathEmpty(std::string path) {
    return std::filesystem::is_empty((path));
  }

  static bool isPathRelative(std::string path) {
    return std::filesystem::path((path)).is_relative();
  }

  static bool isPathAbsolute(std::string path) {
    return std::filesystem::path((path)).is_absolute();
  }

  static bool isCycleDetected(std::string path) { return fileMap[(path)] >= 1; }
};

} // namespace Utils

#endif // UTILS_H