/*
 * Flow-Wing Compiler
 * Copyright © 2023-2026 Kushagra Rathore
 *
 * Inter-token spacing without retroactive `pop_back` for normal word gaps: the
 * visitor requests a single space, and the next *lexical* token append flushes
 * it once (forward-only, idempotent w.r.t. existing trailing whitespace).
 * Trivia and manual `+= "\n"` paths clear pending space so a newline is never
 * preceded by a stale requested gap.
 */
#pragma once

#include <string>
#include <string_view>

namespace flow_wing {
namespace compiler {
namespace format {

struct FormatBuffer {
  std::string text;
  /// Request one ASCII space before the next non-whitespace *token* body.
  bool interTokenSpacePending = false;

  void requestInterTokenSpace() { interTokenSpacePending = true; }
  void clearInterTokenSpace() { interTokenSpacePending = false; }

  void flushInterTokenSpaceIfNeeded() {
    if (!interTokenSpacePending)
      return;
    interTokenSpacePending = false;
    if (text.empty())
      return;
    const char b = text.back();
    if (b == ' ' || b == '\n' || b == '\t' || b == '\r')
      return;
    text += ' ';
  }

  void appendRawChar(char c) {
    if (c == '\n' || c == '\r')
      interTokenSpacePending = false;
    text += c;
  }
  void appendRaw(std::string_view sv) {
    if (sv.find_first_of("\n\r") != std::string_view::npos)
      interTokenSpacePending = false;
    text.append(sv.data(), sv.size());
  }
  void appendTokenLexeme(const std::string &lex) {
    flushInterTokenSpaceIfNeeded();
    text += lex;
  }
  void ensureSpaceIfNeeded() {
    if (text.empty() || text.back() == ' ' || text.back() == '\n')
      return;
    text += ' ';
  }
  void appendNewline() {
    interTokenSpacePending = false;
    text += '\n';
  }
};

} // namespace format
} // namespace compiler
} // namespace flow_wing
