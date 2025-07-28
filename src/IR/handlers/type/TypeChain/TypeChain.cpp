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

#include "TypeChain.h"

void TypeChain::addHandler(std::unique_ptr<TypeTable> handler) {
  handlers.push(std::move(handler));
}

void TypeChain::removeHandler() { handlers.pop(); }

llvm::StructType *TypeChain::getType(const std::string &name) {

  std::string typeName = name.substr(0, name.find('.'));

  std::stack<std::unique_ptr<TypeTable>> currentHandler;
  llvm::StructType *typeValue = nullptr;
  while (!handlers.empty()) {
    std::unique_ptr<TypeTable> &handler = handlers.top();
    typeValue = handler->getType(typeName);
    if (typeValue) {
      break;
    }

    currentHandler.push(std::move(handler));
    handlers.pop();
  }

  while (!currentHandler.empty()) {
    handlers.push(std::move(currentHandler.top()));
    currentHandler.pop();
  }

  return typeValue;
}

bool TypeChain::updateType(const std::string &name,
                           llvm::StructType *typeValue) {
  bool updated = false;
  std::stack<std::unique_ptr<TypeTable>> currentHandler;
  while (!handlers.empty()) {
    std::unique_ptr<TypeTable> &handler = handlers.top();
    if (handler->updateType(name, std::move(typeValue))) {
      updated = true;
      break;
    }
    currentHandler.push(std::move(handler));
    handlers.pop();
  }
  while (!currentHandler.empty()) {
    handlers.push(std::move(currentHandler.top()));
    currentHandler.pop();
  }

  return updated; // Not found in the chain
}

void TypeChain::setGlobalType(const std::string &name,
                              llvm::StructType *typeValue) {
  std::stack<std::unique_ptr<TypeTable>> currentHandler;

  while (!handlers.empty()) {
    std::unique_ptr<TypeTable> &handler = handlers.top();
    currentHandler.push(std::move(handler));
    handlers.pop();
  }
  currentHandler.top()->setType(name, typeValue);
  while (!currentHandler.empty()) {
    handlers.push(std::move(currentHandler.top()));
    currentHandler.pop();
  }
}

void TypeChain::setType(const std::string &name, llvm::StructType *typeValue) {
  if (!handlers.empty()) {
    std::unique_ptr<TypeTable> &handler = handlers.top();
    handler->setType(name, typeValue);
  }
}

size_t TypeChain::getIndex(const std::string &name) {
  std::stack<std::unique_ptr<TypeTable>> currentHandler;
  size_t index = -1;
  while (!handlers.empty()) {
    std::unique_ptr<TypeTable> &handler = handlers.top();
    index = handler->getIndex(name);
    if (index != static_cast<size_t>(-1)) {
      break;
    }
    currentHandler.push(std::move(handler));
    handlers.pop();
  }

  while (!currentHandler.empty()) {
    handlers.push(std::move(currentHandler.top()));
    currentHandler.pop();
  }

  return index;
}

void TypeChain::setGlobalIndex(const std::string &name, size_t index) {
  std::stack<std::unique_ptr<TypeTable>> currentHandler;

  while (!handlers.empty()) {
    std::unique_ptr<TypeTable> &handler = handlers.top();
    currentHandler.push(std::move(handler));
    handlers.pop();
  }
  currentHandler.top()->setIndex(name, index);
  while (!currentHandler.empty()) {
    handlers.push(std::move(currentHandler.top()));
    currentHandler.pop();
  }
}

void TypeChain::setIndex(const std::string &name, size_t index) {
  if (!handlers.empty()) {
    std::unique_ptr<TypeTable> &handler = handlers.top();
    handler->setIndex(name, index);
  }
}
