#pragma once
#include "StatementParser.h"

#include "BlockStatementParser/BlockStatementParser.h"

class StatementParserFactory {
public:
  static std::unique_ptr<StatementParser>
  createStatementParser(const SyntaxKindUtils::SyntaxKind &kind);
};