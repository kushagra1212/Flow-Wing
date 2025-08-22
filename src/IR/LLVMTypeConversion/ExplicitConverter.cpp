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


#include "ExplicitConverter.h"

namespace FlowWing {

namespace EXPLICIT_CONVERTER {
llvm::Value *explicitConvertLLVMValueTo(llvm::Value *value, llvm::Type *type,
                                        CodeGenerationContext *context) {
  std::unique_ptr<GenerationStrategy> generationStrategy =
      std::make_unique<GenerationStrategy>(context);

  TypeMapper *_typeMapper = context->getMapper().get();

  if (_typeMapper->isStringType(type)) {
    return generationStrategy->_typeSpecificValueVisitor->visit(
        generationStrategy->_stringTypeConverter.get(), value);
  } else if (_typeMapper->isInt32Type(type)) {
    return generationStrategy->_typeSpecificValueVisitor->visit(
        generationStrategy->_int32TypeConverter.get(), value);
  } else if (_typeMapper->isInt8Type(type)) {
    return generationStrategy->_typeSpecificValueVisitor->visit(
        generationStrategy->_int8TypeConverter.get(), value);
  } else if (_typeMapper->isDoubleType(type)) {
    return generationStrategy->_typeSpecificValueVisitor->visit(
        generationStrategy->_doubleTypeConverter.get(), value);
  } else if (_typeMapper->isFloatType(type)) {
    return generationStrategy->_typeSpecificValueVisitor->visit(
        generationStrategy->_floatTypeConverter.get(), value);
  } else if (_typeMapper->isBoolType(type)) {
    return generationStrategy->_typeSpecificValueVisitor->visit(
        generationStrategy->_boolTypeConverter.get(), value);
  }

  return value;
}
} // namespace EXPLICIT_CONVERTER

} // namespace FlowWing