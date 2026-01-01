
#pragma once

#include "src/common/types/Type.hpp"
#include <cstddef>
#include <map>
#include <memory>

namespace flow_wing {
namespace types {

class CustomObjectType : public Type {
public:
  CustomObjectType(const std::string &custom_type_name,
                   std::map<std::string, std::shared_ptr<Type>> fields);

  bool operator==(const Type &other) const override;
  bool operator<=(const Type &other) const override;

  std::shared_ptr<Type> getFieldType(const std::string &name) const;
  const std::map<std::string, std::shared_ptr<Type>> &getFields() const;
  const std::string &getCustomTypeName() const;

private:
  std::string m_custom_type_name;
  std::map<std::string, std::shared_ptr<Type>> m_fields;

  std::string buildCustomObjectTypeName(
      const std::string &custom_type_name,
      const std::map<std::string, std::shared_ptr<Type>> &fields);
};

} // namespace types
} // namespace flow_wing