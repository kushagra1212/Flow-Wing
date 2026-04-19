#pragma once
#include <memory>

// clang-format off
#include "src/compiler/diagnostics/DiagnosticPush.hpp"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/Target/TargetMachine.h"
#include "src/compiler/diagnostics/DiagnosticPop.hpp"
// clang-format on

namespace flow_wing {

namespace ir_gen {

class LLVMBackendContext {
public:
  LLVMBackendContext(const std::string &module_name);
  ~LLVMBackendContext();

  llvm::TargetMachine *getTargetMachine() const;
  llvm::LLVMContext *getLLVMContext() const;
  llvm::Module *getLLVMModule() const;

private:
  std::unique_ptr<llvm::LLVMContext> m_context;
  std::unique_ptr<llvm::Module> m_module;
  llvm::TargetMachine *m_target_machine = nullptr;
};

} // namespace ir_gen

} // namespace flow_wing