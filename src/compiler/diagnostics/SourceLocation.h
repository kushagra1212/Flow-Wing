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
#include <cstddef> // For size_t
#include <string>

namespace flow_wing {
namespace diagnostic {

// Structure to represent a specific location (a span of text)
struct SourceLocation {
public:
  size_t line_number;
  size_t column_number;
  size_t length;
  std::string absolute_file_path;

  SourceLocation()
      : line_number(0), column_number(0), length(0), absolute_file_path("") {}

  SourceLocation(size_t line, size_t column, size_t len,
                 const std::string &path)
      : line_number(line), column_number(column), length(len),
        absolute_file_path(std::move(path)) {}
};

} // namespace diagnostic
} // namespace flow_wing
