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


#include "AllocaTable.h"

llvm::AllocaInst *AllocaTable::getAlloca(const std::string &name) {
  if (_allocas.find(name) != _allocas.end()) {
    return _allocas[name];
  }
  return nullptr; // Not found
}

bool AllocaTable::updateAlloca(const std::string &name,
                               llvm::AllocaInst *alloca) {
  if (_allocas.find(name) != _allocas.end()) {
    _allocas[name] = alloca;
    return true; // Updated
  }
  return false; // Not found
}

void AllocaTable::setAlloca(const std::string &name, llvm::AllocaInst *alloca) {
  _allocas[name] = alloca;
}

void AllocaTable::setTypeIndex(const std::string &name, uint64_t index) {
  _typeMap[name] = index;
}
uint64_t AllocaTable::getTypeIndex(const std::string &name) {
  return _typeMap[name];
}

bool AllocaTable::hasTypeIndex(const std::string &name) {
  return _typeMap.find(name) != _typeMap.end();
}

std::pair<llvm::Value *, llvm::Type *>
AllocaTable::getPtr(const std::string &name) {
  if (_ptrs.find(name) != _ptrs.end()) {
    return _ptrs[name];
  }
  return {};
}
bool AllocaTable::updatePtr(const std::string &name,
                            std::pair<llvm::Value *, llvm::Type *> ptr) {
  if (_ptrs.find(name) != _ptrs.end()) {
    _ptrs[name] = ptr;
    return true; // Updated
  }
  return false; // Not found
}
void AllocaTable::setPtr(const std::string &name,
                         std::pair<llvm::Value *, llvm::Type *> ptr) {
  _ptrs[name] = ptr;
}