#pragma once

#include "src/IRGen/LLVMTypeBuilder/LLVMTypeBuilder.hpp"
#include "src/compiler/diagnostics/DiagnosticCode.h"

// clang-format off

#include "src/compiler/diagnostics/DiagnosticPush.hpp"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/Target/TargetMachine.h"
#include <vector>
#include "src/compiler/diagnostics/DiagnosticPop.hpp"
// clang-format on

namespace flow_wing {

class CompilationContext;

namespace diagnostic {
struct SourceLocation;
} // namespace diagnostic

namespace ir_gen {

struct SymbolTable {
  std::vector<std::unordered_map<std::string, llvm::Value *>> scopes;

  void pushScope() { scopes.emplace_back(); }
  void popScope() { scopes.pop_back(); }

  void insert(const std::string &name, llvm::Value *val) {
    scopes.back()[name] = val;
  }

  llvm::Value *lookup(const std::string &name) {
    for (auto it = scopes.rbegin(); it != scopes.rend(); ++it) {
      if (it->count(name))
        return it->at(name);
    }
    return nullptr;
  }
};

class IRGenContext {
public:
  IRGenContext(CompilationContext &context);
  ~IRGenContext();

  //? Error Reporting
  void
  reportError(flow_wing::diagnostic::DiagnosticCode code,
              const std::vector<flow_wing::diagnostic::DiagnosticArg> &args,
              const flow_wing::diagnostic::SourceLocation &location);

  // Getters
  const CompilationContext &getCompilationContext() const;
  const std::unique_ptr<LLVMTypeBuilder> &getTypeBuilder() const;
  llvm::Module *getLLVMModule() const;
  llvm::LLVMContext *getLLVMContext() const;
  const std::unique_ptr<llvm::IRBuilder<>> &getLLVMBuilder() const;

  // Setters
  void storeLLVMIr();

  // --- State Management ---

  /// Returns the function currently being generated
  llvm::Function *getCurrentFunction() const;
  /// Returns the block where instructions are currently being inserted
  llvm::BasicBlock *getCurrentBlock() const;
  /// Use this instead of builder->SetInsertPoint to ensure safety
  void setInsertPoint(llvm::BasicBlock *block);

  // --- Creation Helpers ---

  /// Creates a new block, automatically attached to the current function
  llvm::BasicBlock *createBlock(const std::string &name);
  /// Creates a stack variable (Alloca) in the function's entry block
  llvm::AllocaInst *createAlloca(llvm::Type *type, const std::string &varName);
  void createBranch(llvm::BasicBlock *block);

  // --- Scope Management ---
  void pushScope();
  void popScope();
  void setSymbol(const std::string &name, llvm::Value *value);
  llvm::Value *getSymbol(const std::string &name);
  llvm::Constant *getDefaultValue(types::Type *type, bool is_global = false);

private:
  CompilationContext &m_context;
  llvm::LLVMContext *m_llvm_context;
  llvm::Module *m_llvm_module;
  std::unique_ptr<llvm::IRBuilder<>> m_llvm_builder;

  std::vector<std::unordered_map<std::string, llvm::Value *>> m_symbol_table;

  std::unique_ptr<LLVMTypeBuilder> m_type_builder;
  void initializeLLVM();
  void initializeTargetMachine();
  llvm::TargetMachine *m_target_machine = nullptr;
};
} // namespace ir_gen
} // namespace flow_wing