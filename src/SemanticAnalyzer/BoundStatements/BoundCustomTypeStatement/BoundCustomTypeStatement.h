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


#ifndef __FLOW_BOUNDCUSTOMTYPESTATEMENT_H
#define __FLOW_BOUNDCUSTOMTYPESTATEMENT_H

#include "src/SemanticAnalyzer/BoundExpressions/BoundLiteralExpression/BoundLiteralExpression.h"
#include "src/SemanticAnalyzer/BoundExpressions/BoundTypeExpression/BoundTypeExpression.h"
#include "src/SemanticAnalyzer/BoundSourceLocation/BoundSourceLocation.h"
#include "src/SemanticAnalyzer/BoundStatements/BoundStatement/BoundStatement.h"

class BoundCustomTypeStatement : public BoundStatement,
                                 public BoundSourceLocation {
  std::unique_ptr<BoundLiteralExpression<std::any>> _typeName;
  std::vector<std::pair<std::unique_ptr<BoundLiteralExpression<std::any>>,
                        std::unique_ptr<BoundTypeExpression>>>
      _key_type_pairs;
  bool _isExposed;

public:
  BoundCustomTypeStatement(const DiagnosticUtils::SourceLocation &location,
                           bool isExposed);

  /*
    Setters
  */

  inline auto
  setTypeName(std::unique_ptr<BoundLiteralExpression<std::any>> typeName)
      -> void {
    this->_typeName = std::move(typeName);
  }

  inline auto
  addKeyTypePair(std::unique_ptr<BoundLiteralExpression<std::any>> key,
                 std::unique_ptr<BoundTypeExpression> type) -> void {
    this->_key_type_pairs.push_back(
        std::make_pair(std::move(key), std::move(type)));
  }

  inline auto setTypeNameAsString(std::string typeName) -> void {
    this->_typeName->setValue(typeName);
  }

  /*
    Getters
  */

  inline auto getTypeName()
      -> const std::unique_ptr<BoundLiteralExpression<std::any>> & {
    return this->_typeName;
  }
  inline auto getTypeNameAsString() -> const std::string {
    return std::any_cast<std::string>(this->_typeName->getValue());
  }

  inline auto getKeyPairs() -> const
      std::vector<std::pair<std::unique_ptr<BoundLiteralExpression<std::any>>,
                            std::unique_ptr<BoundTypeExpression>>> & {
    return this->_key_type_pairs;
  }

  inline auto getKeyValue(std::string key)
      -> std::tuple<BoundLiteralExpression<std::any> *, BoundTypeExpression *,
                    uint64_t> {
    uint64_t index = 0;
    for (auto &pair : this->_key_type_pairs) {
      if (std::any_cast<std::string>(pair.first->getValue()) == key) {
        return {pair.first.get(), pair.second.get(), index};
      }
      index++;
    }

    return {nullptr, nullptr, -1};
  }

  inline auto isExposed() -> bool { return this->_isExposed; }

public:
  BinderKindUtils::BoundNodeKind getKind() const override;
  std::vector<BoundNode *> getChildren() override;
};

#endif // __FLOW_BOUNDCUSTOMTYPESTATEMENT_H
