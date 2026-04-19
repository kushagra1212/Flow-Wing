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


#include "LLVMBackendContext.hpp"

namespace flow_wing {
namespace ir_gen {

LLVMBackendContext::LLVMBackendContext(const std::string &module_name)
    : m_context(std::make_unique<llvm::LLVMContext>()),
      m_module(std::make_unique<llvm::Module>(module_name, *m_context)) {}

LLVMBackendContext::~LLVMBackendContext() = default;

llvm::TargetMachine *LLVMBackendContext::getTargetMachine() const {
  return m_target_machine;
}

llvm::LLVMContext *LLVMBackendContext::getLLVMContext() const {
  return m_context.get();
}

llvm::Module *LLVMBackendContext::getLLVMModule() const {
  return m_module.get();
}

} // namespace ir_gen
} // namespace flow_wing