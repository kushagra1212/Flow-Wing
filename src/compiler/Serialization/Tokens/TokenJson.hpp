// TokenJsonSerializer.h
#pragma once

#include "src/diagnostics/DiagnosticUtils/SourceLocation.h"
#include "src/external/include/json.hpp"
#include "src/syntax/SyntaxToken.h"
#include <memory>
#include <vector>

namespace flow_wing::compiler::serializer {

class TokenJson {
public:
  static nlohmann::json
  toJson(const std::vector<std::unique_ptr<flow_wing::syntax::SyntaxToken>>
             &tokens);

private:
  static nlohmann::json
  toJsonToken(const flow_wing::syntax::SyntaxToken *token);

  static nlohmann::json
  toJsonRange(const flow_wing::diagnostic::SourceLocation &location);

  static nlohmann::json
  toJsonSourcePoint(const flow_wing::diagnostic::SourcePoint &point);
};

} // namespace flow_wing::compiler::serializer
