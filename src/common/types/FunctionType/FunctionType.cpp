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



#include "src/common/types/FunctionType/FunctionType.hpp"
#include <sstream>

namespace flow_wing {
namespace types {

FunctionType::FunctionType(
    std::vector<std::shared_ptr<ParameterType>> parameters,
    std::vector<std::shared_ptr<ReturnType>> return_types,
    size_t default_value_start_index, bool is_variadic)
    : Type(buildFunctionName(parameters, return_types), TypeKind::kFunction),
      m_parameters(std::move(parameters)),
      m_return_types(std::move(return_types)),
      m_default_value_start_index(default_value_start_index),
      m_is_variadic(is_variadic) {}

bool FunctionType::operator==(const Type &other) const {
  if (other.getKind() != TypeKind::kFunction) {
    return false;
  }

  const auto *other_func = static_cast<const FunctionType *>(&other);

  if (m_return_types.size() != other_func->m_return_types.size()) {
    return false;
  }

  if (m_parameters.size() != other_func->m_parameters.size()) {
    return false;
  }

  for (size_t i = 0; i < m_parameters.size(); ++i) {
    if ((*m_parameters[i]->type != *other_func->m_parameters[i]->type)) {
      return false;
    }
  }

  for (size_t i = 0; i < m_return_types.size(); ++i) {
    if ((*m_return_types[i]->type != *other_func->m_return_types[i]->type)) {
      return false;
    }
  }

  return true;
}

std::string FunctionType::buildFunctionName(
    const std::vector<std::shared_ptr<ParameterType>> &params,
    const std::vector<std::shared_ptr<ReturnType>> &ret) {
  std::stringstream ss;
  ss << "Function: <(";
  for (size_t i = 0; i < params.size(); ++i) {
    ss << params[i]->type->getName();
    if (i < params.size() - 1) {
      ss << ", ";
    }
  }
  ss << ") -> ";
  for (size_t i = 0; i < ret.size(); ++i) {
    ss << ret[i]->type->getName();
    if (i < ret.size() - 1) {
      ss << ", ";
    }
  }
  ss << ">";
  return ss.str();
}

} // namespace types
} // namespace flow_wing