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

namespace DiagnosticUtils {

std::string toString(DiagnosticLevel level) {
  switch (level) {
  case DiagnosticLevel::Error:
    return "Error";
  case DiagnosticLevel::Warning:
    return "Warning";
  case DiagnosticLevel::Info:
    return "Info";
  case DiagnosticLevel::Debug:
    return "Debug";
  default:
    break;
  }
  return "Unknown";
}

std::string toString(DiagnosticType type) {
  switch (type) {
  case DiagnosticType::Lexical:
    return "Lexical";
  case DiagnosticType::Syntactic:
    return "Syntactic";
  case DiagnosticType::Semantic:
    return "Semantic";
  case DiagnosticType::CodeGen:
    return "CodeGen";
  case DiagnosticType::Runtime:
    return "Runtime";
  case DiagnosticType::Linker:
    return "Linker";
  case DiagnosticType::Fatal:
    return "Fatal";

  default:
    break;
  }
  return "Unknown";
}

} // namespace DiagnosticUtils