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


#ifndef __FLOW__WING__OBJECT_TYPEEXPRESSIONSYNTAX_H__
#define __FLOW__WING__OBJECT_TYPEEXPRESSIONSYNTAX_H__

#include "../TypeExpressionSyntax.h"

class ObjectTypeExpressionSyntax : public TypeExpressionSyntax {
 private:
  std::unique_ptr<LiteralExpressionSyntax<std::any>> _objectTypeIdentifier;

 public:
  ObjectTypeExpressionSyntax(std::unique_ptr<SyntaxToken<std::any>> type);

  const virtual SyntaxKindUtils::SyntaxKind getKind() const override;
  const virtual std::vector<SyntaxNode *> &getChildren() override;
  const virtual DiagnosticUtils::SourceLocation getSourceLocation()
      const override;

  inline auto setObjectTypeIdentifier(
      std::unique_ptr<LiteralExpressionSyntax<std::any>> objectTypeIdentifier)
      -> void {
    this->_objectTypeIdentifier = std::move(objectTypeIdentifier);
  }

  inline auto getObjectTypeIdentifierRef()
      -> const std::unique_ptr<LiteralExpressionSyntax<std::any>> & {
    return this->_objectTypeIdentifier;
  }
};

#endif  // __FLOW__WING__OBJECT_TYPEEXPRESSIONSYNTAX_H__
