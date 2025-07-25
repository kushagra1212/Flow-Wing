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


#ifndef FLOWWING_ALLOCATABLE_H
#define FLOWWING_ALLOCATABLE_H

#include "../../../../common/Common.h"
#include "../AllocaHandler.h"
#include "../AllocaIndexHandler.h"

class AllocaTable : public AllocaHandler, public AllocaIndexHandler {
private:
  std::map<std::string, llvm::AllocaInst *> _allocas;

  std::map<std::string, std::pair<llvm::Value *, llvm::Type *>> _ptrs;
  std::unordered_map<std::string, uint64_t> _typeMap;

public:
  llvm::AllocaInst *getAlloca(const std::string &name) override;
  bool updateAlloca(const std::string &name, llvm::AllocaInst *alloca) override;
  void setAlloca(const std::string &name, llvm::AllocaInst *alloca) override;

  void setTypeIndex(const std::string &name, uint64_t index) override;
  uint64_t getTypeIndex(const std::string &name) override;
  bool hasTypeIndex(const std::string &name) override;

  std::pair<llvm::Value *, llvm::Type *> getPtr(const std::string &name);
  bool updatePtr(const std::string &name,
                 std::pair<llvm::Value *, llvm::Type *> ptr);
  void setPtr(const std::string &name,
              std::pair<llvm::Value *, llvm::Type *> ptr);
};

#endif // FLOWWING_ALLOCATABLE_H