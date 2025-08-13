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

#include <string>
#include <vector>

namespace DiagnosticUtils {
struct SourceLocation;
}

namespace SyntaxKindUtils {
enum SyntaxKind : int;
}

class SyntaxNode {
public:
  size_t lineNumber;
  size_t columnNumber;
  size_t length;
  std::string absoluteFilePath;
  std::vector<SyntaxNode *> _children;

  virtual ~SyntaxNode() = default;
  virtual SyntaxKindUtils::SyntaxKind getKind() const = 0;

  virtual const std::vector<SyntaxNode *> &getChildren() = 0;

  virtual const DiagnosticUtils::SourceLocation getSourceLocation() const = 0;
};