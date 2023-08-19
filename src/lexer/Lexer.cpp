#include "Lexer.h"

Lexer::Lexer(const std::vector<std::string> &text) {
  this->text = text;
  this->lineNumber = 0;
  this->position = 0;
}

char Lexer::getCurrent() {
  if (this->position >= this->text[lineNumber].length()) {
    return '\0';
  }
  return this->text[lineNumber][this->position];
}
void Lexer::updatePosition() {
  this->position = 0;
  this->lineNumber++;
}
void Lexer::next() { this->position++; }

std::unique_ptr<SyntaxToken<std::any>> Lexer::nextToken() {

  if (this->lineNumber >= this->text.size()) {
    return std::make_unique<SyntaxToken<std::any>>(
        this->lineNumber++, SyntaxKindUtils::SyntaxKind::EndOfFileToken,
        this->position, "\0", "\0");
  }

  if (this->position >= this->text[lineNumber].length()) {
    int prevPosition = this->position;
    int prevLineNumber = this->lineNumber;
    this->updatePosition();
    return std::make_unique<SyntaxToken<std::any>>(
        prevLineNumber, SyntaxKindUtils::SyntaxKind::EndOfLineToken,
        prevPosition, "\r\n", "\r\n");
  }

  // check for int

  if (isdigit(this->getCurrent())) {
    int start = this->position;
    while (isdigit(this->getCurrent())) {
      this->next();
    }

    // check for double

    if (this->getCurrent() == '.') {
      this->next();
      while (isdigit(this->getCurrent())) {
        this->next();
      }
      int length = this->position - start;
      std::string text = this->text[lineNumber].substr(start, length);
      try {
        if (SyntaxKindUtils::isDouble(text) == false) {
          throw std::runtime_error("bad number input not double: " + text);
        }
      } catch (std::exception e) {
        std::unique_ptr<SyntaxToken<std::any>> newSyntaxToken =
            std::make_unique<SyntaxToken<std::any>>(
                this->lineNumber, SyntaxKindUtils::SyntaxKind::BadToken, start,
                text, text);
        this->logs.push_back(
            Utils::getLineNumberAndPosition(newSyntaxToken.get()) +
            "ERROR: bad number input not double: " + text);
        return std::move(newSyntaxToken);
      }
      double res = stod(text);

      return std::make_unique<SyntaxToken<std::any>>(
          this->lineNumber, SyntaxKindUtils::SyntaxKind::NumberToken, start,
          text, res);
    }

    int length = this->position - start;
    std::string text = this->text[lineNumber].substr(start, length);
    try {
      if (SyntaxKindUtils::isInt64(text) == false) {
        throw std::runtime_error("bad number input not Int64: " + text);
      }
    } catch (std::exception e) {

      std::unique_ptr<SyntaxToken<std::any>> newSyntaxToken =
          std::make_unique<SyntaxToken<std::any>>(
              this->lineNumber, SyntaxKindUtils::SyntaxKind::BadToken, start,
              text, 0);

      this->logs.push_back(
          Utils::getLineNumberAndPosition(newSyntaxToken.get()) +
          "ERROR: bad number input not Int64: " + text);
      return std::move(newSyntaxToken);
    }
    int resInt = stoi(text);

    return std::make_unique<SyntaxToken<std::any>>(
        this->lineNumber, SyntaxKindUtils::SyntaxKind::NumberToken, start, text,
        int(resInt));
  }

  // Check true or false

  if (isalpha(this->getCurrent())) {
    int start = this->position;
    while (isalnum(this->getCurrent())) {
      this->next();
    }
    int length = this->position - start;
    std::string text = this->text[lineNumber].substr(start, length);
    if (text == "true") {
      return std::make_unique<SyntaxToken<std::any>>(
          this->lineNumber, SyntaxKindUtils::SyntaxKind::TrueKeyword, start,
          text, true);
    }
    if (text == "false") {
      return std::make_unique<SyntaxToken<std::any>>(
          this->lineNumber, SyntaxKindUtils::SyntaxKind::FalseKeyword, start,
          text, false);
    }
    if (text == "var") {
      return std::make_unique<SyntaxToken<std::any>>(
          this->lineNumber, SyntaxKindUtils::SyntaxKind::VarKeyword, start,
          text, "var");
    }

    if (text == "if") {
      return std::make_unique<SyntaxToken<std::any>>(
          this->lineNumber, SyntaxKindUtils::SyntaxKind::IfKeyword, start, text,
          "if");
    }

    if (text == "or") {
      return std::make_unique<SyntaxToken<std::any>>(
          this->lineNumber, SyntaxKindUtils::SyntaxKind::OrKeyword, start, text,
          "or");
    }

    if (text == "else") {
      return std::make_unique<SyntaxToken<std::any>>(
          this->lineNumber, SyntaxKindUtils::SyntaxKind::ElseKeyword, start,
          text, "else");
    }

    if (text == "while") {
      return std::make_unique<SyntaxToken<std::any>>(
          this->lineNumber, SyntaxKindUtils::SyntaxKind::WhileKeyword, start,
          text, "while");
    }

    if (text == "for") {
      return std::make_unique<SyntaxToken<std::any>>(
          this->lineNumber, SyntaxKindUtils::SyntaxKind::ForKeyword, start,
          text, "for");
    }
    if (text == "fun") {
      return std::make_unique<SyntaxToken<std::any>>(
          this->lineNumber, SyntaxKindUtils::SyntaxKind::FunctionKeyword, start,
          text, "fun");
    }

    if (text == "to") {
      return std::make_unique<SyntaxToken<std::any>>(
          this->lineNumber, SyntaxKindUtils::SyntaxKind::ToKeyword, start, text,
          "to");
    }

    if (text == "continue") {
      return std::make_unique<SyntaxToken<std::any>>(
          this->lineNumber, SyntaxKindUtils::SyntaxKind::ContinueKeyword, start,
          text, "continue");
    }

    if (text == "break") {
      return std::make_unique<SyntaxToken<std::any>>(
          this->lineNumber, SyntaxKindUtils::SyntaxKind::BreakKeyword, start,
          text, "break");
    }

    if (text == "return") {
      return std::make_unique<SyntaxToken<std::any>>(
          this->lineNumber, SyntaxKindUtils::SyntaxKind::ReturnKeyword, start,
          text, "return");
    }

    if (text == "const") {
      return std::make_unique<SyntaxToken<std::any>>(
          this->lineNumber, SyntaxKindUtils::SyntaxKind::ConstKeyword, start,
          text, "const");
    }

    return std::make_unique<SyntaxToken<std::any>>(
        this->lineNumber, SyntaxKindUtils::SyntaxKind::IdentifierToken, start,
        text, (text));
  }

  if (isspace(this->getCurrent())) {
    int start = this->position;

    while (isspace(this->getCurrent())) {
      this->next();
    }
    int length = this->position - start;
    std::string text = this->text[lineNumber].substr(start, length);
    return std::make_unique<SyntaxToken<std::any>>(
        this->lineNumber, SyntaxKindUtils::SyntaxKind::WhitespaceToken, start,
        text, 0);
  }

  switch (this->getCurrent()) {
  case '+':
    return std::make_unique<SyntaxToken<std::any>>(
        this->lineNumber, SyntaxKindUtils::SyntaxKind::PlusToken,
        this->position++, "+", "+");
  case '-':
    return std::make_unique<SyntaxToken<std::any>>(
        this->lineNumber, SyntaxKindUtils::SyntaxKind::MinusToken,
        this->position++, "-", "-");
  case '*':
    return std::make_unique<SyntaxToken<std::any>>(
        this->lineNumber, SyntaxKindUtils::SyntaxKind::StarToken,
        this->position++, "*", "*");
  case '/':
    return std::make_unique<SyntaxToken<std::any>>(
        this->lineNumber, SyntaxKindUtils::SyntaxKind::SlashToken,
        this->position++, "/", "/");
  case '(':
    return std::make_unique<SyntaxToken<std::any>>(
        this->lineNumber, SyntaxKindUtils::SyntaxKind::OpenParenthesisToken,
        this->position++, "(", 0);
  case ')':
    return std::make_unique<SyntaxToken<std::any>>(
        this->lineNumber, SyntaxKindUtils::SyntaxKind::CloseParenthesisToken,
        this->position++, ")", 0);
  case '&': {

    if (this->position + 1 < this->text[lineNumber].length() &&
        this->text[lineNumber][this->position + 1] == '&') {
      this->next();
      return std::make_unique<SyntaxToken<std::any>>(
          this->lineNumber,
          SyntaxKindUtils::SyntaxKind::AmpersandAmpersandToken,
          this->position++, "&&", "&&");
    }

    return std::make_unique<SyntaxToken<std::any>>(
        this->lineNumber, SyntaxKindUtils::SyntaxKind::AmpersandToken,
        this->position++, "&", "&");
  }
  case '^':
    return std::make_unique<SyntaxToken<std::any>>(
        this->lineNumber, SyntaxKindUtils::SyntaxKind::CaretToken,
        this->position++, "^", "^");
  case '%':
    return std::make_unique<SyntaxToken<std::any>>(
        this->lineNumber, SyntaxKindUtils::SyntaxKind::PercentToken,
        this->position++, "%", "%");
  case '~':
    return std::make_unique<SyntaxToken<std::any>>(
        this->lineNumber, SyntaxKindUtils::SyntaxKind::TildeToken,
        this->position++, "~", "~");
  case '|': {

    if (this->position + 1 < this->text[lineNumber].length() &&
        this->text[lineNumber][this->position + 1] == '|') {
      this->next();
      return std::make_unique<SyntaxToken<std::any>>(
          this->lineNumber, SyntaxKindUtils::SyntaxKind::PipePipeToken,
          this->position++, "||", 0);
    }

    return std::make_unique<SyntaxToken<std::any>>(
        this->lineNumber, SyntaxKindUtils::SyntaxKind::PipeToken,
        this->position++, "|", 0);
  }
  case '=': {

    if (this->position + 1 < this->text[lineNumber].length() &&
        this->text[lineNumber][this->position + 1] == '=') {
      this->next();
      return std::make_unique<SyntaxToken<std::any>>(
          this->lineNumber, SyntaxKindUtils::SyntaxKind::EqualsEqualsToken,
          this->position++, "==", 0);
    }
    return std::make_unique<SyntaxToken<std::any>>(
        this->lineNumber, SyntaxKindUtils::SyntaxKind::EqualsToken,
        this->position++, "=", 0);
  }

  case '!': {

    if (this->position + 1 < this->text[lineNumber].length() &&
        this->text[lineNumber][this->position + 1] == '=') {
      this->next();
      return std::make_unique<SyntaxToken<std::any>>(
          this->lineNumber, SyntaxKindUtils::SyntaxKind::BangEqualsToken,
          this->position++, "!=", 0);
    }
    return std::make_unique<SyntaxToken<std::any>>(
        this->lineNumber, SyntaxKindUtils::SyntaxKind::BangToken,
        this->position++, "!", 0);
  }

  case '<': {

    if (this->position + 1 < this->text[lineNumber].length() &&
        this->text[lineNumber][this->position + 1] == '=') {
      this->next();
      return std::make_unique<SyntaxToken<std::any>>(
          this->lineNumber, SyntaxKindUtils::SyntaxKind::LessOrEqualsToken,
          this->position++, "<=", 0);
    }
    return std::make_unique<SyntaxToken<std::any>>(
        this->lineNumber, SyntaxKindUtils::SyntaxKind::LessToken,
        this->position++, "<", 0);
  }

  case '>': {

    if (this->position + 1 < this->text[lineNumber].length() &&
        this->text[lineNumber][this->position + 1] == '=') {
      this->next();
      return std::make_unique<SyntaxToken<std::any>>(
          this->lineNumber, SyntaxKindUtils::SyntaxKind::GreaterOrEqualsToken,
          this->position++, ">=", 0);
    }
    return std::make_unique<SyntaxToken<std::any>>(
        this->lineNumber, SyntaxKindUtils::SyntaxKind::GreaterToken,
        this->position++, ">", 0);
  }

  case ';':
    return std::make_unique<SyntaxToken<std::any>>(
        this->lineNumber, SyntaxKindUtils::SyntaxKind::SemicolonToken,
        this->position++, ";", 0);
  case ',':
    return std::make_unique<SyntaxToken<std::any>>(
        this->lineNumber, SyntaxKindUtils::SyntaxKind::CommaToken,
        this->position++, ",", ",");
  case '{':
    return std::make_unique<SyntaxToken<std::any>>(
        this->lineNumber, SyntaxKindUtils::SyntaxKind::OpenBraceToken,
        this->position++, "{", 0);
  case '}':
    return std::make_unique<SyntaxToken<std::any>>(
        this->lineNumber, SyntaxKindUtils::SyntaxKind::CloseBraceToken,
        this->position++, "}", 0);
  case '"':
    return std::move(this->readString());

  default:
    int _pos = this->position;
    int _len = this->text[lineNumber].length() - this->position;

    std::unique_ptr<SyntaxToken<std::any>> newSyntaxToken =
        std::make_unique<SyntaxToken<std::any>>(
            this->lineNumber, SyntaxKindUtils::SyntaxKind::BadToken,
            this->position++, this->text[lineNumber].substr(_pos, _len),
            this->text[lineNumber].substr(_pos, _len));
    this->logs.push_back(Utils::getLineNumberAndPosition(newSyntaxToken.get()) +
                         "ERROR: bad character input: " +
                         this->text[lineNumber].substr(_pos, _len));

    return std::move(newSyntaxToken);
  }

  return std::make_unique<SyntaxToken<std::any>>(
      this->lineNumber, SyntaxKindUtils::SyntaxKind::EndOfFileToken,
      this->position, "", 0);
}

std::unique_ptr<SyntaxToken<std::any>> Lexer::readString() {
  int start = this->position++;
  std::string text = "";
  while (this->getCurrent() != '"') {
    if (this->getCurrent() == '\0') {

      std::unique_ptr<SyntaxToken<std::any>> newSyntaxToken =
          std::make_unique<SyntaxToken<std::any>>(
              this->lineNumber, SyntaxKindUtils::SyntaxKind::BadToken, start,
              this->text[lineNumber].substr(start, this->position - start), 0);

      this->logs.push_back(
          Utils::getLineNumberAndPosition(newSyntaxToken.get()) +
          "ERROR: unterminated string literal");
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
                this->lineNumber, SyntaxKindUtils::SyntaxKind::BadToken, start,
                this->text[lineNumber].substr(start, this->position - start),
                0);
        this->logs.push_back(
            Utils::getLineNumberAndPosition(newSyntaxToken.get()) +
            "ERROR: bad character escape sequence: \\" +
            this->text[lineNumber].substr(this->position, 1));
        return std::move(newSyntaxToken);
      }
    } else {
      text += this->getCurrent();
    }
    this->next();
  }
  this->next();
  return std::make_unique<SyntaxToken<std::any>>(
      this->lineNumber, SyntaxKindUtils::SyntaxKind::StringToken, start, text,
      text);
}