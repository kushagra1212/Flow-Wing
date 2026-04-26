/*
 * Flow-Wing Compiler
 * Copyright © 2023-2026 Kushagra Rathore
 *
 * Document IR for Wadler-style pretty-printing. Nodes are owned by `DocArena`
 * (bump vector of `unique_ptr`) — no `shared_ptr` refcount on the hot path.
 * The current AOT formatter still uses `FormatBuffer`; this tree backs a future
 * visitor that maps the AST → `Doc*`, then `LayoutEngine::render`.
 */
#pragma once

#include <cstddef>
#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace flow_wing {
namespace compiler {
namespace format {

struct Doc {
  enum class Kind { Text, Line, HardLine, Concat, Nest, Group, IfBreak } kind;

  std::string text;             // Text
  int nestIndent = 0;           // Nest
  std::vector<Doc *> children;  // Concat, Nest, Group
  std::string ifbreakFlat, ifbreakBreak; // IfBreak
};

/// Owns all `Doc` nodes for one format run. Not thread-safe.
class DocArena {
  std::vector<std::unique_ptr<Doc>> m_arena;

public:
  DocArena() { m_arena.reserve(4096); }

  Doc *makeText(std::string text) {
    auto d = std::make_unique<Doc>();
    d->kind = Doc::Kind::Text;
    d->text = std::move(text);
    m_arena.push_back(std::move(d));
    return m_arena.back().get();
  }

  Doc *makeLine() {
    auto d = std::make_unique<Doc>();
    d->kind = Doc::Kind::Line;
    m_arena.push_back(std::move(d));
    return m_arena.back().get();
  }

  Doc *makeHardLine() {
    auto d = std::make_unique<Doc>();
    d->kind = Doc::Kind::HardLine;
    m_arena.push_back(std::move(d));
    return m_arena.back().get();
  }

  Doc *makeConcat(std::vector<Doc *> parts) {
    if (parts.empty())
      return makeText("");
    if (parts.size() == 1U)
      return parts[0];
    auto d = std::make_unique<Doc>();
    d->kind = Doc::Kind::Concat;
    d->children = std::move(parts);
    m_arena.push_back(std::move(d));
    return m_arena.back().get();
  }

  Doc *makeNest(int indent, Doc *body) {
    if (!body)
      return makeText("");
    auto d = std::make_unique<Doc>();
    d->kind = Doc::Kind::Nest;
    d->nestIndent = indent;
    d->children = {body};
    m_arena.push_back(std::move(d));
    return m_arena.back().get();
  }

  Doc *makeGroup(Doc *body) {
    if (!body)
      return makeText("");
    auto d = std::make_unique<Doc>();
    d->kind = Doc::Kind::Group;
    d->children = {body};
    m_arena.push_back(std::move(d));
    return m_arena.back().get();
  }

  Doc *makeIfBreak(std::string flat, std::string br) {
    auto d = std::make_unique<Doc>();
    d->kind = Doc::Kind::IfBreak;
    d->ifbreakFlat = std::move(flat);
    d->ifbreakBreak = std::move(br);
    m_arena.push_back(std::move(d));
    return m_arena.back().get();
  }
};

} // namespace format
} // namespace compiler
} // namespace flow_wing
