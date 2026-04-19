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

#include "AstJsonDumperPass.hpp"
#include "src/common/cli/CliReporter.h"
#include "src/compiler/CompilationContext/CompilationContext.h"
#include "src/compiler/Serialization/Ast/AstJson.hpp"
#include "src/compiler/Serialization/Tokens/TokenJson.hpp"
#include "src/external/include/json.hpp"
#include <cstdlib>
#include <fstream>
#include <iostream>

namespace flow_wing {

namespace compiler {
namespace pipeline {

std::string AstJsonDumperPass::getName() const { return "Ast Json Dumper"; }

ReturnStatus AstJsonDumperPass::run(CompilationContext &context) {

  nlohmann::json ast_json = {
      {"stage", "parsing"},
      {"generatedAt",
       std::chrono::system_clock::now().time_since_epoch().count()},
      {"source", context.getAbsoluteSourceFilePath()},
      {"tree",
       flow_wing::compiler::serializer::AstJson().toJson(context.getAst())}};

  const int8_t kDumpIndent = 2;

  if (context.getOptions().dump) {
    flow_wing::cli::Reporter::message(ast_json.dump(kDumpIndent));
  } else {
    std::ofstream ast_json_file(context.getOptions().output_dir + "/ast.json");
    ast_json_file << ast_json.dump(kDumpIndent);
    ast_json_file.close();
    flow_wing::cli::Reporter::message(
        "Ast dumped to " + context.getOptions().output_dir + "/ast.json");
  }

  return ReturnStatus::kSuccess;
}
} // namespace pipeline
} // namespace compiler
} // namespace flow_wing
