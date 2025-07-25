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


#ifndef DIAGNOSTIC_UTILS_H
#define DIAGNOSTIC_UTILS_H
#include <string>
namespace DiagnosticUtils {

enum class DiagnosticLevel { Error, Warning, Info, Debug };

enum class DiagnosticType {
  Lexical,
  Syntactic,
  Semantic,
  CodeGen,
  Runtime,
  Linker,
  Fatal
};

std::string toString(DiagnosticLevel level);

std::string toString(DiagnosticType type);

struct SourceLocation {
public:
  int lineNumber;
  int columnNumber;
  int length;
  std::string absoluteFilePath;

  SourceLocation() {
    this->lineNumber = 0;
    this->columnNumber = 0;
    this->absoluteFilePath = "";
  }

  SourceLocation(int lineNumber, int columnNumber, int length,
                 std::string absoluteFilePath) {
    this->lineNumber = lineNumber;
    this->columnNumber = columnNumber;
    this->length = length;
    this->absoluteFilePath = absoluteFilePath;
  }
};

} // namespace DiagnosticUtils

#endif // DIAGNOSTIC_UTILS_H