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

#include <cstddef>

namespace flow_wing {
namespace diagnostic {

struct SourcePoint {
  size_t line_number = 0;
  size_t column_number = 0;

  SourcePoint() = default;
  SourcePoint(size_t line, size_t column)
      : line_number(line), column_number(column) {}

  bool operator<=(const SourcePoint &other) const {
    return line_number < other.line_number ||
           (line_number == other.line_number &&
            column_number <= other.column_number);
  }

  bool operator>=(const SourcePoint &other) const {
    return line_number > other.line_number ||
           (line_number == other.line_number &&
            column_number >= other.column_number);
  }
};

struct SourceLocation {
public:
  SourcePoint m_start;
  SourcePoint m_end;

  SourceLocation() = default;

  SourceLocation(size_t line, size_t column, size_t length)
      : m_start{line, column}, m_end{line, column + length} {}

  SourceLocation(SourcePoint start_point, SourcePoint end_point)
      : m_start(start_point), m_end(end_point) {}

  static SourceLocation span(const SourceLocation &start,
                             const SourceLocation &end) {
    return SourceLocation(start.m_start, end.m_end);
  }
};
} // namespace diagnostic
} // namespace flow_wing