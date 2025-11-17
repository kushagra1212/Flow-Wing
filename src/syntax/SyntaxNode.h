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

#pragma once

#include "src/diagnostics/DiagnosticUtils/SourceLocation.h"
#include "src/syntax/NodeKind/NodeKind.h"
#include <optional>
#include <vector>

namespace flow_wing {

namespace visitor {
class ASTVisitor;
}

namespace syntax {

class SyntaxNode {

public:
  virtual ~SyntaxNode() = default;
  virtual NodeKind getKind() const = 0;
  virtual const std::vector<const SyntaxNode *> &getChildren() const = 0;
  virtual void accept(visitor::ASTVisitor *visitor) = 0;
  virtual const flow_wing::diagnostic::SourceLocation &
  getSourceLocation() const;

protected:
  SyntaxNode(const flow_wing::diagnostic::SourceLocation &source_location)
      : m_source_location(source_location) {}

  SyntaxNode() = default;

  static diagnostic::SourceLocation
  determineSpan(const std::vector<const SyntaxNode *> &nodes);

  mutable std::optional<flow_wing::diagnostic::SourceLocation>
      m_source_location;
};

} // namespace syntax

} // namespace flow_wing
