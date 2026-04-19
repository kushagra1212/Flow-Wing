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



#include "DiagnosticUtils.h"

namespace flow_wing {
namespace diagnostic {
namespace utils {

std::string toString(DiagnosticLevel level) {
  switch (level) {
  case DiagnosticLevel::kError:
    return "Error";
  case DiagnosticLevel::kWarning:
    return "Warning";
  case DiagnosticLevel::kInfo:
    return "Info";
  case DiagnosticLevel::kDebug:
    return "Debug";
  }
  return "Unknown";
}

std::string toString(DiagnosticType type) {
  switch (type) {
  case DiagnosticType::kLexical:
    return "Lexical";
  case DiagnosticType::kSyntactic:
    return "Syntactic";
  case DiagnosticType::kSemantic:
    return "Semantic";
  case DiagnosticType::kCodeGen:
    return "CodeGen";
  case DiagnosticType::kRuntime:
    return "Runtime";
  case DiagnosticType::kLinker:
    return "Linker";
  case DiagnosticType::kFatal:
    return "Fatal";
  case DiagnosticType::kFileSystem:
    return "File System";
  }
  return "Unknown";
}

} // namespace utils
} // namespace diagnostic
} // namespace flow_wing
