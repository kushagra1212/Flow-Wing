#include "CodeFormatter.h"

#include "../parsers/ParserContext/ParserContext.h"

CodeFormatter::CodeFormatter(ParserContext *parserCtx) : parserCtx(parserCtx) {}

void CodeFormatter::appendNewLine() {
  if (parserCtx->getCurrent() &&
      parserCtx->getKind() != SyntaxKindUtils::SyntaxKind::CommentStatement)
    append(NEW_LINE);
  else
    appendWithSpace();
}

void CodeFormatter::append(const std::string &str) {
  _formattedSourceCode += str;
}
void CodeFormatter::appendWithSpace() { append(ONE_SPACE); }

const std::string &CodeFormatter::getFormattedSourceCode() {
  return _formattedSourceCode;
}

//? Handling Indentation

void CodeFormatter::appendIndentAmount(const std::string &str) {
  _indentAmount += str;
}

void CodeFormatter::setIndentAmount(const std::string &indentAmount) {
  _indentAmount = indentAmount;
}

std::string CodeFormatter::getIndentAmount() { return _indentAmount; }
