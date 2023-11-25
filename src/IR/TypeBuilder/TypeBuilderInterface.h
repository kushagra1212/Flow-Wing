// TypeBuilderInterface.h
#ifndef __FLOWWING_TYPE_BUILDER_INTERFACE_H__
#define __FLOWWING_TYPE_BUILDER_INTERFACE_H__

class CodeGenerationContext;

#include <llvm/IR/DerivedTypes.h>

class TypeBuilderInterface {
public:
  CodeGenerationContext *_codeGenerationContext;

  TypeBuilderInterface(CodeGenerationContext *context)
      : _codeGenerationContext(context) {}

  virtual ~TypeBuilderInterface() = default;
  virtual void buildType() = 0;
  virtual llvm::Type *get() const = 0;
};

#endif // __FLOWWING_TYPE_BUILDER_INTERFACE_H__
