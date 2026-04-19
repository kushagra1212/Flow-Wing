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

#include "FunctionStatementSyntax.h"
#include "src/ASTVisitor/ASTVisitor.hpp"
#include "src/syntax/SyntaxToken.h"
namespace flow_wing {
namespace syntax {

FunctionStatementSyntax::FunctionStatementSyntax(
    const SyntaxToken *fun_keyword,
    std::unique_ptr<ExpressionSyntax> function_identifier,
    const SyntaxToken *open_parenthesis_token,
    std::vector<std::unique_ptr<ExpressionSyntax>> function_parameters,
    std::vector<const SyntaxToken *> comma_tokens,
    const SyntaxToken *close_parenthesis_token,
    const SyntaxToken *right_arrow_token,
    std::unique_ptr<ExpressionSyntax> function_return_type_expression,
    const SyntaxToken *decl_keyword, std::unique_ptr<StatementSyntax> body)
    : m_fun_keyword(fun_keyword),
      m_function_identifier(std::move(function_identifier)),
      m_open_parenthesis_token(open_parenthesis_token),
      m_function_parameters(std::move(function_parameters)),
      m_comma_tokens(std::move(comma_tokens)),
      m_close_parenthesis_token(close_parenthesis_token),
      m_right_arrow_token(right_arrow_token),
      m_function_return_type_expression(
          std::move(function_return_type_expression)),
      m_decl_keyword(decl_keyword), m_body(std::move(body)) {}

syntax::NodeKind FunctionStatementSyntax::getKind() const {
  return NodeKind::kFunctionStatement;
}

void FunctionStatementSyntax::accept(visitor::ASTVisitor *visitor) {
  visitor->visit(this);
}

// Boolean queries

bool FunctionStatementSyntax::hasReturnType() const {
  return m_function_return_type_expression != nullptr;
}

bool FunctionStatementSyntax::hasBody() const { return m_body != nullptr; }

// Getters

const std::unique_ptr<ExpressionSyntax> &
FunctionStatementSyntax::getIdentifier() const {
  return m_function_identifier;
}

const std::vector<std::unique_ptr<ExpressionSyntax>> &
FunctionStatementSyntax::getParameters() const {
  return m_function_parameters;
}

const std::unique_ptr<ExpressionSyntax> &
FunctionStatementSyntax::getReturnType() const {
  return m_function_return_type_expression;
}

const std::unique_ptr<StatementSyntax> &
FunctionStatementSyntax::getBody() const {
  return m_body;
}

const std::vector<const SyntaxNode *> &
FunctionStatementSyntax::getChildren() const {
  if (m_children.empty()) {
    for (const auto *node :
         {static_cast<const SyntaxNode *>(m_fun_keyword),
          static_cast<const SyntaxNode *>(m_function_identifier.get()),
          static_cast<const SyntaxNode *>(m_open_parenthesis_token)}) {
      if (node) {
        m_children.push_back(node);
      }
    }
  }

  size_t max_size =
      std::max(m_function_parameters.size(), m_comma_tokens.size());

  for (size_t i = 0; i < max_size; i++) {
    if (i < m_function_parameters.size()) {
      m_children.push_back(m_function_parameters[i].get());
    }
    if (i < m_comma_tokens.size()) {
      m_children.push_back(m_comma_tokens[i]);
    }
  }

  for (const auto *node :
       {static_cast<const SyntaxNode *>(m_close_parenthesis_token),
        static_cast<const SyntaxNode *>(m_right_arrow_token),
        static_cast<const SyntaxNode *>(
            m_function_return_type_expression.get()),
        static_cast<const SyntaxNode *>(m_decl_keyword),
        static_cast<const SyntaxNode *>(m_body.get())}) {
    if (node) {
      m_children.push_back(node);
    }
  }
  return m_children;
}

} // namespace syntax
} // namespace flow_wing