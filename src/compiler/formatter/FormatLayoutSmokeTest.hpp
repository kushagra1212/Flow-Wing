/*
 * Flow-Wing Compiler
 * Copyright (C) 2023-2026 Kushagra Rathore
 *
 * Dev-only: mock AST → `Doc` → `LayoutEngine::render`. Header-only so it links
 * without a CMake reconfigure for a new `.cpp`. Trigger from `FormatPass` with
 * `FLOWWING_FORMAT_LAYOUT_SMOKE=1`, or call from a debugger.
 */
#pragma once

#include "src/compiler/formatter/FormatDoc.hpp"
#include "src/compiler/formatter/LayoutEngine.hpp"

#include <memory>
#include <string>
#include <vector>

namespace flow_wing {
namespace compiler {
namespace format {
namespace format_layout_smoke {

struct MockNode {
  virtual ~MockNode() = default;
};

struct MockVarDecl : MockNode {
  std::string keyword;
  std::string name;
  std::string value;
};

struct MockCompilationUnit : MockNode {
  std::vector<std::unique_ptr<MockNode>> statements;
};

class MockFormatVisitor {
  DocArena &m_arena;
  Doc *m_current{nullptr};

public:
  explicit MockFormatVisitor(DocArena &a) : m_arena(a) {}

  Doc *dispatch(MockNode *node) {
    m_current = nullptr;
    if (auto *v = dynamic_cast<MockVarDecl *>(node)) {
      visitVarDecl(v);
    } else if (auto *c = dynamic_cast<MockCompilationUnit *>(node)) {
      visitCompilationUnit(c);
    }
    return m_current;
  }

private:
  void visitVarDecl(MockVarDecl *n) {
    m_current = m_arena.makeGroup(m_arena.makeConcat(
        {m_arena.makeText(n->keyword), m_arena.makeLine(), m_arena.makeText(n->name),
         m_arena.makeLine(), m_arena.makeText("="), m_arena.makeLine(),
         m_arena.makeText(n->value), m_arena.makeText(";")}));
  }

  void visitCompilationUnit(MockCompilationUnit *n) {
    std::vector<Doc *> parts;
    for (const auto &s : n->statements) {
      parts.push_back(dispatch(s.get()));
      parts.push_back(m_arena.makeHardLine());
    }
    m_current = m_arena.makeConcat(std::move(parts));
  }
};

} // namespace format_layout_smoke

/// Returns true if a mock `var totalCount = 100;` matches flat layout output.
inline bool runFormatLayoutEngineSmokeTest() {
  using namespace format_layout_smoke;
  auto cu = std::make_unique<MockCompilationUnit>();
  auto d = std::make_unique<MockVarDecl>();
  d->keyword = "var";
  d->name = "totalCount";
  d->value = "100";
  cu->statements.push_back(std::move(d));

  DocArena arena;
  MockFormatVisitor visitor(arena);
  Doc *root = visitor.dispatch(cu.get());
  if (!root) {
    return false;
  }
  const std::string flat = LayoutEngine::render(root, 80);
  return flat == "var totalCount = 100;\n";
}

} // namespace format
} // namespace compiler
} // namespace flow_wing
