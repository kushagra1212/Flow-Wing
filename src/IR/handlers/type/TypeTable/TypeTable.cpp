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


#include "TypeTable.h"

llvm::StructType *TypeTable::getType(const std::string &name) {
  if (_type_map.find(name) != _type_map.end()) {
    return _type_map[name];
  }
  return nullptr;  // Not found
}

bool TypeTable::updateType(const std::string &name,
                           llvm::StructType *typeValue) {
  if (_type_map.find(name) != _type_map.end()) {
    _type_map[name] = typeValue;
    return true;  // Updated
  }
  return false;  // Not found
}
void TypeTable::setType(const std::string &name, llvm::StructType *typeValue) {
  _type_map[name] = typeValue;
}
