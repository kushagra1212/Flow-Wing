// TypeBuilderInterface.h
#ifndef __FLOWWING_TYPE_BUILDER_INTERFACE_H__
#define __FLOWWING_TYPE_BUILDER_INTERFACE_H__

#include <llvm/IR/DerivedTypes.h>

#include "llvm/IR/Instructions.h"

class CodeGenerationContext;

class TypeBuilderInterface {
 public:
  CodeGenerationContext *_codeGenerationContext;

  TypeBuilderInterface(CodeGenerationContext *context)
      : _codeGenerationContext(context) {}

  virtual ~TypeBuilderInterface() = default;
  virtual void buildType() = 0;
  virtual llvm::Type *get() const = 0;
};

#endif  // __FLOWWING_TYPE_BUILDER_INTERFACE_H__
