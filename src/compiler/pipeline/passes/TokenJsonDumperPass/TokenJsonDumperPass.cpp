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

#include "TokenJsonDumperPass.hpp"
#include "src/common/cli/CliReporter.h"
#include "src/compiler/CompilationContext/CompilationContext.h"
#include "src/compiler/pipeline/passes/ArtifactWriter.hpp"
#include "src/compiler/Serialization/Tokens/TokenJson.hpp"
#include "src/external/include/json.hpp"
#include <cstdlib>
#include <fstream>
#include <iostream>

namespace flow_wing {

namespace compiler {
namespace pipeline {

std::string TokenJsonDumperPass::getName() const { return "Token Json Dumper"; }

ReturnStatus TokenJsonDumperPass::run(CompilationContext &context) {

  nlohmann::json tokens_json = {
      {"stage", "tokenization"},
      {"generatedAt",
       std::chrono::system_clock::now().time_since_epoch().count()},
      {"source", context.getAbsoluteSourceFilePath()},
      {"tokens", flow_wing::compiler::serializer::TokenJson::toJson(
                     context.getTokens())}};

  const int8_t kDumpIndent = 1;

  return emitArtifact(context, "Tokens", "tokens.json",
                      tokens_json.dump(kDumpIndent));
}
} // namespace pipeline
} // namespace compiler
} // namespace flow_wing
