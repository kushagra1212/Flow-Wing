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

#include "GlobalDeclarationsInitializer.hpp"
#include "src/IRGen/IRGenContext/IRGenContext.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundLiteralExpression/BoundIntegerLiteralExpression/BoundIntegerLiteralExpression.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundLiteralExpression/BoundCharacterLiteralExpression/BoundCharacterLiteralExpression.hpp"
#include "src/SemanticAnalyzer/NodeKind/NodeKind.h"
#include "src/SemanticAnalyzer/BoundExpressions/BoundLiteralExpression/BoundFloatLiteralExpression/BoundFloatLiteralExpression.hpp"
#include "src/SemanticAnalyzer/BoundStatements/BoundBlockStatement/BoundBlockStatement.h"
#include "src/SemanticAnalyzer/BoundStatements/BoundClassStatement/BoundClassStatement.hpp"
#include "src/SemanticAnalyzer/BoundStatements/BoundExposeStatement/BoundExposeStatement.hpp"
#include "src/SemanticAnalyzer/BoundStatements/BoundModuleStatement/BoundModuleStatement.hpp"
#include "src/SemanticAnalyzer/Builtins/Builtins.hpp"
#include "src/SemanticAnalyzer/SyntaxBinder/BoundCompilationUnit.hpp"
#include "src/common/Symbol/FunctionSymbol.hpp"
#include "src/common/Symbol/ModuleSymbol.hpp"
#include "src/common/Symbol/ModuleSymbol.hpp"
#include "src/common/Symbol/ScopedSymbolTable/ScopedSymbolTable.hpp"
#include "src/common/Symbol/Symbol.hpp"
#include "src/common/Symbol/VariableSymbol.hpp"
#include "src/common/types/ClassType/ClassType.hpp"
#include "src/common/types/FunctionType/FunctionType.hpp"
#include "src/compiler/CompilationContext/CompilationContext.h"
#include "llvm/IR/Attributes.h"
#include "llvm/IR/Constant.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/GlobalVariable.h"
#include "llvm/IR/Instructions.h"
#include "llvm/TargetParser/Host.h"

#include <string>
#include <vector>

namespace flow_wing {
namespace ir_gen {

/// Matches `LLVMTypeBuilder::convertFunction`: hidden `i8*` only when the
/// function returns a non-`nthg` value using the FlowWing convention (void +
/// return buffer).
static bool needsHiddenReturnPointer(const types::FunctionType *function_type) {
  const auto &rets = function_type->getReturnTypes();
  if (rets.empty())
    return false;
  const auto *r0 = rets[0].get();
  return r0->type_convention == types::TypeConvention::kFlowWing &&
         !r0->type->isNthg();
}

static bool targetTripleNeedsX86Sret(IRGenContext &ir_ctx) {
  std::string target_triple = ir_ctx.getLLVMModule()->getTargetTriple();
  if (target_triple.empty())
    target_triple = llvm::sys::getDefaultTargetTriple();
  return target_triple.find("x86_64") != std::string::npos ||
         target_triple.find("amd64") != std::string::npos;
}

namespace {

/// SysV x86-64 (typical Linux CI) requires `sret` on the hidden return pointer;
/// without it LLVM may not follow the ABI and callers read uninitialized
/// memory. Do **not** apply on AArch64 / Apple Silicon: the ABI differs and
/// adding `sret` miscompiles (e.g. runtime null receiver).
void addHiddenStructReturnAttr(IRGenContext &ir_ctx, llvm::Function *llvm_function,
                               const types::FunctionType *function_type) {
  if (!needsHiddenReturnPointer(function_type))
    return;
  if (!targetTripleNeedsX86Sret(ir_ctx))
    return;
  std::vector<types::Type *> rts;
  rts.reserve(function_type->getReturnTypes().size());
  for (const auto &r : function_type->getReturnTypes())
    rts.push_back(r->type.get());
  llvm::StructType *sret_struct =
      ir_ctx.getTypeBuilder()->createOrGetStructType(rts);
  llvm_function->addParamAttr(
      0, llvm::Attribute::getWithStructRetType(
             ir_ctx.getLLVMModule()->getContext(), sret_struct));
}

} // namespace

void applyHiddenStructReturnAttrToCall(
    IRGenContext &ir_ctx, llvm::CallInst *call,
    const types::FunctionType *function_type,
    llvm::StructType *return_struct_type) {
  if (!call || !needsHiddenReturnPointer(function_type) || !return_struct_type)
    return;
  if (!targetTripleNeedsX86Sret(ir_ctx))
    return;
  call->addParamAttr(
      0, llvm::Attribute::getWithStructRetType(
             ir_ctx.getLLVMModule()->getContext(), return_struct_type));
}

GlobalDeclarationsInitializer::GlobalDeclarationsInitializer(
    IRGenContext &ir_gen_context)
    : m_ir_gen_context(ir_gen_context) {}

void GlobalDeclarationsInitializer::initialize() {
  m_ir_gen_context.getCompilationContext().getBoundTree()->accept(this);
  m_ir_gen_context.storeLLVMIr();
}

void GlobalDeclarationsInitializer::declareFunctionsRecursively(
    analysis::ScopedSymbolTable *symbol_table) {
  declareFunctions(symbol_table);
  symbol_table->lookupSymbol(
      [&](const analysis::Symbol *symbol) {
        if (symbol->getKind() == analysis::SymbolKind::kModule) {
          const auto *mod =
              static_cast<const analysis::ModuleSymbol *>(symbol);
          auto *inner = mod->getModuleSymbolTable().get();
          // Module self-alias (`m` in module `m`'s table) points at the same
          // symbol table; avoid infinite recursion.
          if (inner != symbol_table) {
            declareFunctionsRecursively(inner);
          }
        }
        return true;
      },
      analysis::SymbolKind::kModule);
}

void GlobalDeclarationsInitializer::declareGlobalVariablesFromSymbolTableRecursively(
    analysis::ScopedSymbolTable *symbol_table,
    bool inside_brought_module) {
  declareGlobalVariablesFromSymbolTable(symbol_table, inside_brought_module);
  symbol_table->lookupSymbol(
      [&](const analysis::Symbol *symbol) {
        if (symbol->getKind() == analysis::SymbolKind::kModule) {
          const auto *mod = static_cast<const analysis::ModuleSymbol *>(symbol);
          auto *inner = mod->getModuleSymbolTable().get();
          if (inner != symbol_table) {
            const bool nested_inside =
                inside_brought_module || mod->isImportedViaBring();
            declareGlobalVariablesFromSymbolTableRecursively(inner,
                                                               nested_inside);
          }
        }
        return true;
      },
      analysis::SymbolKind::kModule);
}

void GlobalDeclarationsInitializer::declareFunctions(
    analysis::ScopedSymbolTable *global_symbol_table) {
  global_symbol_table->lookupSymbol(
      [&](const analysis::Symbol *symbol) {
        auto function_symbol =
            static_cast<const analysis::FunctionSymbol *>(symbol);

        // Skip built-in functions as they are not native functions
        if (analysis::Builtins::isBuiltInFunction(function_symbol->getName())) {
          return true;
        }

        llvm::Module *llvm_module = m_ir_gen_context.getLLVMModule();
        if (llvm_module->getFunction(function_symbol->getMangledName())) {
          return true;
        }

        auto function_type = static_cast<const types::FunctionType *>(
            function_symbol->getType().get());

        auto llvm_function_type =
            m_ir_gen_context.getTypeBuilder()->convertFunction(function_type);

        auto is_return_by_reference =
            function_type->getReturnTypes()[0]->type_convention ==
            types::TypeConvention::kFlowWing;
        // External linkage so definitions are exported from each .o file and
        // unresolved references from other TUs resolve at link time.
        auto llvm_function = llvm::Function::Create(
            llvm_function_type, llvm::Function::ExternalLinkage,
            function_symbol->getMangledName(), llvm_module);

        addHiddenStructReturnAttr(m_ir_gen_context, llvm_function,
                                  function_type);

        if (!is_return_by_reference) {
          size_t arg_idx = 0;
          for (auto &arg : llvm_function->args()) {

            // Get the original FlowWing parameter type
            auto param_fw_type =
                function_type->getParameterTypes()[arg_idx]->type.get();

            // Sign Extension (SExt) [Sign Extension is a way to convert a
            // smaller integer type to a larger integer type while preserving
            // the sign of the original value.]
            if (param_fw_type ==
                analysis::Builtins::m_int8_type_instance.get()) {
              arg.addAttr(llvm::Attribute::SExt);
            }

            arg_idx++;
          }
        }

        CODEGEN_DEBUG_LOG("Declared Function: ", function_symbol->getName());
        return true;
      },
      analysis::SymbolKind::kFunction);
}

void GlobalDeclarationsInitializer::visit(
    binding::BoundCompilationUnit *compilation_unit) {

  const auto &global_symbol_table = compilation_unit->getSymbolTable();

  // Declare Built-in Functions
  declareFunctionsRecursively(global_symbol_table.get());

  for (const auto &statement : compilation_unit->getStatements()) {
    statement->accept(this);
  }

  // Symbols merged from `bring` have no BoundVariableDeclaration /
  // BoundClassStatement in this file; emit their LLVM globals and class
  // metadata so IRGen can resolve identifiers and method calls.
  declareGlobalVariablesFromSymbolTableRecursively(global_symbol_table.get());
  declareClassSymbolsFromGlobalScope(global_symbol_table.get());

  CODEGEN_DEBUG_LOG("Global Declarations Initialized", "");
}

void GlobalDeclarationsInitializer::emitGlobalVariableForSymbol(
    const analysis::VariableSymbol *variable_symbol, bool force_extern_import) {

  auto *module = m_ir_gen_context.getLLVMModule();

  auto variable_type = variable_symbol->getType().get();
  auto llvm_type =
      m_ir_gen_context.getTypeBuilder()->getLLVMType(variable_type);

  CODEGEN_DEBUG_LOG("Variable Type", variable_type->getName());

  assert(llvm_type && "LLVM type is null");

  const bool imported =
      variable_symbol->isImportedViaBring() || force_extern_import;

  // Already handled in SemanticAnalyzer
  bool is_llvm_constant = false;

  llvm::Constant *default_value = nullptr;

  if (variable_type->getKind() == types::TypeKind::kObject ||
      variable_type->getKind() == types::TypeKind::kArray ||
      variable_type->getKind() == types::TypeKind::kClass) {
    llvm_type = llvm_type->getPointerTo();
    if (!imported) {
      default_value = llvm::ConstantPointerNull::get(
          llvm::cast<llvm::PointerType>(llvm_type));
    }
  } else if (!imported) {
    const auto *init_expr = variable_symbol->getInitializerExpression().get();
    if (init_expr &&
        init_expr->getKind() == binding::NodeKind::kNumberLiteralExpression &&
        variable_type == analysis::Builtins::m_int32_type_instance.get()) {
      const auto *lit = static_cast<const binding::BoundIntegerLiteralExpression *>(
          init_expr);
      default_value = llvm::ConstantInt::get(
          llvm::cast<llvm::IntegerType>(llvm_type),
          static_cast<uint64_t>(lit->getValue()), /*isSigned=*/true);
    } else {
      default_value = m_ir_gen_context.getDefaultValue(variable_type, true);
    }
  }

  // Imported globals are extern declarations (resolved in another .o).
  // Definitions use external linkage so the symbol is exported from its .o.
  auto *globalVar = new llvm::GlobalVariable(
      *module, llvm_type, is_llvm_constant,
      llvm::GlobalValue::ExternalLinkage,
      imported ? nullptr : default_value, variable_symbol->getName());

  m_ir_gen_context.setSymbol(variable_symbol->getName(), globalVar);

  CODEGEN_DEBUG_LOG("Global Variable Declared", variable_symbol->getName());
}

void GlobalDeclarationsInitializer::declareGlobalVariablesFromSymbolTable(
    analysis::ScopedSymbolTable *symbol_table, bool force_extern_for_variables) {
  llvm::Module *llvm_module = m_ir_gen_context.getLLVMModule();
  symbol_table->forEachGlobalSymbol(
      [&](const std::string &name,
          const std::shared_ptr<analysis::Symbol> &symbol) {
        if (symbol->getKind() != analysis::SymbolKind::kVariable) {
          return;
        }
        if (m_ir_gen_context.getSymbol(name)) {
          return;
        }
        if (llvm::GlobalVariable *gv =
                llvm_module->getGlobalVariable(name, true)) {
          m_ir_gen_context.setSymbol(name, gv);
          return;
        }
        emitGlobalVariableForSymbol(
            static_cast<const analysis::VariableSymbol *>(symbol.get()),
            force_extern_for_variables);
      });
}

// Global Variable Declarations
void GlobalDeclarationsInitializer::visit(
    binding::BoundVariableDeclaration *variable_declaration) {

  CODEGEN_DEBUG_LOG("Visiting Bound Variable Declaration", "");

  for (const auto &symbol : variable_declaration->getSymbols()) {
    const auto &variable_symbol =
        static_cast<const analysis::VariableSymbol *>(symbol.get());
    emitGlobalVariableForSymbol(variable_symbol);
  }
}

void GlobalDeclarationsInitializer::visit(
    [[maybe_unused]] binding::BoundFunctionStatement *function_statement) {}

void GlobalDeclarationsInitializer::visit(
    [[maybe_unused]] binding::BoundNewExpression *new_expression) {}

void GlobalDeclarationsInitializer::visit(
    binding::BoundBlockStatement *block_statement) {
  for (const auto &statement : block_statement->getStatements()) {
    statement->accept(this);
  }
}

void GlobalDeclarationsInitializer::visit(
    binding::BoundModuleStatement *module_statement) {
  for (const auto &statement : module_statement->getStatements()) {
    statement->accept(this);
  }
}
void GlobalDeclarationsInitializer::visit(
    binding::BoundExposeStatement *expose_statement) {
  expose_statement->getStatement()->accept(this);
}
void GlobalDeclarationsInitializer::visit(
    [[maybe_unused]] binding::BoundCustomTypeStatement *custom_type_statement) {
}
void GlobalDeclarationsInitializer::visit(
    [[maybe_unused]] binding::BoundIfStatement *if_statement) {}
void GlobalDeclarationsInitializer::visit(
    [[maybe_unused]] binding::BoundWhileStatement *while_statement) {}
void GlobalDeclarationsInitializer::visit(
    [[maybe_unused]] binding::BoundForStatement *for_statement) {}
void GlobalDeclarationsInitializer::visit(
    [[maybe_unused]] binding::BoundBreakStatement *break_statement) {}
void GlobalDeclarationsInitializer::visit(
    [[maybe_unused]] binding::BoundContinueStatement *continue_statement) {}
void GlobalDeclarationsInitializer::visit(
    [[maybe_unused]] binding::BoundReturnStatement *return_statement) {}
void GlobalDeclarationsInitializer::visit(
    [[maybe_unused]] binding::BoundSwitchStatement *switch_statement) {}
void GlobalDeclarationsInitializer::emitClassLayoutAndVtable(
    types::ClassType *class_type) {

  (void)m_ir_gen_context.getTypeBuilder()->getLLVMType(class_type);

  llvm::Module *llvm_module = m_ir_gen_context.getLLVMModule();
  class_type->forEachFunctionMember(
      [&](const std::shared_ptr<analysis::Symbol> &symbol) {
        auto *function_symbol =
            static_cast<const analysis::FunctionSymbol *>(symbol.get());
        if (llvm_module->getFunction(function_symbol->getMangledName())) {
          return;
        }
        auto *function_type = static_cast<const types::FunctionType *>(
            function_symbol->getType().get());

        auto *llvm_function_type =
            m_ir_gen_context.getTypeBuilder()->convertFunction(function_type);

        llvm::Function *llvm_fn = llvm::Function::Create(
            llvm_function_type, llvm::Function::ExternalLinkage,
            function_symbol->getMangledName(), llvm_module);
        addHiddenStructReturnAttr(m_ir_gen_context, llvm_fn, function_type);
      });

  llvm::Module *module = m_ir_gen_context.getLLVMModule();
  llvm::LLVMContext &ctx = *m_ir_gen_context.getLLVMContext();
  llvm::PointerType *i8p = llvm::Type::getInt8PtrTy(ctx);
  const std::string vt_global_name = "__vt_" + class_type->getName();
  // Avoid duplicate globals if this visitor is ever reached twice for the same
  // class (should not happen for a well-formed program).
  if (module->getGlobalVariable(vt_global_name, true)) {
    return;
  }

  const auto &vtable = class_type->getVtableEntries();
  std::vector<llvm::Constant *> elems;
  elems.reserve(vtable.size());
  for (const auto &sym : vtable) {
    llvm::Function *fn = module->getFunction(sym->getMangledName());
    if (!fn) {
      // In Release builds, assert is stripped; bitcasting nullptr is UB and
      // often surfaces as SIGBUS. Preserve slot count with a null pointer; the
      // verifier still accepts the module. (Missing fn usually indicates a
      // codegen ordering bug for inherited vtable entries.)
      elems.push_back(llvm::ConstantPointerNull::get(i8p));
      continue;
    }
    assert(fn && "vtable entry: LLVM function must exist");
    elems.push_back(llvm::ConstantExpr::getBitCast(fn, i8p));
  }
  llvm::ArrayType *arr_ty = llvm::ArrayType::get(i8p, elems.size());
  llvm::Constant *init = elems.empty()
                             ? llvm::ConstantAggregateZero::get(arr_ty)
                             : llvm::ConstantArray::get(arr_ty, elems);
  // Link-once so a single strong definition is visible across object files when
  // needed; other TUs may reference the same symbol as extern.
  new llvm::GlobalVariable(*module, arr_ty, true,
                           llvm::GlobalValue::LinkOnceODRLinkage, init,
                           vt_global_name);
}

void GlobalDeclarationsInitializer::declareImportedClassExterns(
    types::ClassType *class_type) {

  (void)m_ir_gen_context.getTypeBuilder()->getLLVMType(class_type);

  llvm::Module *llvm_module = m_ir_gen_context.getLLVMModule();
  class_type->forEachFunctionMember(
      [&](const std::shared_ptr<analysis::Symbol> &symbol) {
        auto *function_symbol =
            static_cast<const analysis::FunctionSymbol *>(symbol.get());
        if (llvm_module->getFunction(function_symbol->getMangledName())) {
          return;
        }
        auto *function_type = static_cast<const types::FunctionType *>(
            function_symbol->getType().get());

        auto *llvm_function_type =
            m_ir_gen_context.getTypeBuilder()->convertFunction(function_type);

        llvm::Function *llvm_fn = llvm::Function::Create(
            llvm_function_type, llvm::Function::ExternalLinkage,
            function_symbol->getMangledName(), llvm_module);
        addHiddenStructReturnAttr(m_ir_gen_context, llvm_fn, function_type);
      });

  llvm::LLVMContext &ctx = *m_ir_gen_context.getLLVMContext();
  llvm::PointerType *i8p = llvm::Type::getInt8PtrTy(ctx);
  const std::string vt_global_name = "__vt_" + class_type->getName();
  if (llvm_module->getGlobalVariable(vt_global_name, true)) {
    return;
  }

  const auto &vtable = class_type->getVtableEntries();
  llvm::ArrayType *arr_ty = llvm::ArrayType::get(i8p, vtable.size());
  new llvm::GlobalVariable(*llvm_module, arr_ty, true,
                           llvm::GlobalValue::ExternalLinkage, nullptr,
                           vt_global_name);
}

void GlobalDeclarationsInitializer::ensureImportedClassExterns(
    types::ClassType *class_type) {
  declareImportedClassExterns(class_type);
}

void GlobalDeclarationsInitializer::declareClassSymbolsFromGlobalScope(
    analysis::ScopedSymbolTable *symbol_table) {
  symbol_table->forEachGlobalSymbol(
      [&](const std::string &name,
          const std::shared_ptr<analysis::Symbol> &symbol) {
        (void)name;
        if (symbol->getKind() != analysis::SymbolKind::kClass) {
          return;
        }
        auto class_type = std::dynamic_pointer_cast<types::ClassType>(
            symbol->getType());
        if (!class_type) {
          return;
        }
        llvm::Module *module = m_ir_gen_context.getLLVMModule();
        const std::string vt_global_name = "__vt_" + class_type->getName();
        if (module->getGlobalVariable(vt_global_name, true)) {
          return;
        }
        if (symbol->isImportedViaBring()) {
          declareImportedClassExterns(class_type.get());
          return;
        }
        emitClassLayoutAndVtable(class_type.get());
      });
}

void GlobalDeclarationsInitializer::visit(
    [[maybe_unused]] binding::BoundClassStatement *class_statement) {
  auto class_type = std::static_pointer_cast<types::ClassType>(
      class_statement->getClassSymbol()->getType());
  emitClassLayoutAndVtable(class_type.get());
}
void GlobalDeclarationsInitializer::visit(
    [[maybe_unused]] binding::BoundIdentifierExpression
        *identifier_expression) {}
void GlobalDeclarationsInitializer::visit(
    [[maybe_unused]] binding::BoundIndexExpression *index_expression) {}
void GlobalDeclarationsInitializer::visit(
    [[maybe_unused]] binding::BoundIntegerLiteralExpression
        *integer_literal_expression) {}

void GlobalDeclarationsInitializer::visit(
    [[maybe_unused]] binding::BoundContainerExpression *container_expression) {}

void GlobalDeclarationsInitializer::visit(
    [[maybe_unused]] binding::BoundDoubleLiteralExpression
        *double_literal_expression) {}
void GlobalDeclarationsInitializer::visit(
    [[maybe_unused]] binding::BoundStringLiteralExpression
        *string_literal_expression) {}
void GlobalDeclarationsInitializer::visit(
    [[maybe_unused]] binding::BoundBooleanLiteralExpression
        *boolean_literal_expression) {}

void GlobalDeclarationsInitializer::visit(
    [[maybe_unused]] binding::BoundFloatLiteralExpression
        *float_literal_expression) {}

void GlobalDeclarationsInitializer::visit(
    [[maybe_unused]] binding::BoundCharacterLiteralExpression
        *character_literal_expression) {}

void GlobalDeclarationsInitializer::visit(
    [[maybe_unused]] binding::BoundTemplateStringLiteralExpression
        *template_string_literal_expression) {}

void GlobalDeclarationsInitializer::visit(
    [[maybe_unused]] binding::BoundErrorStatement *error_statement) {}
void GlobalDeclarationsInitializer::visit(
    [[maybe_unused]] binding::BoundErrorExpression *error_expression) {}
void GlobalDeclarationsInitializer::visit(
    [[maybe_unused]] binding::BoundCallExpression *call_expression) {}
void GlobalDeclarationsInitializer::visit(
    [[maybe_unused]] binding::BoundTernaryExpression *ternary_expression) {}
void GlobalDeclarationsInitializer::visit(
    [[maybe_unused]] binding::BoundUnaryExpression *unary_expression) {}
void GlobalDeclarationsInitializer::visit(
    [[maybe_unused]] binding::BoundBinaryExpression *binary_expression) {}
void GlobalDeclarationsInitializer::visit(
    [[maybe_unused]] binding::BoundAssignmentExpression
        *assignment_expression) {}
void GlobalDeclarationsInitializer::visit(
    [[maybe_unused]] binding::BoundExpressionStatement *expression_statement) {}
void GlobalDeclarationsInitializer::visit(
    [[maybe_unused]] binding::BoundModuleAccessExpression
        *module_access_expression) {}
void GlobalDeclarationsInitializer::visit(
    [[maybe_unused]] binding::BoundMemberAccessExpression
        *member_access_expression) {}
void GlobalDeclarationsInitializer::visit(
    [[maybe_unused]] binding::BoundNirastLiteralExpression
        *nirast_literal_expression) {}

void GlobalDeclarationsInitializer::visit(
    [[maybe_unused]] binding::BoundParenthesizedExpression
        *parenthesized_expression) {}

void GlobalDeclarationsInitializer::visit(
    [[maybe_unused]] binding::BoundObjectExpression *object_expression) {}

void GlobalDeclarationsInitializer::visit(
    [[maybe_unused]] binding::BoundColonExpression *colon_expression) {}
void GlobalDeclarationsInitializer::visit(
    [[maybe_unused]] binding::BoundDimensionClauseExpression
        *dimension_clause_expression) {}

} // namespace ir_gen
} // namespace flow_wing