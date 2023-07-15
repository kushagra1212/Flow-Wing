#include "Lexer.h"

Lexer::Lexer(std::string text) { this->text = text; }

char Lexer::getCurrent() {
  if (this->position >= this->text.length()) {
    return '\0';
  }
  return this->text[this->position];
}

void Lexer::next() { this->position++; }

SyntaxToken *Lexer::nextToken() {
  if (this->position >= this->text.length()) {
    return new SyntaxToken(SyntaxKindUtils::SyntaxKind::EndOfFileToken,
                           this->position, "\0", nullptr);
  }

  if (isdigit(this->getCurrent())) {
    int start = this->position;
    while (isdigit(this->getCurrent())) {
      this->next();
    }
    int length = this->position - start;
    std::string text = this->text.substr(start, length);
    try {
      if (SyntaxKindUtils::isInt32(text) == false) {
        throw std::exception();
      }
    } catch (std::exception e) {
      logs.push_back("ERROR: bad number input not i32: " + text);
      return new SyntaxToken(SyntaxKindUtils::SyntaxKind::BadToken, start, text,
                             nullptr);
    }
    int res = stoi(text);

    return new SyntaxToken(SyntaxKindUtils::SyntaxKind::NumberToken, start,
                           text, std::make_shared<int>(res));
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
      return new SyntaxToken(SyntaxKindUtils::SyntaxKind::TrueKeyword, start,
                             text, nullptr);
    }
    if (text == "false") {
      return new SyntaxToken(SyntaxKindUtils::SyntaxKind::FalseKeyword, start,
                             text, nullptr);
    }

    return new SyntaxToken(SyntaxKindUtils::SyntaxKind::IdentifierToken, start,
                           text, nullptr);
  }

  if (isspace(this->getCurrent())) {
    int start = this->position;
    while (isspace(this->getCurrent())) {
      this->next();
    }
    int length = this->position - start;
    std::string text = this->text.substr(start, length);
    return new SyntaxToken(SyntaxKindUtils::SyntaxKind::WhitespaceToken, start,
                           text, nullptr);
  }

  switch (this->getCurrent()) {
  case '+':
    return new SyntaxToken(SyntaxKindUtils::SyntaxKind::PlusToken,
                           this->position++, "+", nullptr);
  case '-':
    return new SyntaxToken(SyntaxKindUtils::SyntaxKind::MinusToken,
                           this->position++, "-", nullptr);
  case '*':
    return new SyntaxToken(SyntaxKindUtils::SyntaxKind::StarToken,
                           this->position++, "*", nullptr);
  case '/':
    return new SyntaxToken(SyntaxKindUtils::SyntaxKind::SlashToken,
                           this->position++, "/", nullptr);
  case '(':
    return new SyntaxToken(SyntaxKindUtils::SyntaxKind::OpenParenthesisToken,
                           this->position++, "(", nullptr);
  case ')':
    return new SyntaxToken(SyntaxKindUtils::SyntaxKind::CloseParenthesisToken,
                           this->position++, ")", nullptr);
  case '&':
    if (this->position + 1 < this->text.length() &&
        this->text[this->position + 1] == '&') {
      return new SyntaxToken(
          SyntaxKindUtils::SyntaxKind::AmpersandAmpersandToken,
          this->position++, "&&", nullptr);
    }
    logs.push_back("ERROR: bad character input: " +
                   this->text.substr(this->position, 1));
    return new SyntaxToken(SyntaxKindUtils::SyntaxKind::BadToken,
                           this->position++,
                           this->text.substr(this->position - 1, 1), nullptr);
  case '|': {

    if (this->position + 1 < this->text.length() &&
        this->text[this->position + 1] == '|') {
      return new SyntaxToken(SyntaxKindUtils::SyntaxKind::PipePipeToken,
                             this->position++, "||", nullptr);
    }
    logs.push_back("ERROR: bad character input: " +
                   this->text.substr(this->position, 1));
    return new SyntaxToken(SyntaxKindUtils::SyntaxKind::BadToken,
                           this->position++,
                           this->text.substr(this->position - 1, 1), nullptr);
  }
  case '=':
    if (this->position + 1 < this->text.length() &&
        this->text[this->position + 1] == '=') {
      return new SyntaxToken(SyntaxKindUtils::SyntaxKind::EqualsEqualsToken,
                             this->position++, "==", nullptr);
    }
    return new SyntaxToken(SyntaxKindUtils::SyntaxKind::EqualsToken,
                           this->position++, "=", nullptr);

  case '!':
    if (this->position + 1 < this->text.length() &&
        this->text[this->position + 1] == '=') {
      return new SyntaxToken(SyntaxKindUtils::SyntaxKind::BangEqualsToken,
                             this->position++, "!=", nullptr);
    }
    return new SyntaxToken(SyntaxKindUtils::SyntaxKind::BangToken,
                           this->position++, "!", nullptr);

  case '<':
    if (this->position + 1 < this->text.length() &&
        this->text[this->position + 1] == '=') {
      return new SyntaxToken(SyntaxKindUtils::SyntaxKind::LessOrEqualsToken,
                             this->position++, "<=", nullptr);
    }
    return new SyntaxToken(SyntaxKindUtils::SyntaxKind::LessToken,
                           this->position++, "<", nullptr);

  case '>':
    if (this->position + 1 < this->text.length() &&
        this->text[this->position + 1] == '=') {
      return new SyntaxToken(SyntaxKindUtils::SyntaxKind::GreaterOrEqualsToken,
                             this->position++, ">=", nullptr);
    }
    return new SyntaxToken(SyntaxKindUtils::SyntaxKind::GreaterToken,
                           this->position++, ">", nullptr);

  case ';':
    return new SyntaxToken(SyntaxKindUtils::SyntaxKind::SemicolonToken,
                           this->position++, ";", nullptr);
  case ',':
    return new SyntaxToken(SyntaxKindUtils::SyntaxKind::CommaToken,
                           this->position++, ",", nullptr);
  case '{':
    return new SyntaxToken(SyntaxKindUtils::SyntaxKind::OpenBraceToken,
                           this->position++, "{", nullptr);
  case '}':
    return new SyntaxToken(SyntaxKindUtils::SyntaxKind::CloseBraceToken,
                           this->position++, "}", nullptr);
  case '"':
    return this->readString();

  default:
    logs.push_back("ERROR: bad character input: " +
                   this->text.substr(this->position, 1));
    return new SyntaxToken(SyntaxKindUtils::SyntaxKind::BadToken,
                           this->position++,
                           this->text.substr(this->position - 1, 1), nullptr);
  }
}

SyntaxToken *Lexer::readString() {
  int start = this->position++;
  std::string text = "";
  while (this->getCurrent() != '"') {
    if (this->getCurrent() == '\0') {
      logs.push_back("ERROR: unterminated string literal");
      return new SyntaxToken(SyntaxKindUtils::SyntaxKind::BadToken, start,
                             this->text.substr(start, this->position - start),
                             nullptr);
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
        return new SyntaxToken(SyntaxKindUtils::SyntaxKind::BadToken, start,
                               this->text.substr(start, this->position - start),
                               nullptr);
      }
    } else {
      text += this->getCurrent();
    }
    this->next();
  }
  this->next();
  return new SyntaxToken(SyntaxKindUtils::SyntaxKind::StringToken, start,
                         this->text.substr(start, this->position - start),
                         std::make_shared<std::string>(text));

  //&(text)
}