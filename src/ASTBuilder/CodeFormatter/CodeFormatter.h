#pragma once

#define ONE_SPACE " "
#define TWO_SPACES "  "
#define TAB_SPACE "  "
#define NEW_LINE "\n"

#include "../../syntax/SyntaxKindUtils.h"

class ParserContext;

class CodeFormatter {
private:
  std::string _formattedSourceCode = "";
  ParserContext *parserCtx = nullptr;
  std::string _indentAmount = "";

public:
  CodeFormatter(ParserContext *parserCtx);

  void append(const std::string &str);
  void appendWithSpace();
  void appendNewLine();

  const std::string &getFormattedSourceCode();

  //? Handling Indentation

  void appendIndentAmount(const std::string &str);
  void setIndentAmount(const std::string &indentAmount);
  std::string getIndentAmount();
};
