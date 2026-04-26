/*
 * Flow-Wing Compiler
 * Copyright (C) 2023-2026 Kushagra Rathore
 */

#include "FormatPass.hpp"
#include "src/compiler/CompilationContext/CompilationContext.h"
#include "src/compiler/diagnostics/Diagnostic.h"
#include "src/compiler/formatter/FormatLayoutSmokeTest.hpp"
#include "src/compiler/formatter/SourceFormatter.hpp"
#include "src/utils/LogConfig.h"
#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

namespace flow_wing {
namespace compiler {
namespace pipeline {

std::string FormatPass::getName() const { return "Format"; }

ReturnStatus FormatPass::run(CompilationContext &context) {
  if (context.getDiagnostics()->hasError(diagnostic::DiagnosticType::kLexical) ||
      context.getDiagnostics()->hasError(diagnostic::DiagnosticType::kSyntactic)) {
    return ReturnStatus::kFailure;
  }

  const auto &opt = context.getOptions();

  if (std::getenv("FLOWWING_FORMAT_LAYOUT_SMOKE") != nullptr) {
    if (!format::runFormatLayoutEngineSmokeTest()) {
      return ReturnStatus::kFailure;
    }
  }

  const auto &ast = context.getAst();
  if (!ast) {
    return ReturnStatus::kFailure;
  }

  std::size_t hint = 0;
  for (const auto &l : context.getSourceLines()) {
    hint += l.size() + 1;
  }

  std::string out = format::SourceFormatter::format(ast, hint);

  if (opt.format_print) {
    std::cout << out;
    return ReturnStatus::kSuccess;
  }

  if (opt.format_source) {
    const std::string &path = opt.input_file_path;
    std::string original;
    original.reserve(hint);
    for (std::size_t i = 0; i < context.getSourceLines().size(); ++i) {
      if (i) {
        original += '\n';
      }
      original += context.getSourceLines()[i];
    }
    if (out == original) {
      return ReturnStatus::kSuccess;
    }
    std::ofstream f(path, std::ios::binary);
    if (!f) {
      return ReturnStatus::kFailure;
    }
    f << out;
    return f ? ReturnStatus::kSuccess : ReturnStatus::kFailure;
  }

  return ReturnStatus::kFailure;
}

} // namespace pipeline
} // namespace compiler
} // namespace flow_wing
