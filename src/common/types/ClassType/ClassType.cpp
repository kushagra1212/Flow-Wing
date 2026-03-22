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


#include "src/common/types/ClassType/ClassType.hpp"
#include "src/common/Symbol/FunctionSymbol.hpp"
#include "src/common/types/FunctionType/FunctionType.hpp"
#include "src/common/types/Type.hpp"

namespace flow_wing {
namespace types {

ClassType::ClassType(const std::string &name,
                     std::shared_ptr<ClassType> base_class)
    : Type(name, TypeKind::kClass), m_base_class(std::move(base_class)) {}

void ClassType::rebuildMembersCache() const {
  m_members_cache.clear();
  for (const auto &p : m_fields) {
    m_members_cache[p.first] = p.second;
  }
  for (const auto &[name, overloads] : m_methods) {
    for (size_t i = 0; i < overloads.size(); i++) {
      m_members_cache[name + "#" + std::to_string(i)] = overloads[i];
    }
  }
  m_members_cache_dirty = false;
}

bool ClassType::defineMember(std::shared_ptr<analysis::Symbol> member) {
  m_members_cache_dirty = true;
  m_vtable_cache_dirty = true;
  if (member->getKind() == analysis::SymbolKind::kFunction) {
    auto *ft = static_cast<const types::FunctionType *>(member->getType().get());
    std::vector<std::shared_ptr<types::ParameterType>> vis;
    if (!ft->getParameterTypes().empty()) {
      for (size_t i = 0; i + 1 < ft->getParameterTypes().size(); i++)
        vis.push_back(ft->getParameterTypes()[i]);
    }
    if (resolveMethodLocal(member->getName(), vis))
      return false;
    auto fn_sym = std::static_pointer_cast<analysis::FunctionSymbol>(member);
    m_methods[fn_sym->getName()].push_back(fn_sym);
    m_method_declaration_order.push_back(fn_sym);
    return true;
  }
  return m_fields.emplace(member->getName(), std::move(member)).second;
}

bool ClassType::defineMember(const std::string &key,
                             std::shared_ptr<analysis::Symbol> member) {
  m_members_cache_dirty = true;
  m_vtable_cache_dirty = true;
  return m_fields.emplace(key, std::move(member)).second;
}

std::shared_ptr<analysis::Symbol>
ClassType::lookupField(const std::string &name) const {
  auto it = m_fields.find(name);
  if (it != m_fields.end() &&
      it->second->getKind() == analysis::SymbolKind::kVariable)
    return it->second;
  if (m_base_class)
    return m_base_class->lookupField(name);
  return nullptr;
}

std::vector<std::shared_ptr<analysis::Symbol>>
ClassType::getMethodOverloads(const std::string &name) const {
  auto it = m_methods.find(name);
  if (it != m_methods.end())
    return it->second;
  return {};
}

static bool visibleParamsMatch(
    const types::FunctionType *ft,
    const std::vector<std::shared_ptr<types::ParameterType>> &visible) {
  const auto &pts = ft->getParameterTypes();
  if (pts.size() != visible.size() + 1)
    return false;
  for (size_t i = 0; i < visible.size(); i++) {
    if (!pts[i]->type || !visible[i]->type)
      return false;
    if (*pts[i]->type != *visible[i]->type)
      return false;
  }
  return true;
}

std::shared_ptr<analysis::FunctionSymbol> ClassType::resolveMethodLocal(
    const std::string &name,
    const std::vector<std::shared_ptr<types::ParameterType>> &visible_params)
    const {
  for (const auto &sym : getMethodOverloads(name)) {
    auto *ft = static_cast<const types::FunctionType *>(sym->getType().get());
    if (visibleParamsMatch(ft, visible_params))
      return std::static_pointer_cast<analysis::FunctionSymbol>(sym);
  }
  return nullptr;
}

std::shared_ptr<analysis::FunctionSymbol> ClassType::resolveMethodForCall(
    const std::string &name,
    const std::vector<std::shared_ptr<types::Type>> &argument_types) const {
  auto try_here = [&](const ClassType *cls)
      -> std::shared_ptr<analysis::FunctionSymbol> {
    for (const auto &sym : cls->getMethodOverloads(name)) {
      auto *ft = static_cast<const types::FunctionType *>(sym->getType().get());
      const auto &pts = ft->getParameterTypes();
      if (pts.empty())
        continue;
      const size_t visible = pts.size() - 1;
      const size_t ds = ft->getDefaultValueStartIndex();
      if (argument_types.size() > visible)
        continue;
      if (ds == static_cast<size_t>(-1)) {
        if (argument_types.size() != visible)
          continue;
      } else {
        if (argument_types.size() < ds)
          continue;
      }
      bool ok = true;
      for (size_t i = 0; i < argument_types.size(); i++) {
        if (!argument_types[i] || !pts[i]->type) {
          ok = false;
          break;
        }
        if (*argument_types[i] > *pts[i]->type) {
          ok = false;
          break;
        }
      }
      if (ok)
        return std::static_pointer_cast<analysis::FunctionSymbol>(sym);
    }
    return nullptr;
  };
  auto r = try_here(this);
  if (r)
    return r;
  if (m_base_class)
    return m_base_class->resolveMethodForCall(name, argument_types);
  return nullptr;
}

std::shared_ptr<analysis::FunctionSymbol> ClassType::resolveMethod(
    const std::string &name,
    const std::vector<std::shared_ptr<types::ParameterType>> &visible_params)
    const {
  for (const auto &sym : getMethodOverloads(name)) {
    auto *ft = static_cast<const types::FunctionType *>(sym->getType().get());
    if (visibleParamsMatch(ft, visible_params))
      return std::static_pointer_cast<analysis::FunctionSymbol>(sym);
  }
  if (m_base_class)
    return m_base_class->resolveMethod(name, visible_params);
  return nullptr;
}

std::shared_ptr<analysis::Symbol>
ClassType::lookupMember(const std::string &name) const {
  auto f = lookupField(name);
  if (f)
    return f;
  auto ov = getMethodOverloads(name);
  if (ov.size() == 1)
    return ov[0];
  if (m_base_class) {
    auto b = m_base_class->lookupMember(name);
    if (b)
      return b;
  }
  return nullptr;
}

std::shared_ptr<ClassType> ClassType::getBaseClass() const {
  return m_base_class;
}

const std::map<std::string, std::shared_ptr<analysis::Symbol>> &
ClassType::getFieldMembers() const {
  return m_fields;
}

const std::map<std::string, std::shared_ptr<analysis::Symbol>> &
ClassType::getMembers() const {
  if (m_members_cache_dirty)
    rebuildMembersCache();
  return m_members_cache;
}

void ClassType::forEachFunctionMember(
    const std::function<void(const std::shared_ptr<analysis::Symbol> &)> &fn)
    const {
  for (const auto &[name, overloads] : m_methods) {
    (void)name;
    for (const auto &sym : overloads)
      fn(sym);
  }
}

int ClassType::getMemberFieldIndex(const std::string &name) const {
  if (m_base_class) {
    int base_idx = m_base_class->getMemberFieldIndex(name);
    if (base_idx >= 0)
      return base_idx;
  }
  const int index_after_base =
      m_base_class ? m_base_class->getLLVMFieldCount() : 1; // vptr at root
  int index = index_after_base;
  for (const auto &[member_name, symbol] : m_fields) {
    if (symbol->getKind() != analysis::SymbolKind::kVariable)
      continue;
    if (member_name == name)
      return index;
    index++;
  }
  return -1;
}

int ClassType::getTotalFieldCount() const {
  int count = 0;
  if (m_base_class) {
    count = m_base_class->getTotalFieldCount();
  }
  for (const auto &[name, symbol] : m_fields) {
    if (symbol->getKind() == analysis::SymbolKind::kVariable)
      count++;
  }
  return count;
}

int ClassType::getLLVMFieldCount() const {
  const int base_count = m_base_class ? m_base_class->getLLVMFieldCount() : 1;
  int local = 0;
  for (const auto &[name, symbol] : m_fields) {
    if (symbol->getKind() == analysis::SymbolKind::kVariable)
      local++;
  }
  return base_count + local;
}

void ClassType::rebuildVtableEntries() const {
  m_vtable_entries.clear();
  if (m_base_class) {
    const auto &base_vt = m_base_class->getVtableEntries();
    m_vtable_entries.assign(base_vt.begin(), base_vt.end());
  }
  for (const auto &sym : m_method_declaration_order) {
    if (sym->getName() == "init")
      continue;
    auto *ft = static_cast<const types::FunctionType *>(sym->getType().get());
    std::vector<std::shared_ptr<types::ParameterType>> vis;
    if (!ft->getParameterTypes().empty()) {
      for (size_t i = 0; i + 1 < ft->getParameterTypes().size(); i++)
        vis.push_back(ft->getParameterTypes()[i]);
    }
    bool replaced = false;
    for (size_t j = 0; j < m_vtable_entries.size(); j++) {
      auto *old_sym = m_vtable_entries[j].get();
      if (old_sym->getName() != sym->getName())
        continue;
      auto *oft = static_cast<const types::FunctionType *>(old_sym->getType().get());
      if (visibleParamsMatch(oft, vis)) {
        m_vtable_entries[j] = sym;
        replaced = true;
        break;
      }
    }
    if (!replaced)
      m_vtable_entries.push_back(sym);
  }
  m_vtable_cache_dirty = false;
}

const std::vector<std::shared_ptr<analysis::FunctionSymbol>> &
ClassType::getVtableEntries() const {
  if (m_vtable_cache_dirty)
    rebuildVtableEntries();
  return m_vtable_entries;
}

bool ClassType::operator<=(const Type &other) const {
  if (other.isDynamic())
    return Type::operator<=(other);
  if (other.getKind() != TypeKind::kClass)
    return Type::operator<=(other);
  if (*this == other)
    return true;
  for (const ClassType *p = m_base_class.get(); p; p = p->getBaseClass().get()) {
    if (*p == other)
      return true;
  }
  return false;
}

int ClassType::getVirtualSlotForMethod(const analysis::FunctionSymbol *fn) const {
  const auto &vt = getVtableEntries();
  for (size_t i = 0; i < vt.size(); i++) {
    if (vt[i].get() == fn)
      return static_cast<int>(i);
  }
  const auto *ft = static_cast<const types::FunctionType *>(fn->getType().get());
  std::vector<std::shared_ptr<types::ParameterType>> vis;
  if (!ft->getParameterTypes().empty()) {
    for (size_t i = 0; i + 1 < ft->getParameterTypes().size(); i++)
      vis.push_back(ft->getParameterTypes()[i]);
  }
  for (size_t i = 0; i < vt.size(); i++) {
    auto *cand = vt[i].get();
    if (cand->getName() != fn->getName())
      continue;
    auto *cft = static_cast<const types::FunctionType *>(cand->getType().get());
    if (visibleParamsMatch(cft, vis))
      return static_cast<int>(i);
  }
  return -1;
}

} // namespace types
} // namespace flow_wing
