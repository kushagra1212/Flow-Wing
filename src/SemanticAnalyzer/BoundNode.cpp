/*
 * FlowWing Compiler
 * Copyright (C) 2023-2025 Kushagra Rathore
 */
#include "BoundNode.hpp"

namespace flow_wing {
namespace binding {

const flow_wing::diagnostic::SourceLocation &
BoundNode::getSourceLocation() const {
  return m_source_location;
}

} // namespace binding
} // namespace flow_wing
