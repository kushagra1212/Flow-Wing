
#pragma once

#include "src/common/types/Type.hpp"
#include <string>

namespace flow_wing {

namespace analysis {

enum class SymbolKind {
  kVariable,
  kFunction,
  kParameter,
  kType,
  kModule,
  kObject,
  kClass,
};

class Symbol {
public:
  Symbol(std::string name, SymbolKind kind, std::shared_ptr<types::Type> type);
  virtual ~Symbol() = default;

  // Setters
  void setIsExposed(bool is_exposed) const;

  // Getters
  SymbolKind getKind() const;
  const std::string &getName() const;
  std::shared_ptr<types::Type> getType() const;
  bool isExposed() const;

private:
  std::string m_name;
  SymbolKind m_kind;
  mutable bool m_is_exposed;
  std::shared_ptr<types::Type> m_type;
};

} // namespace analysis
} // namespace flow_wing