#include "Lexer.h"

Lexer::Lexer(const std::vector<std::string> &sourceCode,
             FLowWing::DiagnosticHandler *diagnosticHandler) {
  textSize = sourceCode.size();

  this->_sourceCode = sourceCode;
  this->lineNumber = 0;
  this->position = 0;
  this->_diagnosticHandler = diagnosticHandler;
}

char Lexer::getCurrent() {
  if (this->lineNumber >= textSize)
    return this->endOfFile;

  if (this->position >= this->_sourceCode[lineNumber].length())
    return this->endOfLine;

  return this->_sourceCode[lineNumber][this->position];
}

auto Lexer::peek(const int64_t &offset) const -> const char {
  if (this->lineNumber >= textSize)
    return this->endOfFile;

  if (this->position + offset >= this->_sourceCode[lineNumber].length())
    return this->endOfLine;

  return this->_sourceCode[lineNumber][this->position + offset];
}

void Lexer::next() { this->position++; }

std::unique_ptr<SyntaxToken<std::any>> Lexer::readDecimal(const int &start) {
  this->next();
  while (!this->isEndOfLineOrFile() && isdigit(this->getCurrent())) {
    this->next();
  }
  if (this->getCurrent() == 'd') {
    this->next();
  }
  const int &length = this->position - start;
  const std::string &text = this->_sourceCode[lineNumber].substr(start, length);

  return std::make_unique<SyntaxToken<std::any>>(
      this->_diagnosticHandler->getAbsoluteFilePath(), this->lineNumber,
      SyntaxKindUtils::SyntaxKind::NumberToken, start, text, text);
}

bool Lexer::isEndOfLineOrFile() {
  return this->getCurrent() == this->endOfFile ||
         this->getCurrent() == this->endOfLine;
}

std::unique_ptr<SyntaxToken<std::any>> Lexer::readNumber() {
  int start = this->position;

  while (!this->isEndOfLineOrFile() && isdigit(this->getCurrent())) {
    this->next();
  }

  //  double check

  if (this->getCurrent() == '.') {
    return std::move(this->readDecimal(start));
  }

  const size_t &length = this->position - start;
  const std::string &text = this->_sourceCode[lineNumber].substr(start, length);
  try {
    if (SyntaxKindUtils::isInt64(text) == false) {
      throw std::runtime_error("ERROR: Bad Number Input Not Int64: " + text);
    }
  } catch (std::exception e) {
    std::unique_ptr<SyntaxToken<std::any>> newSyntaxToken =
        std::make_unique<SyntaxToken<std::any>>(
            this->_diagnosticHandler->getAbsoluteFilePath(), this->lineNumber,
            SyntaxKindUtils::SyntaxKind::BadToken, start, text, 0);

    this->_diagnosticHandler->addDiagnostic(
        Diagnostic(e.what(), DiagnosticUtils::DiagnosticLevel::Error,
                   DiagnosticUtils::DiagnosticType::Lexical,
                   Utils::getSourceLocation(newSyntaxToken.get())));

    return std::move(newSyntaxToken);
  }

  return std::make_unique<SyntaxToken<std::any>>(
      this->_diagnosticHandler->getAbsoluteFilePath(), this->lineNumber,
      SyntaxKindUtils::SyntaxKind::NumberToken, start, text, text);
}

std::unique_ptr<SyntaxToken<std::any>> Lexer::readKeyword() {
  const int start = this->position;
  while (!this->isEndOfLineOrFile() &&
         (isalnum(this->getCurrent()) || this->getCurrent() == '_')) {
    this->next();
  }
  const int length = this->position - start;
  const std::string &text = this->_sourceCode[lineNumber].substr(start, length);

  if (text == "true") {
    return std::make_unique<SyntaxToken<std::any>>(
        this->_diagnosticHandler->getAbsoluteFilePath(), this->lineNumber,
        SyntaxKindUtils::SyntaxKind::TrueKeyword, start, text, true);
  } else if (text == "false") {
    return std::make_unique<SyntaxToken<std::any>>(
        this->_diagnosticHandler->getAbsoluteFilePath(), this->lineNumber,
        SyntaxKindUtils::SyntaxKind::FalseKeyword, start, text, false);
  } else if (text == "var") {
    return std::make_unique<SyntaxToken<std::any>>(
        this->_diagnosticHandler->getAbsoluteFilePath(), this->lineNumber,
        SyntaxKindUtils::SyntaxKind::VarKeyword, start, text, "var");
  } else if (text == "if") {
    return std::make_unique<SyntaxToken<std::any>>(
        this->_diagnosticHandler->getAbsoluteFilePath(), this->lineNumber,
        SyntaxKindUtils::SyntaxKind::IfKeyword, start, text, "if");
  }

  else if (text == "or") {
    return std::make_unique<SyntaxToken<std::any>>(
        this->_diagnosticHandler->getAbsoluteFilePath(), this->lineNumber,
        SyntaxKindUtils::SyntaxKind::OrKeyword, start, text, "or");
  }

  else if (text == "else") {
    return std::make_unique<SyntaxToken<std::any>>(
        this->_diagnosticHandler->getAbsoluteFilePath(), this->lineNumber,
        SyntaxKindUtils::SyntaxKind::ElseKeyword, start, text, "else");
  }

  else if (text == "while") {
    return std::make_unique<SyntaxToken<std::any>>(
        this->_diagnosticHandler->getAbsoluteFilePath(), this->lineNumber,
        SyntaxKindUtils::SyntaxKind::WhileKeyword, start, text, "while");
  }

  else if (text == "for") {
    return std::make_unique<SyntaxToken<std::any>>(
        this->_diagnosticHandler->getAbsoluteFilePath(), this->lineNumber,
        SyntaxKindUtils::SyntaxKind::ForKeyword, start, text, "for");
  } else if (text == "fun") {
    return std::make_unique<SyntaxToken<std::any>>(
        this->_diagnosticHandler->getAbsoluteFilePath(), this->lineNumber,
        SyntaxKindUtils::SyntaxKind::FunctionKeyword, start, text, "fun");
  }

  else if (text == "to") {
    return std::make_unique<SyntaxToken<std::any>>(
        this->_diagnosticHandler->getAbsoluteFilePath(), this->lineNumber,
        SyntaxKindUtils::SyntaxKind::ToKeyword, start, text, "to");
  }

  else if (text == "continue") {
    return std::make_unique<SyntaxToken<std::any>>(
        this->_diagnosticHandler->getAbsoluteFilePath(), this->lineNumber,
        SyntaxKindUtils::SyntaxKind::ContinueKeyword, start, text, "continue");
  }

  else if (text == "break") {
    return std::make_unique<SyntaxToken<std::any>>(
        this->_diagnosticHandler->getAbsoluteFilePath(), this->lineNumber,
        SyntaxKindUtils::SyntaxKind::BreakKeyword, start, text, "break");
  }

  else if (text == "return") {
    return std::make_unique<SyntaxToken<std::any>>(
        this->_diagnosticHandler->getAbsoluteFilePath(), this->lineNumber,
        SyntaxKindUtils::SyntaxKind::ReturnKeyword, start, text, "return");
  }

  else if (text == "const") {
    return std::make_unique<SyntaxToken<std::any>>(
        this->_diagnosticHandler->getAbsoluteFilePath(), this->lineNumber,
        SyntaxKindUtils::SyntaxKind::ConstKeyword, start, text, "const");
  } else if (text == "nthg") {
    return std::make_unique<SyntaxToken<std::any>>(
        this->_diagnosticHandler->getAbsoluteFilePath(), this->lineNumber,
        SyntaxKindUtils::SyntaxKind::NthgKeyword, start, text, "nthg");
  }

  else if (text == "int") {
    return std::make_unique<SyntaxToken<std::any>>(
        this->_diagnosticHandler->getAbsoluteFilePath(), this->lineNumber,
        SyntaxKindUtils::SyntaxKind::Int32Keyword, start, text, "int");
  }

  else if (text == "int8") {
    return std::make_unique<SyntaxToken<std::any>>(
        this->_diagnosticHandler->getAbsoluteFilePath(), this->lineNumber,
        SyntaxKindUtils::SyntaxKind::Int8Keyword, start, text, "int8");
  } else if (text == "int64") {
    return std::make_unique<SyntaxToken<std::any>>(
        this->_diagnosticHandler->getAbsoluteFilePath(), this->lineNumber,
        SyntaxKindUtils::SyntaxKind::Int64Keyword, start, text, "int64");
  } else if (text == "bool") {
    return std::make_unique<SyntaxToken<std::any>>(
        this->_diagnosticHandler->getAbsoluteFilePath(), this->lineNumber,
        SyntaxKindUtils::SyntaxKind::BoolKeyword, start, text, "bool");
  }

  else if (text == "str") {
    return std::make_unique<SyntaxToken<std::any>>(
        this->_diagnosticHandler->getAbsoluteFilePath(), this->lineNumber,
        SyntaxKindUtils::SyntaxKind::StrKeyword, start, text, "string");
  }

  else if (text == "deci") {
    return std::make_unique<SyntaxToken<std::any>>(
        this->_diagnosticHandler->getAbsoluteFilePath(), this->lineNumber,
        SyntaxKindUtils::SyntaxKind::DeciKeyword, start, text, "double");
  }

  else if (text == "deci32") {
    return std::make_unique<SyntaxToken<std::any>>(
        this->_diagnosticHandler->getAbsoluteFilePath(), this->lineNumber,
        SyntaxKindUtils::SyntaxKind::Deci32Keyword, start, text, "float");
  }

  else if (text == "bring") {
    return std::make_unique<SyntaxToken<std::any>>(
        this->_diagnosticHandler->getAbsoluteFilePath(), this->lineNumber,
        SyntaxKindUtils::SyntaxKind::BringKeyword, start, text, text);
  }

  else if (text == "expose") {
    return std::make_unique<SyntaxToken<std::any>>(
        this->_diagnosticHandler->getAbsoluteFilePath(), this->lineNumber,
        SyntaxKindUtils::SyntaxKind::ExposeKeyword, start, text, "expose");
  }

  else if (text == "from") {
    return std::make_unique<SyntaxToken<std::any>>(
        this->_diagnosticHandler->getAbsoluteFilePath(), this->lineNumber,
        SyntaxKindUtils::SyntaxKind::FromKeyword, start, text, "from");
  }

  else if (text == "fill") {
    return std::make_unique<SyntaxToken<std::any>>(
        this->_diagnosticHandler->getAbsoluteFilePath(), this->lineNumber,
        SyntaxKindUtils::SyntaxKind::FillKeyword, start, text, "fill");
  }

  else if (text == "type") {
    return std::make_unique<SyntaxToken<std::any>>(
        this->_diagnosticHandler->getAbsoluteFilePath(), this->lineNumber,
        SyntaxKindUtils::SyntaxKind::TypeKeyword, start, text, "type");
  } else if (text == "decl") {
    return std::make_unique<SyntaxToken<std::any>>(
        this->_diagnosticHandler->getAbsoluteFilePath(), this->lineNumber,
        SyntaxKindUtils::SyntaxKind::DeclKeyword, start, text, "decl");
  } else if (text == "new") {
    return std::make_unique<SyntaxToken<std::any>>(
        this->_diagnosticHandler->getAbsoluteFilePath(), this->lineNumber,
        SyntaxKindUtils::SyntaxKind::NewKeyword, start, text, "new");
  } else if (text == "class") {
    return std::make_unique<SyntaxToken<std::any>>(
        this->_diagnosticHandler->getAbsoluteFilePath(), this->lineNumber,
        SyntaxKindUtils::SyntaxKind::ClassKeyword, start, text, "class");
  } else if (text == "inout") {
    return std::make_unique<SyntaxToken<std::any>>(
        this->_diagnosticHandler->getAbsoluteFilePath(), this->lineNumber,
        SyntaxKindUtils::SyntaxKind::INOUTKeyword, start, text, "inout");
  }
  return std::make_unique<SyntaxToken<std::any>>(
      this->_diagnosticHandler->getAbsoluteFilePath(), this->lineNumber,
      SyntaxKindUtils::SyntaxKind::IdentifierToken, start, text, text);
}

std::unique_ptr<SyntaxToken<std::any>> Lexer::readWhitespace() {
  int start = this->position;

  while (!this->isEndOfLineOrFile() && isspace(this->getCurrent())) {
    this->next();
  }

  return std::make_unique<SyntaxToken<std::any>>(
      this->_diagnosticHandler->getAbsoluteFilePath(), this->lineNumber,
      SyntaxKindUtils::SyntaxKind::WhitespaceToken, start, "", 0);
}

std::unique_ptr<SyntaxToken<std::any>> Lexer::readEndOfFile() {

  std::unique_ptr<SyntaxToken<std::any>> newSyntaxToken =
      std::make_unique<SyntaxToken<std::any>>(
          this->_diagnosticHandler->getAbsoluteFilePath(), lineNumber,
          SyntaxKindUtils::SyntaxKind::EndOfFileToken, this->position, "", 0);

  return std::move(newSyntaxToken);
}

std::unique_ptr<SyntaxToken<std::any>> Lexer::readMultiLineComment() {
  std::string text = "\n";
  int lineN = this->lineNumber;
  int pos = this->position + 1;
  text += this->getCurrent();
  this->next(); // skip /
  text += this->getCurrent();
  this->next(); // skip #

  while (this->getCurrent() != endOfFile &&
         (this->getCurrent() != '#' ||
          (this->getCurrent() == '#' && this->peek(1) != '/'))) {
    if (this->getCurrent() == endOfFile) {
      text += this->getCurrent();
      std::unique_ptr<SyntaxToken<std::any>> newSyntaxToken =
          std::move(readEndOfFile());

      this->_diagnosticHandler->addDiagnostic(Diagnostic(
          "Unterminated Comment Block", DiagnosticUtils::DiagnosticLevel::Error,
          DiagnosticUtils::DiagnosticType::Lexical,
          Utils::getSourceLocation(newSyntaxToken.get())));

      return std::move(newSyntaxToken);
    } else if (this->getCurrent() == endOfLine) {
      text += "\n";
      this->lineNumber++;
      this->position = 0;
    } else {
      text += this->getCurrent();
      this->next();
    }
  }

  text += this->getCurrent();
  this->next();
  text += this->getCurrent();
  this->next();

  if (this->getCurrent() == endOfLine) {
    text += "\n";
    this->lineNumber++;
    this->position = 0;
  }
  return std::make_unique<SyntaxToken<std::any>>(
      this->_diagnosticHandler->getAbsoluteFilePath(), lineN,
      SyntaxKindUtils::SyntaxKind::CommentStatement, pos, text, nullptr);
}

std::unique_ptr<SyntaxToken<std::any>> Lexer::readSingleLineComment() {
  std::string text = "\n";
  int lineN = this->lineNumber;
  int pos = this->position + 1;
  text += this->getCurrent();
  this->next(); // skip /
  text += this->getCurrent();
  this->next(); // skip ;
  while (!this->isEndOfLineOrFile()) {
    if (this->getCurrent() == endOfLine) {
      std::unique_ptr<SyntaxToken<std::any>> newSyntaxToken =
          std::move(readEndOfFile());

      this->_diagnosticHandler->addDiagnostic(Diagnostic(
          "Unterminated Comment Block", DiagnosticUtils::DiagnosticLevel::Error,
          DiagnosticUtils::DiagnosticType::Lexical,
          Utils::getSourceLocation(newSyntaxToken.get())));

      return std::move(newSyntaxToken);
    } else {
      text += this->getCurrent();
      this->next();
    }
  }
  text += '\n';
  this->lineNumber++;
  this->position = 0;
  return std::make_unique<SyntaxToken<std::any>>(
      this->_diagnosticHandler->getAbsoluteFilePath(), lineN,
      SyntaxKindUtils::SyntaxKind::CommentStatement, pos, text, nullptr);
}

std::unique_ptr<SyntaxToken<std::any>> Lexer::readSymbol() {
  int start = this->position;
  switch (this->getCurrent()) {
  case '+':
    return std::make_unique<SyntaxToken<std::any>>(
        this->_diagnosticHandler->getAbsoluteFilePath(), this->lineNumber,
        SyntaxKindUtils::SyntaxKind::PlusToken, this->position++, "+", nullptr);
  case '-':
    return std::make_unique<SyntaxToken<std::any>>(
        this->_diagnosticHandler->getAbsoluteFilePath(), this->lineNumber,
        SyntaxKindUtils::SyntaxKind::MinusToken, this->position++, "-",
        nullptr);

  case '*':
    return std::make_unique<SyntaxToken<std::any>>(
        this->_diagnosticHandler->getAbsoluteFilePath(), this->lineNumber,
        SyntaxKindUtils::SyntaxKind::StarToken, this->position++, "*", nullptr);
  case ';':
    return std::make_unique<SyntaxToken<std::any>>(
        this->_diagnosticHandler->getAbsoluteFilePath(), this->lineNumber,
        SyntaxKindUtils::SyntaxKind::SemicolonToken, this->position++, ";",
        nullptr);
  case ',':
    return std::make_unique<SyntaxToken<std::any>>(
        this->_diagnosticHandler->getAbsoluteFilePath(), this->lineNumber,
        SyntaxKindUtils::SyntaxKind::CommaToken, this->position++, ",",
        nullptr);
  case '{':
    return std::make_unique<SyntaxToken<std::any>>(
        this->_diagnosticHandler->getAbsoluteFilePath(), this->lineNumber,
        SyntaxKindUtils::SyntaxKind::OpenBraceToken, this->position++, "{",
        nullptr);
  case '}':
    return std::make_unique<SyntaxToken<std::any>>(
        this->_diagnosticHandler->getAbsoluteFilePath(), this->lineNumber,
        SyntaxKindUtils::SyntaxKind::CloseBraceToken, this->position++, "}",
        nullptr);
  case '[':
    return std::make_unique<SyntaxToken<std::any>>(
        this->_diagnosticHandler->getAbsoluteFilePath(), this->lineNumber,
        SyntaxKindUtils::SyntaxKind::OpenBracketToken, this->position++, "[",
        nullptr);

  case ']':
    return std::make_unique<SyntaxToken<std::any>>(
        this->_diagnosticHandler->getAbsoluteFilePath(), this->lineNumber,
        SyntaxKindUtils::SyntaxKind::CloseBracketToken, this->position++, "]",
        nullptr);

  case '#':
    return std::make_unique<SyntaxToken<std::any>>(
        this->_diagnosticHandler->getAbsoluteFilePath(), this->lineNumber,
        SyntaxKindUtils::SyntaxKind::HashToken, this->position++, "#", nullptr);

  case '(':
    return std::make_unique<SyntaxToken<std::any>>(
        this->_diagnosticHandler->getAbsoluteFilePath(), this->lineNumber,
        SyntaxKindUtils::SyntaxKind::OpenParenthesisToken, this->position++,
        "(", nullptr);
  case ')':
    return std::make_unique<SyntaxToken<std::any>>(
        this->_diagnosticHandler->getAbsoluteFilePath(), this->lineNumber,
        SyntaxKindUtils::SyntaxKind::CloseParenthesisToken, this->position++,
        ")", nullptr);

  case '^':
    return std::make_unique<SyntaxToken<std::any>>(
        this->_diagnosticHandler->getAbsoluteFilePath(), this->lineNumber,
        SyntaxKindUtils::SyntaxKind::CaretToken, this->position++, "^",
        nullptr);
  case '%':
    return std::make_unique<SyntaxToken<std::any>>(
        this->_diagnosticHandler->getAbsoluteFilePath(), this->lineNumber,
        SyntaxKindUtils::SyntaxKind::PercentToken, this->position++, "%",
        nullptr);
  case '~':
    return std::make_unique<SyntaxToken<std::any>>(
        this->_diagnosticHandler->getAbsoluteFilePath(), this->lineNumber,
        SyntaxKindUtils::SyntaxKind::TildeToken, this->position++, "~",
        nullptr);
  case ':':
    return std::make_unique<SyntaxToken<std::any>>(
        this->_diagnosticHandler->getAbsoluteFilePath(), this->lineNumber,
        SyntaxKindUtils::SyntaxKind::ColonToken, this->position++, ":",
        nullptr);

  case '.':
    return std::make_unique<SyntaxToken<std::any>>(
        this->_diagnosticHandler->getAbsoluteFilePath(), this->lineNumber,
        SyntaxKindUtils::SyntaxKind::DotToken, this->position++, ".", nullptr);
  case '&': {
    if (this->peek(1) == '&') {
      this->next();
      return std::make_unique<SyntaxToken<std::any>>(
          this->_diagnosticHandler->getAbsoluteFilePath(), this->lineNumber,
          SyntaxKindUtils::SyntaxKind::AmpersandAmpersandToken,
          this->position++, "&&", nullptr);
    }

    return std::make_unique<SyntaxToken<std::any>>(
        this->_diagnosticHandler->getAbsoluteFilePath(), this->lineNumber,
        SyntaxKindUtils::SyntaxKind::AmpersandToken, this->position++, "&",
        nullptr);
  }
  case '/': {
    if (this->peek(1) == '#') {
      return std::move(this->readMultiLineComment());
    } else if (this->peek(1) == ';') {
      return std::move(this->readSingleLineComment());
    } else if (this->peek(1) == '/') {
      this->next(); // Skip /
      return std::make_unique<SyntaxToken<std::any>>(
          this->_diagnosticHandler->getAbsoluteFilePath(), this->lineNumber,
          SyntaxKindUtils::SyntaxKind::SlashSlashToken, this->position++, "//",
          nullptr);
    }
    return std::make_unique<SyntaxToken<std::any>>(
        this->_diagnosticHandler->getAbsoluteFilePath(), this->lineNumber,
        SyntaxKindUtils::SyntaxKind::SlashToken, this->position++, "/",
        nullptr);
  }

  case '|': {
    if (this->peek(1) == '|') {
      this->next();
      return std::make_unique<SyntaxToken<std::any>>(
          this->_diagnosticHandler->getAbsoluteFilePath(), this->lineNumber,
          SyntaxKindUtils::SyntaxKind::PipePipeToken, this->position++, "||",
          nullptr);
    }

    return std::make_unique<SyntaxToken<std::any>>(
        this->_diagnosticHandler->getAbsoluteFilePath(), this->lineNumber,
        SyntaxKindUtils::SyntaxKind::PipeToken, this->position++, "|", nullptr);
  }
  case '=': {
    if (this->peek(1) == '=') {
      this->next();
      return std::make_unique<SyntaxToken<std::any>>(
          this->_diagnosticHandler->getAbsoluteFilePath(), this->lineNumber,
          SyntaxKindUtils::SyntaxKind::EqualsEqualsToken, this->position++,
          "==", nullptr);
    }
    return std::make_unique<SyntaxToken<std::any>>(
        this->_diagnosticHandler->getAbsoluteFilePath(), this->lineNumber,
        SyntaxKindUtils::SyntaxKind::EqualsToken, this->position++, "=",
        nullptr);
  }

  case '!': {
    if (this->peek(1) == '=') {
      this->next();
      return std::make_unique<SyntaxToken<std::any>>(
          this->_diagnosticHandler->getAbsoluteFilePath(), this->lineNumber,
          SyntaxKindUtils::SyntaxKind::BangEqualsToken, this->position++,
          "!=", nullptr);
    }
    return std::make_unique<SyntaxToken<std::any>>(
        this->_diagnosticHandler->getAbsoluteFilePath(), this->lineNumber,
        SyntaxKindUtils::SyntaxKind::BangToken, this->position++, "!", nullptr);
  }

  case '<': {
    if (this->peek(1) == '-') {
      this->next();
      return std::make_unique<SyntaxToken<std::any>>(
          this->_diagnosticHandler->getAbsoluteFilePath(), this->lineNumber,
          SyntaxKindUtils::SyntaxKind::AssignmentToken, this->position++, "<-",
          nullptr);
    }

    if (this->peek(1) == '=') {
      this->next();
      return std::make_unique<SyntaxToken<std::any>>(
          this->_diagnosticHandler->getAbsoluteFilePath(), this->lineNumber,
          SyntaxKindUtils::SyntaxKind::LessOrEqualsToken, this->position++,
          "<=", nullptr);
    }
    return std::make_unique<SyntaxToken<std::any>>(
        this->_diagnosticHandler->getAbsoluteFilePath(), this->lineNumber,
        SyntaxKindUtils::SyntaxKind::LessToken, this->position++, "<", nullptr);
  }

  case '>': {
    if (this->peek(1) == '=') {
      this->next();
      return std::make_unique<SyntaxToken<std::any>>(
          this->_diagnosticHandler->getAbsoluteFilePath(), this->lineNumber,
          SyntaxKindUtils::SyntaxKind::GreaterOrEqualsToken, this->position++,
          ">=", nullptr);
    }
    return std::make_unique<SyntaxToken<std::any>>(
        this->_diagnosticHandler->getAbsoluteFilePath(), this->lineNumber,
        SyntaxKindUtils::SyntaxKind::GreaterToken, this->position++, ">",
        nullptr);
  }

  case '"': {
    return std::move(this->readString(start));
  }

  default: {
    break;
  }
  }

  const int _len = std::max(
      (int)this->_sourceCode[lineNumber].length() - (int)start, (int)0);

  const std::string &str = this->_sourceCode[lineNumber].substr(start, _len);

  std::unique_ptr<SyntaxToken<std::any>> newSyntaxToken =
      std::make_unique<SyntaxToken<std::any>>(
          this->_diagnosticHandler->getAbsoluteFilePath(), this->lineNumber,
          SyntaxKindUtils::SyntaxKind::BadToken, this->position++, str,
          nullptr);

  this->_diagnosticHandler->addDiagnostic(
      Diagnostic("Bad Character Input <" + str + ">",
                 DiagnosticUtils::DiagnosticLevel::Error,
                 DiagnosticUtils::DiagnosticType::Lexical,
                 Utils::getSourceLocation(newSyntaxToken.get())));

  return std::move(newSyntaxToken);
}

std::unique_ptr<SyntaxToken<std::any>> Lexer::nextToken() {
  // For Debugging

  // std::cout << "Lexer::nextToken()" << this->getCurrent() << this->lineNumber
  //           << this->position << this->textSize << "ENDED";

  if (this->getCurrent() == endOfFile) {
    return std::move(this->readEndOfFile());
  }

  if (this->getCurrent() == endOfLine || this->getCurrent() == '\n') {
    return std::move(this->readEndOfLine());
  }
  if (isspace(this->getCurrent())) {
    return std::move(this->readWhitespace());
  }

  if (isdigit(this->getCurrent())) {
    return std::move(this->readNumber());
  }

  if (isalpha(this->getCurrent())) {
    return std::move(this->readKeyword());
  }

  return std::move(this->readSymbol());
}

std::unique_ptr<SyntaxToken<std::any>> Lexer::readEndOfLine() {
  std::unique_ptr<SyntaxToken<std::any>> newSyntaxToken =
      std::make_unique<SyntaxToken<std::any>>(
          this->_diagnosticHandler->getAbsoluteFilePath(), this->lineNumber,
          SyntaxKindUtils::SyntaxKind::EndOfLineToken, this->position, "", 0);

  if (this->getCurrent() == '\n') {
    this->position++;
  } else {
    this->position = 0;
    this->lineNumber++;
  }

  return std::move(newSyntaxToken);
}

std::unique_ptr<SyntaxToken<std::any>> Lexer::readString(const int &start) {
  this->next();
  std::string text = "", valueText = "";
  while (!this->isEndOfLineOrFile() && this->getCurrent() != '"') {
    if (this->getCurrent() == '\0') {
      std::unique_ptr<SyntaxToken<std::any>> newSyntaxToken =
          std::make_unique<SyntaxToken<std::any>>(
              this->_diagnosticHandler->getAbsoluteFilePath(), this->lineNumber,
              SyntaxKindUtils::SyntaxKind::BadToken, start,
              this->_sourceCode[lineNumber].substr(start,
                                                   this->position - start),
              0);

      this->_diagnosticHandler->addDiagnostic(
          Diagnostic("Unterminated String Literal",
                     DiagnosticUtils::DiagnosticLevel::Error,
                     DiagnosticUtils::DiagnosticType::Lexical,
                     Utils::getSourceLocation(newSyntaxToken.get())));

      return std::move(newSyntaxToken);
    }
    if (this->getCurrent() == '\\') {
      text += this->getCurrent();
      this->next();
      text += this->getCurrent();
      switch (this->getCurrent()) {
      case '"':
        valueText += '"';
        break;
      case '\\':
        valueText += '\\';
        break;
      case 'n':
        valueText += '\n';
        break;
      case 'r':
        valueText += '\r';
        break;
      case 't':
        valueText += '\t';
        break;
      default:
        std::unique_ptr<SyntaxToken<std::any>> newSyntaxToken =
            std::make_unique<SyntaxToken<std::any>>(
                this->_diagnosticHandler->getAbsoluteFilePath(),
                this->lineNumber, SyntaxKindUtils::SyntaxKind::BadToken, start,
                this->_sourceCode[lineNumber].substr(start,
                                                     this->position - start),
                0);

        this->_diagnosticHandler->addDiagnostic(Diagnostic(
            "Bad Character Escape Sequence: \\" +
                this->_sourceCode[lineNumber].substr(this->position, 1),
            DiagnosticUtils::DiagnosticLevel::Error,
            DiagnosticUtils::DiagnosticType::Lexical,
            Utils::getSourceLocation(newSyntaxToken.get())));

        return std::move(newSyntaxToken);
      }
    } else {
      text += this->getCurrent();
      valueText += this->getCurrent();
    }
    this->next();
  }

  if (this->getCurrent() != '"') {
    std::unique_ptr<SyntaxToken<std::any>> newSyntaxToken =
        std::make_unique<SyntaxToken<std::any>>(
            this->_diagnosticHandler->getAbsoluteFilePath(), this->lineNumber,
            SyntaxKindUtils::SyntaxKind::BadToken, start,
            this->_sourceCode[lineNumber].substr(start, this->position - start),
            0);

    this->_diagnosticHandler->addDiagnostic(Diagnostic(
        "Unterminated String Literal", DiagnosticUtils::DiagnosticLevel::Error,
        DiagnosticUtils::DiagnosticType::Lexical,
        Utils::getSourceLocation(newSyntaxToken.get())));

    return std::move(newSyntaxToken);
  }

  this->next();
  return std::make_unique<SyntaxToken<std::any>>(
      this->_diagnosticHandler->getAbsoluteFilePath(), this->lineNumber,
      SyntaxKindUtils::SyntaxKind::StringToken, start, '"' + text + '"',
      valueText);
}