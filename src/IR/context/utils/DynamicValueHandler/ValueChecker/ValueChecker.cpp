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


#include "ValueChecker.h"

namespace DYNAMIC_VALUE_HANDLER {
namespace VALUE_CHECKER {

int8_t isDynamicType(llvm::Type *type, CodeGenerationContext *ctx) {
  return llvm::StructType::getTypeByName(
             *ctx->getContext(), DYNAMIC_VALUE::TYPE::DYNAMIC_VALUE_TYPE) ==
         type;
}

int8_t isDynamicCompatibleType(llvm::Type *rhsType,
                               CodeGenerationContext *ctx) {
  if (ctx->getMapper()->isPrimitiveType(rhsType) ||
      rhsType == llvm::Type::getVoidTy(*ctx->getContext())) {
    return 1;
  }
  return 0;
}

} // namespace VALUE_CHECKER
} // namespace DYNAMIC_VALUE_HANDLER