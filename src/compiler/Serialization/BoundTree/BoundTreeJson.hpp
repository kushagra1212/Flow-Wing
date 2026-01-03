// TokenJsonSerializer.h
#pragma once

#include "src/BoundTreeVisitor/BoundTreeVisitor.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundBinaryOperator/BoundBinaryOperator.hpp"
#include "src/common/Symbol/FunctionSymbol.hpp"
#include "src/common/Symbol/ModuleSymbol.hpp"
#include "src/common/types/FunctionType/FunctionType.hpp"
#include "src/diagnostics/DiagnosticUtils/SourceLocation.h"
#include "src/external/include/json.hpp"
#include <memory>

namespace flow_wing::compiler::serializer {

class BoundTreeJson : public visitor::BoundTreeVisitor {
public:
  nlohmann::json toJson(
      const std::unique_ptr<binding::BoundCompilationUnit> &bound_tree) const;

  nlohmann::json
  toJsonSourcePoint(const flow_wing::diagnostic::SourcePoint &point);

  nlohmann::json
  toJsonRange(const flow_wing::diagnostic::SourceLocation &location);

private:
  nlohmann::json m_bound_tree_json;
  nlohmann::json m_symbols_json;
  nlohmann::json m_types_json;
  nlohmann::json
      m_last_node_json; // The result of the most recently visited node

  std::unordered_map<const void *, size_t> m_ptr_to_id_map;
  size_t m_next_id = 1;

  void visit(binding::BoundCompilationUnit *compilation_unit) override;
  void visit(binding::BoundBlockStatement *block_statement) override;
  void visit(binding::BoundExposeStatement *expose_statement) override;
  void visit(binding::BoundCustomTypeStatement *custom_type_statement) override;
  void visit(binding::BoundVariableDeclaration *node) override;
  void visit(binding::BoundFunctionStatement *node) override;
  void visit(binding::BoundIfStatement *node) override;
  void visit(binding::BoundWhileStatement *node) override;
  void visit(binding::BoundForStatement *node) override;
  void visit(binding::BoundBreakStatement *node) override;
  void visit(binding::BoundContinueStatement *node) override;
  void visit(binding::BoundReturnStatement *node) override;
  void visit(binding::BoundSwitchStatement *node) override;
  void visit(binding::BoundClassStatement *node) override;
  void visit(binding::BoundIdentifierExpression *node) override;
  void visit(binding::BoundIndexExpression *node) override;
  void visit(binding::BoundIntegerLiteralExpression *node) override;
  void visit(binding::BoundDoubleLiteralExpression *node) override;
  void visit(binding::BoundFloatLiteralExpression *node) override;
  void visit(binding::BoundCharacterLiteralExpression *node) override;
  void visit(binding::BoundStringLiteralExpression *node) override;
  void visit(binding::BoundBooleanLiteralExpression *node) override;
  void visit(binding::BoundTemplateStringLiteralExpression *node) override;
  void visit(binding::BoundNirastLiteralExpression *node) override;
  void visit(binding::BoundErrorStatement *node) override;
  void visit(binding::BoundErrorExpression *node) override;
  void visit(binding::BoundModuleAccessExpression *node) override;
  void visit(binding::BoundCallExpression *node) override;
  void visit(binding::BoundMemberAccessExpression *node) override;
  void visit(binding::BoundTernaryExpression *node) override;
  void visit(binding::BoundNewExpression *node) override;
  void visit(binding::BoundParenthesizedExpression *node) override;
  void visit(binding::BoundObjectExpression *node) override;
  void visit(binding::BoundUnaryExpression *node) override;
  void visit(binding::BoundBinaryExpression *node) override;
  void visit(binding::BoundAssignmentExpression *node) override;
  void visit(binding::BoundExpressionStatement *node) override;
  void visit(binding::BoundColonExpression *colon_expression) override;

  // Symbols
  std::string getSymbolId(const analysis::FunctionSymbol *function_symbol);
  std::string getSymbolId(const analysis::ParameterSymbol *parameter_symbol);
  std::string getSymbolId(const analysis::VariableSymbol *variable_symbol);
  std::string getSymbolId(const analysis::ModuleSymbol *module_symbol);
  std::string getSymbolId(const analysis::Symbol *symbol);

  // types
  std::string getTypeId(const types::FunctionType *type);
  std::string getTypeId(const types::ParameterType *type);
  std::string getTypeId(const types::ReturnType *type);
  std::string getTypeId(const types::Type *type);

  // operators
  nlohmann::json
  getBinaryOperatorJson(const binding::BoundBinaryOperator *binary_operator);

  // Utility functions
  std::string getShortId(const void *ptr);

  // Serialization
  template <typename T>
  void serializeChild(const std::unique_ptr<T> &node, nlohmann::json &parent,
                      const std::string &key) {
    if (node) {
      node->accept(this);
      parent[key] = std::move(m_last_node_json);
    } else {
      parent[key] = nullptr;
    }
  }

  template <typename T>
  void serializeArray(const std::vector<std::unique_ptr<T>> &nodes,
                      nlohmann::json &parent, const std::string &key) {
    nlohmann::json array = nlohmann::json::array();
    for (const auto &node : nodes) {
      if (node) {
        node->accept(this);
        array.push_back(std::move(m_last_node_json));
      }
    }
    parent[key] = std::move(array);
  }
};

} // namespace flow_wing::compiler::serializer
