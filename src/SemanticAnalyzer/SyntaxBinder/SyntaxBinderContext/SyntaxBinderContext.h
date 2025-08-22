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

#include "src/SemanticAnalyzer/SyntaxBinder/BoundGlobalScope/BoundGlobalScope.h"
#include "src/SemanticAnalyzer/SyntaxBinder/BoundScope/BoundScope.h"
#include "src/diagnostics/DiagnosticHandler/DiagnosticHandler.h"
#include "src/utils/BuiltInFunction/BuiltInFunction.h"
#include <string>

class SyntaxBinderContext {
  std::unique_ptr<BoundScope> _root;
  FlowWing::DiagnosticHandler *_diagnosticHandler;
  std::string _currentModuleName;
  std::unordered_map<std::string, bool> _moduleDependencyMap;

public:
  SyntaxBinderContext(std::unique_ptr<BoundScope> parent,
                      FlowWing::DiagnosticHandler *diagnosticHandler);

  //? Getters

  FlowWing::DiagnosticHandler *getDiagnosticHandler();
  bool doesModuleAlreadyExist(const std::string &moduleName);
  const std::string &getCurrentModuleName();
  std::unique_ptr<BoundScope> &getRootRef();

  //? Setters
  void updateModuleDependencyMap(const std::string &moduleName,
                                 const bool &dependencyStatus);
  void setCurrentModuleName(const std::string &moduleName);
  void updateBoundScope(std::unique_ptr<BoundGlobalScope> &scope);
  void insertScope();
  void removeScope();
};
