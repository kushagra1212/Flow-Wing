#include "Lexer.h"

Lexer::Lexer(std::vector<std::string> sourceCode,
             DiagnosticHandler *diagnosticHandler) {

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

void Lexer::next() { this->position++; }

std::unique_ptr<SyntaxToken<std::any>> Lexer::readDecimal(const int &start) {
  this->next();
  while (!this->isEndOfLineOrFile() && isdigit(this->getCurrent())) {
    this->next();
  }
  const int &length = this->position - start;
  std::string text = this->_sourceCode[lineNumber].substr(start, length);

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
  std::string text = this->_sourceCode[lineNumber].substr(start, length);
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
  while (!this->isEndOfLineOrFile() && isalnum(this->getCurrent())) {
    this->next();
  }
  const int length = this->position - start;
  const std::string text = this->_sourceCode[lineNumber].substr(start, length);
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

  else if (text == "bool") {
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

  else if (text == "bring") {

    return std::make_unique<SyntaxToken<std::any>>(
        this->_diagnosticHandler->getAbsoluteFilePath(), this->lineNumber,
        SyntaxKindUtils::SyntaxKind::BringKeyword, start, text, text);
  } else if (text == "expose") {
    return std::make_unique<SyntaxToken<std::any>>(
        this->_diagnosticHandler->getAbsoluteFilePath(), this->lineNumber,
        SyntaxKindUtils::SyntaxKind::ExposeKeyword, start, text, "expose");
  } else if (text == "from") {
    return std::make_unique<SyntaxToken<std::any>>(
        this->_diagnosticHandler->getAbsoluteFilePath(), this->lineNumber,
        SyntaxKindUtils::SyntaxKind::FromKeyword, start, text, "from");
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
  this->next(); // skip /
  this->next(); // skip #
  while (this->getCurrent() != endOfFile &&
         (this->getCurrent() != '#' ||
          (this->getCurrent() == '#' &&
           this->position + 1 < this->_sourceCode[lineNumber].length() &&
           this->_sourceCode[lineNumber][this->position + 1] != '/'))) {
    if (this->getCurrent() == endOfFile) {
      std::unique_ptr<SyntaxToken<std::any>> newSyntaxToken =
          std::move(readEndOfFile());

      this->_diagnosticHandler->addDiagnostic(Diagnostic(
          "Unterminated Comment Block", DiagnosticUtils::DiagnosticLevel::Error,
          DiagnosticUtils::DiagnosticType::Lexical,
          Utils::getSourceLocation(newSyntaxToken.get())));

      return std::move(newSyntaxToken);
    } else if (this->getCurrent() == endOfLine) {
      this->lineNumber++;
      this->position = 0;
    } else {
      this->next();
    }
  }

  this->next();
  return std::make_unique<SyntaxToken<std::any>>(
      this->_diagnosticHandler->getAbsoluteFilePath(), this->lineNumber,
      SyntaxKindUtils::SyntaxKind::CommentStatement, this->position++, "/##/",
      nullptr);
}

std::unique_ptr<SyntaxToken<std::any>> Lexer::readSingleLineComment() {
  this->next(); // skip /
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
      this->next();
    }
  }
  return std::make_unique<SyntaxToken<std::any>>(
      this->_diagnosticHandler->getAbsoluteFilePath(), this->lineNumber,
      SyntaxKindUtils::SyntaxKind::CommentStatement, this->position++, "/;",
      nullptr);
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

  case '&': {

    if (this->position + 1 < this->_sourceCode[lineNumber].length() &&
        this->_sourceCode[lineNumber][this->position + 1] == '&') {
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
    if (this->position + 1 < this->_sourceCode[lineNumber].length() &&
        this->_sourceCode[lineNumber][this->position + 1] == '#') {
      return std::move(this->readMultiLineComment());
    } else if (this->position + 1 < this->_sourceCode[lineNumber].length() &&
               this->_sourceCode[lineNumber][this->position + 1] == ';') {
      return std::move(this->readSingleLineComment());
    } else if (this->position + 1 < this->_sourceCode[lineNumber].length() &&
               this->_sourceCode[lineNumber][this->position + 1] == '/') {

      this->next(); // Skip /
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

    if (this->position + 1 < this->_sourceCode[lineNumber].length() &&
        this->_sourceCode[lineNumber][this->position + 1] == '|') {
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

    if (this->position + 1 < this->_sourceCode[lineNumber].length() &&
        this->_sourceCode[lineNumber][this->position + 1] == '=') {
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

    if (this->position + 1 < this->_sourceCode[lineNumber].length() &&
        this->_sourceCode[lineNumber][this->position + 1] == '=') {
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

    if (this->position + 1 < this->_sourceCode[lineNumber].length() &&
        this->_sourceCode[lineNumber][this->position + 1] == '=') {
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

    if (this->position + 1 < this->_sourceCode[lineNumber].length() &&
        this->_sourceCode[lineNumber][this->position + 1] == '=') {
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

  const int &_len = std::max(
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
  std::string text = "";
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
      this->next();
      switch (this->getCurrent()) {
      case '"':
        text += '"';
        break;
      case '\\':
        text += '\\';
        break;
      case 'n':
        text += '\n';
        break;
      case 'r':
        text += '\r';
        break;
      case 't':
        text += '\t';
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
      SyntaxKindUtils::SyntaxKind::StringToken, start, text, text);
}