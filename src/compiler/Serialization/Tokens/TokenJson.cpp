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


#include "TokenJson.hpp"
#include "src/syntax/SyntaxToken.h"

namespace flow_wing::compiler::serializer {

nlohmann::json TokenJson::toJson(
    const std::vector<std::unique_ptr<flow_wing::syntax::SyntaxToken>>
        &tokens) {
  nlohmann::json token_array;
  for (const auto &token : tokens) {
    token_array.push_back(toJsonToken(token.get()));
  }
  return {{"tokens", token_array}};
}

nlohmann::json
TokenJson::toJsonToken(const flow_wing::syntax::SyntaxToken *token) {
  return {{"type", toString(token->getTokenKind())},
          {"lexeme", token->getText()},
          {"range", toJsonRange(token->getSourceLocation())}};
}

nlohmann::json
TokenJson::toJsonRange(const flow_wing::diagnostic::SourceLocation &location) {
  return {{"start", toJsonSourcePoint(location.m_start)},
          {"end", toJsonSourcePoint(location.m_end)}};
}

nlohmann::json
TokenJson::toJsonSourcePoint(const flow_wing::diagnostic::SourcePoint &point) {
  return {{"line", point.line_number}, {"column", point.column_number}};
}

} // namespace flow_wing::compiler::serializer