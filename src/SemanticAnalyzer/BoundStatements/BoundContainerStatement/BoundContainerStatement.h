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


#ifndef __BOUND_CONTAINER_STATEMENT_H__
#define __BOUND_CONTAINER_STATEMENT_H__

#include "../../../utils/Utils.h"
#include "../../BinderKindUtils.h"
#include "../../BoundExpressions/BoundContainerExpression/BoundContainerExpression.h"
#include "../../BoundExpressions/BoundExpression/BoundExpression.h"
#include "../../BoundExpressions/BoundLiteralExpression/BoundLiteralExpression.h"
#include "../../BoundNode.h"
#include "../../BoundSourceLocation/BoundSourceLocation.h"

class BoundContainerStatement : public BoundStatement,
                                public BoundSourceLocation {
private:
  Utils::type _type;
  std::string _variableName;
  std::vector<std::unique_ptr<BoundExpression>> _containerSizeExpressions;
  std::unique_ptr<BoundExpression> _containerExpression;

public:
  BoundContainerStatement(const DiagnosticUtils::SourceLocation &location,
                          const Utils::type &type, std::string variableName);

  /*
    Overrides
  */
  BinderKindUtils::BoundNodeKind getKind() const override;
  std::vector<BoundNode *> getChildren() override;

  /*
    Setters
  */
  inline void addContainerSizeExpression(
      std::unique_ptr<BoundExpression> containerSizeExpression) {
    this->_containerSizeExpressions.push_back(
        std::move(containerSizeExpression));
  }

  inline void
  setRHSExpression(std::unique_ptr<BoundExpression> containerExpression) {
    _containerExpression = std::move(containerExpression);
  }

  /*
    Getters
  */
  auto getVariableNameRef() const -> const std::string &;
  auto getContainerTypeRef() const -> const Utils::type &;
  inline auto getRHSExpressionRef() const
      -> const std::unique_ptr<BoundExpression> & {
    return _containerExpression;
  }

  inline auto getContainerSizeExpressions() const
      -> const std::vector<std::unique_ptr<BoundExpression>> & {
    return this->_containerSizeExpressions;
  }

  inline const std::vector<std::unique_ptr<BoundExpression>> &
  getContainerSizeExpressionsRef() const {
    return this->_containerSizeExpressions;
  }
};

#endif //  __BOUND_CONTAINER_STATEMENT_H__