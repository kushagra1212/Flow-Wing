#ifndef TYPE_SPECIFIC_VALUE_VISITOR_H
#define TYPE_SPECIFIC_VALUE_VISITOR_H

#include "ValueVisitor.h"

class TypeSpecificValueVisitor : public ValueVisitor {
public:
  llvm::Value *visit(Int32TypeConverter *converter,
                     llvm::Value *&value) override;

  llvm::Value *visit(DoubleTypeConverter *converter,
                     llvm::Value *&value) override;

  llvm::Value *visit(BoolTypeConverter *converter,
                     llvm::Value *&value) override;

  llvm::Value *visit(StringTypeConverter *converter,
                     llvm::Value *&value) override;

  llvm::Value *visit(FloatTypeConverter *converter,
                     llvm::Value *&value) override;
};

#endif // TYPE_SPECIFIC_VALUE_VISITOR_H