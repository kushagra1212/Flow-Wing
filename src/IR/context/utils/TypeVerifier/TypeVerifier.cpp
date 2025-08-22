/*
 * FlowWing Compiler
 * Copyright (C) 2023-2025 Kushagra Rathore
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

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

  for (size_t i = 0; i < lhsSizes.size(); i++) {
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