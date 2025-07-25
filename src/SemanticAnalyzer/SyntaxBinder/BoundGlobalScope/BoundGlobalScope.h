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


#ifndef BOUNDSCOPEGLOBAL_H
#define BOUNDSCOPEGLOBAL_H
#include "../../../common/Common.h"
#include "../../../diagnostics/DiagnosticHandler/DiagnosticHandler.h"
#include "../../../utils/Utils.h"
#include "../../BoundExpressions/BoundExpression/BoundExpression.h"
#include "../../BoundStatements/BoundClassStatement/BoundClassStatement.h"
#include "../../BoundStatements/BoundCustomTypeStatement/BoundCustomTypeStatement.h"
#include "../../BoundStatements/BoundFunctionDeclaration/BoundFunctionDeclaration.h"
#include "../../BoundStatements/BoundModuleStatement/BoundModuleStatement.h"
#include "../../BoundStatements/BoundStatement/BoundStatement.h"
#include "../../BoundStatements/BoundVariableDeclaration/BoundVariableDeclaration.h"
#include "../BoundScope/BoundScope.h"

class BoundGlobalScope {
public:
  BoundGlobalScope(std::unique_ptr<BoundGlobalScope> previous,
                   BoundScope *scope,
                   std::unordered_map<std::string, std::any> variablesValues,
                   FlowWing::DiagnosticHandler *diagnosticHandler,
                   std::unique_ptr<BoundBlockStatement> statement);

  bool tryLookupVariable(std::string name);
  bool tryAssignVariable(std::string name, BoundVariableDeclaration *value);
  BoundVariableDeclaration *getVariable(std::string name);

  bool tryLookupVariableValue(std::string name);

  bool tryAssignVariableValue(std::string name, std::any value);

  std::any getVariableValue(std::string name);

public:
  std::unique_ptr<BoundGlobalScope> previous;
  std::unordered_map<std::string, BoundVariableDeclaration *> variables;
  std::unordered_map<std::string, BoundCustomTypeStatement *> customTypes;
  std::unordered_map<std::string, BoundClassStatement *> classes;
  std::unordered_map<std::string, BoundModuleStatement *> modules;
  std::unordered_map<std::string, std::any> variablesValues;
  std::unordered_map<std::string, BoundFunctionDeclaration *> functions;
  FlowWing::DiagnosticHandler *_diagnosticHandler;
  std::unique_ptr<BoundBlockStatement> globalStatement;
};

#endif