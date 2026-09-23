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

#include "src/compiler/pipeline/ICompilationPass.h"
#include <functional>
#include <memory>
#include <vector>

namespace flow_wing {
namespace compiler {
namespace pipeline {

// A recipe for a pipeline: each entry makes a fresh pass, so one list can
// build any number of pipelines, as brought files need.
using PassCreator = std::function<std::unique_ptr<ICompilationPass>()>;
using PassList = std::vector<PassCreator>;

} // namespace pipeline
} // namespace compiler
} // namespace flow_wing
