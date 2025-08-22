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

#include "BoolTypeConverter/BoolTypeConverter.h"
#include "DoubleTypeConverter/DoubleTypeConverter.h"
#include "FloatTypeConverter/FloatTypeConverter.h"
#include "Int32TypeConverter/Int32TypeConverter.h"
#include "Int8TypeConverter/Int8TypeConverter.h"
#include "StringTypeConverter/StringTypeConverter.h"

class ValueVisitor {
public:
  virtual ~ValueVisitor() = default;
  virtual llvm::Value *visit(Int32TypeConverter *converter,
                             llvm::Value *&value) = 0;
  virtual llvm::Value *visit(DoubleTypeConverter *converter,
                             llvm::Value *&value) = 0;
  virtual llvm::Value *visit(BoolTypeConverter *converter,
                             llvm::Value *&value) = 0;

  virtual llvm::Value *visit(StringTypeConverter *converter,
                             llvm::Value *&value) = 0;

  virtual llvm::Value *visit(FloatTypeConverter *converter,
                             llvm::Value *&value) = 0;

  virtual llvm::Value *visit(Int8TypeConverter *converter,
                             llvm::Value *&value) = 0;
};
