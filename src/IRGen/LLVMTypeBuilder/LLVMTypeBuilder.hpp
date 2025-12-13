#pragma once

#include "src/common/types/ArrayType/ArrayType.hpp"
#include "src/common/types/ClassType/ClassType.hpp"
#include "src/common/types/FunctionType/FunctionType.hpp"
#include "src/common/types/Type.hpp"

// clang-format off
#include "src/compiler/diagnostics/DiagnosticPush.hpp"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Type.h"
#include "src/compiler/diagnostics/DiagnosticPop.hpp"
// clang-format on
#include <map>

namespace flow_wing {
namespace ir_gen {

class LLVMTypeBuilder {
public:
  explicit LLVMTypeBuilder(llvm::LLVMContext &context) : m_context(context) {}

  llvm::Type *getLLVMType(const flow_wing::types::Type *type);
  llvm::FunctionType *convertFunction(const types::FunctionType *type);

private:
  llvm::LLVMContext &m_context;

  std::map<const types::Type *, llvm::Type *> m_type_cache;

  llvm::Type *convertPrimitive(const types::Type *type);
  llvm::Type *createDynamicValueType();
  llvm::Type *convertFunctionReturnType(const types::ReturnType *type);
  llvm::Type *convertFunctionParameter(const types::ParameterType *type);

  llvm::Type *convertArray(const types::ArrayType *type);
  llvm::Type *convertClass(const types::ClassType *type);
};

} // namespace ir_gen
} // namespace flow_wing