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

#include "src/SemanticAnalyzer/NodeKind/NodeKind.h"
#include "src/diagnostics/DiagnosticUtils/SourceLocation.h"
#include <optional>

namespace flow_wing {

namespace binding {

class BoundNode {

public:
  virtual ~BoundNode() = default;
  virtual NodeKind getKind() const = 0;
  virtual const flow_wing::diagnostic::SourceLocation &
  getSourceLocation() const;

protected:
  BoundNode(const flow_wing::diagnostic::SourceLocation &source_location)
      : m_source_location(source_location) {}

  BoundNode() = default;

  flow_wing::diagnostic::SourceLocation m_source_location;
};

} // namespace binding

} // namespace flow_wing
