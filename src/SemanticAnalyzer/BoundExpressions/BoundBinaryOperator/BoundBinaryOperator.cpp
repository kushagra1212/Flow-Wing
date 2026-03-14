/*
 * FlowWing Compiler
 * Copyright (C) 2023-2026 Kushagra Rathore
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

#include "BoundBinaryOperator.hpp"
#include "src/SemanticAnalyzer/Builtins/Builtins.hpp"
#include "src/common/types/CustomObjectType/CustomObjectType.hpp"
#include "src/utils/LogConfig.h"

namespace flow_wing {

namespace binding {

namespace type_conversion {
void initializeIntegerExplicitConversionMap(
    BoundBinaryOperator::ExplicitConversionMap &explicit_conversion_map) {
  explicit_conversion_map[analysis::Builtins::m_int32_type_instance.get()] = {
      analysis::Builtins::m_char_type_instance.get(),
      analysis::Builtins::m_bool_type_instance.get(),
      analysis::Builtins::m_int8_type_instance.get(),
      analysis::Builtins::m_int64_type_instance.get(),
      analysis::Builtins::m_deci32_type_instance.get(),
      analysis::Builtins::m_deci_type_instance.get(),
      analysis::Builtins::m_str_type_instance.get(),
  };

  explicit_conversion_map[analysis::Builtins::m_int64_type_instance.get()] = {
      analysis::Builtins::m_bool_type_instance.get(),
      analysis::Builtins::m_int8_type_instance.get(),
      analysis::Builtins::m_int32_type_instance.get(),
      analysis::Builtins::m_char_type_instance.get(),
      analysis::Builtins::m_deci32_type_instance.get(),
      analysis::Builtins::m_deci_type_instance.get(),
      analysis::Builtins::m_str_type_instance.get(),
  };

  explicit_conversion_map[analysis::Builtins::m_int8_type_instance.get()] = {
      analysis::Builtins::m_bool_type_instance.get(),
      analysis::Builtins::m_int32_type_instance.get(),
      analysis::Builtins::m_char_type_instance.get(),
      analysis::Builtins::m_int64_type_instance.get(),
      analysis::Builtins::m_deci32_type_instance.get(),
      analysis::Builtins::m_deci_type_instance.get(),
      analysis::Builtins::m_str_type_instance.get(),
  };
}

void initializeDecimalExplicitConversionMap(
    BoundBinaryOperator::ExplicitConversionMap &explicit_conversion_map) {
  explicit_conversion_map[analysis::Builtins::m_deci_type_instance.get()] = {
      analysis::Builtins::m_deci32_type_instance.get(),
      analysis::Builtins::m_bool_type_instance.get(),
      analysis::Builtins::m_int8_type_instance.get(),
      analysis::Builtins::m_int32_type_instance.get(),
      analysis::Builtins::m_int64_type_instance.get(),
      analysis::Builtins::m_str_type_instance.get(),
  };

  explicit_conversion_map[analysis::Builtins::m_deci32_type_instance.get()] = {
      analysis::Builtins::m_deci_type_instance.get(),
      analysis::Builtins::m_bool_type_instance.get(),
      analysis::Builtins::m_int8_type_instance.get(),
      analysis::Builtins::m_int32_type_instance.get(),
      analysis::Builtins::m_int64_type_instance.get(),
      analysis::Builtins::m_str_type_instance.get(),
  };
}

void initializeBoolExplicitConversionMap(
    BoundBinaryOperator::ExplicitConversionMap &explicit_conversion_map) {
  explicit_conversion_map[analysis::Builtins::m_bool_type_instance.get()] = {
      analysis::Builtins::m_int8_type_instance.get(),
      analysis::Builtins::m_int32_type_instance.get(),
      analysis::Builtins::m_int64_type_instance.get(),
      analysis::Builtins::m_deci32_type_instance.get(),
      analysis::Builtins::m_deci_type_instance.get(),
      analysis::Builtins::m_str_type_instance.get(),
  };
}

void initializeStringExplicitConversionMap(
    BoundBinaryOperator::ExplicitConversionMap &explicit_conversion_map) {
  explicit_conversion_map[analysis::Builtins::m_str_type_instance.get()] = {
      analysis::Builtins::m_bool_type_instance.get(),
      analysis::Builtins::m_char_type_instance.get(),
      analysis::Builtins::m_int8_type_instance.get(),
      analysis::Builtins::m_int32_type_instance.get(),
      analysis::Builtins::m_int64_type_instance.get(),
      analysis::Builtins::m_deci32_type_instance.get(),
      analysis::Builtins::m_deci_type_instance.get(),
  };
}

void initializeCharExplicitConversionMap(
    BoundBinaryOperator::ExplicitConversionMap &explicit_conversion_map) {
  explicit_conversion_map[analysis::Builtins::m_char_type_instance.get()] = {
      analysis::Builtins::m_str_type_instance.get(),
      analysis::Builtins::m_deci32_type_instance.get(),
      analysis::Builtins::m_deci_type_instance.get(),
      analysis::Builtins::m_bool_type_instance.get(),
      analysis::Builtins::m_int32_type_instance.get(),
      analysis::Builtins::m_int64_type_instance.get(),
      analysis::Builtins::m_int8_type_instance.get()};
}

BoundBinaryOperator::ExplicitConversionMap initializeExplicitConversionMap() {
  BoundBinaryOperator::ExplicitConversionMap explicit_conversion_map;

  initializeIntegerExplicitConversionMap(explicit_conversion_map);
  initializeDecimalExplicitConversionMap(explicit_conversion_map);
  initializeBoolExplicitConversionMap(explicit_conversion_map);
  initializeCharExplicitConversionMap(explicit_conversion_map);
  return explicit_conversion_map;
}
} // namespace type_conversion

namespace type_conversion {

void updateWithBothOperandTypes(std::vector<BoundBinaryOperator> &operators,
                                lexer::TokenKind token,
                                std::shared_ptr<types::Type> type,
                                std::shared_ptr<types::Type> other_type,
                                std::shared_ptr<types::Type> result_type) {

  operators.emplace_back(token, type, other_type, result_type);
  if (type == other_type) {
    return;
  }
  operators.emplace_back(token, other_type, type, result_type);
}

void initializeNirastOperators(std::vector<BoundBinaryOperator> &operators) {
  for (const auto &token : {lexer::TokenKind::kEqualsEqualsToken,
                            lexer::TokenKind::kBangEqualsToken}) {

    operators.emplace_back(token, analysis::Builtins::m_nirast_type_instance,
                           analysis::Builtins::m_nirast_type_instance,
                           analysis::Builtins::m_bool_type_instance);
  }
}

void initializeStringOperators(std::vector<BoundBinaryOperator> &operators) {

  for (const auto &other_type : {analysis::Builtins::m_int32_type_instance,
                                 analysis::Builtins::m_int8_type_instance,
                                 analysis::Builtins::m_str_type_instance,
                                 analysis::Builtins::m_char_type_instance,
                                 analysis::Builtins::m_int64_type_instance,
                                 analysis::Builtins::m_deci32_type_instance,
                                 analysis::Builtins::m_deci_type_instance,
                                 analysis::Builtins::m_bool_type_instance}) {

    updateWithBothOperandTypes(operators, lexer::TokenKind::kPlusToken,
                               analysis::Builtins::m_str_type_instance,
                               other_type,
                               analysis::Builtins::m_str_type_instance);
  }

  for (const auto &token :
       {lexer::TokenKind::kEqualsEqualsToken,
        lexer::TokenKind::kBangEqualsToken, lexer::TokenKind::kLessToken,
        lexer::TokenKind::kLessOrEqualsToken, lexer::TokenKind::kGreaterToken,
        lexer::TokenKind::kGreaterOrEqualsToken}) {

    operators.emplace_back(token, analysis::Builtins::m_str_type_instance,
                           analysis::Builtins::m_str_type_instance,
                           analysis::Builtins::m_bool_type_instance);
  }
}

void initializeCharOperators(std::vector<BoundBinaryOperator> &operators) {

  for (const auto &other_type : {analysis::Builtins::m_int32_type_instance,
                                 analysis::Builtins::m_int8_type_instance,
                                 analysis::Builtins::m_str_type_instance,
                                 analysis::Builtins::m_int64_type_instance,
                                 analysis::Builtins::m_deci32_type_instance,
                                 analysis::Builtins::m_deci_type_instance,
                                 analysis::Builtins::m_bool_type_instance}) {

    updateWithBothOperandTypes(operators, lexer::TokenKind::kPlusToken,
                               analysis::Builtins::m_char_type_instance,
                               other_type,
                               analysis::Builtins::m_char_type_instance);
  }

  updateWithBothOperandTypes(operators, lexer::TokenKind::kPlusToken,
                             analysis::Builtins::m_char_type_instance,
                             analysis::Builtins::m_char_type_instance,
                             analysis::Builtins::m_str_type_instance);

  for (const auto &token :
       {lexer::TokenKind::kEqualsEqualsToken,
        lexer::TokenKind::kBangEqualsToken, lexer::TokenKind::kLessToken,
        lexer::TokenKind::kLessOrEqualsToken, lexer::TokenKind::kGreaterToken,
        lexer::TokenKind::kGreaterOrEqualsToken}) {

    operators.emplace_back(token, analysis::Builtins::m_char_type_instance,
                           analysis::Builtins::m_char_type_instance,
                           analysis::Builtins::m_bool_type_instance);
  }
}

void initializeDecimalOperators(std::vector<BoundBinaryOperator> &operators) {

  auto deci32_type = analysis::Builtins::m_deci32_type_instance;
  auto deci_type = analysis::Builtins::m_deci_type_instance;

  std::vector<std::shared_ptr<types::Type>> decimal_types = {deci32_type,
                                                             deci_type};

  for (size_t i = 0; i < decimal_types.size(); ++i) {
    for (size_t j = i; j < decimal_types.size(); ++j) {
      auto t1 = decimal_types[i];
      auto t2 = decimal_types[j];

      for (const auto &token : {
               lexer::TokenKind::kPlusToken,
               lexer::TokenKind::kMinusToken,
               lexer::TokenKind::kStarToken,
               lexer::TokenKind::kSlashToken,
           }) {
        updateWithBothOperandTypes(operators, token, t1, t2, t1);
      }

      for (const auto &token :
           {lexer::TokenKind::kEqualsEqualsToken,
            lexer::TokenKind::kBangEqualsToken, lexer::TokenKind::kLessToken,
            lexer::TokenKind::kLessOrEqualsToken,
            lexer::TokenKind::kGreaterToken,
            lexer::TokenKind::kGreaterOrEqualsToken}) {
        updateWithBothOperandTypes(operators, token, t1, t2,
                                   analysis::Builtins::m_bool_type_instance);
      }
    }
  }
}

void initializeBoolOperators(std::vector<BoundBinaryOperator> &operators) {
  for (const auto &token :
       {lexer::TokenKind::kAmpersandAmpersandToken,
        lexer::TokenKind::kPipePipeToken, lexer::TokenKind::kEqualsEqualsToken,
        lexer::TokenKind::kBangEqualsToken, lexer::TokenKind::kLessToken,
        lexer::TokenKind::kLessOrEqualsToken, lexer::TokenKind::kGreaterToken,
        lexer::TokenKind::kGreaterOrEqualsToken}) {
    operators.emplace_back(token, analysis::Builtins::m_bool_type_instance,
                           analysis::Builtins::m_bool_type_instance,
                           analysis::Builtins::m_bool_type_instance);
  }
}

void initializeIntegerOperators(std::vector<BoundBinaryOperator> &operators) {
  // 1. Get Type Instances
  auto int8 = analysis::Builtins::m_int8_type_instance;
  auto int32 = analysis::Builtins::m_int32_type_instance;
  auto int64 = analysis::Builtins::m_int64_type_instance;
  auto deci32 = analysis::Builtins::m_deci32_type_instance;
  auto deci = analysis::Builtins::m_deci_type_instance;
  auto boolean = analysis::Builtins::m_bool_type_instance;

  std::vector<std::shared_ptr<types::Type>> intTypes = {int8, int32, int64};

  std::vector<lexer::TokenKind> arithmetic_operators = {
      lexer::TokenKind::kPlusToken,    lexer::TokenKind::kMinusToken,
      lexer::TokenKind::kStarToken,    lexer::TokenKind::kSlashSlashToken,
      lexer::TokenKind::kPercentToken, lexer::TokenKind::kAmpersandToken,
      lexer::TokenKind::kPipeToken,    lexer::TokenKind::kCaretToken};

  std::vector<lexer::TokenKind> comparison_operators = {
      lexer::TokenKind::kEqualsEqualsToken,
      lexer::TokenKind::kBangEqualsToken,
      lexer::TokenKind::kLessToken,
      lexer::TokenKind::kLessOrEqualsToken,
      lexer::TokenKind::kGreaterToken,
      lexer::TokenKind::kGreaterOrEqualsToken};

  for (size_t i = 0; i < intTypes.size(); ++i) {
    for (size_t j = i; j < intTypes.size(); ++j) {
      auto t1 = intTypes[i];
      auto t2 = intTypes[j];

      auto resultType = (t1 == int64 || t2 == int64) ? int64 : int32;

      for (auto op : arithmetic_operators) {
        updateWithBothOperandTypes(operators, op, t1, t2, resultType);
      }

      auto divResultType = (t1 == int64 || t2 == int64) ? deci : deci32;
      updateWithBothOperandTypes(operators, lexer::TokenKind::kSlashToken, t1,
                                 t2, divResultType);

      for (auto op : comparison_operators) {
        updateWithBothOperandTypes(operators, op, t1, t2, boolean);
      }
    }
  }

  for (auto t : intTypes) {
    for (const auto &token : {
             lexer::TokenKind::kPlusToken,
             lexer::TokenKind::kMinusToken,
             lexer::TokenKind::kStarToken,
             lexer::TokenKind::kSlashToken,
         }) {
      updateWithBothOperandTypes(operators, token, t, deci32,
                                 t != int64 ? deci32 : deci);

      updateWithBothOperandTypes(operators, token, t, deci, deci);
    }
  }
}

BoundBinaryOperator::OperatorMap initializeOperatorMap() {
  std::vector<BoundBinaryOperator> operators = {};

  // Nirast
  initializeNirastOperators(operators);

  // String (str => +, Comparisons, and other types)
  initializeStringOperators(operators);

  // Char (char => +, Comparisons, and other types)
  initializeCharOperators(operators);

  // Decimal (deci, deci32 => +, -, *, /, Comparisons)
  initializeDecimalOperators(operators);

  // Bool (Comparisons)
  initializeBoolOperators(operators);

  // Char (char => +, Comparisons)
  initializeCharOperators(operators);

  // Integer (int8, int32, int64)
  initializeIntegerOperators(operators);

  BoundBinaryOperator::OperatorMap map;
  for (const auto &op : operators) {
    map.emplace(BinaryOperatorKey{op.getSyntaxKind(), op.getLeftType().get(),
                                  op.getRightType().get()},
                std::make_shared<BoundBinaryOperator>(
                    op.getSyntaxKind(), op.getLeftType(), op.getRightType(),
                    op.getResultType()));
  }
  return map;
}
} // namespace type_conversion

BoundBinaryOperator::ExplicitConversionMap
    BoundBinaryOperator::s_explicit_conversion_map =
        type_conversion::initializeExplicitConversionMap();

BoundBinaryOperator::BoundBinaryOperator(
    lexer::TokenKind syntax_kind, std::shared_ptr<types::Type> left_type,
    std::shared_ptr<types::Type> right_type,
    std::shared_ptr<types::Type> result_type)
    : m_syntax_kind(syntax_kind), m_left_type(std::move(left_type)),
      m_right_type(std::move(right_type)),
      m_result_type(std::move(result_type)) {}

// The static map, initialized once using the helper

std::shared_ptr<BoundBinaryOperator>
BoundBinaryOperator::bind(lexer::TokenKind operator_kind,
                          std::shared_ptr<types::Type> left_type,
                          std::shared_ptr<types::Type> right_type) {

  // Reject nthg (void) in binary operations
  if (left_type->isNthg() || right_type->isNthg()) {
    return nullptr;
  }

  // Handling Exceptional Cases
  if ((left_type->isDynamic() && right_type->isDynamic()) ||
      (left_type->isDynamic() && right_type->isPrimitive()) ||
      (left_type->isPrimitive() && right_type->isDynamic())) {
    return std::make_shared<BoundBinaryOperator>(
        operator_kind, left_type, right_type,
        analysis::Builtins::m_dynamic_type_instance);
  }

  if (left_type->getKind() == types::TypeKind::kClass ||
      right_type->getKind() == types::TypeKind::kClass) {
    return bindClassType(operator_kind, left_type, right_type);
  }

  if (left_type->getKind() == types::TypeKind::kObject ||
      right_type->getKind() == types::TypeKind::kObject) {
    return bindObjectType(operator_kind, left_type, right_type);
  }

  // Handling Normal Cases
  BinaryOperatorKey key = {operator_kind, left_type.get(), right_type.get()};
  auto &operator_map = getOperatorMap();
  auto it = operator_map.find(key);
  if (it != operator_map.end()) {
    return it->second;
  }

  // Handling Type Conversion Cases
  for (const auto &target_type : {analysis::Builtins::m_str_type_instance,
                                  analysis::Builtins::m_deci32_type_instance,
                                  analysis::Builtins::m_deci_type_instance,
                                  analysis::Builtins::m_int64_type_instance,
                                  analysis::Builtins::m_int32_type_instance,
                                  analysis::Builtins::m_int8_type_instance,
                                  analysis::Builtins::m_bool_type_instance}) {
    if (left_type == target_type || right_type == target_type) {
      return bindType(operator_kind, left_type, right_type, target_type);
    }
  }

  return nullptr;
}

bool BoundBinaryOperator::canConvert(types::Type *from_type,
                                     types::Type *to_type) {
  if (from_type == to_type) {
    return true;
  }

  auto it = s_explicit_conversion_map.find(from_type);
  if (it != s_explicit_conversion_map.end()) {
    return it->second.find(to_type) != it->second.end();
  }

  return false;
}

std::shared_ptr<BoundBinaryOperator>
BoundBinaryOperator::bindType(lexer::TokenKind operator_kind,
                              std::shared_ptr<types::Type> left_type,
                              std::shared_ptr<types::Type> right_type,
                              std::shared_ptr<types::Type> to_type) {

  auto left_converts = canConvert(left_type.get(), to_type.get());
  auto right_converts = canConvert(right_type.get(), to_type.get());

  if (left_converts && right_converts) {

    BinaryOperatorKey key = {operator_kind, to_type.get(), to_type.get()};
    auto &operator_map = getOperatorMap();
    auto it = operator_map.find(key);
    if (it != operator_map.end()) {
      return it->second;
    }
  }

  BINDER_DEBUG_LOG(
      "bindType(operator_kind, left_type, right_type, to_type): %s, %s, %s, %s",
      lexer::toString(operator_kind), left_type->getName(),
      right_type->getName(), to_type->getName());
  return nullptr;
}

const BoundBinaryOperator::OperatorMap &BoundBinaryOperator::getOperatorMap() {
  // initialized the first time this function is called.
  static BoundBinaryOperator::OperatorMap map =
      type_conversion::initializeOperatorMap();
  return map;
}

std::shared_ptr<BoundBinaryOperator>
BoundBinaryOperator::bindClassType(lexer::TokenKind operator_kind,
                                   std::shared_ptr<types::Type> left_type,
                                   std::shared_ptr<types::Type> right_type) {

  if (!((left_type->getKind() == types::TypeKind::kClass ||
         left_type == analysis::Builtins::m_nirast_type_instance) &&
        (right_type->getKind() == types::TypeKind::kClass ||
         right_type == analysis::Builtins::m_nirast_type_instance))) {

    return nullptr;
  }

  switch (operator_kind) {
  case lexer::TokenKind::kEqualsEqualsToken:
  case lexer::TokenKind::kBangEqualsToken:
  case lexer::TokenKind::kPipePipeToken:
  case lexer::TokenKind::kAmpersandAmpersandToken: {

    return std::make_shared<BoundBinaryOperator>(
        operator_kind, left_type, right_type,
        analysis::Builtins::m_bool_type_instance);
  }
  default:
    return nullptr;
  }
}

std::shared_ptr<BoundBinaryOperator>
BoundBinaryOperator::bindObjectType(lexer::TokenKind operator_kind,
                                    std::shared_ptr<types::Type> left_type,
                                    std::shared_ptr<types::Type> right_type) {

  if (!((left_type->getKind() == types::TypeKind::kObject ||
         left_type == analysis::Builtins::m_nirast_type_instance) &&
        (right_type->getKind() == types::TypeKind::kObject ||
         right_type == analysis::Builtins::m_nirast_type_instance))) {

    return nullptr;
  }

  switch (operator_kind) {
  case lexer::TokenKind::kEqualsEqualsToken:
  case lexer::TokenKind::kBangEqualsToken: {
    return std::make_shared<BoundBinaryOperator>(
        operator_kind, left_type, right_type,
        analysis::Builtins::m_bool_type_instance);
  }
  default:
    return nullptr;
  }
}

} // namespace binding
} // namespace flow_wing