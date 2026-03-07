
#pragma once

#include "src/common/types/Type.hpp"
#include <cstddef>
#include <map>
#include <memory>

namespace flow_wing {
namespace types {

class CustomObjectType : public Type {
public:
  CustomObjectType(
      const std::string &custom_type_name,
      const std::map<std::string, std::shared_ptr<Type>> &field_types_map,
      bool is_pre_declared = false);

  bool operator==(const Type &other) const override;
  bool operator<=(const Type &other) const override;

  const std::string &getCustomTypeName() const;
  const std::map<std::string, std::shared_ptr<Type>> &getFieldTypesMap() const;
  void setFieldTypesMap(
      std::map<std::string, std::shared_ptr<Type>> field_types_map);
  void setPreDeclared(bool is_pre_declared);

  bool isObjectExpression() const;
  bool isPreDeclared() const;

private:
  std::string m_custom_type_name;
  std::map<std::string, std::shared_ptr<Type>> m_field_types_map;
  bool m_is_pre_declared = false;

  std::string buildCustomObjectTypeName(
      const std::string &custom_type_name,
      const std::map<std::string, std::shared_ptr<Type>> &field_types_map);
};

} // namespace types
} // namespace flow_wing