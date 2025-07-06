#pragma once

#include "../../../../diagnostics/Diagnostic/DiagnosticCode.h"
#include "../../../context/CodeGenerationContext.h"

namespace TYPE_VERIFIER {

int8_t verifyArrayType(
    llvm::ArrayType *lhsType, llvm::ArrayType *rhsType,
    const std::vector<FLOW_WING::DIAGNOSTIC::DiagnosticCode> &diagnosticCodes,
    const std::vector<FLOW_WING::DIAGNOSTIC::DiagnosticArg> &diagnosticArgs,
    CodeGenerationContext *ctx);

} // namespace TYPE_VERIFIER