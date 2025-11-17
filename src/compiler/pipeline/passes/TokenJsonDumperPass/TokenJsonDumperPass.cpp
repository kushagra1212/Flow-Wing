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



#include "TokenJsonDumperPass.h"
#include "src/common/cli/CliReporter.h"
#include "src/compiler/CompilationContext/CompilationContext.h"
#include "src/compiler/Serialization/Tokens/TokenJson.hpp"
#include <cstdlib>
#include <fstream>
#include <iostream>

namespace flow_wing {

namespace compiler {
namespace pipeline {

std::string TokenJsonDumperPass::getName() const { return "Token Json Dumper"; }

ReturnStatus TokenJsonDumperPass::run(CompilationContext &context) {

  auto tokens_json =
      flow_wing::compiler::serializer::TokenJson::toJson(context.getTokens());

  const int8_t kDumpIndent = 1;

  if (context.getOptions().dump) {
    flow_wing::cli::Reporter::message(tokens_json.dump(kDumpIndent));
  } else {
    std::ofstream tokens_json_file(context.getOptions().output_dir +
                                   "/tokens.json");
    tokens_json_file << tokens_json.dump(kDumpIndent);
    tokens_json_file.close();
    flow_wing::cli::Reporter::message(
        "Tokens dumped to " + context.getOptions().output_dir + "/tokens.json");
  }

  return ReturnStatus::kSuccess;
}
} // namespace pipeline
} // namespace compiler
} // namespace flow_wing
