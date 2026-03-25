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

#include "src/IRGen/IRGenerator/IRGenerator.hpp"
#include "src/IRGen/FlowWingConstants/FlowWingConstants.hpp"
#include "src/IRGen/GlobalDeclarationsInitializer/GlobalDeclarationsInitializer.hpp"
#include "src/IRGen/IRGenContext/IRGenContext.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundColonExpression/BoundColonExpression.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundContainerExpression/BoundContainerExpression.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundLiteralExpression/BoundCharacterLiteralExpression/BoundCharacterLiteralExpression.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundLiteralExpression/BoundFloatLiteralExpression/BoundFloatLiteralExpression.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundLiteralExpression/BoundStringLiteralExpression/BoundStringLiteralExpression.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundObjectExpression/BoundObjectExpression.hpp"
#include "src/SemanticAnalyzer/BoundStatements/BoundExposeStatement/BoundExposeStatement.hpp"
#include "src/SemanticAnalyzer/BoundStatements/BoundModuleStatement/BoundModuleStatement.hpp"
#include "src/SemanticAnalyzer/Builtins/Builtins.hpp"
#include "src/SemanticAnalyzer/NodeKind/NodeKind.h"
#include "src/SemanticAnalyzer/SyntaxBinder/BoundCompilationUnit.hpp"
#include "src/common/Symbol/FunctionSymbol.hpp"
#include "src/common/Symbol/VariableSymbol.hpp"
#include "src/common/types/ClassType/ClassType.hpp"
#include "src/compiler/CompilationContext/CompilationContext.h"
#include <string>

// clang-format off
#include "src/compiler/diagnostics/DiagnosticPush.hpp"
#include "llvm-c/Analysis.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/GlobalVariable.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Verifier.h"
#include "src/compiler/diagnostics/DiagnosticPop.hpp"
#include "src/diagnostics/DiagnosticUtils/SourceLocation.h"
#include <cstdlib>
// clang-format on

namespace flow_wing {
namespace ir_gen {

namespace {

/// Register a void () function as a global constructor so it runs before
/// `main` (needed for brought dependency .o files that emit top-level stores
/// without defining a second `main`).
void registerGlobalCtor(llvm::Module *module, llvm::Function *ctor_fn) {
  llvm::LLVMContext &ctx = module->getContext();
  llvm::Type *i32 = llvm::Type::getInt32Ty(ctx);
  llvm::Type *fn_ptr = llvm::PointerType::getUnqual(ctx);
  llvm::Type *i8p = llvm::Type::getInt8PtrTy(ctx);
  llvm::StructType *elt_ty = llvm::StructType::get(ctx, {i32, fn_ptr, i8p});

  llvm::Constant *ctor_entry = llvm::ConstantStruct::get(
      elt_ty,
      {llvm::ConstantInt::get(i32, 65535),
       llvm::ConstantExpr::getBitCast(ctor_fn, fn_ptr),
       llvm::ConstantPointerNull::get(llvm::cast<llvm::PointerType>(i8p))});

  llvm::ArrayType *arr_ty = llvm::ArrayType::get(elt_ty, 1);
  llvm::Constant *arr_init = llvm::ConstantArray::get(arr_ty, {ctor_entry});

  if (module->getGlobalVariable("llvm.global_ctors")) {
    return;
  }
  new llvm::GlobalVariable(*module, arr_ty, false,
                           llvm::GlobalValue::AppendingLinkage, arr_init,
                           "llvm.global_ctors");
}

} // namespace

IRGenerator::IRGenerator(IRGenContext &ir_gen_context)
    : m_ir_gen_context(ir_gen_context) {}

void IRGenerator::generate() {
  m_ir_gen_context.getCompilationContext().getBoundTree()->accept(this);
  m_ir_gen_context.storeLLVMIr();
}

llvm::Function *IRGenerator::createEntryPointFunction() {

  llvm::Type *intType =
      llvm::Type::getInt32Ty(*m_ir_gen_context.getLLVMContext());
  llvm::Type *charType =
      llvm::Type::getInt8Ty(*m_ir_gen_context.getLLVMContext());
  llvm::Type *charPtrType = charType->getPointerTo(); // i8* (char*)
  llvm::Type *argvType = charPtrType->getPointerTo(); // i8** (char**)

  auto function_type =
      llvm::FunctionType::get(intType, {intType, argvType}, false);

  return llvm::Function::Create(function_type, llvm::Function::ExternalLinkage,
                                constants::functions::kMain_fn.data(),
                                m_ir_gen_context.getLLVMModule());
}

void IRGenerator::handleReturn() {

  auto return_block = m_ir_gen_context.createBlock("return");
  m_ir_gen_context.createBranch(return_block);
  m_ir_gen_context.setInsertPoint(return_block);
  m_ir_gen_context.getLLVMBuilder()->CreateRet(llvm::ConstantInt::get(
      llvm::Type::getInt32Ty(*m_ir_gen_context.getLLVMContext()), 0));
}

void IRGenerator::verifyModule() {
  char *output_message = nullptr;
  // Do not use LLVMAbortProcessAction: in Release builds a verifier failure
  // calls abort(); some environments surface that as SIGBUS/SIGILL confusion.
  LLVMBool invalid = LLVMVerifyModule(
      wrap(m_ir_gen_context.getLLVMModule()),
      LLVMReturnStatusAction, &output_message);

  const flow_wing::diagnostic::SourceLocation source_location =
      m_ir_gen_context.getCompilationContext()
          .getBoundTree()
          ->getSourceLocation();

  if (invalid) {
    std::string msg = output_message ? output_message : std::string("invalid LLVM module");
    if (output_message) {
      free(output_message);
    }
    m_ir_gen_context.reportError(
        flow_wing::diagnostic::DiagnosticCode::kInternalIRGenerationError,
        {flow_wing::diagnostic::DiagnosticArg(msg)},
        source_location);
  }
}

void IRGenerator::visit(
    [[maybe_unused]] binding::BoundCompilationUnit *compilation_unit) {

  CODEGEN_DEBUG_LOG("Visiting Bound Compilation Unit", "IR GENERATION");

  llvm::Function *entry_point_function = nullptr;
  llvm::Function *brought_init_fn = nullptr;

  if (!m_ir_gen_context.getCompilationContext().getOptions()
           .emit_brought_dependency_object) {
    entry_point_function = createEntryPointFunction();
    auto entry_block = llvm::BasicBlock::Create(
        *m_ir_gen_context.getLLVMContext(), "entry", entry_point_function);
    m_ir_gen_context.setInsertPoint(entry_block);
  } else {
    llvm::Module *mod = m_ir_gen_context.getLLVMModule();
    llvm::LLVMContext &ctx = *m_ir_gen_context.getLLVMContext();
    llvm::FunctionType *init_ft =
        llvm::FunctionType::get(llvm::Type::getVoidTy(ctx), false);
    brought_init_fn = llvm::Function::Create(
        init_ft, llvm::Function::InternalLinkage, "__fw_brought_module_init",
        mod);
    llvm::BasicBlock *init_bb =
        llvm::BasicBlock::Create(ctx, "entry", brought_init_fn);
    m_ir_gen_context.setInsertPoint(init_bb);
  }
  // Brought dependency .o: no `main`; top-level statements run in
  // __fw_brought_module_init (registered as a global ctor).

  for (const auto &statement : compilation_unit->getStatements()) {
    statement->accept(this);
  }

  m_ir_gen_context.popScope();

  if (m_ir_gen_context.getCompilationContext().getOptions()
          .emit_brought_dependency_object) {
    auto &builder = m_ir_gen_context.getLLVMBuilder();
    llvm::BasicBlock *cur = builder->GetInsertBlock();
    if (cur && !cur->getTerminator()) {
      builder->CreateRetVoid();
    }
    registerGlobalCtor(m_ir_gen_context.getLLVMModule(), brought_init_fn);
    verifyModule();
    return;
  }

  handleReturn();
  CODEGEN_DEBUG_LOG("Verifying Entry Point Function", "IR GENERATION");
  llvm::verifyFunction(*entry_point_function);
  verifyModule();
}

void IRGenerator::visit(
    [[maybe_unused]] binding::BoundBlockStatement *block_statement) {
  CODEGEN_DEBUG_LOG("Visiting Bound Block Statement", "IR GENERATION");

  m_ir_gen_context.pushScope();

  for (const auto &statement : block_statement->getStatements()) {
    statement->accept(this);
    clearLast();
  }

  m_ir_gen_context.popScope();
}

void IRGenerator::visit(
    [[maybe_unused]] binding::BoundModuleStatement *module_statement) {
  CODEGEN_DEBUG_LOG("Visiting Bound Module Statement", "IR GENERATION");
  // Do not push an IR scope: module members share the entry function's symbol
  // table depth so globals and cross-statement lookups behave like top-level.
  for (const auto &statement : module_statement->getStatements()) {
    statement->accept(this);
    clearLast();
  }
}

void IRGenerator::visit([[maybe_unused]] binding::BoundParenthesizedExpression
                            *parenthesized_expression) {
  CODEGEN_DEBUG_LOG("Visiting Bound Parenthesized Expression", "IR GENERATION");
  parenthesized_expression->getExpression()->accept(this);
}

void IRGenerator::visit(binding::BoundExposeStatement *expose_statement) {
  CODEGEN_DEBUG_LOG("Visiting Bound Expose Statement", "IR GENERATION");
  // `expose` only marks symbols for importers; IR is the same as the wrapped
  // declaration (variable, type, function, class).
  expose_statement->getStatement()->accept(this);
  clearLast();
}

// BoundWhileStatement is implemented in WhileStatementIrGen.cpp
// BoundForStatement is implemented in ForStatementIrGen.cpp

// BoundBreakStatement is implemented in BreakStatementIrGen.cpp
// BoundContinueStatement is implemented in ContinueStatementIrGen.cpp

void IRGenerator::visit(binding::BoundClassStatement *statement) {
  CODEGEN_DEBUG_LOG("Visiting Bound Class Statement", "IR GENERATION");
  auto class_type = std::static_pointer_cast<types::ClassType>(
      statement->getClassSymbol()->getType());
  (void)m_ir_gen_context.getTypeBuilder()->getLLVMType(class_type.get());

  for (const auto &member_stmt : statement->getClassMemberStatements()) {
    if (member_stmt->getKind() == binding::NodeKind::kFunctionStatement) {
      member_stmt->accept(this);
    }
  }
}

void IRGenerator::visit(
    [[maybe_unused]] binding::BoundErrorStatement *statement) {
  // No code generation for error statements (e.g. break/continue outside loop).
  // Diagnostics were already reported during binding.
}
void IRGenerator::visit(
    [[maybe_unused]] binding::BoundErrorExpression *statement) {
  // No IR for error expressions; diagnostics were reported during binding.
  (void)statement;
}

namespace {

static void emitClassInstanceDefaultStringFieldsImpl(
    types::ClassType *root_class, types::ClassType *level,
    llvm::StructType *struct_type, llvm::Value *heap_ptr, IRGenContext &ctx,
    llvm::Constant *empty_str_const) {
  auto &builder = ctx.getLLVMBuilder();
  auto *str_ty = analysis::Builtins::m_str_type_instance.get();
  if (level->getBaseClass()) {
    emitClassInstanceDefaultStringFieldsImpl(
        root_class, level->getBaseClass().get(), struct_type, heap_ptr, ctx,
        empty_str_const);
  }
  for (const auto &[name, sym] : level->getFieldMembers()) {
    if (sym->getKind() != analysis::SymbolKind::kVariable)
      continue;
    types::Type *ft = sym->getType().get();
    if (*ft == *str_ty) {
      int idx = root_class->getMemberFieldIndex(name);
      assert(idx >= 0 && "str field must appear in class layout");
      llvm::Value *field_ptr = builder->CreateStructGEP(
          struct_type, heap_ptr, static_cast<unsigned>(idx), "strdef." + name);
      builder->CreateStore(empty_str_const, field_ptr);
    }
  }
}

static void emitClassInstanceDefaultStringFields(types::ClassType *ct,
                                                 llvm::StructType *struct_type,
                                                 llvm::Value *heap_ptr,
                                                 IRGenContext &ctx) {
  llvm::Constant *empty =
      ctx.getDefaultValue(analysis::Builtins::m_str_type_instance.get(), false);
  emitClassInstanceDefaultStringFieldsImpl(ct, ct, struct_type, heap_ptr, ctx,
                                           empty);
}

} // namespace

// BoundTernaryExpression is implemented in TernaryExpressionIrGen.cpp
void IRGenerator::visit(binding::BoundNewExpression *new_expr) {
  CODEGEN_DEBUG_LOG("Visiting Bound New Expression", "IR GENERATION");
  auto class_type_shared = new_expr->getType();
  auto *class_type = class_type_shared.get();
  assert(class_type->getKind() == types::TypeKind::kClass &&
         "New expression type must be a class");
  auto *ct = static_cast<types::ClassType *>(class_type);
  auto *llvm_type = m_ir_gen_context.getTypeBuilder()->getLLVMType(class_type);
  assert(llvm_type->isStructTy() && "Class LLVM type must be a struct");
  auto *struct_type = llvm::cast<llvm::StructType>(llvm_type);

  // Classes used only via `module::Class` may not appear in the importer's
  // merged global symbol table, so declareClassSymbolsFromGlobalScope never
  // emitted extern `__vt_*`. Ensure layout / vtable externs before loading.
  GlobalDeclarationsInitializer decl_helper(m_ir_gen_context);
  decl_helper.ensureImportedClassExterns(ct);

  auto &builder = m_ir_gen_context.getLLVMBuilder();
  auto *gc_malloc = m_ir_gen_context.getLLVMModule()->getFunction(
      std::string(constants::functions::kGC_malloc_fn));
  assert(gc_malloc && "GC_malloc function not found");
  const llvm::DataLayout &dl =
      m_ir_gen_context.getLLVMModule()->getDataLayout();
  uint64_t type_size_bytes = dl.getTypeAllocSize(struct_type);
  llvm::CallInst *malloc_call = builder->CreateCall(
      gc_malloc, llvm::ConstantInt::get(
                     llvm::Type::getInt64Ty(*m_ir_gen_context.getLLVMContext()),
                     type_size_bytes));
  malloc_call->setTailCall(false);
  auto *heap_ptr = builder->CreateBitCast(
      malloc_call, struct_type->getPointerTo(), "new." + class_type->getName());
  builder->CreateStore(llvm::ConstantAggregateZero::get(struct_type), heap_ptr);

  const std::string vt_name = std::string("__vt_") + ct->getName();
  llvm::GlobalVariable *vt_global =
      m_ir_gen_context.getLLVMModule()->getGlobalVariable(vt_name, true);
  assert(vt_global && "class vtable global must exist before new()");
  llvm::Value *vtable_as_ptr = builder->CreateBitCast(
      vt_global, builder->getPtrTy(), "vtable." + ct->getName());
  llvm::Value *vptr_field =
      builder->CreateStructGEP(struct_type, heap_ptr, 0, "vptr_slot");
  builder->CreateStore(vtable_as_ptr, vptr_field);

  emitClassInstanceDefaultStringFields(ct, struct_type, heap_ptr,
                                       m_ir_gen_context);

  emitClassInstanceFieldInitializers(ct, struct_type, heap_ptr);

  // Store heap pointer into a local alloca so that the rest of the pipeline
  // (emitTypedStore, argument passing) can treat it uniformly as alloca→ptr.
  llvm::Value *alloca = m_ir_gen_context.createAlloca(
      builder->getPtrTy(), "new." + class_type->getName() + ".slot");
  builder->CreateStore(heap_ptr, alloca);

  const auto &ctor_args = new_expr->getArguments();
  std::vector<std::shared_ptr<types::Type>> ctor_arg_types;
  for (const auto &a : ctor_args) {
    ctor_arg_types.push_back(a->getType());
  }
  std::shared_ptr<analysis::Symbol> init_member =
      ct->resolveMethodForCall("init", ctor_arg_types);

  if (init_member &&
      init_member->getKind() == analysis::SymbolKind::kFunction) {
    auto *init_fn_symbol =
        static_cast<analysis::FunctionSymbol *>(init_member.get());
    auto *init_fn_type =
        static_cast<types::FunctionType *>(init_fn_symbol->getType().get());

    auto *llvm_init_fn = m_ir_gen_context.getLLVMModule()->getFunction(
        init_fn_symbol->getMangledName());
    assert(llvm_init_fn && "init function not found in LLVM module");

    std::vector<llvm::Value *> llvm_args;

    bool is_void_return = true;
    bool is_ret_via_arg = false;
    if (!init_fn_type->getReturnTypes().empty()) {
      auto *ret_raw = init_fn_type->getReturnTypes()[0]->type.get();
      is_void_return =
          (*ret_raw == *analysis::Builtins::m_nthg_type_instance.get()) &&
          !ret_raw->isDynamic();
      is_ret_via_arg = !is_void_return &&
                       init_fn_type->getReturnTypes()[0]->type_convention !=
                           types::TypeConvention::kC;
    }
    if (is_ret_via_arg) {
      auto *ret_slot = m_ir_gen_context.createAlloca(
          m_ir_gen_context.getTypeBuilder()->createOrGetStructType(
              {init_fn_type->getReturnTypes()[0]->type.get()}),
          "init_ret_slot");
      llvm_args.push_back(ret_slot);
    }

    const auto &param_types = init_fn_type->getParameterTypes();
    const size_t visible_param_count = param_types.size() - 1; // exclude self
    const size_t default_start = init_fn_type->getDefaultValueStartIndex();

    auto emit_one_init_param = [&](size_t i) {
      assert(m_last_value && "m_last_value is null");
      auto *param_raw_type = param_types[i]->type.get();

      llvm::Value *arg_slot = nullptr;
      llvm::Value *val = nullptr;
      if (param_raw_type->getKind() == types::TypeKind::kObject ||
          param_raw_type->getKind() == types::TypeKind::kClass) {
        arg_slot =
            m_ir_gen_context.createAlloca(builder->getPtrTy(), "init_obj_arg");
        if (llvm::isa<llvm::AllocaInst>(m_last_value) ||
            llvm::isa<llvm::GlobalVariable>(m_last_value)) {
          val = builder->CreateLoad(m_ir_gen_context.getTypeBuilder()
                                        ->getLLVMType(param_raw_type)
                                        ->getPointerTo(),
                                    m_last_value, "heap_ptr");
        } else {
          val = m_last_value;
        }
        builder->CreateStore(val, arg_slot);
      } else {
        arg_slot = m_ir_gen_context.createAlloca(
            m_ir_gen_context.getTypeBuilder()->getLLVMType(param_raw_type),
            "init_arg");
        val = resolveValue(m_last_value, m_last_type);
        emitTypedStore(arg_slot, param_raw_type, val, m_last_type);
      }
      llvm_args.push_back(arg_slot);
      clearLast();
    };

    for (size_t i = 0; i < visible_param_count; i++) {
      if (i < ctor_args.size()) {
        ctor_args[i]->accept(this);
      } else {
        if (default_start == static_cast<size_t>(-1) || i < default_start) {
          assert(false && "missing ctor argument without default value");
        }
        auto *param_sym = init_fn_symbol->getParameters()[i].get();
        assert(param_sym->getDefaultValueExpression() &&
               "default value missing for init parameter");
        param_sym->getDefaultValueExpression()->accept(this);
      }
      emit_one_init_param(i);
    }

    // self argument (last parameter) — alloca is already ptr* holding heap_ptr
    llvm_args.push_back(alloca);

    builder->CreateCall(llvm_init_fn, llvm_args);
  }

  m_last_value = alloca;
  m_last_llvm_type = llvm_type->getPointerTo();
  m_last_type = new_expr->getType().get();
}

void IRGenerator::visit([[maybe_unused]] binding::BoundDimensionClauseExpression
                            *dimension_clause_expression) {
  CODEGEN_DEBUG_LOG("Visiting Bound Dimension Clause Expression",
                    "IR GENERATION");
  dimension_clause_expression->getDimensionExpression()->accept(this);
}

void IRGenerator::visit(
    [[maybe_unused]] binding::BoundExpressionStatement *expression_statement) {
  CODEGEN_DEBUG_LOG("Visiting Bound Expression Statement", "IR GENERATION");

  expression_statement->getExpression()->accept(this);
}
void IRGenerator::visit(
    binding::BoundModuleAccessExpression *module_access_expression) {
  CODEGEN_DEBUG_LOG("Visiting Bound Module Access Expression", "IR GENERATION");
  module_access_expression->getMemberAccessExpression()->accept(this);
}

llvm::Value *IRGenerator::resolveValue(llvm::Value *value, types::Type *type) {

  if (type->isDynamic()) {
    return value;
  }

  // Literal Null check (Nir)
  if (llvm::isa<llvm::ConstantPointerNull>(value)) {
    return value;
  }

  if (type->getKind() == types::TypeKind::kObject ||
      type->getKind() == types::TypeKind::kClass) {
    if (llvm::isa<llvm::AllocaInst>(value) ||
        llvm::isa<llvm::GlobalVariable>(value)) {
      auto *ptr_type =
          m_ir_gen_context.getTypeBuilder()->getLLVMType(type)->getPointerTo();
      return m_ir_gen_context.getLLVMBuilder()->CreateLoad(ptr_type, value,
                                                           "load_class_or_obj");
    }
    return ensurePointer(value, type, "aggregate_spill");
  }

  if (llvm::isa<llvm::AllocaInst>(value)) {
    auto expected_llvm_type =
        m_ir_gen_context.getTypeBuilder()->getLLVMType(type);
    return m_ir_gen_context.getLLVMBuilder()->CreateLoad(expected_llvm_type,
                                                         value, "load_var");
  }

  if (llvm::isa<llvm::Argument>(value) && value->getType()->isPointerTy()) {
    auto expected_llvm_type =
        m_ir_gen_context.getTypeBuilder()->getLLVMType(type);
    return m_ir_gen_context.getLLVMBuilder()->CreateLoad(expected_llvm_type,
                                                         value, "arg_load");
  }

  // Handle GEPs (Instructions and Constant Expressions); GetElementPtrInst
  // may not cast to GEPOperator in all LLVM versions.
  llvm::Type *source_elem_ty = nullptr;
  if (auto *gep_inst = llvm::dyn_cast<llvm::GetElementPtrInst>(value)) {
    source_elem_ty = gep_inst->getSourceElementType();
  } else if (auto *gep_op = llvm::dyn_cast<llvm::GEPOperator>(value)) {
    source_elem_ty = gep_op->getSourceElementType();
  }
  if (source_elem_ty) {
    auto expected_llvm_type =
        m_ir_gen_context.getTypeBuilder()->getLLVMType(type);

    if (source_elem_ty->isStructTy()) {
      return m_ir_gen_context.getLLVMBuilder()->CreateLoad(expected_llvm_type,
                                                           value, "field_load");
    }

    if (source_elem_ty->isArrayTy()) {
      auto *array_type = llvm::cast<llvm::ArrayType>(source_elem_ty);
      llvm::Type *element_type = array_type->getElementType();

      if (element_type->isIntegerTy(8) && expected_llvm_type->isPointerTy()) {
        return value;
      }

      return m_ir_gen_context.getLLVMBuilder()->CreateLoad(expected_llvm_type,
                                                           value, "array_load");
    }
  }

  if (auto *globalVar = llvm::dyn_cast<llvm::GlobalVariable>(value)) {
    if (globalVar->getValueType()->isArrayTy()) {
      std::vector<llvm::Value *> indices = {
          m_ir_gen_context.getLLVMBuilder()->getInt32(0),
          m_ir_gen_context.getLLVMBuilder()->getInt32(0)};
      return m_ir_gen_context.getLLVMBuilder()->CreateInBoundsGEP(
          globalVar->getValueType(), globalVar, indices, "str_ptr");
    }

    auto expected_llvm_type =
        m_ir_gen_context.getTypeBuilder()->getLLVMType(type);
    return m_ir_gen_context.getLLVMBuilder()->CreateLoad(
        expected_llvm_type, globalVar, "global_load");
  }

  auto expected_llvm_type =
      m_ir_gen_context.getTypeBuilder()->getLLVMType(type);
  if (value->getType()->isPointerTy() &&
      value->getType() != expected_llvm_type) {
    return m_ir_gen_context.getLLVMBuilder()->CreateLoad(expected_llvm_type,
                                                         value, "load_val");
  }

  return value;
}

void IRGenerator::visit(binding::BoundColonExpression *colon_expression) {
  // Object literals are usually handled by BoundObjectExpression; if a colon
  // node is visited directly, evaluate the field value like ObjectExpressionIrGen.
  CODEGEN_DEBUG_LOG("Visiting Bound Colon Expression", "IR GENERATION");
  colon_expression->getRightExpression()->accept(this);
}

llvm::Value *IRGenerator::ensurePointer(llvm::Value *value, types::Type *type,
                                        const std::string &name_suffix) {

  if (value->getType()->isPointerTy()) {
    return value;
  }

  //  Value (Register) to Pointer conversion
  auto *llvm_type = m_ir_gen_context.getTypeBuilder()->getLLVMType(type);
  auto *alloca_inst =
      m_ir_gen_context.createAlloca(llvm_type, "spill_" + name_suffix);

  m_ir_gen_context.getLLVMBuilder()->CreateStore(value, alloca_inst);

  return alloca_inst;
}

void IRGenerator::emitClassInstanceFieldInitializersImpl(
    types::ClassType *root_class, types::ClassType *level,
    llvm::StructType *struct_type, llvm::Value *heap_ptr) {
  if (level->getBaseClass()) {
    emitClassInstanceFieldInitializersImpl(
        root_class, level->getBaseClass().get(), struct_type, heap_ptr);
  }
  auto &builder = m_ir_gen_context.getLLVMBuilder();
  for (const auto &[name, sym] : level->getFieldMembers()) {
    if (sym->getKind() != analysis::SymbolKind::kVariable)
      continue;
    auto *vs = static_cast<analysis::VariableSymbol *>(sym.get());
    const auto &init_expr = vs->getInitializerExpression();
    if (!init_expr)
      continue;
    if (init_expr->getKind() == binding::NodeKind::kErrorExpression)
      continue;

    types::Type *field_ty = sym->getType().get();
    int idx = root_class->getMemberFieldIndex(name);
    assert(idx >= 0 && "class field must have LLVM layout index");
    llvm::Value *field_ptr = builder->CreateStructGEP(
        struct_type, heap_ptr, static_cast<unsigned>(idx), "fldinit." + name);

    init_expr->accept(this);
    assert(m_last_value && "class field initializer produced no value");
    emitTypedStore(field_ptr, field_ty, m_last_value, m_last_type);
    clearLast();
  }
}

void IRGenerator::emitClassInstanceFieldInitializers(
    types::ClassType *root_class, llvm::StructType *struct_type,
    llvm::Value *heap_ptr) {
  emitClassInstanceFieldInitializersImpl(root_class, root_class, struct_type,
                                         heap_ptr);
}

} // namespace ir_gen
} // namespace flow_wing