/*
 * Flow-Wing Compiler
 * Copyright © 2023-2026 Kushagra Rathore
 *
 * Iterative Wadler-style layout: explicit stack for render and for `fits`,
 * avoiding deep C++ recursion on pathological `Doc` trees.
 */
#pragma once

#include "src/compiler/formatter/FormatDoc.hpp"

#include <cstdint>
#include <limits>
#include <string>
#include <vector>

namespace flow_wing {
namespace compiler {
namespace format {

struct LayoutWorkItem {
  int indent{};
  enum class Mode { Flat, Break } mode{Mode::Break};
  const Doc *doc{nullptr};
};

class LayoutEngine {
public:
  static std::string render(const Doc *root, int maxLineWidth = 80) {
    if (!root)
      return "\n";

    std::string output;
    output.reserve(8192);
    int currentColumn = 0;

    std::vector<LayoutWorkItem> stack;
    stack.push_back({0, LayoutWorkItem::Mode::Break, root});

    while (!stack.empty()) {
      LayoutWorkItem item = stack.back();
      stack.pop_back();

      const Doc *d = item.doc;
      if (!d)
        continue;

      switch (d->kind) {
      case Doc::Kind::Text: {
        output += d->text;
        currentColumn += static_cast<int>(d->text.size());
        break;
      }
      case Doc::Kind::Line: {
        if (item.mode == LayoutWorkItem::Mode::Flat) {
          output += ' ';
          currentColumn += 1;
        } else {
          output += '\n';
          output.append(static_cast<std::size_t>(item.indent), ' ');
          currentColumn = item.indent;
        }
        break;
      }
      case Doc::Kind::HardLine: {
        output += '\n';
        output.append(static_cast<std::size_t>(item.indent), ' ');
        currentColumn = item.indent;
        break;
      }
      case Doc::Kind::Nest: {
        if (!d->children.empty())
          stack.push_back(
              {item.indent + d->nestIndent, item.mode, d->children[0]});
        break;
      }
      case Doc::Kind::Concat: {
        for (auto it = d->children.rbegin(); it != d->children.rend(); ++it)
          stack.push_back({item.indent, item.mode, *it});
        break;
      }
      case Doc::Kind::Group: {
        LayoutWorkItem::Mode nextMode = item.mode;
        if (nextMode == LayoutWorkItem::Mode::Break && !d->children.empty()) {
          if (fits(currentColumn, maxLineWidth, item.indent, d->children[0]))
            nextMode = LayoutWorkItem::Mode::Flat;
        }
        if (!d->children.empty())
          stack.push_back({item.indent, nextMode, d->children[0]});
        break;
      }
      case Doc::Kind::IfBreak: {
        const std::string &textToEmit =
            (item.mode == LayoutWorkItem::Mode::Flat) ? d->ifbreakFlat
                                                        : d->ifbreakBreak;
        output += textToEmit;
        currentColumn += static_cast<int>(textToEmit.size());
        break;
      }
      }
    }

    if (output.empty() || output.back() != '\n')
      output += '\n';
    return output;
  }

private:
  struct FitsWorkItem {
    int indent{};
    LayoutWorkItem::Mode mode{LayoutWorkItem::Mode::Flat};
    const Doc *doc{nullptr};
  };

  static bool fits(int currentColumn, int maxWidth, int initialIndent,
                   const Doc *doc) {
    if (!doc)
      return true;

    int64_t remaining =
        static_cast<int64_t>(maxWidth) - static_cast<int64_t>(currentColumn);
    if (remaining < 0)
      return false;

    std::vector<FitsWorkItem> stack;
    stack.push_back({initialIndent, LayoutWorkItem::Mode::Flat, doc});

    while (!stack.empty()) {
      FitsWorkItem item = stack.back();
      stack.pop_back();

      const Doc *d = item.doc;
      if (!d)
        continue;

      if (remaining < 0)
        return false;

      switch (d->kind) {
      case Doc::Kind::Text:
        remaining -= static_cast<int64_t>(d->text.size());
        break;
      case Doc::Kind::Line:
        remaining -= 1;
        break;
      case Doc::Kind::HardLine:
        return false;
      case Doc::Kind::Nest:
        if (!d->children.empty())
          stack.push_back(
              {item.indent + d->nestIndent, item.mode, d->children[0]});
        break;
      case Doc::Kind::Concat:
        for (auto it = d->children.rbegin(); it != d->children.rend(); ++it)
          stack.push_back({item.indent, item.mode, *it});
        break;
      case Doc::Kind::Group:
        if (!d->children.empty())
          stack.push_back({item.indent, LayoutWorkItem::Mode::Flat,
                           d->children[0]});
        break;
      case Doc::Kind::IfBreak:
        remaining -= static_cast<int64_t>(d->ifbreakFlat.size());
        break;
      }
    }
    return remaining >= 0;
  }
};

/// Effectively infinite width: `Line` → space, `HardLine` → newline, groups
/// stay flat when they fit.
inline std::string renderDocFlat(const Doc *d) {
  return LayoutEngine::render(d, std::numeric_limits<int>::max());
}

inline std::string renderDocWithWidth(const Doc *d, std::size_t maxLineWidth) {
  if (!d)
    return "\n";
  if (maxLineWidth == 0U)
    return renderDocFlat(d);
  if (maxLineWidth >
      static_cast<std::size_t>(std::numeric_limits<int>::max()))
    return LayoutEngine::render(d, std::numeric_limits<int>::max());
  return LayoutEngine::render(d, static_cast<int>(maxLineWidth));
}

} // namespace format
} // namespace compiler
} // namespace flow_wing
