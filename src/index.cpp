#include <algorithm>
#include <iostream>
#include <iterator>
#include <limits>
#include <map>
#include <memory>
#include <string>
#include <vector>
using namespace std;
// ANSI color codes
constexpr auto RESET = "\033[0m";
constexpr auto RED = "\033[31m";
constexpr auto GREEN = "\033[32m";
constexpr auto YELLOW = "\033[33m";
constexpr auto BLUE = "\033[34m";
enum SyntaxKind {
  NumberToken,
  WhitespaceToken,
  PlusToken,
  MinusToken,
  StarToken,
  SlashToken,
  OpenParenthesisToken,
  CloseParenthesisToken,
  BadToken,
  EndOfFileToken,
  NumberExpression,
  BinaryExpression,
  ParenthesizedExpression,
  CompilationUnit,
};
std::map<SyntaxKind, std::string> enum_to_string_map;
bool isInt32(const std::string &str) {
  try {
    size_t pos;
    int32_t number = std::stoi(str, &pos);
    return pos == str.size() && number >= std::numeric_limits<int32_t>::min() &&
           number <= std::numeric_limits<int32_t>::max();
  } catch (const std::exception &) {
    return false;
  }
}
void init_enum_to_string_map() {
  enum_to_string_map[SyntaxKind::NumberToken] = "NumberToken";
  enum_to_string_map[SyntaxKind::WhitespaceToken] = "WhitespaceToken";
  enum_to_string_map[SyntaxKind::PlusToken] = "PlusToken";
  enum_to_string_map[SyntaxKind::MinusToken] = "MinusToken";
  enum_to_string_map[SyntaxKind::StarToken] = "StarToken";
  enum_to_string_map[SyntaxKind::SlashToken] = "SlashToken";
  enum_to_string_map[SyntaxKind::OpenParenthesisToken] = "OpenParenthesisToken";
  enum_to_string_map[SyntaxKind::CloseParenthesisToken] =
      "CloseParenthesisToken";
  enum_to_string_map[SyntaxKind::BadToken] = "BadToken";
  enum_to_string_map[SyntaxKind::EndOfFileToken] = "EndOfFileToken";
  enum_to_string_map[SyntaxKind::NumberExpression] = "NumberExpression";
  enum_to_string_map[SyntaxKind::BinaryExpression] = "BinaryExpression";
  enum_to_string_map[SyntaxKind::ParenthesizedExpression] =
      "ParenthesizedExpression";
  enum_to_string_map[SyntaxKind::CompilationUnit] = "CompilationUnit";
}
class SyntaxNode {

public:
  virtual SyntaxKind getKind() = 0;

public:
  virtual vector<SyntaxNode *> getChildren() = 0;
};
class SyntaxToken : public SyntaxNode {
private:
  SyntaxKind kind;

private:
  int position;

private:
  string text;

private:
  unique_ptr<int> value;

public:
  SyntaxToken(SyntaxKind kind, int position, string text, unique_ptr<int> v) {
    this->kind = kind;
    this->position = position;
    this->text = text;
    this->value = move(v);
  }

public:
  SyntaxKind getKind() { return this->kind; }

public:
  int getPosition() { return this->position; }

public:
  string getText() { return this->text; }

public:
  unique_ptr<int> getValue() { return move(this->value); }

public:
  string getKindText() { return enum_to_string_map[this->kind]; }

public:
  int getUnaryOperatorPrecedence() {
    switch (this->kind) {
    case PlusToken:
    case MinusToken:
      return 3;
    default:
      return 0;
    }
  }

public:
  int getBinaryOperatorPrecedence() {
    switch (this->kind) {
    case StarToken:
    case SlashToken:
      return 2;
    case PlusToken:
    case MinusToken:
      return 1;
    default:
      return 0;
    }
  }

public:
public:
  vector<SyntaxNode *> children;
  vector<SyntaxNode *> getChildren() { return children; }
};

class Lexer {

private:
  string text;

private:
  int position;

public:
  vector<string> logs;

public:
  Lexer(string text) { this->text = text; }

private:
  char getCurrent() {
    if (this->position >= this->text.length()) {
      return '\0';
    }
    return this->text[this->position];
  }

private:
  void next() { this->position++; }

public:
  SyntaxToken *nextToken() {
    if (this->position >= this->text.length()) {
      return new SyntaxToken(EndOfFileToken, this->position, "\0", nullptr);
    }

    if (isdigit(this->getCurrent())) {
      int start = this->position;
      while (isdigit(this->getCurrent())) {
        this->next();
      }
      int length = this->position - start;
      string text = this->text.substr(start, length);
      try {
        if (isInt32(text) == false) {
          throw exception();
        }
      } catch (exception e) {
        logs.push_back("ERROR: bad number input not i32: " + text);
        return new SyntaxToken(BadToken, start, text, nullptr);
      }
      int res = stoi(text);

      return new SyntaxToken(NumberToken, start, text, make_unique<int>(res));
    }

    if (isspace(this->getCurrent())) {
      int start = this->position;
      while (isspace(this->getCurrent())) {
        this->next();
      }
      int length = this->position - start;
      string text = this->text.substr(start, length);
      return new SyntaxToken(WhitespaceToken, start, text, nullptr);
    }

    switch (this->getCurrent()) {
    case '+':
      return new SyntaxToken(PlusToken, this->position++, "+", nullptr);
    case '-':
      return new SyntaxToken(MinusToken, this->position++, "-", nullptr);
    case '*':
      return new SyntaxToken(StarToken, this->position++, "*", nullptr);
    case '/':
      return new SyntaxToken(SlashToken, this->position++, "/", nullptr);
    case '(':
      return new SyntaxToken(OpenParenthesisToken, this->position++, "(",
                             nullptr);
    case ')':
      return new SyntaxToken(CloseParenthesisToken, this->position++, ")",
                             nullptr);
    default:
      logs.push_back("ERROR: bad character input: " +
                     this->text.substr(this->position, 1));
      return new SyntaxToken(BadToken, this->position++,
                             this->text.substr(this->position - 1, 1), nullptr);
    }
  }
};

class ExpressionSyntax : public SyntaxNode {

public:
  virtual SyntaxKind getKind() = 0;

public:
  virtual vector<SyntaxNode *> getChildren() = 0;
};

class NumberExpressionSyntax : public ExpressionSyntax {

private:
  SyntaxToken *numberToken;

public:
  vector<SyntaxNode *> children;
  NumberExpressionSyntax(SyntaxToken *numberToken) {
    cout << numberToken->getText() << "gekl" << endl;
    this->numberToken = numberToken;

    children.push_back(this->numberToken);
  }

public:
  SyntaxKind getKind() { return NumberExpression; }

public:
  string getKindText() { return enum_to_string_map[this->getKind()]; }

public:
  SyntaxToken *getNumberToken() { return this->numberToken; }

public:
  vector<SyntaxNode *> getChildren() { return children; }
};

class BinaryExpressionSyntax : public ExpressionSyntax {

private:
  ExpressionSyntax *left;
  SyntaxToken *operatorToken;
  ExpressionSyntax *right;

public:
  vector<SyntaxNode *> children;
  BinaryExpressionSyntax(ExpressionSyntax *left, SyntaxToken *operatorToken,
                         ExpressionSyntax *right) {
    this->left = left;
    this->operatorToken = operatorToken;
    this->right = right;
    children.push_back(this->left);
    children.push_back(this->operatorToken);
    children.push_back(this->right);
  }

public:
  SyntaxKind getKind() { return BinaryExpression; }

public:
  ExpressionSyntax *getLeft() { return this->left; }

public:
  SyntaxToken *getOperatorToken() { return this->operatorToken; }

public:
  ExpressionSyntax *getRight() { return this->right; }

public:
  vector<SyntaxNode *> getChildren() { return children; }
};

class ParenthesizedExpressionSyntax : public ExpressionSyntax {
private:
  SyntaxToken *openParenthesisToken;
  ExpressionSyntax *expression;
  SyntaxToken *closeParenthesisToken;

public:
  vector<SyntaxNode *> children;

  ParenthesizedExpressionSyntax(SyntaxToken *openParenthesisToken,
                                ExpressionSyntax *expression,
                                SyntaxToken *closeParenthesisToken) {
    this->openParenthesisToken = openParenthesisToken;
    this->expression = expression;
    this->closeParenthesisToken = closeParenthesisToken;
    children.push_back(this->openParenthesisToken);
    children.push_back(this->expression);
    children.push_back(this->closeParenthesisToken);
  }

public:
  SyntaxKind getKind() { return ParenthesizedExpression; }

public:
  SyntaxToken *getOpenParenthesisToken() { return this->openParenthesisToken; }

public:
  ExpressionSyntax *getExpression() { return this->expression; }

public:
  SyntaxToken *getCloseParenthesisToken() {
    return this->closeParenthesisToken;
  }

public:
  vector<SyntaxNode *> getChildren() { return children; }
};

class CompilationUnitSyntax {
private:
  ExpressionSyntax *expression;
  SyntaxToken *endOfFileToken;

public:
  vector<string> logs;
  CompilationUnitSyntax(vector<string> &logs, ExpressionSyntax *expression,
                        SyntaxToken *endOfFileToken) {
    this->expression = expression;
    this->endOfFileToken = endOfFileToken;
    this->logs = logs;
  }

public:
  SyntaxKind getKind() { return CompilationUnit; }

public:
  ExpressionSyntax *getExpression() { return this->expression; }

public:
  SyntaxToken *getEndOfFileToken() { return this->endOfFileToken; }
};

class Parser {
private:
  std::vector<SyntaxToken *> tokens;
  int position;

public:
  vector<string> logs;

public:
  Parser(string text) {
    Lexer *lexer = new Lexer(text);
    SyntaxToken *token;
    do {
      token = lexer->nextToken();
      if (token->getKind() != WhitespaceToken && token->getKind() != BadToken) {
        this->tokens.push_back(token);
      }
    } while (token->getKind() != EndOfFileToken);

    if (lexer->logs.size()) {
      this->logs = lexer->logs;
    }
  }

private:
  SyntaxToken *peek(int offset) {
    int index = this->position + offset;
    if (index >= this->tokens.size()) {
      return this->tokens[this->tokens.size() - 1];
    }
    return this->tokens[index];
  }

private:
  SyntaxToken *getCurrent() { return this->peek(0); }

private:
  SyntaxToken *nextToken() {
    SyntaxToken *current = this->getCurrent();
    this->position++;
    return current;
  }

private:
  SyntaxToken *match(SyntaxKind kind) {
    if (this->getCurrent()->getKind() == kind) {
      return this->nextToken();
    }
    this->logs.push_back("ERROR: unexpected token <" +
                         this->getCurrent()->getKindText() + ">, expected <" +
                         enum_to_string_map[EndOfFileToken] + ">");

    return new SyntaxToken(kind, this->getCurrent()->getPosition(), "\0",
                           nullptr);
  }

public:
  CompilationUnitSyntax *parseCompilationUnit() {
    ExpressionSyntax *expression = this->parseExpression();
    SyntaxToken *endOfFileToken = this->match(EndOfFileToken);
    return new CompilationUnitSyntax(this->logs, expression, endOfFileToken);
  }

private:
  ExpressionSyntax *parseExpression(int parentPrecedence = 0) {
    ExpressionSyntax *left;
    int unaryOperatorPrecedence =
        this->getCurrent()->getUnaryOperatorPrecedence();
    if (unaryOperatorPrecedence != 0 &&
        unaryOperatorPrecedence >= parentPrecedence) {
      SyntaxToken *operatorToken = this->nextToken();
      ExpressionSyntax *operand =
          this->parseExpression(unaryOperatorPrecedence);
      left = new BinaryExpressionSyntax(
          new NumberExpressionSyntax(operatorToken), operatorToken, operand);
    } else {
      left = this->parsePrimaryExpression();
    }

    while (true) {
      int precedence = this->getCurrent()->getBinaryOperatorPrecedence();
      if (precedence == 0 || precedence <= parentPrecedence) {
        break;
      }
      SyntaxToken *operatorToken = this->nextToken();
      ExpressionSyntax *right = this->parseExpression(precedence);
      left = new BinaryExpressionSyntax(left, operatorToken, right);
    }

    return left;
  }

private:
  ExpressionSyntax *parsePrimaryExpression() {
    switch (this->getCurrent()->getKind()) {
    case OpenParenthesisToken: {
      SyntaxToken *left = this->nextToken();
      ExpressionSyntax *expression = this->parseExpression();
      SyntaxToken *right = this->match(CloseParenthesisToken);
      return new ParenthesizedExpressionSyntax(left, expression, right);
    }
    case NumberToken: {
      SyntaxToken *numberToken = this->nextToken();
      return new NumberExpressionSyntax(numberToken);
    }
    default:
      return new NumberExpressionSyntax(new SyntaxToken(
          NumberToken, this->getCurrent()->getPosition(), "0", nullptr));
    }
  }
};

class Evaluator {
public:
  static int evaluate(ExpressionSyntax *node) {

    switch (node->getKind()) {
    case NumberExpression: {
      NumberExpressionSyntax *numberExpression = (NumberExpressionSyntax *)node;

      return *(numberExpression->getNumberToken()->getValue().get());
    }
    case BinaryExpression: {
      BinaryExpressionSyntax *binaryExpression = (BinaryExpressionSyntax *)node;
      int left = Evaluator::evaluate(binaryExpression->getLeft());
      int right = Evaluator::evaluate(binaryExpression->getRight());
      switch (binaryExpression->getOperatorToken()->getKind()) {
      case PlusToken:
        return left + right;
      case MinusToken:
        return left - right;
      case StarToken:
        return left * right;
      case SlashToken:
        return left / right;
      default:
        throw "Unexpected binary operator";
      }
    }
    case ParenthesizedExpression: {
      ParenthesizedExpressionSyntax *parenthesizedExpression =
          (ParenthesizedExpressionSyntax *)node;
      return Evaluator::evaluate(parenthesizedExpression->getExpression());
    }
    default:
      throw "Unexpected node";
    }
  }
};

class Compiler {

public:
  static int compile(string text) {
    Parser *parser = new Parser(text);

    // CompilationUnitSyntax *compilationUnit =
    parser->parseCompilationUnit();
    // return Evaluator::evaluate(compilationUnit->getExpression());
    return 0;
  }
};

void prettyPrint(SyntaxNode *node, string indent = "", bool isLast = true) {
  cout << indent;
  if (isLast) {
    cout << "\\-";
    indent += "  ";
  } else {
    cout << "|-";
    indent += "| ";
  }
  cout << enum_to_string_map[node->getKind()] << endl;
  vector<SyntaxNode *> children = node->getChildren();
  for (int i = 0; i < children.size(); i++) {
    prettyPrint(children[i], indent, i == children.size() - 1);
  }
}

int main() {

  init_enum_to_string_map();
  string line;

  getline(cin, line);

  Parser *parser = new Parser(line);
  CompilationUnitSyntax *compilationUnit =
      (CompilationUnitSyntax *)parser->parseCompilationUnit();

  prettyPrint(compilationUnit->getExpression());
  if (compilationUnit->logs.size()) {
    for (int i = 0; i < parser->parseCompilationUnit()->logs.size(); i++) {
      cout << RED << parser->parseCompilationUnit()->logs[i] << RESET << endl;
    }
  } else {

    cout << GREEN << Evaluator::evaluate(compilationUnit->getExpression())
         << RESET << endl;
  }

  return 0;
}
