#pragma once

#include "src/SourceTokenizer/TokenKind/TokenKind.h"
#include "src/common/types/Type.hpp"
#include <unordered_map>
#include <unordered_set>
#include <vector>
namespace flow_wing {
namespace binding {

struct BinaryOperatorKey {
  lexer::TokenKind Kind;
  types::Type *left_type;
  types::Type *right_type;

  bool operator==(const BinaryOperatorKey &other) const {
    return Kind == other.Kind && left_type == other.left_type &&
           right_type == other.right_type;
  }
};

// Need a hash function for the map key
struct BinaryOperatorKeyHash {
  std::size_t operator()(const BinaryOperatorKey &k) const {

    return std::hash<int>()(static_cast<int>(k.Kind)) ^
           (std::hash<types::Type *>()(k.left_type) << 1) ^
           (std::hash<types::Type *>()(k.right_type) << 2);
  }
};

class BoundBinaryOperator {
public:
  BoundBinaryOperator(lexer::TokenKind operator_kind,
                      std::shared_ptr<types::Type> left_type,
                      std::shared_ptr<types::Type> right_type,
                      std::shared_ptr<types::Type> result_type);

  using ExplicitConversionMap =
      std::unordered_map<types::Type *, std::unordered_set<types::Type *>>;

  using OperatorMap = std::unordered_map<BinaryOperatorKey,
                                         std::shared_ptr<BoundBinaryOperator>,
                                         BinaryOperatorKeyHash>;

  // Getters
  lexer::TokenKind getSyntaxKind() const { return m_syntax_kind; }
  std::shared_ptr<types::Type> getLeftType() const { return m_left_type; }
  std::shared_ptr<types::Type> getRightType() const { return m_right_type; }
  std::shared_ptr<types::Type> getResultType() const { return m_result_type; }

  static std::shared_ptr<BoundBinaryOperator>
  bind(lexer::TokenKind operator_kind, std::shared_ptr<types::Type> left_type,
       std::shared_ptr<types::Type> right_type);

  static std::shared_ptr<BoundBinaryOperator>
  bindClassType(lexer::TokenKind operator_kind,
                std::shared_ptr<types::Type> left_type,
                std::shared_ptr<types::Type> right_type);

  static std::shared_ptr<BoundBinaryOperator>
  bindType(lexer::TokenKind operator_kind,
           std::shared_ptr<types::Type> left_type,
           std::shared_ptr<types::Type> right_type,
           std::shared_ptr<types::Type> to_type);

  static bool canConvert(types::Type *from_type, types::Type *to_type);

private:
  lexer::TokenKind m_syntax_kind;
  std::shared_ptr<types::Type> m_left_type;
  std::shared_ptr<types::Type> m_right_type;
  std::shared_ptr<types::Type> m_result_type;

  // Static list holding all valid binary operators
  static std::vector<BoundBinaryOperator> s_operators;
  static ExplicitConversionMap s_explicit_conversion_map;
  static OperatorMap s_operator_map;
};

} // namespace binding
} // namespace flow_wing