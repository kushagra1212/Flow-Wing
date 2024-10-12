#pragma once

#include "../../../../syntax/statements/MultipleVariableDeclarationSyntax/MultipleVariableDeclarationSyntax.h"
#include "../../ParserUtils/VariableParserUtils.h"
#include "../StatementParser.h"
#include "../StatementParserFactory.h"

class MultipleVariableDeclarationParser : public StatementParser {

  std::unique_ptr<VariableDeclarationSyntax> _initialVarDec = nullptr;

public:
  std::unique_ptr<StatementSyntax> parseStatement(ParserContext *ctx) override;

  void
  setInitialVarDec(std::unique_ptr<VariableDeclarationSyntax> initialVarDec) {
    _initialVarDec = std::move(initialVarDec);
  }
};