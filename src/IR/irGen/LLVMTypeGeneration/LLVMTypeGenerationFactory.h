
#pragma once

class CodeGenerationContext;
class LLVMTypeGenerationStrategy;
#include "../../../bind/BinderKindUtils.h"

class LLVMTypeGenerationFactory {
 public:
  CodeGenerationContext *_codeGenerationContext;

  LLVMTypeGenerationFactory(CodeGenerationContext *context);

  std::unique_ptr<LLVMTypeGenerationStrategy> createStrategy(
      BinderKindUtils::BoundNodeKind kind);
};