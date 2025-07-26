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

#include "src/common/Common.h"
#include "src/IR/handlers/CustomTypeStatement/CustomTypeStatementTable/CustomTypeStatementTable.h"

class CustomTypeStatementChain {
private:
  std::stack<std::unique_ptr<CustomTypeStatementTable>> handlers;

public:
  inline void addHandler(std::unique_ptr<CustomTypeStatementTable> handler) {
    handlers.push(std::move(handler));
  }

  inline void removeHandler() {
    if (!handlers.empty())
      handlers.pop();
  }

  BoundCustomTypeStatement *getExpr(const std::string &name);
  void setExpr(const std::string &name, BoundCustomTypeStatement *value);

  void setGlobalExpr(const std::string &name, BoundCustomTypeStatement *value);
};
