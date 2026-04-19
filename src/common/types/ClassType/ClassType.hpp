#pragma once

#include "src/common/Symbol/Symbol.hpp"
#include "src/common/types/Type.hpp"
#include <functional>
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace flow_wing {

namespace analysis {
class FunctionSymbol;
}

namespace types {

struct ParameterType;

class ClassType : public Type {
public:
  ClassType(const std::string &name, std::shared_ptr<ClassType> base_class);

  bool defineMember(std::shared_ptr<analysis::Symbol> member);
  bool defineMember(const std::string &key,
                    std::shared_ptr<analysis::Symbol> member);

  std::shared_ptr<analysis::Symbol> lookupMember(const std::string &name) const;

  std::shared_ptr<analysis::Symbol> lookupField(const std::string &name) const;

  std::vector<std::shared_ptr<analysis::Symbol>>
  getMethodOverloads(const std::string &name) const;

  std::shared_ptr<analysis::FunctionSymbol> resolveMethod(
      const std::string &name,
      const std::vector<std::shared_ptr<ParameterType>> &visible_params) const;

  std::shared_ptr<analysis::FunctionSymbol> resolveMethodLocal(
      const std::string &name,
      const std::vector<std::shared_ptr<ParameterType>> &visible_params) const;

  std::shared_ptr<analysis::FunctionSymbol> resolveMethodForCall(
      const std::string &name,
      const std::vector<std::shared_ptr<Type>> &argument_types) const;

  std::shared_ptr<ClassType> getBaseClass() const;

  const std::map<std::string, std::shared_ptr<analysis::Symbol>> &
  getFieldMembers() const;

  const std::map<std::string, std::shared_ptr<analysis::Symbol>> &
  getMembers() const;

  void forEachFunctionMember(
      const std::function<void(const std::shared_ptr<analysis::Symbol> &)> &fn)
      const;

  int getMemberFieldIndex(const std::string &name) const;
  int getTotalFieldCount() const;

  int getLLVMFieldCount() const;

  const std::vector<std::shared_ptr<analysis::FunctionSymbol>> &
  getVtableEntries() const;

  int getVirtualSlotForMethod(const analysis::FunctionSymbol *fn) const;

  bool operator<=(const Type &other) const override;

private:
  void rebuildMembersCache() const;
  void rebuildVtableEntries() const;

  std::shared_ptr<ClassType> m_base_class;
  std::map<std::string, std::shared_ptr<analysis::Symbol>> m_fields;
  std::map<std::string, std::vector<std::shared_ptr<analysis::Symbol>>>
      m_methods;
  std::vector<std::shared_ptr<analysis::FunctionSymbol>>
      m_method_declaration_order;
  mutable std::map<std::string, std::shared_ptr<analysis::Symbol>>
      m_members_cache;
  mutable bool m_members_cache_dirty = true;

  mutable std::vector<std::shared_ptr<analysis::FunctionSymbol>>
      m_vtable_entries;
  mutable bool m_vtable_cache_dirty = true;
};

} // namespace types
} // namespace flow_wing
