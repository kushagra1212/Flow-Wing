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

#pragma once

#include "src/compiler/CompilerOptions/CompilerOptions.h"
#include "src/compiler/pipeline/ICompilationPass.h"

namespace llvm {
class Module;
class TargetMachine;
} // namespace llvm

namespace flow_wing {
namespace compiler {
namespace pipeline {

// Runs LLVM's standard per-module pipeline at the given level.
//
// Shared by the two back ends because they optimize different modules. The
// object path optimizes the module held in the backend context. The JIT does
// not use that module at all: JITCompilerPass re-reads the generated `.ll`
// files from disk and links them, so it optimizes the linked result instead,
// which also lets the inliner work across translation units.
//
// `target_machine` may be null, in which case the pipeline uses defaults.
// Does nothing at O0.
void optimizeModule(llvm::Module &module, llvm::TargetMachine *target_machine,
                    OptimizationLevel level);

// Runs LLVM's standard optimization pipeline over the generated module.
//
// This sits between IR generation and the back ends, so the JIT, object and
// executable pipelines all get the same optimized IR. Object emission goes
// through LLVMTargetMachineEmitToFile and the JIT hands the module to ORC;
// neither optimizes on its own, so without this pass `-O2` reached code
// generation with exactly the same IR as `-O0`.
//
// `-E ir` dumps the module before this pass, so that output stays a faithful
// view of what IR generation produced.
class OptimizationPass : public ICompilationPass {
public:
  std::string getName() const override;
  ReturnStatus run(CompilationContext &context) override;
};

} // namespace pipeline
} // namespace compiler

} // namespace flow_wing
