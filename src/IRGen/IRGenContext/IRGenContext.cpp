/*
 * FlowWing Compiler
 * Copyright (C) 2023-2026 Kushagra Rathore
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include "IRGenContext.hpp"
#include "src/IRGen/LLVMBackendContext/LLVMBackendContext.hpp"
#include "src/IRGen/LLVMTypeBuilder/LLVMTypeBuilder.hpp"
#include "src/SemanticAnalyzer/Builtins/Builtins.hpp"
#include "src/common/cli/CliReporter.h"
#include "src/compiler/CompilationContext/CompilationContext.h"
#include "src/compiler/diagnostics/DiagnosticCode.h"
#include "src/compiler/diagnostics/DiagnosticFactory.h"
#include "src/diagnostics/DiagnosticUtils/SourceLocation.h"

// clang-format off
#include "src/compiler/diagnostics/DiagnosticPush.hpp"
#include "llvm/IR/Value.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Target/TargetOptions.h"
#include "llvm/TargetParser/Host.h"
#include "src/compiler/diagnostics/DiagnosticPop.hpp"
// clang-format on

namespace flow_wing {
namespace ir_gen {

IRGenContext::IRGenContext(CompilationContext &context) : m_context(context) {
  initializeLLVM();
  pushScope();
}

void IRGenContext::storeLLVMIr() {
  std::string ir;
  llvm::raw_string_ostream ir_stream(ir);
  m_llvm_module->print(ir_stream, nullptr);
  m_context.setLLVMIr(ir_stream.str());
  ir_stream.flush();
}

void IRGenContext::initializeLLVM() {
  m_context.setBackendContext(std::make_unique<LLVMBackendContext>(
      m_context.getAbsoluteSourceFilePath()));

  m_llvm_context = m_context.getBackendContext()->getLLVMContext();
  m_llvm_module = m_context.getBackendContext()->getLLVMModule();
  m_llvm_builder = std::make_unique<llvm::IRBuilder<>>(*m_llvm_context);
  m_type_builder = std::make_unique<LLVMTypeBuilder>(*m_llvm_context);

  llvm::InitializeNativeTarget();
  llvm::InitializeNativeTargetAsmPrinter();
  llvm::InitializeNativeTargetAsmParser();
  initializeTargetMachine();
  m_llvm_module->setDataLayout(m_target_machine->createDataLayout());
}

const std::unique_ptr<LLVMTypeBuilder> &IRGenContext::getTypeBuilder() const {
  return m_type_builder;
}

llvm::Module *IRGenContext::getLLVMModule() const { return m_llvm_module; }

void IRGenContext::initializeTargetMachine() {
  m_llvm_module->setTargetTriple(llvm::sys::getDefaultTargetTriple());

  std::string error;
  auto target = llvm::TargetRegistry::lookupTarget(
      m_llvm_module->getTargetTriple(), error);
  if (error.size() > 0) {
    flow_wing::cli::Reporter::error("Failed to lookup target: " + error);
    exit(EXIT_FAILURE);
  }

  auto kHostCPU = "generic";
  auto kHostFeatures = "";
  llvm::TargetOptions target_options;
  llvm::Reloc::Model reloc_model = llvm::Reloc::Model::PIC_;
  m_target_machine =
      target->createTargetMachine(m_llvm_module->getTargetTriple(), kHostCPU,
                                  kHostFeatures, target_options, reloc_model);
}

llvm::LLVMContext *IRGenContext::getLLVMContext() const {
  return m_llvm_context;
}

const std::unique_ptr<llvm::IRBuilder<>> &IRGenContext::getLLVMBuilder() const {
  return m_llvm_builder;
}

IRGenContext::~IRGenContext() = default;

void IRGenContext::reportError(
    flow_wing::diagnostic::DiagnosticCode code,
    const std::vector<flow_wing::diagnostic::DiagnosticArg> &args,
    const flow_wing::diagnostic::SourceLocation &location) {
  m_context.getDiagnostics()->report(
      flow_wing::diagnostic::DiagnosticFactory::create(
          code, args, location, flow_wing::diagnostic::DiagnosticLevel::kError,
          flow_wing::diagnostic::DiagnosticType::kCodeGen));
}

const CompilationContext &IRGenContext::getCompilationContext() const {
  return m_context;
}

llvm::Function *IRGenContext::getCurrentFunction() const {
  auto *block = m_llvm_builder->GetInsertBlock();
  if (!block)
    return nullptr; // Guard against builder not being set
  return block->getParent();
}

llvm::BasicBlock *IRGenContext::getCurrentBlock() const {
  return m_llvm_builder->GetInsertBlock();
}

void IRGenContext::setInsertPoint(llvm::BasicBlock *block) {
  m_llvm_builder->SetInsertPoint(block);
}

void IRGenContext::createBranch(llvm::BasicBlock *block) {
  m_llvm_builder->CreateBr(block);
}

llvm::BasicBlock *IRGenContext::createBlock(const std::string &name) {
  return llvm::BasicBlock::Create(*m_llvm_context, name, getCurrentFunction());
}

llvm::AllocaInst *IRGenContext::createAlloca(llvm::Type *type,
                                             const std::string &varName) {
  llvm::Function *fn = getCurrentFunction();
  llvm::IRBuilder<> temp_builder(&fn->getEntryBlock(),
                                 fn->getEntryBlock().begin());

  // Optional: If you want to be extra safe about not breaking existing IR:
  if (!fn->getEntryBlock().empty()) {
    temp_builder.SetInsertPoint(&fn->getEntryBlock(),
                                fn->getEntryBlock().getFirstInsertionPt());
  }

  return temp_builder.CreateAlloca(type, nullptr, varName);
}

void IRGenContext::pushScope() { m_symbol_table.emplace_back(); }
void IRGenContext::popScope() { m_symbol_table.pop_back(); }
void IRGenContext::setSymbol(const std::string &name, llvm::Value *value) {
  m_symbol_table.back()[name] = value;

  CODEGEN_DEBUG_LOG("Defined symbol '" + name + "' in Scope " +
                        std::to_string(m_symbol_table.size() - 1),
                    "IR GENERATION");
}

llvm::Value *IRGenContext::getSymbol(const std::string &name) {
  for (auto it = m_symbol_table.rbegin(); it != m_symbol_table.rend(); ++it) {
    auto search = it->find(name);
    if (search != it->end()) {
      return search->second;
    }
  }
  return nullptr;
}

bool IRGenContext::isGlobalScope() const { return m_symbol_table.size() == 1; }

llvm::Constant *IRGenContext::getDefaultValue(types::Type *type,
                                              bool is_global) {

  if (type == analysis::Builtins::m_int32_type_instance.get()) {
    return getLLVMBuilder()->getInt32(0);
  }
  if (type == analysis::Builtins::m_int64_type_instance.get()) {
    return getLLVMBuilder()->getInt64(0);
  }

  if (type == analysis::Builtins::m_int8_type_instance.get()) {
    return getLLVMBuilder()->getInt8(0);
  }

  if (type == analysis::Builtins::m_deci_type_instance.get()) {
    return llvm::ConstantFP::get(*getLLVMContext(), llvm::APFloat(0.0));
  }
  if (type == analysis::Builtins::m_deci32_type_instance.get()) {
    return llvm::ConstantFP::get(*getLLVMContext(),
                                 llvm::APFloat(static_cast<float>(0.0)));
  }
  if (type == analysis::Builtins::m_bool_type_instance.get()) {
    return getLLVMBuilder()->getInt1(false);
  }

  if (type == analysis::Builtins::m_int8_type_instance.get() ||
      type == analysis::Builtins::m_str_type_instance.get()) {

    if (!is_global) {

      return llvm::cast<llvm::Constant>(
          getLLVMBuilder()->CreateGlobalStringPtr(""));
    }

    llvm::Constant *strConstant =
        llvm::ConstantDataArray::getString(*getLLVMContext(), "");

    auto *globalVar =
        new llvm::GlobalVariable(*getLLVMModule(), strConstant->getType(),
                                 true, // isConstant
                                 llvm::GlobalValue::PrivateLinkage, strConstant,
                                 ".str" // Name
        );

    // Ensure it can be merged with other strings
    globalVar->setUnnamedAddr(llvm::GlobalValue::UnnamedAddr::Global);

    std::vector<llvm::Constant *> indices;
    indices.push_back(
        llvm::ConstantInt::get(llvm::Type::getInt32Ty(*getLLVMContext()), 0));
    indices.push_back(
        llvm::ConstantInt::get(llvm::Type::getInt32Ty(*getLLVMContext()), 0));

    return llvm::ConstantExpr::getInBoundsGetElementPtr(strConstant->getType(),
                                                        globalVar, indices);
  }

  if (type == analysis::Builtins::m_nthg_type_instance.get()) {
    return nullptr;
  }
  if (type == analysis::Builtins::m_nirast_type_instance.get()) {
    return llvm::ConstantPointerNull::get(
        llvm::Type::getInt8PtrTy(*getLLVMContext()));
  }

  if (type == analysis::Builtins::m_char_type_instance.get()) {
    return getLLVMBuilder()->getInt32(0);
  }

  assert(false && "Unsupported type [getDefaultValue]");
  return nullptr;
}

} // namespace ir_gen
} // namespace flow_wing