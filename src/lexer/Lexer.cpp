#include "Lexer.h"

Lexer::Lexer(std::string text) { this->text = text; }

char Lexer::getCurrent() {
  if (this->position >= this->text.length()) {
    return '\0';
  }
  return this->text[this->position];
}

void Lexer::next() { this->position++; }

SyntaxToken<std::any> *Lexer::nextToken() {
  if (this->position >= this->text.length()) {
    return new SyntaxToken<std::any>(
        SyntaxKindUtils::SyntaxKind::EndOfFileToken, this->position, "\0", 0);
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
      std::string text = this->text.substr(start, length);
      try {
        if (SyntaxKindUtils::isDouble(text) == false) {
          throw std::exception();
        }
      } catch (std::exception e) {
        logs.push_back("ERROR: bad number input not double: " + text);
        return new SyntaxToken<std::any>(SyntaxKindUtils::SyntaxKind::BadToken,
                                         start, text, 0);
      }
      double res = stod(text);

      return new SyntaxToken<std::any>(SyntaxKindUtils::SyntaxKind::NumberToken,
                                       start, text, (res));
    }

    int length = this->position - start;
    std::string text = this->text.substr(start, length);
    try {
      if (SyntaxKindUtils::isInt64(text) == false) {
        throw std::exception();
      }
    } catch (std::exception e) {
      logs.push_back("ERROR: bad number input not i32: " + text);
      return new SyntaxToken<std::any>(SyntaxKindUtils::SyntaxKind::BadToken,
                                       start, text, 0);
    }
    int res = stoi(text);

    return new SyntaxToken<std::any>(SyntaxKindUtils::SyntaxKind::NumberToken,
                                     start, text, res);
  }

  // Check true or false

  if (isalpha(this->getCurrent())) {
    int start = this->position;
    while (isalpha(this->getCurrent())) {
      this->next();
    }
    int length = this->position - start;
    std::string text = this->text.substr(start, length);
    if (text == "true") {
      return new SyntaxToken<std::any>(SyntaxKindUtils::SyntaxKind::TrueKeyword,
                                       start, text, true);
    }
    if (text == "false") {
      return new SyntaxToken<std::any>(
          SyntaxKindUtils::SyntaxKind::FalseKeyword, start, text, false);
    }

    return new SyntaxToken<std::any>(
        SyntaxKindUtils::SyntaxKind::IdentifierToken, start, text, (text));
  }

  if (isspace(this->getCurrent())) {
    int start = this->position;
    while (isspace(this->getCurrent())) {
      this->next();
    }
    int length = this->position - start;
    std::string text = this->text.substr(start, length);
    return new SyntaxToken<std::any>(
        SyntaxKindUtils::SyntaxKind::WhitespaceToken, start, text, 0);
  }

  switch (this->getCurrent()) {
  case '+':
    return new SyntaxToken<std::any>(SyntaxKindUtils::SyntaxKind::PlusToken,
                                     this->position++, "+", 0);
  case '-':
    return new SyntaxToken<std::any>(SyntaxKindUtils::SyntaxKind::MinusToken,
                                     this->position++, "-", 0);
  case '*':
    return new SyntaxToken<std::any>(SyntaxKindUtils::SyntaxKind::StarToken,
                                     this->position++, "*", 0);
  case '/':
    return new SyntaxToken<std::any>(SyntaxKindUtils::SyntaxKind::SlashToken,
                                     this->position++, "/", 0);
  case '(':
    return new SyntaxToken<std::any>(
        SyntaxKindUtils::SyntaxKind::OpenParenthesisToken, this->position++,
        "(", 0);
  case ')':
    return new SyntaxToken<std::any>(
        SyntaxKindUtils::SyntaxKind::CloseParenthesisToken, this->position++,
        ")", 0);
  case '&': {

    if (this->position + 1 < this->text.length() &&
        this->text[this->position + 1] == '&') {
      this->next();
      return new SyntaxToken<std::any>(
          SyntaxKindUtils::SyntaxKind::AmpersandAmpersandToken,
          this->position++, "&&", 0);
    }

    return new SyntaxToken<std::any>(
        SyntaxKindUtils::SyntaxKind::AmpersandToken, this->position++, "&", 0);
  }
  case '^':
    return new SyntaxToken<std::any>(SyntaxKindUtils::SyntaxKind::CaretToken,
                                     this->position++, "^", 0);
  case '%':
    return new SyntaxToken<std::any>(SyntaxKindUtils::SyntaxKind::PercentToken,
                                     this->position++, "%", 0);
  case '~':
    return new SyntaxToken<std::any>(SyntaxKindUtils::SyntaxKind::TildeToken,
                                     this->position++, "~", 0);
  case '|': {

    if (this->position + 1 < this->text.length() &&
        this->text[this->position + 1] == '|') {
      this->next();
      return new SyntaxToken<std::any>(
          SyntaxKindUtils::SyntaxKind::PipePipeToken, this->position++, "||",
          0);
    }

    return new SyntaxToken<std::any>(SyntaxKindUtils::SyntaxKind::PipeToken,
                                     this->position++, "|", 0);
  }
  case '=': {

    if (this->position + 1 < this->text.length() &&
        this->text[this->position + 1] == '=') {
      this->next();
      return new SyntaxToken<std::any>(
          SyntaxKindUtils::SyntaxKind::EqualsEqualsToken, this->position++,
          "==", 0);
    }
    return new SyntaxToken<std::any>(SyntaxKindUtils::SyntaxKind::EqualsToken,
                                     this->position++, "=", 0);
  }

  case '!': {

    if (this->position + 1 < this->text.length() &&
        this->text[this->position + 1] == '=') {
      this->next();
      return new SyntaxToken<std::any>(
          SyntaxKindUtils::SyntaxKind::BangEqualsToken, this->position++,
          "!=", 0);
    }
    return new SyntaxToken<std::any>(SyntaxKindUtils::SyntaxKind::BangToken,
                                     this->position++, "!", 0);
  }

  case '<': {

    if (this->position + 1 < this->text.length() &&
        this->text[this->position + 1] == '=') {
      this->next();
      return new SyntaxToken<std::any>(
          SyntaxKindUtils::SyntaxKind::LessOrEqualsToken, this->position++,
          "<=", 0);
    }
    return new SyntaxToken<std::any>(SyntaxKindUtils::SyntaxKind::LessToken,
                                     this->position++, "<", 0);
  }

  case '>': {

    if (this->position + 1 < this->text.length() &&
        this->text[this->position + 1] == '=') {
      this->next();
      return new SyntaxToken<std::any>(
          SyntaxKindUtils::SyntaxKind::GreaterOrEqualsToken, this->position++,
          ">=", 0);
    }
    return new SyntaxToken<std::any>(SyntaxKindUtils::SyntaxKind::GreaterToken,
                                     this->position++, ">", 0);
  }

  case ';':
    return new SyntaxToken<std::any>(
        SyntaxKindUtils::SyntaxKind::SemicolonToken, this->position++, ";", 0);
  case ',':
    return new SyntaxToken<std::any>(SyntaxKindUtils::SyntaxKind::CommaToken,
                                     this->position++, ",", 0);
  case '{':
    return new SyntaxToken<std::any>(
        SyntaxKindUtils::SyntaxKind::OpenBraceToken, this->position++, "{", 0);
  case '}':
    return new SyntaxToken<std::any>(
        SyntaxKindUtils::SyntaxKind::CloseBraceToken, this->position++, "}", 0);
  case '"':
    return this->readString();

  default:
    logs.push_back("ERROR: bad character input: " +
                   this->text.substr(this->position, 1));
    return new SyntaxToken<std::any>(
        SyntaxKindUtils::SyntaxKind::BadToken, this->position++,
        this->text.substr(this->position - 1, 1), 0);
  }
}

SyntaxToken<std::any> *Lexer::readString() {
  int start = this->position++;
  std::string text = "";
  while (this->getCurrent() != '"') {
    if (this->getCurrent() == '\0') {
      logs.push_back("ERROR: unterminated string literal");
      return new SyntaxToken<std::any>(
          SyntaxKindUtils::SyntaxKind::BadToken, start,
          this->text.substr(start, this->position - start), 0);
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
        logs.push_back("ERROR: bad character escape sequence: \\" +
                       this->text.substr(this->position, 1));
        return new SyntaxToken<std::any>(
            SyntaxKindUtils::SyntaxKind::BadToken, start,
            this->text.substr(start, this->position - start), 0);
      }
    } else {
      text += this->getCurrent();
    }
    this->next();
  }
  this->next();
  return new SyntaxToken<std::any>(
      SyntaxKindUtils::SyntaxKind::StringToken, start,
      this->text.substr(start, this->position - start), (text));

  //&(text)
}