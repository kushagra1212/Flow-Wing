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

#include <llvm/IR/Module.h>

class IRParser {
public:
  IRParser();
  void mergeIR(const std::string &ir);
  void mergeIR(llvm::Module *module);

  const std::string &getIR() const;
  std::string getIR(llvm::Module *module);
  void removeDuplicates();
  std::string removeDuplicatesStartWithAndEndWith(const std::string &startWith,
                                                  const std::string &endWith);

  void printIR();

private:
  std::string _ir;
};
