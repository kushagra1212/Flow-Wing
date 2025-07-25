/*
 * FlowWing Compiler
 * Copyright (C) 2023-2025 Kushagra Rathore
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


#ifndef __TYPE_CONVERTER_BASE_H__
#define __TYPE_CONVERTER_BASE_H__

#include <llvm/IR/LLVMContext.h>

#include "../constants/FlowWingIRConstants.h"
#include "../context/CodeGenerationContext.h"
#include "../logger/LLVMLogger.h"
#include "../mappers/TypeMapper/TypeMapper.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Value.h"
using namespace FLOWWING::IR::CONSTANTS;

class TypeConverterBase {
public:
  CodeGenerationContext *_codeGenerationContext;
  llvm::IRBuilder<> *_builder;
  llvm::IRBuilder<> *_preBuilder;
  llvm::Module *_module;
  TypeMapper *_mapper;
  LLVMLogger *_logger;
  llvm::LLVMContext *_llvmContext;

  TypeConverterBase(CodeGenerationContext *context)
      : _module(context->getModule().get()),
        _mapper(context->getMapper().get()),
        _logger(context->getLogger().get()),
        _builder(context->getBuilder().get()),
        _llvmContext(context->getContext().get()),
        _codeGenerationContext(context){};

  virtual llvm::Value *convertExplicit(llvm::Value *&value) = 0;

  virtual llvm::Value *convertImplicit(llvm::Value *&value) = 0;

  inline auto setBuilder(llvm::IRBuilder<> *builder) {
    _preBuilder = _builder;
    _builder = builder;
  }

  inline auto resetBuilder() { _builder = _preBuilder; }
};

#endif // __TYPE_CONVERTER_BASE_H__
