#ifndef IR_UTILS_H
#define IR_UTILS_H

// LLVM Imports
#include "llvm-14/llvm/IR/Type.h"
#include <llvm-14/llvm/ADT/APInt.h>
#include <llvm-14/llvm/ADT/StringRef.h>
#include <llvm-14/llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm-14/llvm/ExecutionEngine/GenericValue.h>
#include <llvm-14/llvm/IR/IRBuilder.h>
#include <llvm-14/llvm/IR/IRPrintingPasses.h>
#include <llvm-14/llvm/IR/InstrTypes.h>
#include <llvm-14/llvm/IR/Instruction.h>
#include <llvm-14/llvm/IR/Instructions.h>
#include <llvm-14/llvm/IR/LLVMContext.h>
#include <llvm-14/llvm/IR/Module.h>
#include <llvm-14/llvm/IR/Verifier.h>
#include <llvm-14/llvm/IRReader/IRReader.h>
#include <llvm-14/llvm/Support/MemoryBuffer.h>
#include <llvm-14/llvm/Support/raw_ostream.h>
#include <llvm-14/llvm/Transforms/Utils/Cloning.h>

#include <llvm-14/llvm/Support/Error.h>
#include <llvm-14/llvm/Support/SourceMgr.h>

#include <llvm-14/llvm/IRReader/IRReader.h>
// ExecutionEngine
#include <llvm-14/llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm-14/llvm/ExecutionEngine/GenericValue.h>
#include <llvm-14/llvm/ExecutionEngine/Interpreter.h>
#include <llvm-14/llvm/ExecutionEngine/MCJIT.h>
#include <llvm-14/llvm/ExecutionEngine/SectionMemoryManager.h>
#include <llvm-14/llvm/IR/LegacyPassManager.h>
#include <llvm-14/llvm/IR/Module.h>
#include <llvm-14/llvm/Support/SourceMgr.h>
#include <llvm-14/llvm/Support/TargetSelect.h>

#include "llvm-14/llvm//IR/Value.h"
#include "llvm-14/llvm/IR/Constants.h"

// Elang Files Import

#include "../../Common.h"
#include "../../bind/Binder/Binder.h"
#include "../../bind/Binder/BoundScopeGlobal/BoundScopeGlobal.h"
#include "../../bind/BinderKindUtils.h"
#include "../../bind/BoundAssignmentExpression/BoundAssignmentExpression.h"
#include "../../bind/BoundBinaryExpression/BoundBinaryExpression.h"
#include "../../bind/BoundBlockStatement/BoundBlockStatement.h"
#include "../../bind/BoundExpression.h"
#include "../../bind/BoundExpressionStatement/BoundExpressionStatement.h"
#include "../../bind/BoundLiteralExpression/BoundLiteralExpression.h"
#include "../../bind/BoundParenthesizedExpression/BoundParenthesizedExpression.h"
#include "../../bind/BoundStatement/BoundStatement.h"
#include "../../bind/BoundUnaryExpression/BoundUnaryExpression.h"
#include "../../bind/BoundVariableExpression/BoundVariableExpression.h"
#include "../../syntax/CompilationUnitSyntax.h"

#include "../llvm/IRGenerator.h"

namespace IRUtils {

llvm::Value *getLLVMValue(std::any value, llvm::Module *TheModule,
                          llvm::LLVMContext *TheContext,
                          llvm::IRBuilder<> *Builder);

size_t calculateStringLength(llvm::Value *strPtr, llvm::Module *TheModule,
                             llvm::IRBuilder<> *Builder);

std::string getString(std::shared_ptr<BoundExpression> node);

std::string valueToString(llvm::Value *val);

llvm::Value *convertToString(llvm::Value *val, llvm::IRBuilder<> *Builder);

llvm::Value *concatenateStrings(llvm::Value *lhs, llvm::Value *rhs,
                                llvm::Module *TheModule,
                                llvm::IRBuilder<> *Builder);

llvm::Type *getTypeFromAny(std::any value, llvm::LLVMContext *TheContext);

bool isStringType(llvm::Type *type);

bool isIntType(llvm::Type *type);

bool isBoolType(llvm::Type *type);

bool isDoubleType(llvm::Type *type);

llvm::Value *convertToDouble(llvm::Value *val, llvm::IRBuilder<> *Builder);

llvm::Value *convertToInt(llvm::Value *val, llvm::IRBuilder<> *Builder);

llvm::Value *convertToBool(llvm::Value *val, llvm::IRBuilder<> *Builder);

llvm::Value *getResultFromBinaryOperationOnDouble(
    llvm::Value *lhsValue, llvm::Value *rhsValue, llvm::IRBuilder<> *Builder,
    llvm::Module *TheModule,
    std::shared_ptr<BoundBinaryExpression> binaryExpression);

llvm::Value *getResultFromBinaryOperationOnInt(
    llvm::Value *lhsValue, llvm::Value *rhsValue, llvm::IRBuilder<> *Builder,
    llvm::Module *TheModule,
    std::shared_ptr<BoundBinaryExpression> binaryExpression);

llvm::Value *getResultFromBinaryOperationOnBool(
    llvm::Value *lhsValue, llvm::Value *rhsValue, llvm::IRBuilder<> *Builder,
    llvm::Module *TheModule,
    std::shared_ptr<BoundBinaryExpression> binaryExpression);

} // namespace IRUtils

#endif