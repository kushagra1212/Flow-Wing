#ifndef IR_UTILS_H
#define IR_UTILS_H

namespace IRUtils {
llvm::Value *convertToI8Pointer(llvm::Value *val);
llvm::Value *concatenateStrings(llvm::Value *lhs, llvm::Value *rhs);
llvm::Value *getLLVMValue(std::any value);

std::string getString(BoundExpression *node);
std::string valueToString(llvm::Value *val);

bool isStringType(llvm::Type *type);
size_t calculateStringLength(llvm::Value *strPtr);
} // namespace IRUtils