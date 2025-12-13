#pragma once

#include "src/SemanticAnalyzer/BinderContext/BinderContext.hpp"
#include "src/common/Symbol/Symbol.hpp"
#include "src/common/types/FunctionType/FunctionType.hpp"
#include "src/common/types/Type.hpp"
#include <memory>
#include <unordered_map>
#include <vector>

namespace flow_wing {
namespace binding {
class BinderContext;
} // namespace binding
namespace analysis {

// This class is the single source of truth for all built-in language
// constructs.
class Builtins {
public:
  // --- Built-in Types ---
  static std::shared_ptr<types::Type> m_int8_type_instance;
  static std::shared_ptr<types::Type> m_int32_type_instance;
  static std::shared_ptr<types::Type> m_int64_type_instance;
  static std::shared_ptr<types::Type> m_deci_type_instance;
  static std::shared_ptr<types::Type> m_deci32_type_instance;
  static std::shared_ptr<types::Type> m_str_type_instance;
  static std::shared_ptr<types::Type> m_bool_type_instance;
  static std::shared_ptr<types::Type> m_nirast_type_instance;
  static std::shared_ptr<types::Type> m_nthg_type_instance;
  static std::shared_ptr<types::Type> m_dynamic_type_instance;

  static bool initialize(binding::BinderContext *context);
  static void initializeInternalFunctions();

  // Helper to get all symbols at once for easy registration
  static const std::vector<std::shared_ptr<Symbol>> &getAll();
  static bool isBuiltInFunction(const std::string &name);
  static bool isBuiltInType(const std::string &name);

private:
  static std::shared_ptr<types::Type>
  createBuiltinType(const std::string &name);
  static void createBuiltinFunction(
      const std::string &name,
      std::vector<std::shared_ptr<types::ParameterType>> params,
      std::vector<std::shared_ptr<types::ReturnType>> return_types,
      bool is_variadic = false);
  static void
  createInternalFunction(const std::string &name,
                         std::vector<std::shared_ptr<types::Type>> params,
                         std::vector<std::shared_ptr<types::Type>> returns,
                         bool is_variadic = false);

  static void
  createBuiltinFunctionOverloads(const std::string &name,
                                 std::shared_ptr<types::Type> param_type,
                                 std::shared_ptr<types::Type> return_type);

  static std::vector<std::shared_ptr<Symbol>> m_all_symbols;
  static std::unordered_map<std::string, std::vector<std::shared_ptr<Symbol>>>
      m_functions_symbols_map;
  static std::unordered_map<std::string, std::shared_ptr<Symbol>>
      m_types_symbols_map;
};

} // namespace analysis
} // namespace flow_wing