/*
 * FlowWing Compiler
 * Copyright (C) 2023-2025 Kushagra Rathore
 */
#include "SyntaxNode.h"

namespace flow_wing {
namespace syntax {

const flow_wing::diagnostic::SourceLocation &
SyntaxNode::getSourceLocation() const {
  if (!m_source_location) {
    m_source_location = determineSpan(getChildren());
  }

  return m_source_location.value();
}

diagnostic::SourceLocation
SyntaxNode::determineSpan(const std::vector<const SyntaxNode *> &nodes) {
  const SyntaxNode *first_node = nullptr;
  const SyntaxNode *last_node = nullptr;

  for (const auto *node : nodes) {
    if (node) {
      if (!first_node) {
        first_node = node;
      } else {
        last_node = node;
      }
    }
  }

  if (first_node && last_node) {
    return diagnostic::SourceLocation::span(first_node->getSourceLocation(),
                                            last_node->getSourceLocation());
  }

  if (first_node) {
    return first_node->getSourceLocation();
  }

  return diagnostic::SourceLocation();
}

} // namespace syntax
} // namespace flow_wing
