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

#include "FunctionTypeExpressionSyntax.h"
#include "src/ASTVisitor/ASTVisitor.hpp"

namespace flow_wing {
namespace syntax {

FunctionTypeExpressionSyntax::FunctionTypeExpressionSyntax(
    const SyntaxToken *open_bracket_token,
    const SyntaxToken *open_parenthesis_token,
    std::unordered_map<size_t, const syntax::SyntaxToken *>
        as_parameter_keywords_table,
    std::unordered_map<size_t, const syntax::SyntaxToken *> const_keyword_table,
    std::unordered_map<size_t, const syntax::SyntaxToken *> inout_keyword_table,
    std::vector<std::unique_ptr<syntax::ExpressionSyntax>> parameter_types,
    std::vector<const syntax::SyntaxToken *> parameter_comma_tokens,
    const syntax::SyntaxToken *close_parenthesis_token,
    const syntax::SyntaxToken *right_arrow_token,
    const syntax::SyntaxToken *as_return_keyword,
    std::vector<std::unique_ptr<syntax::ExpressionSyntax>> return_types,
    const syntax::SyntaxToken *close_bracket_token)
    : m_open_bracket_token(open_bracket_token),
      m_open_parenthesis_token(open_parenthesis_token),
      m_as_parameter_keywords_table(std::move(as_parameter_keywords_table)),
      m_constant_keyword_table(std::move(const_keyword_table)),
      m_inout_keyword_table(std::move(inout_keyword_table)),
      m_parameter_types(std::move(parameter_types)),
      m_parameter_comma_tokens(std::move(parameter_comma_tokens)),
      m_close_parenthesis_token(close_parenthesis_token),
      m_right_arrow_token(right_arrow_token),
      m_as_return_keyword(as_return_keyword),
      m_return_types(std::move(return_types)),
      m_close_bracket_token(close_bracket_token) {}

NodeKind FunctionTypeExpressionSyntax::getKind() const {
  return NodeKind::kFunctionTypeExpression;
}

void FunctionTypeExpressionSyntax::accept(visitor::ASTVisitor *visitor) {
  visitor->visit(this);
}

const std::vector<std::unique_ptr<syntax::ExpressionSyntax>> &
FunctionTypeExpressionSyntax::getParameterTypes() const {
  return m_parameter_types;
}

const std::vector<std::unique_ptr<syntax::ExpressionSyntax>> &
FunctionTypeExpressionSyntax::getReturnTypes() const {
  return m_return_types;
}

const syntax::SyntaxToken *
FunctionTypeExpressionSyntax::getAsReturnTypeKeyword() const {
  return m_as_return_keyword;
}

const std::unordered_map<size_t, const syntax::SyntaxToken *> &
FunctionTypeExpressionSyntax::getAsParameterKeywordsTable() const {
  return m_as_parameter_keywords_table;
}

const std::unordered_map<size_t, const syntax::SyntaxToken *> &
FunctionTypeExpressionSyntax::getConstantKeywordTable() const {
  return m_constant_keyword_table;
}

const std::unordered_map<size_t, const syntax::SyntaxToken *> &
FunctionTypeExpressionSyntax::getInoutKeywordTable() const {
  return m_inout_keyword_table;
}

bool FunctionTypeExpressionSyntax::hasAsReturnType() const {
  return m_as_return_keyword != nullptr;
}

const std::vector<const SyntaxNode *> &
FunctionTypeExpressionSyntax::getChildren() const {

  if (m_children.empty()) {

    for (const auto *node : {
             static_cast<const SyntaxNode *>(m_open_bracket_token),
             static_cast<const SyntaxNode *>(m_open_parenthesis_token),
         }) {
      if (node)
        m_children.emplace_back(node);
    }

    size_t parameter_count = 0;
    for (auto &parameterType : m_parameter_types) {
      if (m_constant_keyword_table.count(parameter_count) > 0) {
        m_children.emplace_back(m_constant_keyword_table.at(parameter_count));
      }

      if (m_inout_keyword_table.count(parameter_count) > 0) {
        m_children.emplace_back(m_inout_keyword_table.at(parameter_count));
      }

      if (m_as_parameter_keywords_table.count(parameter_count) > 0) {
        m_children.emplace_back(
            m_as_parameter_keywords_table.at(parameter_count));
      }
      parameter_count++;
      m_children.emplace_back(parameterType.get());
    }

    for (auto &parameterCommaToken : m_parameter_comma_tokens) {
      if (parameterCommaToken)
        m_children.emplace_back(parameterCommaToken);
    }

    for (const auto *node : {
             static_cast<const SyntaxNode *>(m_close_parenthesis_token),
             static_cast<const SyntaxNode *>(m_right_arrow_token),
             static_cast<const SyntaxNode *>(m_as_return_keyword),
         }) {
      if (node)
        m_children.emplace_back(node);
    }

    for (auto &returnType : m_return_types) {
      m_children.push_back(returnType.get());
    }

    if (m_close_bracket_token)
      m_children.emplace_back(m_close_bracket_token);
  }

  return m_children;
}

} // namespace syntax
} // namespace flow_wing