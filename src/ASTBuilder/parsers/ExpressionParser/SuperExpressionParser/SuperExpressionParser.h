/*
 * Flow-Wing Compiler
 * Copyright (C) 2023-2026 Kushagra Rathore
 */

#pragma once

#include "src/ASTBuilder/parsers/ExpressionParser/ExpressionParser.h"
#include <memory>

namespace flow_wing {

namespace syntax {
class SyntaxToken;
} // namespace syntax

namespace parser {

class SuperExpressionParser : public ExpressionParser {
public:
  explicit SuperExpressionParser(ParserContext *ctx);

  std::unique_ptr<syntax::ExpressionSyntax> parse() override;

private:
  ParserContext *m_ctx;
};
} // namespace parser
} // namespace flow_wing
