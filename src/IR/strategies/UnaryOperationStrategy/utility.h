#include "../../../SemanticAnalyzer/BoundExpressions/BoundUnaryExpression/BoundUnaryExpression.h"

namespace UnaryOperationSupport {

struct BoolStrategyTag {};
struct DoubleStrategyTag {};
struct Int8StrategyTag {};
struct Int32StrategyTag {};
struct ClassStrategyTag {};
// Overload for Booleans
inline bool isSupported(BoolStrategyTag,
                        BinderKindUtils::BoundUnaryOperatorKind op) {
  return op == BinderKindUtils::BoundUnaryOperatorKind::LogicalNegation;
}

// Overload for Doubles

inline bool isSupported(DoubleStrategyTag,
                        BinderKindUtils::BoundUnaryOperatorKind op) {
  switch (op) {
  case BinderKindUtils::BoundUnaryOperatorKind::Negation:
  case BinderKindUtils::BoundUnaryOperatorKind::Identity:
  case BinderKindUtils::BoundUnaryOperatorKind::LogicalNegation:
    return true;
  default:
    return false;
  }
}

// Overload for Floats
struct FloatStrategyTag {};
inline bool isSupported(FloatStrategyTag,
                        BinderKindUtils::BoundUnaryOperatorKind op) {
  return isSupported(DoubleStrategyTag{}, op);
}

// Overload for Integers
inline bool isSupported(Int32StrategyTag,
                        BinderKindUtils::BoundUnaryOperatorKind op) {
  switch (op) {
  case BinderKindUtils::BoundUnaryOperatorKind::Negation:
  case BinderKindUtils::BoundUnaryOperatorKind::Identity:
  case BinderKindUtils::BoundUnaryOperatorKind::BitwiseNegation:
  case BinderKindUtils::BoundUnaryOperatorKind::LogicalNegation:
    return true;
  default:
    return false;
  }
}

// Overload for Int8

inline bool isSupported(Int8StrategyTag,
                        BinderKindUtils::BoundUnaryOperatorKind op) {
  return isSupported(Int32StrategyTag{}, op);
}

// Overload for Nirast
struct NirastStrategyTag {};
inline bool isSupported(NirastStrategyTag,
                        BinderKindUtils::BoundUnaryOperatorKind op) {
  return op == BinderKindUtils::BoundUnaryOperatorKind::LogicalNegation;
}

// Overload for Strings
struct StringStrategyTag {};
inline bool isSupported(StringStrategyTag,
                        BinderKindUtils::BoundUnaryOperatorKind op) {
  return op == BinderKindUtils::BoundUnaryOperatorKind::LogicalNegation;
}

// Overload for Class
inline bool isSupported(ClassStrategyTag,
                        BinderKindUtils::BoundUnaryOperatorKind op) {

  return op == BinderKindUtils::BoundUnaryOperatorKind::LogicalNegation;
}
} // namespace UnaryOperationSupport