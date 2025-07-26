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


#ifndef FLOWWING_TYPE_CHAIN_H
#define FLOWWING_TYPE_CHAIN_H

#include "src/common/Common.h"
#include "src/IR/handlers/type/TypeTable/TypeTable.h"

class TypeChain {
private:
  std::stack<std::unique_ptr<TypeTable>> handlers;

public:
  void addHandler(std::unique_ptr<TypeTable> handler);

  void removeHandler();

  llvm::StructType *getType(const std::string &name);
  bool updateType(const std::string &name, llvm::StructType *typeValue);
  void setType(const std::string &name, llvm::StructType *typeValue);

  size_t getIndex(const std::string &name);
  void setIndex(const std::string &name, size_t index);

  // Global

  void setGlobalType(const std::string &name, llvm::StructType *typeValue);
  void setGlobalIndex(const std::string &name, size_t index);
};

#endif // FLOWWING_TYPE_CHAIN_H