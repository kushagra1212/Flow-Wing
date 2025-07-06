#include "TypeVerifier.h"

namespace TYPE_VERIFIER {

int8_t verifyArrayType(
    llvm::ArrayType *lhsType, llvm::ArrayType *rhsType,
    const std::vector<FLOW_WING::DIAGNOSTIC::DiagnosticCode> &diagnosticCodes,
    const std::vector<FLOW_WING::DIAGNOSTIC::DiagnosticArg> &diagnosticArgs,
    CodeGenerationContext *ctx) {
  std::vector<FLOW_WING::DIAGNOSTIC::DiagnosticArg> _diagnosticArgs(
      diagnosticArgs.begin(), diagnosticArgs.end());

  std::vector<uint64_t> lhsSizes, rhsSizes;
  llvm::Type *lshEType = (lhsType), *rhsEType = (rhsType);
  ctx->createArraySizesAndArrayElementType(lhsSizes, lshEType);
  ctx->createArraySizesAndArrayElementType(rhsSizes, rhsEType);

  if (lshEType != rhsEType) {
    _diagnosticArgs.emplace_back(ctx->getMapper()->getLLVMTypeName(lhsType));
    _diagnosticArgs.emplace_back(ctx->getMapper()->getLLVMTypeName(rhsType));

    ctx->getLogger()->logError(diagnosticCodes[0], _diagnosticArgs);
    return EXIT_FAILURE;
  }

  if (lhsSizes.size() != rhsSizes.size()) {
    _diagnosticArgs.emplace_back(ctx->getMapper()->getLLVMTypeName(lhsType));
    _diagnosticArgs.emplace_back(std::to_string(lhsSizes.size()));
    _diagnosticArgs.emplace_back(std::to_string(rhsSizes.size()));

    ctx->getLogger()->logError(diagnosticCodes[1], _diagnosticArgs);
    return EXIT_FAILURE;
  }

  for (int i = 0; i < lhsSizes.size(); i++) {
    if (lhsSizes[i] < rhsSizes[i]) {
      _diagnosticArgs.emplace_back(ctx->getMapper()->getLLVMTypeName(lhsType));
      _diagnosticArgs.emplace_back(std::to_string(i + 1));
      _diagnosticArgs.emplace_back(std::to_string(rhsSizes[i]));
      _diagnosticArgs.emplace_back(std::to_string(lhsSizes[i]));

      ctx->getLogger()->logError(diagnosticCodes[2], _diagnosticArgs);
      return EXIT_FAILURE;
    }
  }

  return EXIT_SUCCESS;
}

} // namespace TYPE_VERIFIER