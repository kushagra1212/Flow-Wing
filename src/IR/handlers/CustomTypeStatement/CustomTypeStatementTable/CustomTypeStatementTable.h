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


#ifndef FLOWWING_CUSTOM_TYPE_EXP_TABLE_H
#define FLOWWING_CUSTOM_TYPE_EXP_TABLE_H

#include "../../../../SemanticAnalyzer/BoundStatements/BoundCustomTypeStatement/BoundCustomTypeStatement.h"
#include "../../../../common/Common.h"

class CustomTypeStatementTable {
private:
  std::unordered_map<std::string, BoundCustomTypeStatement *> _type_exp_map;

public:
  inline BoundCustomTypeStatement *getExp(const std::string &name) {
    if (_type_exp_map.find(name) != _type_exp_map.end()) {
      return _type_exp_map[name];
    }
    return nullptr; // Not found
  }

  inline void setExp(const std::string &name, BoundCustomTypeStatement *value) {
    _type_exp_map[name] = value;
  }
};

#endif // FLOWWING_CUSTOM_TYPE_EXP_TABLE_H