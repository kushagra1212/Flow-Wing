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

#include "ObjectEmissionPass.hpp"
#include "src/IRGen/io/ObjectUtils.hpp"
#include "src/common/cli/CliReporter.h"
#include "src/compiler/CompilationContext/CompilationContext.h"
#include <cstdlib>
#include <fstream>

namespace flow_wing {

namespace compiler {
namespace pipeline {

std::string ObjectEmissionPass::getName() const { return "Object Emission"; }

ReturnStatus ObjectEmissionPass::run(CompilationContext &context) {

  const auto llvm_module = context.getBackendContext()->getLLVMModule();
  // Must match paths used when registering brought-in objects (CompilationContext
  // canonical path, not necessarily the raw CLI path).
  const std::string file_path = context.getAbsoluteSourceFilePath();
  if (!ir_gen::ObjectUtils::createObjectFile(
          llvm_module, file_path, context.getOptions().output_dir)) {
    return ReturnStatus::kFailure;
  }

  return ReturnStatus::kSuccess;
}
} // namespace pipeline
} // namespace compiler
} // namespace flow_wing
