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

#include "src/IR/handlers/alloca/AllocaTable/AllocaTable.h"
#include "src/common/Common.h"
#include <memory>
#include <stack>

class AllocaChain {
private:
  std::stack<std::unique_ptr<AllocaTable>> handlers;
  std::unique_ptr<AllocaTable> _globalTable;

public:
  AllocaChain();
  void addHandler(std::unique_ptr<AllocaTable> handler);

  void removeHandler();

  llvm::AllocaInst *getAllocaInst(const std::string &name);

  bool updateAllocaInst(const std::string &name, llvm::AllocaInst *value);

  void setAllocaInst(const std::string &name, llvm::AllocaInst *value);

  void setTypeIndex(const std::string &name, uint64_t index);
  uint64_t getTypeIndex(const std::string &name);

  bool hasTypeIndex(const std::string &name);

  void setGlobalTypeIndex(const std::string &name, uint64_t index);
  uint64_t getGlobalTypeIndex(const std::string &name);
  std::pair<llvm::Value *, llvm::Type *> getPtr(const std::string name);

  bool updatePtr(const std::string &name,
                 std::pair<llvm::Value *, llvm::Type *> ptr);

  void setPtr(const std::string &name,
              std::pair<llvm::Value *, llvm::Type *> ptr);
};
