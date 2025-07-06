#pragma once

#include "../../../../../IR/constants/FlowWingIRConstants.h"
#include "../../../../context/CodeGenerationContext.h"
#include <llvm/IR/DerivedTypes.h>

namespace DYNAMIC_VALUE_HANDLER {
namespace VALUE_CHECKER {

int8_t isDynamicType(llvm::Type *type, CodeGenerationContext *ctx);

int8_t isDynamicCompatibleType(llvm::Type *rhsType, CodeGenerationContext *ctx);

} // namespace VALUE_CHECKER
} // namespace DYNAMIC_VALUE_HANDLER
