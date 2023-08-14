#ifndef PARSER_H
#define PARSER_H
#include "../lexer/Lexer.h"
#include "../syntax/CompilationUnitSyntax.h"
#include "../syntax/MemberSyntax.h"
#include "../syntax/expression/AssignmentExpressionSyntax.h"
#include "../syntax/expression/BinaryExpressionSyntax.h"
#include "../syntax/expression/CallExpressionSyntax/CallExpressionSyntax.h"
#include "../syntax/expression/LiteralExpressionSyntax.h"
#include "../syntax/expression/ParenthesizedExpressionSyntax.h"
#include "../syntax/expression/UnaryExpressionSyntax.h"
#include "../syntax/expression/VariableExpressionSyntax.h"
#include "../syntax/statements/BlockStatementSyntax/BlockStatementSyntax.h"
#include "../syntax/statements/BreakStatementSyntax/BreakStatementSyntax.h"
#include "../syntax/statements/ContinueStatementSyntax/ContinueStatementSyntax.h"
#include "../syntax/statements/ExpressionStatementSyntax/ExpressionStatementSyntax.h"
#include "../syntax/statements/ForStatementSyntax/ForStatementSyntax.h"
#include "../syntax/statements/FunctionDeclarationSyntax/FunctionDeclarationSyntax.h"
#include "../syntax/statements/GlobalStatementSyntax/GlobalStatementSyntax.h"
#include "../syntax/statements/IfStatementSyntax/IfStatementSyntax.h"
#include "../syntax/statements/ParameterSyntax/ParameterSyntax.h"
#include "../syntax/statements/ReturnStatementSyntax/ReturnStatementSyntax.h"
#include "../syntax/statements/StatementSyntax.h"
#include "../syntax/statements/VariableDeclarationSyntax/VariableDeclarationSyntax.h"
#include "../syntax/statements/WhileStatementSyntax/WhileStatementSyntax.h"
#include "../utils/Utils.h"
#include <typeindex>
class Parser {
private:
  std::vector<std::shared_ptr<SyntaxToken<std::any>>> tokens;
  int position;

  std::shared_ptr<SyntaxToken<std::any>> peek(int offset);

  std::shared_ptr<SyntaxToken<std::any>> getCurrent();

  std::shared_ptr<SyntaxToken<std::any>> nextToken();

  std::shared_ptr<SyntaxToken<std::any>>
  match(SyntaxKindUtils::SyntaxKind kind);
  bool matchKind(SyntaxKindUtils::SyntaxKind kind);

  std::shared_ptr<StatementSyntax> parseStatement();
  std::shared_ptr<BlockStatementSyntax> parseBlockStatement();
  std::shared_ptr<BreakStatementSyntax> parseBreakStatement();
  std::shared_ptr<ReturnStatementSyntax> parseReturnStatement();
  std::shared_ptr<ContinueStatementSyntax> parseContinueStatement();
  std::shared_ptr<ExpressionStatementSyntax> parseExpressionStatement();
  std::shared_ptr<StatementSyntax> parseVariableDeclaration();
  std::shared_ptr<IfStatementSyntax> parseIfStatement();
  std::shared_ptr<WhileStatementSyntax> parseWhileStatement();

  std::shared_ptr<ForStatementSyntax> parseForStatement();

  std::shared_ptr<ExpressionSyntax> parseNameorCallExpression();

  std::vector<std::shared_ptr<MemberSyntax>> parseMemberList();

  std::shared_ptr<MemberSyntax> parseMember();

  std::shared_ptr<FunctionDeclarationSyntax> parseFunctionDeclaration();

  std::shared_ptr<GlobalStatementSyntax> parseGlobalStatement();

  std::shared_ptr<ExpressionSyntax> parseExpression(int parentPrecedence = 0);

  std::shared_ptr<ExpressionSyntax> parsePrimaryExpression();

public:
  std::vector<std::string> logs;

  std::shared_ptr<CompilationUnitSyntax> parseCompilationUnit();
  Parser(const std::vector<std::string> &text);
};
#endif