
#pragma once

#include "src/common/types/Type.hpp"
#include <memory>
#include <vector>

namespace flow_wing {
namespace types {

enum class ValueKind {
  kByValue,     // (a: int)
  kByReference, // (inout a: int)
};

enum class TypeConvention {
  kFlowWing, // (a: int)
  kC,        // (a: as int)
};

// const or not
enum class Constness {
  kConst,
  kMutable,
};

std::string toString(ValueKind value_kind);
std::string toString(TypeConvention type_convention);
std::string toString(Constness constness);

struct ParameterType {
  std::shared_ptr<types::Type> type;
  ValueKind value_kind;
  TypeConvention type_convention;
  Constness constness;

  ParameterType(std::shared_ptr<types::Type> type,
                ValueKind value_kind = ValueKind::kByValue,
                TypeConvention type_convention = TypeConvention::kFlowWing,
                Constness constness = Constness::kMutable)
      : type(type), value_kind(value_kind), type_convention(type_convention),
        constness(constness) {}

  bool equals(const ParameterType &other) const {
    return value_kind == other.value_kind &&
           type_convention == other.type_convention && *type == *other.type;
  }
};

struct ReturnType {
  std::shared_ptr<types::Type> type;
  TypeConvention type_convention;

  ReturnType(std::shared_ptr<types::Type> type,
             TypeConvention type_convention = TypeConvention::kFlowWing)
      : type(type), type_convention(type_convention) {}

  bool equals(const ReturnType &other) const {
    return type_convention == other.type_convention && *type == *other.type;
  }
};

class FunctionType : public Type {
public:
  FunctionType(std::vector<std::shared_ptr<ParameterType>> parameters,
               std::vector<std::shared_ptr<ReturnType>> return_types,
               size_t default_value_start_index = static_cast<size_t>(-1),
               bool is_variadic = false, bool is_external = false);

  const std::vector<std::shared_ptr<ParameterType>> &getParameterTypes() const {
    return m_parameters;
  }
  const std::vector<std::shared_ptr<ReturnType>> &getReturnTypes() const {
    return m_return_types;
  }
  void addReturnType(std::shared_ptr<ReturnType> return_type) {
    m_return_types.push_back(std::move(return_type));
  }
  bool isVariadic() const { return m_is_variadic; }
  size_t getDefaultValueStartIndex() const {
    return m_default_value_start_index;
  }

  bool isExternal() const { return m_is_external; }

  bool operator==(const Type &other) const override;

private:
  std::vector<std::shared_ptr<ParameterType>> m_parameters;
  std::vector<std::shared_ptr<ReturnType>> m_return_types;
  size_t m_default_value_start_index;
  bool m_is_variadic;
  bool m_is_external;

  static std::string
  buildFunctionName(const std::vector<std::shared_ptr<ParameterType>> &params,
                    const std::vector<std::shared_ptr<ReturnType>> &ret);
};

} // namespace types
} // namespace flow_wing