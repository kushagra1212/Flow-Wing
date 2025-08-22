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


#include "CustomTypeStatementChain.h"

BoundCustomTypeStatement *
CustomTypeStatementChain::getExpr(const std::string &name) {
  std::stack<std::unique_ptr<CustomTypeStatementTable>> currentHandler;
  BoundCustomTypeStatement *exp = nullptr;

  std::string typeName = name.substr(0, name.find('.'));
  while (!handlers.empty()) {
    std::unique_ptr<CustomTypeStatementTable> &handler = handlers.top();
    exp = handler->getExp(typeName);
    if (exp) {
      break;
    }
    currentHandler.push(std::move(handler));
    handlers.pop();
  }

  while (!currentHandler.empty()) {
    handlers.push(std::move(currentHandler.top()));
    currentHandler.pop();
  }

  return exp;
}

void CustomTypeStatementChain::setExpr(const std::string &name,
                                       BoundCustomTypeStatement *value) {
  if (!handlers.empty()) {
    std::unique_ptr<CustomTypeStatementTable> &handler = handlers.top();
    handler->setExp(name, value);
  }
}

void CustomTypeStatementChain::setGlobalExpr(const std::string &name,
                                             BoundCustomTypeStatement *value) {
  std::stack<std::unique_ptr<CustomTypeStatementTable>> currentHandler;
  while (!handlers.empty()) {
    std::unique_ptr<CustomTypeStatementTable> &handler = handlers.top();
    currentHandler.push(std::move(handler));
    handlers.pop();
  }

  currentHandler.top()->setExp(name, value);

  while (!currentHandler.empty()) {
    handlers.push(std::move(currentHandler.top()));
    currentHandler.pop();
  }
}