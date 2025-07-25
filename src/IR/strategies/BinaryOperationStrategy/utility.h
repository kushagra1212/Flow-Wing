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


#include "../../../SemanticAnalyzer/BoundExpressions/BoundBinaryExpression/BoundBinaryExpression.h"

namespace OperationSupport {

struct BoolStrategyTag {};
struct DoubleStrategyTag {};
struct FloatStrategyTag {};
struct Int8StrategyTag {};
struct Int32StrategyTag {};
struct NirastStrategyTag {};
struct StringStrategyTag {};
struct ClassStrategyTag {};
// Overload for Booleans
inline bool isSupported(BoolStrategyTag,
                        BinderKindUtils::BoundBinaryOperatorKind op) {
  switch (op) {
  case BinderKindUtils::BoundBinaryOperatorKind::Addition:
  case BinderKindUtils::BoundBinaryOperatorKind::Subtraction:
  case BinderKindUtils::BoundBinaryOperatorKind::Multiplication:
  case BinderKindUtils::BoundBinaryOperatorKind::Modulus:
  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseAnd:
  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseOr:
  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseXor:
  case BinderKindUtils::BoundBinaryOperatorKind::Division:
  case BinderKindUtils::BoundBinaryOperatorKind::LogicalAnd:
  case BinderKindUtils::BoundBinaryOperatorKind::LogicalOr:
  case BinderKindUtils::BoundBinaryOperatorKind::Equals:
  case BinderKindUtils::BoundBinaryOperatorKind::NotEquals:
  case BinderKindUtils::BoundBinaryOperatorKind::Less:
  case BinderKindUtils::BoundBinaryOperatorKind::LessOrEquals:
  case BinderKindUtils::BoundBinaryOperatorKind::Greater:
  case BinderKindUtils::BoundBinaryOperatorKind::GreaterOrEquals:
    return true;
  default:
    return false;
  }
}

// Overload for Doubles

inline bool isSupported(DoubleStrategyTag,
                        BinderKindUtils::BoundBinaryOperatorKind op) {
  switch (op) {
  case BinderKindUtils::BoundBinaryOperatorKind::Addition:
  case BinderKindUtils::BoundBinaryOperatorKind::Subtraction:
  case BinderKindUtils::BoundBinaryOperatorKind::Multiplication:
  case BinderKindUtils::BoundBinaryOperatorKind::Division:
  case BinderKindUtils::BoundBinaryOperatorKind::Equals:
  case BinderKindUtils::BoundBinaryOperatorKind::NotEquals:
  case BinderKindUtils::BoundBinaryOperatorKind::Less:
  case BinderKindUtils::BoundBinaryOperatorKind::LessOrEquals:
  case BinderKindUtils::BoundBinaryOperatorKind::Greater:
  case BinderKindUtils::BoundBinaryOperatorKind::GreaterOrEquals:
    return true;
  default:
    return false;
  }
}

// Overload for Floats
inline bool isSupported(FloatStrategyTag,
                        BinderKindUtils::BoundBinaryOperatorKind op) {
  return isSupported(DoubleStrategyTag{}, op);
}

// Overload for Integers
inline bool isSupported(Int32StrategyTag,
                        BinderKindUtils::BoundBinaryOperatorKind op) {
  switch (op) {
  case BinderKindUtils::BoundBinaryOperatorKind::Addition:
  case BinderKindUtils::BoundBinaryOperatorKind::Subtraction:
  case BinderKindUtils::BoundBinaryOperatorKind::Multiplication:
  case BinderKindUtils::BoundBinaryOperatorKind::IntegerDivision:
  case BinderKindUtils::BoundBinaryOperatorKind::Division:
  case BinderKindUtils::BoundBinaryOperatorKind::Modulus:
  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseAnd:
  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseOr:
  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseXor:
  case BinderKindUtils::BoundBinaryOperatorKind::LogicalAnd:
  case BinderKindUtils::BoundBinaryOperatorKind::LogicalOr:
  case BinderKindUtils::BoundBinaryOperatorKind::Equals:
  case BinderKindUtils::BoundBinaryOperatorKind::NotEquals:
  case BinderKindUtils::BoundBinaryOperatorKind::Less:
  case BinderKindUtils::BoundBinaryOperatorKind::LessOrEquals:
  case BinderKindUtils::BoundBinaryOperatorKind::Greater:
  case BinderKindUtils::BoundBinaryOperatorKind::GreaterOrEquals:
    return true;
  default:
    return false;
  }
}

// Overload for Int8

inline bool isSupported(Int8StrategyTag,
                        BinderKindUtils::BoundBinaryOperatorKind op) {
  return isSupported(Int32StrategyTag{}, op);
}

// Overload for Nirast
inline bool isSupported(NirastStrategyTag,
                        BinderKindUtils::BoundBinaryOperatorKind op) {
  switch (op) {
  case BinderKindUtils::BoundBinaryOperatorKind::Equals:
  case BinderKindUtils::BoundBinaryOperatorKind::NotEquals:
    return true;
  default:
    return false;
  }
}

// Overload for Strings
inline bool isSupported(StringStrategyTag,
                        BinderKindUtils::BoundBinaryOperatorKind op) {
  switch (op) {
  case BinderKindUtils::BoundBinaryOperatorKind::Addition:
  case BinderKindUtils::BoundBinaryOperatorKind::Equals:
  case BinderKindUtils::BoundBinaryOperatorKind::NotEquals:
  case BinderKindUtils::BoundBinaryOperatorKind::Less:
  case BinderKindUtils::BoundBinaryOperatorKind::LessOrEquals:
  case BinderKindUtils::BoundBinaryOperatorKind::Greater:
  case BinderKindUtils::BoundBinaryOperatorKind::GreaterOrEquals:
    return true;
  default:
    return false;
  }
}

// Overload for Class
inline bool isSupported(ClassStrategyTag,
                        BinderKindUtils::BoundBinaryOperatorKind op) {
  switch (op) {
  case BinderKindUtils::BoundBinaryOperatorKind::Equals:
  case BinderKindUtils::BoundBinaryOperatorKind::NotEquals:
  case BinderKindUtils::BoundBinaryOperatorKind::LogicalOr:
  case BinderKindUtils::BoundBinaryOperatorKind::LogicalAnd:
    return true;
  default:
    return false;
  }
}
} // namespace OperationSupport