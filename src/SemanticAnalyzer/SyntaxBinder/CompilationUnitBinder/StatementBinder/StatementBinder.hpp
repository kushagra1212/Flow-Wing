#pragma once

#include "src/SemanticAnalyzer/BoundStatements/BoundStatement/BoundStatement.h"
#include <memory>
namespace flow_wing {

namespace syntax {
class StatementSyntax;

// -- Custom Type Statements --
class CustomTypeStatementSyntax;
// -- Expose Statement --
class ExposeStatementSyntax;
// -- If Statement --
class IfStatementSyntax;
// -- Block Statement --
class BlockStatementSyntax;
// -- Function Statement --
class FunctionStatementSyntax;
// -- Variable Declaration Statement --
class VariableDeclarationSyntax;
// -- Custom Type Statement --
class CustomTypeStatementSyntax;
// -- While Statement --
class WhileStatementSyntax;
// -- For Statement --
class ForStatementSyntax;
// -- Break Statement --
class BreakStatementSyntax;
// -- Continue Statement --
class ContinueStatementSyntax;
// -- Return Statement --
class ReturnStatementSyntax;
// -- Bring Statement --
class SwitchStatementSyntax;
// -- Class Statement --
class ClassStatementSyntax;
// -- Expression Statement --
class ExpressionStatementSyntax;
} // namespace syntax

namespace binding {
class BinderContext;
class ExpressionBinder;

class StatementBinder {
public:
  StatementBinder(BinderContext *context, ExpressionBinder *expression_binder);

  std::unique_ptr<BoundStatement> bind(syntax::StatementSyntax *statement);

private:
  BinderContext *m_context;
  ExpressionBinder *m_expression_binder;

  // -- Binders
  std::unique_ptr<BoundStatement>
  bindBlockStatement(syntax::BlockStatementSyntax *statement);
  std::unique_ptr<BoundStatement>
  bindFunctionStatement(syntax::FunctionStatementSyntax *statement);
  std::unique_ptr<BoundStatement>
  bindVariableDeclaration(syntax::VariableDeclarationSyntax *statement);

  // -- Custom Type Statements --
  std::unique_ptr<BoundStatement>
  bindCustomTypeStatement(syntax::CustomTypeStatementSyntax *statement);

  // -- Expose Statement --
  std::unique_ptr<BoundStatement>
  bindExposeStatement(syntax::ExposeStatementSyntax *statement);

  // -- If Statement --
  std::unique_ptr<BoundStatement>
  bindIfStatement(syntax::IfStatementSyntax *statement);

  // -- While Statement --
  std::unique_ptr<BoundStatement>
  bindWhileStatement(syntax::WhileStatementSyntax *statement);

  // -- For Statement --
  std::unique_ptr<BoundStatement>
  bindForStatement(syntax::ForStatementSyntax *statement);

  // -- Break Statement --
  std::unique_ptr<BoundStatement>
  bindBreakStatement(syntax::BreakStatementSyntax *statement);

  // -- Continue Statement --
  std::unique_ptr<BoundStatement>
  bindContinueStatement(syntax::ContinueStatementSyntax *statement);

  // -- Return Statement --
  std::unique_ptr<BoundStatement>
  bindReturnStatement(syntax::ReturnStatementSyntax *statement);

  // -- Bring Statement --
  std::unique_ptr<BoundStatement>
  bindSwitchStatement(syntax::SwitchStatementSyntax *statement);

  // -- Class Statement --
  std::unique_ptr<BoundStatement>
  bindClassStatement(syntax::ClassStatementSyntax *statement);

  // -- Expression Statement --
  std::unique_ptr<BoundStatement>
  bindExpressionStatement(syntax::ExpressionStatementSyntax *statement);
};
} // namespace binding
} // namespace flow_wing