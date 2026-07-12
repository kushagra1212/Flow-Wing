/*
 * FlowWing Compiler
 * ... (copyright header) ...
 */

#pragma once

#include <memory>
#include <string>

namespace flow_wing {
namespace types {

enum class TypeKind {
  kPrimitive,
  kFunction,
  kObject,
  kModule,
  kArray,
  kClass,
  kError // A special type to prevent cascade errors after a semantic error
};

class Type {
public:
  using TypePtr = std::shared_ptr<Type>;

  explicit Type(std::string name, TypeKind kind);
  virtual ~Type() = default;

  const std::string &getName() const { return m_name; }
  TypeKind getKind() const { return m_kind; }

  // --- Core Type System Logic ---

  virtual bool operator==(const Type &other) const;
  virtual bool operator!=(const Type &other) const;
  virtual bool operator<=(const Type &other) const;
  virtual bool operator>(const Type &other) const;

  virtual bool isNthg() const;
  virtual bool isDynamic() const;
  virtual bool isPrimitive() const;
  virtual bool isNirast() const;
  virtual bool isInteger() const;
  bool isString() const;
  // True for types whose runtime value is a single traced GC heap pointer:
  // objects, classes, arrays and strings. Dynamic is boxed inline (a struct),
  // not a single pointer, so it is intentionally excluded.
  bool isGcReference() const;

  static std::string toString(TypeKind kind);

protected:
  std::string m_name;

private:
  TypeKind m_kind;
};

} // namespace types
} // namespace flow_wing