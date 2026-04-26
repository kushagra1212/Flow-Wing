/*
 * Flow-Wing Compiler
 * Copyright (C) 2023-2026 Kushagra Rathore
 *
 * AST-based source pretty-printer. Walks the concrete syntax tree in document
 * order, preserving comments via per-token leading trivia, and normalizing
 * indentation and top-level vertical spacing. Single pass over the tree,
 * O(n) in the number of syntax nodes; output buffer reserved from source size.
 */
#pragma once

#include "src/ASTVisitor/ASTVisitor.hpp"
#include "src/compiler/formatter/FormatBuffer.hpp"
#include "src/syntax/CompilationUnitSyntax.h"
#include "src/syntax/SyntaxNode.h"
#include "src/syntax/SyntaxToken.h"
#include "src/syntax/expression/ColonExpressionSyntax/ColonExpressionSyntax.h"
#include "src/syntax/expression/ErrorExpressionSyntax/ErrorExpressionSyntax.hpp"
#include <cstddef>
#include <memory>
#include <string>

namespace flow_wing {
namespace compiler {
namespace format {

class SourceFormatter final : public visitor::ASTVisitor {
public:
  static std::string
  format(const std::unique_ptr<syntax::CompilationUnitSyntax> &root,
         std::size_t sourceLengthHint = 0);

private:
  SourceFormatter() = default;

  FormatBuffer m_buf;
  int m_blockDepth = 0;
  /// After emitting a unary + / - / !, suppress a space before the operand's
  /// first token (e.g. `-100`, `!x`), while binary ops still get spacing.
  bool m_suppressSpaceBeforeNextToken = false;
  /// Nesting: function decl `(` … `)` and call `(` … `)` — drop
  /// kEndOfLineToken in leading trivia so split args in messy source rejoin
  /// (each entry increments; nested calls get depth > 1).
  int m_collapseEolParenListDepth = 0;
  /// return-expr, var/decl remainder — drop EOLs in leading trivia of tokens so
  /// `return\\n arr` / split decls rejoin to one line per construct.
  int m_collapseEolExpressionDepth = 0;
  /// Declarator / parameter / object-field `name: type` — strip stray spaces
  /// before `:`  so we emit `a: int` not `a : int` (ternary `:`  excluded).
  int m_tightTypeColonDepth = 0;
  /// Nesting of `[` / `]` array literals: depth 1 = outer; only outermost
  /// `[\n  …\n]` "block" style when a row itself contains a nested `[` … `]`.
  int m_bracketArrayLiteralNesting = 0;
  /// Last "real" token appended in `visitTokenCore` (not trivia-only fragments).
  const syntax::SyntaxToken *m_lastEmittedToken = nullptr;
  /// Emitted just before the current token (enables `) ->` vs `a->` without
  /// scanning the output for `)` / comment-spliced lookbehind).
  const syntax::SyntaxToken *m_prevEmittedToken = nullptr;

  static constexpr int kIndentSize = 4;

  bool controlKeywordWantsSpaceBeforeOpenParen() const;

  void visitChild(const syntax::SyntaxNode *node);
  void emitDefault(const syntax::SyntaxNode *node);
  void spaceBefore(const syntax::SyntaxToken *t);
  void emitLeadingTrivia(const syntax::SyntaxToken *t);
  void appendBlockIndent();
  void finishOutput();
  void trimTrailingLineSpacesInPlace();
  void visitTokenCore(syntax::SyntaxToken *t);

  void visit(syntax::SyntaxToken *node) override;
  void visit(syntax::ErrorExpressionSyntax *node) override;
  void visit(syntax::CompilationUnitSyntax *node) override;
  void visit(syntax::IdentifierExpressionSyntax *node) override;
  void visit(syntax::ParameterExpressionSyntax *node) override;
  void visit(syntax::DimensionClauseExpressionSyntax *node) override;
  void visit(syntax::IntegerLiteralExpressionSyntax *node) override;
  void visit(syntax::Int64LiteralExpressionSyntax *node) override;
  void visit(syntax::AssignmentExpressionSyntax *node) override;
  void visit(syntax::BooleanLiteralExpressionSyntax *node) override;
  void visit(syntax::BracketedExpressionSyntax *node) override;
  void visit(syntax::CallExpressionSyntax *node) override;
  void visit(syntax::CharacterLiteralExpressionSyntax *node) override;
  void visit(syntax::ContainerExpressionSyntax *node) override;
  void visit(syntax::DeclaratorExpressionSyntax *node) override;
  void visit(syntax::DoubleLiteralExpressionSyntax *node) override;
  void visit(syntax::FieldDeclarationSyntax *node) override;
  void visit(syntax::FillExpressionSyntax *node) override;
  void visit(syntax::FloatLiteralExpressionSyntax *node) override;
  void visit(syntax::FunctionReturnTypeExpressionSyntax *node) override;
  void visit(syntax::IndexExpressionSyntax *node) override;
  void visit(syntax::MemberAccessExpressionSyntax *node) override;
  void visit(syntax::ModuleAccessExpressionSyntax *node) override;
  void visit(syntax::NewExpressionSyntax *node) override;
  void visit(syntax::NirastExpressionSyntax *node) override;
  void visit(syntax::SuperExpressionSyntax *node) override;
  void visit(syntax::ObjectExpressionSyntax *node) override;
  void visit(syntax::ColonExpressionSyntax *node) override;
  void visit(syntax::ParenthesizedExpressionSyntax *node) override;
  void visit(syntax::StringLiteralExpressionSyntax *node) override;
  void visit(syntax::TemplateStringLiteralExpressionSyntax *node) override;
  void visit(syntax::TernaryExpressionSyntax *node) override;
  void visit(syntax::BinaryExpressionSyntax *node) override;
  void visit(syntax::CharTypeExpressionSyntax *node) override;
  void visit(syntax::ArrayTypeExpressionSyntax *node) override;
  void visit(syntax::BoolTypeExpressionSyntax *node) override;
  void visit(syntax::Deci32TypeExpressionSyntax *node) override;
  void visit(syntax::DeciTypeExpressionSyntax *node) override;
  void visit(syntax::FunctionTypeExpressionSyntax *node) override;
  void visit(syntax::Int8TypeExpressionSyntax *node) override;
  void visit(syntax::DynTypeExpressionSyntax *node) override;
  void visit(syntax::Int32TypeExpressionSyntax *node) override;
  void visit(syntax::Int64TypeExpressionSyntax *node) override;
  void visit(syntax::ModuleAccessTypeExpressionSyntax *node) override;
  void visit(syntax::NthgTypeExpressionSyntax *node) override;
  void visit(syntax::ObjectTypeExpressionSyntax *node) override;
  void visit(syntax::StrTypeExpressionSyntax *node) override;
  void visit(syntax::UnaryExpressionSyntax *node) override;
  void visit(syntax::ExposeStatementSyntax *node) override;
  void visit(syntax::BlockStatementSyntax *node) override;
  void visit(syntax::ExpressionStatementSyntax *node) override;
  void visit(syntax::FunctionStatementSyntax *node) override;
  void visit(syntax::BreakStatementSyntax *node) override;
  void visit(syntax::BringStatementSyntax *node) override;
  void visit(syntax::CaseStatementSyntax *node) override;
  void visit(syntax::ClassStatementSyntax *node) override;
  void visit(syntax::ContinueStatementSyntax *node) override;
  void visit(syntax::CustomTypeStatementSyntax *node) override;
  void visit(syntax::DefaultCaseStatementSyntax *node) override;
  void visit(syntax::ElseClauseSyntax *node) override;
  void visit(syntax::ForStatementSyntax *node) override;
  void visit(syntax::IfStatementSyntax *node) override;
  void visit(syntax::ModuleStatementSyntax *node) override;
  void visit(syntax::OrIfStatementSyntax *node) override;
  void visit(syntax::ReturnStatementSyntax *node) override;
  void visit(syntax::SwitchStatementSyntax *node) override;
  void visit(syntax::VariableDeclarationSyntax *node) override;
  void visit(syntax::WhileStatementSyntax *node) override;
};

} // namespace format
} // namespace compiler
} // namespace flow_wing
