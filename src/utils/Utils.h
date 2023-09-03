#ifndef UTILS_H
#define UTILS_H
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
#include <regex>
#include <typeinfo>

namespace Utils {
enum type { INT32, DECIMAL, STRING, BOOL, NOTHING, UNKNOWN };
void prettyPrint(SyntaxNode *node, std::string indent = "", bool isLast = true);

void prettyPrint(CompilationUnitSyntax *compilationUnit,
                 std::string indent = "", bool isLast = true);

void prettyPrint(BoundStatement *statement, std::string indent = "",
                 bool isLast = true);
void prettyPrint(BoundNode *statement, std::string indent = "",
                 bool isLast = true);
void printErrors(const std::vector<std::string> &errors,
                 std::ostream &outputStream, bool isWarning = false);

const std::string concatErrors(const std::vector<std::string> &errors,
                               std::ostream &outputStream,
                               bool isWarning = false);

std::string getTypeString(const std::any &value);
Utils::type getTypeFromAny(const std::any &value);
std::string getSourceCode(CompilationUnitSyntax *node);
std::string getSourceCode(SyntaxNode *node, bool include);

bool isInteger(const std::string &str);

bool isDouble(const std::string &str);
auto isSyntaxToken(SyntaxNode *node) -> bool;
auto typeToString(Utils::type type) -> std::string;

enum class SymbolKind {
  Variable,
  Function,
  Parameter,
  Type,
  Namespace,
  Label,
  None
};

DiagnosticUtils::SourceLocation getSourceLocation(SyntaxToken<std::any> *token);

struct Variable {
  std::any value;
  bool isConst;
  SymbolKind kind;
  Variable() = default;
  Variable(std::any value, bool isConst) {
    this->value = value;
    this->isConst = isConst;
    this->kind = SymbolKind::Variable;
  }
};

struct FunctionParameterSymbol {
  std::string name;
  bool isConst;
  SymbolKind kind;
  FunctionParameterSymbol() = default;
  FunctionParameterSymbol(std::string name, bool isConst) {
    this->name = name;
    this->isConst = isConst;
    this->kind = SymbolKind::Parameter;
  }
};

struct FunctionSymbol {
  std::string name;
  std::vector<FunctionParameterSymbol> parameters;
  type return_type;
  SymbolKind kind;
  FunctionSymbol() { this->kind = SymbolKind::None; }
  FunctionSymbol(std::string name,
                 std::vector<FunctionParameterSymbol> parameters,
                 type return_type = Utils::type::NOTHING) {
    this->name = name;
    this->parameters = parameters;
    this->kind = SymbolKind::Function;
    this->return_type = return_type;
  }

  const type &getReturnType() { return return_type; }

  int arity() { return (int)parameters.size(); }
};

class BuiltInFunctions {
public:
  static FunctionSymbol print;
  static FunctionSymbol input;
  static FunctionSymbol random;

  // Conversations

  static FunctionSymbol String;
  static FunctionSymbol Int32;
  static FunctionSymbol Decimal;
  static FunctionSymbol Bool;
  static FunctionSymbol Nothing;

  static std::vector<FunctionSymbol> getAllFunctions();

  static FunctionSymbol getFunctionSymbol(std::string name);

  static auto isBuiltInFunction(std::string name) -> bool;
};

} // namespace Utils

#endif // UTILS_H