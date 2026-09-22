#pragma once

#include "src/IRGen/GCDescriptor/GCDescriptorEmitter.hpp"
#include "src/IRGen/LLVMTypeBuilder/LLVMTypeBuilder.hpp"
#include "src/compiler/diagnostics/DiagnosticCode.h"

// clang-format off

#include "src/compiler/diagnostics/DiagnosticPush.hpp"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Value.h"
#include "llvm/Target/TargetMachine.h"
#include <vector>
#include "src/compiler/diagnostics/DiagnosticPop.hpp"
#include <memory>
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
  GCDescriptorEmitter *getGCDescriptorEmitter();
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
  bool isGlobalScope() const;
  llvm::Constant *getDefaultValue(types::Type *type, bool is_global = false);

  // Emits fw_gc_alloc(size, descriptor): every allocation the precise GC makes.
  //
  // The C runtime takes the size as size_t, which is as wide as a pointer: 64
  // bits on native targets, 32 on wasm32. So the declaration is built here from
  // the module's data layout, not registered as a builtin with a fixed int64
  // parameter. A fixed width links natively, where linkers never compare
  // types, and is rejected by wasm-ld ("function signature mismatch").
  llvm::CallInst *createGcAlloc(uint64_t size_bytes, llvm::Value *descriptor,
                                const llvm::Twine &name = "");

  // --- Loop targets for break/continue ---
  void pushLoop(llvm::BasicBlock *cond_block, llvm::BasicBlock *after_block);
  void popLoop();
  llvm::BasicBlock *getCurrentLoopCond() const;
  llvm::BasicBlock *getCurrentLoopAfter() const;

  // --- Per-function GC shadow-stack roots ---
  // Pointer-typed local/param allocas that hold a single heap pointer. The
  // shadow-frame emitter (IRGenerator::emitGcShadowFrame) consumes this list at
  // the end of each function and clears it per function via clearGcRootAllocas.
  void addGcRootAlloca(llvm::AllocaInst *root_alloca);
  std::vector<llvm::AllocaInst *> &getGcRootAllocas();
  void clearGcRootAllocas();

  // Additional GC root "slots" expressed as (base alloca, byte offset) pairs.
  // Used to root individual heap-pointer leaves inside a wider stack aggregate
  // (e.g. the pointer fields of a multi-return `ret_slot`) that the single-word
  // per-alloca root model cannot reach. The shadow-frame emitter computes
  // `i8* base + offset` in the prologue and appends each as a `void**` root.
  void addGcRootSlot(llvm::AllocaInst *base, uint64_t byte_offset);
  std::vector<std::pair<llvm::AllocaInst *, uint64_t>> &getGcRootSlots();

private:
  CompilationContext &m_context;
  llvm::LLVMContext *m_llvm_context;
  llvm::Module *m_llvm_module;
  std::unique_ptr<llvm::IRBuilder<>> m_llvm_builder;

  std::vector<std::unordered_map<std::string, llvm::Value *>> m_symbol_table;

  struct LoopTargets {
    llvm::BasicBlock *cond_block = nullptr;
    llvm::BasicBlock *after_block = nullptr;
  };
  std::vector<LoopTargets> m_loop_stack;

  // Reset at each function entry; holds pointer-typed root allocas for the
  // shadow frame emitted when the function's body + terminator are complete.
  std::vector<llvm::AllocaInst *> m_gc_root_allocas;
  std::vector<std::pair<llvm::AllocaInst *, uint64_t>> m_gc_root_slots;

  std::unique_ptr<LLVMTypeBuilder> m_type_builder;
  std::unique_ptr<GCDescriptorEmitter> m_gc_descriptor_emitter;
  void initializeLLVM();
  void initializeTargetMachine();

  // wasm32 path: sets the module's triple and data layout directly, leaving
  // m_target_machine null. See the definition for why no TargetMachine exists.
  void initializeWasmTarget();

  // Triple and data layout for wasm32-unknown-emscripten.
  //
  // These must match the clang inside emcc exactly. LLVM refuses to run code
  // generation when the module's data layout differs from the target's by even
  // one field:
  //
  //   fatal error: Can't create a MachineFunction using a Module with a
  //   Target-incompatible DataLayout attached
  //
  // The value below is what `emcc -S -emit-llvm` prints for emscripten 6.0.10
  // (clang 24). Older LLVM, including the 17 this compiler links against, omit
  // `i128:128`, so copying the string out of the host LLVM produces exactly
  // that error. Re-read it from emcc after an emsdk upgrade:
  //
  //   echo 'int main(void){}' > t.c && emcc -S -emit-llvm t.c -o - | grep datalayout
  static constexpr const char *kWasm32Triple = "wasm32-unknown-emscripten";
  static constexpr const char *kWasm32DataLayout =
      "e-m:e-p:32:32-p10:8:8-p20:8:8-i64:64-i128:128-f128:64-n32:64-S128-ni:1:"
      "10:20";

  llvm::TargetMachine *m_target_machine = nullptr;
};
} // namespace ir_gen
} // namespace flow_wing