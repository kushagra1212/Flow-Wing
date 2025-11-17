#pragma once

#include "src/common/Symbol/Symbol.hpp"
#include "src/common/types/Type.hpp"
#include <map>
#include <memory>
#include <string>

namespace flow_wing {
namespace types {

class ClassType : public Type {
public:
  ClassType(const std::string &name, std::shared_ptr<ClassType> base_class);

  bool defineMember(std::shared_ptr<analysis::Symbol> member);

  // Finds a member, searching up the inheritance chain
  std::shared_ptr<analysis::Symbol> lookupMember(const std::string &name) const;

  std::shared_ptr<ClassType> getBaseClass() const;

private:
  std::shared_ptr<ClassType> m_base_class;
  std::map<std::string, std::shared_ptr<analysis::Symbol>> m_members;
};

} // namespace types
} // namespace flow_wing