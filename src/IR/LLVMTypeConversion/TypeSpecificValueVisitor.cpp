#include "TypeSpecificValueVisitor.h"

llvm::Value *TypeSpecificValueVisitor::visit(Int32TypeConverter *converter,
                                             llvm::Value *&value) {
  return converter->convertExplicit(value);
}

llvm::Value *TypeSpecificValueVisitor::visit(DoubleTypeConverter *converter,
                                             llvm::Value *&value) {
  return converter->convertExplicit(value);
}

llvm::Value *TypeSpecificValueVisitor::visit(BoolTypeConverter *converter,
                                             llvm::Value *&value) {
  return converter->convertExplicit(value);
}

llvm::Value *TypeSpecificValueVisitor::visit(StringTypeConverter *converter,
                                             llvm::Value *&value) {
  return converter->convertExplicit(value);
}

llvm::Value *TypeSpecificValueVisitor::visit(FloatTypeConverter *converter,
                                             llvm::Value *&value) {
  return converter->convertExplicit(value);
}

llvm::Value *TypeSpecificValueVisitor::visit(Int8TypeConverter *converter,
                                             llvm::Value *&value) {
  return converter->convertExplicit(value);
}