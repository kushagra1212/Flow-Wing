#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Module.h"
#include "llvm/Pass.h"

using namespace llvm;

namespace {
struct DivisionByZeroPass : public FunctionPass {
  static char ID;
  DivisionByZeroPass() : FunctionPass(ID) {}

  bool runOnFunction(Function &F) override {
    for (auto &BB : F) {
      for (auto &I : BB) {
        if (BinaryOperator *BO = dyn_cast<BinaryOperator>(&I)) {
          if (BO->getOpcode() == Instruction::SDiv) {
            Value *rhsValue = BO->getOperand(1);
            if (ConstantInt *C = dyn_cast<ConstantInt>(rhsValue)) {
              if (C->isZero()) {
                errs() << "Division by zero detected in function "
                       << F.getName() << "!\n";
              }
            }
          }
        }
      }
    }
    return false;
  }
};
} // namespace

char DivisionByZeroPass::ID = 0;
static RegisterPass<DivisionByZeroPass> X("divbyzero",
                                          "Detect Division by Zero");
