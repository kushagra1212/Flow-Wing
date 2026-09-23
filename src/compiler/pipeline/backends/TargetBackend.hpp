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
#include "src/compiler/pipeline/PassList.hpp"

namespace flow_wing {
namespace compiler {
namespace pipeline {

// The last passes of --emit=obj and --emit=exe: the ones that turn optimized
// LLVM IR into files for one machine.
//
// Every pass before them, from source loading to optimization, is the same
// for every target. The target changes only the module's triple and data
// layout, which IR generation reads from the options. So PipelineFactory
// builds the shared passes and a TargetBackend finishes the pipeline, and a
// new target is a new TargetBackend, not a change to the factory.
class TargetBackend {
public:
  virtual ~TargetBackend() = default;

  // One unit's optimized module -> its object file. Each brought file is
  // compiled with these as well.
  virtual PassList objectPasses() const = 0;

  // Run after objectPasses: every unit's object file -> the program.
  virtual PassList linkPasses() const = 0;

  static const TargetBackend &forPlatform(TargetPlatform platform);
};

} // namespace pipeline
} // namespace compiler
} // namespace flow_wing
