
#pragma once

#include "src/common/types/Type.hpp"
#include "src/diagnostics/DiagnosticUtils/SourceLocation.h"
#include <optional>
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
  /// True when this symbol was merged into the current file via `bring` from
  /// another translation unit (needs extern declarations in IR, not defs).
  void setImportedViaBring(bool imported) const;

  /// Where this symbol was declared (absolute path + source range). Set for
  /// every declared symbol in the defining translation unit; preserved when the
  /// same symbol is merged via `bring` so IDEs can jump to the defining file.
  void setDeclarationSite(const std::string &absolute_path,
                          const flow_wing::diagnostic::SourceLocation &location);

  // Getters
  SymbolKind getKind() const;
  const std::string &getName() const;
  std::shared_ptr<types::Type> getType() const;
  bool isExposed() const;
  bool isImportedViaBring() const;
  bool hasDeclarationSite() const;
  const std::optional<std::string> &getDeclarationSourcePath() const;
  const std::optional<flow_wing::diagnostic::SourceLocation> &
  getDeclarationLocation() const;
  static std::string toString(SymbolKind kind);

private:
  std::string m_name;
  SymbolKind m_kind;
  mutable bool m_is_exposed;
  mutable bool m_imported_via_bring = false;
  std::shared_ptr<types::Type> m_type;
  std::optional<std::string> m_declaration_source_path;
  std::optional<flow_wing::diagnostic::SourceLocation> m_declaration_location;
};

} // namespace analysis
} // namespace flow_wing