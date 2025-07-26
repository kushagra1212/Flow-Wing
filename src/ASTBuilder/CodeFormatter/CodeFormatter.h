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

#define ONE_SPACE " "
#define TWO_SPACES "  "
#define TAB_SPACE "  "
#define NEW_LINE "\n"

#include <string>

class ParserContext;

class CodeFormatter {
private:
  std::string _formattedSourceCode = "";
  ParserContext *parserCtx = nullptr;
  std::string _indentAmount = "";

public:
  CodeFormatter(ParserContext *parserCtx);

  void append(const std::string &str);
  void appendWithSpace();
  void appendNewLine();

  const std::string &getFormattedSourceCode();

  //? Handling Indentation

  void appendIndentAmount(const std::string &str);
  void setIndentAmount(const std::string &indentAmount);
  std::string getIndentAmount();
};
