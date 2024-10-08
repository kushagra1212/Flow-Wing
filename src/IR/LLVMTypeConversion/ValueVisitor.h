#ifndef VALUE_VISITOR_H
#define VALUE_VISITOR_H

#include "BoolTypeConverter/BoolTypeConverter.h"
#include "DoubleTypeConverter/DoubleTypeConverter.h"
#include "FloatTypeConverter/FloatTypeConverter.h"
#include "Int32TypeConverter/Int32TypeConverter.h"
#include "Int8TypeConverter/Int8TypeConverter.h"
#include "StringTypeConverter/StringTypeConverter.h"

class ValueVisitor {
public:
  virtual llvm::Value *visit(Int32TypeConverter *converter,
                             llvm::Value *&value) = 0;
  virtual llvm::Value *visit(DoubleTypeConverter *converter,
                             llvm::Value *&value) = 0;
  virtual llvm::Value *visit(BoolTypeConverter *converter,
                             llvm::Value *&value) = 0;

  virtual llvm::Value *visit(StringTypeConverter *converter,
                             llvm::Value *&value) = 0;

  virtual llvm::Value *visit(FloatTypeConverter *converter,
                             llvm::Value *&value) = 0;

  virtual llvm::Value *visit(Int8TypeConverter *converter,
                             llvm::Value *&value) = 0;
};

#endif // VALUE_VISITOR_H