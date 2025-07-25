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

#include "BoundExpressions/BoundCallExpression/BoundCallExpression.h"
#include "BoundExpressions/BoundVariableExpression/BoundVariableExpression.h"

class BoundUtils {
public:
  ~BoundUtils() = default;
  static BoundCallExpression *getCallExpression(BoundExpression *expression) {

    if (expression->getKind() ==
        BinderKindUtils::BoundNodeKind::CallExpression) {

      return static_cast<BoundCallExpression *>(expression);

    } else if (expression->getKind() ==
               BinderKindUtils::BoundNodeKind::VariableExpression) {

      BoundVariableExpression *variableExpression =
          static_cast<BoundVariableExpression *>(expression);

      for (auto &expr : variableExpression->getDotExpressionList()) {
        if (expr->getKind() == BinderKindUtils::BoundNodeKind::CallExpression) {
          return static_cast<BoundCallExpression *>(expr.get());
        }
      }
    }

    return nullptr;
  }
};