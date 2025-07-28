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

#include "SyntaxBinderContext.h"

SyntaxBinderContext::SyntaxBinderContext(
    std::unique_ptr<BoundScope> parent,
    FlowWing::DiagnosticHandler *diagnosticHandler)
    : _root(std::make_unique<BoundScope>(std::move(parent))),
      _diagnosticHandler(diagnosticHandler) {
  BuiltInFunction::setupBuiltInFunctions();
}

//? Getters

FlowWing::DiagnosticHandler *SyntaxBinderContext::getDiagnosticHandler() {
  return _diagnosticHandler;
}

bool SyntaxBinderContext::doesModuleAlreadyExist(
    const std::string &moduleName) {
  return _moduleDependencyMap.find(moduleName) != _moduleDependencyMap.end();
}

const std::string &SyntaxBinderContext::getCurrentModuleName() {
  return _currentModuleName;
}

std::unique_ptr<BoundScope> &SyntaxBinderContext::getRootRef() { return _root; }

//? Setters

void SyntaxBinderContext::updateModuleDependencyMap(
    const std::string &moduleName, const bool &dependencyStatus) {
  _moduleDependencyMap[moduleName] = dependencyStatus;
}

void SyntaxBinderContext::setCurrentModuleName(const std::string &moduleName) {
  _currentModuleName = moduleName;
}

void SyntaxBinderContext::insertScope() {
  _root = std::make_unique<BoundScope>(std::move(_root));
}

void SyntaxBinderContext::removeScope() { _root = std::move(_root->parent); }

void SyntaxBinderContext::updateBoundScope(
    std::unique_ptr<BoundGlobalScope> &scope) {
  _root->variables = scope->variables;
  _root->functions = scope->functions;
  _root->customTypes = scope->customTypes;
  _root->classes = scope->classes;
  _root->modules = scope->modules;
}