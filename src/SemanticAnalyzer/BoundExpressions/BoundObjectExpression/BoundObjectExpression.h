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

#include "src/SemanticAnalyzer/BoundExpressions/BoundExpression/BoundExpression.h"
#include "src/SemanticAnalyzer/BoundExpressions/BoundLiteralExpression/BoundLiteralExpression.h"
#include <any>
#include <memory>
#include <vector>

class BoundObjectExpression : public BoundExpression {
  std::vector<std::pair<std::unique_ptr<BoundLiteralExpression<std::any>>,
                        std::unique_ptr<BoundExpression>>>
      _key_value_pairs;

public:
  BoundObjectExpression(const DiagnosticUtils::SourceLocation &location);

  /*
    Overrides
  */

  BinderKindUtils::BoundNodeKind getKind() const override;
  std::vector<BoundNode *> getChildren() override;
  inline virtual const std::type_info &getType() override {
    return typeid(BoundObjectExpression);
  }
  /*
    Setters
  */

  inline auto
  addKeyValuePair(std::unique_ptr<BoundLiteralExpression<std::any>> key,
                  std::unique_ptr<BoundExpression> value) -> void {
    this->_key_value_pairs.push_back(
        std::make_pair(std::move(key), std::move(value)));
  }

  /*
    Getters
  */

  inline auto getKeyValuePairs() -> const
      std::vector<std::pair<std::unique_ptr<BoundLiteralExpression<std::any>>,
                            std::unique_ptr<BoundExpression>>> & {
    return this->_key_value_pairs;
  }
};
