/*
 * FlowWing Compiler
 * Copyright (C) 2023-2026 Kushagra Rathore
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

#pragma once

#include "src/syntax/SyntaxToken.h"
#include "src/syntax/expression/ExpressionSyntax.h"
#include <memory>
#include <unordered_map>
#include <vector>

namespace flow_wing {
namespace syntax {

class FunctionTypeExpressionSyntax : public ExpressionSyntax {

public:
  FunctionTypeExpressionSyntax(
      const SyntaxToken *open_bracket_token,
      const SyntaxToken *open_parenthesis_token,
      std::unordered_map<size_t, const syntax::SyntaxToken *>
          as_parameter_keywords_table,
      std::unordered_map<size_t, const syntax::SyntaxToken *>
          const_keyword_table,
      std::unordered_map<size_t, const syntax::SyntaxToken *>
          inout_keyword_table,
      std::vector<std::unique_ptr<syntax::ExpressionSyntax>> parameter_types,
      std::vector<const syntax::SyntaxToken *> parameter_comma_tokens,
      const syntax::SyntaxToken *close_parenthesis_token,
      const syntax::SyntaxToken *right_arrow_token,
      const syntax::SyntaxToken *as_return_keyword,
      std::vector<std::unique_ptr<syntax::ExpressionSyntax>> return_types,
      const syntax::SyntaxToken *close_bracket_token);

  // Overrides
  NodeKind getKind() const override;
  const std::vector<const SyntaxNode *> &getChildren() const override;
  void accept(visitor::ASTVisitor *visitor) override;

  // Getters
  const std::vector<std::unique_ptr<syntax::ExpressionSyntax>> &
  getParameterTypes() const;
  const std::vector<std::unique_ptr<syntax::ExpressionSyntax>> &
  getReturnTypes() const;
  const syntax::SyntaxToken *getAsReturnTypeKeyword() const;
  const std::unordered_map<size_t, const syntax::SyntaxToken *> &
  getAsParameterKeywordsTable() const;
  const std::unordered_map<size_t, const syntax::SyntaxToken *> &
  getConstantKeywordTable() const;
  const std::unordered_map<size_t, const syntax::SyntaxToken *> &
  getInoutKeywordTable() const;

  // Boolean queries
  bool hasAsReturnType() const;

private:
  const SyntaxToken *m_open_bracket_token;
  const SyntaxToken *m_open_parenthesis_token;
  std::unordered_map<size_t, const syntax::SyntaxToken *>
      m_as_parameter_keywords_table;
  std::unordered_map<size_t, const syntax::SyntaxToken *>
      m_constant_keyword_table;
  std::unordered_map<size_t, const syntax::SyntaxToken *> m_inout_keyword_table;

  std::vector<std::unique_ptr<syntax::ExpressionSyntax>> m_parameter_types;
  std::vector<const syntax::SyntaxToken *> m_parameter_comma_tokens;
  const syntax::SyntaxToken *m_close_parenthesis_token;
  const syntax::SyntaxToken *m_right_arrow_token;
  const syntax::SyntaxToken *m_as_return_keyword;
  std::vector<std::unique_ptr<syntax::ExpressionSyntax>> m_return_types;
  const syntax::SyntaxToken *m_close_bracket_token;

  mutable std::vector<const SyntaxNode *> m_children;
};

} // namespace syntax
} // namespace flow_wing