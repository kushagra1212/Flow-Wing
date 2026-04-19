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

#include "SemanticTreeJsonDumperPass.hpp"
#include "src/common/cli/CliReporter.h"
#include "src/compiler/CompilationContext/CompilationContext.h"
#include "src/compiler/Serialization/Ast/AstJson.hpp"
#include "src/compiler/Serialization/BoundTree/BoundTreeJson.hpp"
#include "src/compiler/Serialization/Tokens/TokenJson.hpp"
#include "src/external/include/json.hpp"
#include <cstdlib>
#include <fstream>
#include <iostream>

namespace flow_wing {

namespace compiler {
namespace pipeline {

std::string SemanticTreeJsonDumperPass::getName() const {
  return "Semantic Tree Json Dumper";
}

ReturnStatus SemanticTreeJsonDumperPass::run(CompilationContext &context) {

  nlohmann::json bound_tree_json = {
      {"stage", "semantic analysis"},
      {"generatedAt",
       std::chrono::system_clock::now().time_since_epoch().count()},
      {"source", context.getAbsoluteSourceFilePath()},
      {"sem", flow_wing::compiler::serializer::BoundTreeJson().toJson(
                  context.getBoundTree())}};

  const int8_t kDumpIndent = 2;

  if (context.getOptions().dump) {
    flow_wing::cli::Reporter::message(bound_tree_json.dump(kDumpIndent));
  } else {
    std::ofstream bound_tree_json_file(context.getOptions().output_dir +
                                       "/semantic_tree.json");
    bound_tree_json_file << bound_tree_json.dump(kDumpIndent);
    bound_tree_json_file.close();
    flow_wing::cli::Reporter::message("Semantic tree dumped to " +
                                      context.getOptions().output_dir +
                                      "/semantic_tree.json");
  }

  return ReturnStatus::kSuccess;
}
} // namespace pipeline
} // namespace compiler
} // namespace flow_wing
