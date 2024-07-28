#ifndef PARSER_H
#define PARSER_H
#include <typeindex>

#include "../diagnostics/DiagnosticHandler/DiagnosticHandler.h"
#include "../lexer/Lexer.h"
#include "../syntax/CompilationUnitSyntax.h"
#include "../syntax/MemberSyntax.h"
#include "../syntax/expression/AssignmentExpressionSyntax.h"
#include "../syntax/expression/BinaryExpressionSyntax.h"
#include "../syntax/expression/BracketedExpressionSyntax/BracketedExpressionSyntax.h"
#include "../syntax/expression/CallExpressionSyntax/CallExpressionSyntax.h"
#include "../syntax/expression/ContainerExpressionSyntax/ContainerExpressionSyntax.h"
#include "../syntax/expression/FillExpressionSyntax/FillExpressionSyntax.h"
#include "../syntax/expression/IndexExpressionSyntax/IndexExpressionSyntax.h"
#include "../syntax/expression/LiteralExpressionSyntax.h"
#include "../syntax/expression/ObjectExpressionSyntax/ObjectExpressionSyntax.h"
#include "../syntax/expression/ParenthesizedExpressionSyntax.h"
#include "../syntax/expression/TypeExpressionSyntax/ArrayTypeExpressionSyntax/ArrayTypeExpressionSyntax.h"
#include "../syntax/expression/TypeExpressionSyntax/ObjectTypeExpressionSyntax/ObjectTypeExpressionSyntax.h"
#include "../syntax/expression/TypeExpressionSyntax/TypeExpressionSyntax.h"
#include "../syntax/expression/UnaryExpressionSyntax.h"
#include "../syntax/expression/VariableExpressionSyntax/VariableExpressionSyntax.h"
#include "../syntax/statements/BlockStatementSyntax/BlockStatementSyntax.h"
#include "../syntax/statements/BreakStatementSyntax/BreakStatementSyntax.h"
#include "../syntax/statements/BringStatementSyntax/BringStatementSyntax.h"
#include "../syntax/statements/ClassStatementSyntax/ClassStatementSyntax.h"
#include "../syntax/statements/ContainerStatementSyntax/ContainerStatementSyntax.h"
#include "../syntax/statements/ContinueStatementSyntax/ContinueStatementSyntax.h"
#include "../syntax/statements/CustomTypeStatementSyntax/CustomTypeStatementSyntax.h"
#include "../syntax/statements/EmptyStatementSyntax/EmptyStatementSyntax.h"
#include "../syntax/statements/ExpressionStatementSyntax/ExpressionStatementSyntax.h"
#include "../syntax/statements/ForStatementSyntax/ForStatementSyntax.h"
#include "../syntax/statements/FunctionDeclarationSyntax/FunctionDeclarationSyntax.h"
#include "../syntax/statements/GlobalStatementSyntax/GlobalStatementSyntax.h"
#include "../syntax/statements/IfStatementSyntax/IfStatementSyntax.h"
#include "../syntax/statements/OrIfStatementSyntax/OrIfStatementSyntax.h"
#include "../syntax/statements/ParameterSyntax/ParameterSyntax.h"
#include "../syntax/statements/ReturnStatementSyntax/ReturnStatementSyntax.h"
#include "../syntax/statements/StatementSyntax.h"
#include "../syntax/statements/VariableDeclarationSyntax/VariableDeclarationSyntax.h"
#include "../syntax/statements/WhileStatementSyntax/WhileStatementSyntax.h"
#include "../utils/Utils.h"
#define ONE_SPACE " "
#define TWO_SPACES "  "
#define TAB_SPACE "  "
#define NEW_LINE "\n"
class Parser {
public:
  std::vector<std::unique_ptr<SyntaxToken<std::any>>> tokens;

  std::unique_ptr<Lexer> lexer;

  Parser(const std::vector<std::string> &sourceCode,
         FLowWing::DiagnosticHandler *diagnosticHandler,
         std::unordered_map<std::string, int8_t> bringStatementPathsMap =
             std::unordered_map<std::string, int8_t>());
  ~Parser();

  std::unique_ptr<CompilationUnitSyntax> parseCompilationUnit();

  inline auto setIsFormattedCodeRequired(const bool isFormattedCodeRequired) {
    _isFormattedCodeRequired = isFormattedCodeRequired;
  }

  inline std::string getFormattedSourceCode() { return _formattedSourceCode; }

  inline auto getTokensRef()
      -> const std::vector<std::unique_ptr<SyntaxToken<std::any>>> & {
    return tokens;
  }

private:
  FLowWing::DiagnosticHandler *_diagnosticHandler;
  std::unique_ptr<CompilationUnitSyntax> compilationUnit;
  int position = 0;

  bool _isFormattedCodeRequired = false;

  bool matchKind(const SyntaxKindUtils::SyntaxKind &kind);
  void parseMemberList(std::vector<std::unique_ptr<MemberSyntax>> members);

  std::unique_ptr<SyntaxToken<std::any>>
  match(const SyntaxKindUtils::SyntaxKind &kind);
  SyntaxToken<std::any> *peek(const int &offset);
  SyntaxToken<std::any> *getCurrent();
  SyntaxKindUtils::SyntaxKind getKind();
  std::unique_ptr<SyntaxToken<std::any>> nextToken();
  std::string _formattedSourceCode = "";
  std::string INDENT = "";
  //

  inline void appendWithSpace() { _formattedSourceCode += ONE_SPACE; }
  inline void removeWithSpace() {
    _formattedSourceCode =
        _formattedSourceCode.erase(_formattedSourceCode.length() - 1, 1);
  }
  inline void appendNewLine() {
    if (this->getCurrent() &&
        this->getKind() != SyntaxKindUtils::SyntaxKind::CommentStatement) {
      _formattedSourceCode += NEW_LINE;
    } else
      appendWithSpace();
  }

  /*
    STATEMENTS
  */

  std::unique_ptr<StatementSyntax> parseStatement();
  std::unique_ptr<BlockStatementSyntax> parseBlockStatement();
  std::unique_ptr<BreakStatementSyntax> parseBreakStatement();
  std::unique_ptr<StatementSyntax> parseCommentStatement();
  std::unique_ptr<ReturnStatementSyntax> parseReturnStatement();
  std::unique_ptr<ContinueStatementSyntax> parseContinueStatement();
  std::unique_ptr<ExpressionStatementSyntax> parseExpressionStatement();
  std::unique_ptr<VariableDeclarationSyntax>
  parseVariableDeclaration(bool isFuncDec = false);
  std::unique_ptr<IfStatementSyntax> parseIfStatement();
  std::unique_ptr<ElseClauseSyntax> parseElseStatement();
  std::unique_ptr<WhileStatementSyntax> parseWhileStatement();
  std::unique_ptr<ForStatementSyntax> parseForStatement();
  std::unique_ptr<StatementSyntax> parseBringStatement();
  std::unique_ptr<CustomTypeStatementSyntax> parseCustomTypeStatement();
  std::unique_ptr<GlobalStatementSyntax>
  parseGlobalStatement(const bool &isExposed);
  std::unique_ptr<StatementSyntax> parseClassStatement();
  /*
    EXPRESSIONS
  */
  std::unique_ptr<ExpressionSyntax>
  parseIndexExpression(std::unique_ptr<SyntaxToken<std::any>> selfKeyword);
  std::unique_ptr<ExpressionSyntax>
  parseNameorCallExpression(std::unique_ptr<SyntaxToken<std::any>> selfKeyword);
  std::unique_ptr<ExpressionSyntax> parseCallExpression();
  std::unique_ptr<FunctionDeclarationSyntax>
  parseFunctionDeclaration(const bool &isExposed,
                           bool isMemberFunction = false);
  std::unique_ptr<FunctionDeclarationSyntax> handleOptionalType(
      std::unique_ptr<FunctionDeclarationSyntax> &functionDeclaration);
  std::unique_ptr<ExpressionSyntax> parseExpression(int parentPrecedence = 0);
  std::unique_ptr<ExpressionSyntax> parsePrimaryExpression();
  std::unique_ptr<ContainerExpressionSyntax> parseContainerExpression();
  std::unique_ptr<ExpressionSyntax>
  parseVariableExpression(std::unique_ptr<SyntaxToken<std::any>> selfKeyword);
  std::unique_ptr<ExpressionSyntax> parseBracketedExpression();
  std::unique_ptr<FillExpressionSyntax> parseFillExpression();
  std::unique_ptr<TypeExpressionSyntax> parseTypeExpression();
  std::unique_ptr<ArrayTypeExpressionSyntax> parseArrayTypeExpression();
  std::unique_ptr<ObjectTypeExpressionSyntax> parseObjectTypeExpression();
  std::unique_ptr<SyntaxToken<std::any>> parsePrimitiveType();
  std::unique_ptr<ObjectExpressionSyntax> parseObjectExpression();

  std::unordered_map<std::string, int8_t> _bringStatementsPathsMap;

  std::unique_ptr<MemberSyntax> parseMember();
};
#endif