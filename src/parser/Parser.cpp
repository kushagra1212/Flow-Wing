#include "Parser.h"
Parser::Parser(const std::vector<std::string> &sourceCode,
               FLowWing::DiagnosticHandler *diagnosticHandler,
               std::unordered_map<std::string, int8_t> bringStatementPathsMap) {
  this->tokens = std::vector<std::unique_ptr<SyntaxToken<std::any>>>();
  this->_diagnosticHandler = diagnosticHandler;

  this->_bringStatementsPathsMap = bringStatementPathsMap;
  lexer = std::make_unique<Lexer>(sourceCode, diagnosticHandler);

  SyntaxKindUtils::SyntaxKind _kind =
      SyntaxKindUtils::SyntaxKind::EndOfFileToken;

  do {
    std::unique_ptr<SyntaxToken<std::any>> token =
        std::move(lexer->nextToken());
    _kind = token->getKind();

    // For debugging
    // std::cout << SyntaxKindUtils::to_string(_kind) << std::endl;

    if (_kind == SyntaxKindUtils::SyntaxKind::BadToken) {
      this->_diagnosticHandler->addDiagnostic(
          Diagnostic("Unexpected Character <" + token->getText() + ">",
                     DiagnosticUtils::DiagnosticLevel::Error,
                     DiagnosticUtils::DiagnosticType::Syntactic,
                     Utils::getSourceLocation(token.get())));
    }

    if (_kind != SyntaxKindUtils::SyntaxKind::WhitespaceToken &&
        _kind != SyntaxKindUtils::SyntaxKind::EndOfLineToken) {
      this->tokens.push_back(std::move(token));
    } else {
      token.reset();
    }

  } while (_kind != SyntaxKindUtils::SyntaxKind::EndOfFileToken);

#if (defined(DEBUG) && defined(JIT_MODE)) ||                                   \
    (defined(DEBUG) && defined(AOT_MODE))

  Utils::prettyPrint(this->tokens);

#endif

  compilationUnit = std::make_unique<CompilationUnitSyntax>();
}

Parser::~Parser() {
  for (auto &token : this->tokens) {
    token.reset();
  }
  lexer.reset();

  this->tokens.clear();
}

SyntaxToken<std::any> *Parser::peek(const int &offset) {
  const int index = this->position + offset;
  if (index >= this->tokens.size()) {
    return this->tokens[this->tokens.size() - 1].get();
  }
  return this->tokens[index].get();
}

SyntaxToken<std::any> *Parser::getCurrent() { return this->peek(0); }

std::unique_ptr<SyntaxToken<std::any>> Parser::nextToken() {
  if (this->position == this->tokens.size()) {
    return std::unique_ptr<SyntaxToken<std::any>>(
        this->tokens[this->tokens.size() - 1].release());
  } else {
    return std::unique_ptr<SyntaxToken<std::any>>(
        this->tokens[this->position++].release());
  }
}

SyntaxKindUtils::SyntaxKind Parser::getKind() {
  while (this->getCurrent()->getKind() == SyntaxKindUtils::CommentStatement) {
    _formattedSourceCode += this->getCurrent()->getText();
    (this->nextToken());
  }

  return this->getCurrent()->getKind();
}

std::unique_ptr<SyntaxToken<std::any>>
Parser::match(const SyntaxKindUtils::SyntaxKind &kind) {

  _formattedSourceCode += this->getCurrent()->getText();

  if (this->getKind() == kind) {
    return std::move(this->nextToken());
  }
  this->_diagnosticHandler->addDiagnostic(Diagnostic(
      "Unexpected Token <" + SyntaxKindUtils::to_string(this->getKind()) +
          ">, Expected <" + SyntaxKindUtils::to_string(kind) + ">",
      DiagnosticUtils::DiagnosticLevel::Error,
      DiagnosticUtils::DiagnosticType::Syntactic,
      Utils::getSourceLocation(this->getCurrent())));
  if (this->getKind() != SyntaxKindUtils::SyntaxKind::EndOfFileToken) {
    return std::move(this->nextToken());
  } else {

    return std::make_unique<SyntaxToken<std::any>>(
        this->getCurrent()->getAbsoluteFilePath(),
        this->getCurrent()->getLineNumber(),
        SyntaxKindUtils::SyntaxKind::BadToken,
        this->getCurrent()->getColumnNumber(), this->getCurrent()->getText(),
        this->getCurrent()->getValue());
  }
}

bool Parser::matchKind(const SyntaxKindUtils::SyntaxKind &kind) {
  return this->getKind() == kind;
}
std::unique_ptr<CompilationUnitSyntax> Parser::parseCompilationUnit() {
  this->position = 0;

  while (this->getKind() != SyntaxKindUtils::SyntaxKind::EndOfFileToken) {
    // if (this->getKind() == SyntaxKindUtils::SyntaxKind::CommentStatement) {

    //   this->match(SyntaxKindUtils::SyntaxKind::CommentStatement);
    //   continue;
    // }
    this->compilationUnit->addMember(std::move(this->parseMember()));
  }

  std::unique_ptr<SyntaxToken<std::any>> endOfFileToken =
      std::move(this->match(SyntaxKindUtils::SyntaxKind::EndOfFileToken));

  this->compilationUnit->setEndOfFileToken(std::move(endOfFileToken));

  return std::move(this->compilationUnit);
}

std::unique_ptr<MemberSyntax> Parser::parseMember() {
  bool isExposed = false;
  // if (this->getKind() ==
  //     SyntaxKindUtils::SyntaxKind::ExposeKeyword) {
  //   isExposed = true;
  // }

  // if (isExposed) {
  //   SyntaxKindUtils::SyntaxKind kind = this->getKind();

  //   if (!(kind == SyntaxKindUtils::SyntaxKind::FunctionKeyword ||
  //         kind == SyntaxKindUtils::SyntaxKind::VarKeyword ||
  //         kind == SyntaxKindUtils::SyntaxKind::ConstKeyword)) {
  //     this->_diagnosticHandler->addDiagnostic(Diagnostic(
  //         "Unexpected Token <" +
  //             SyntaxKindUtils::to_string(this->getKind()) +
  //             ">, Expected <" +
  //             SyntaxKindUtils::to_string(
  //                 SyntaxKindUtils::SyntaxKind::FunctionKeyword) +
  //             "> or <" +
  //             SyntaxKindUtils::to_string(
  //                 SyntaxKindUtils::SyntaxKind::VarKeyword) +
  //             "> or <" +
  //             SyntaxKindUtils::to_string(
  //                 SyntaxKindUtils::SyntaxKind::ConstKeyword) +
  //             ">",
  //         DiagnosticUtils::DiagnosticLevel::Error,
  //         DiagnosticUtils::DiagnosticType::Syntactic,
  //         Utils::getSourceLocation(this->getCurrent())));
  //   }
  // }

  SyntaxKindUtils::SyntaxKind currentKind = this->getKind();
  if (currentKind == SyntaxKindUtils::SyntaxKind::ExposeKeyword) {
    currentKind = this->peek(1)->getKind();
  }

  if (currentKind == SyntaxKindUtils::SyntaxKind::FunctionKeyword) {
    appendNewLine();
    return std::move(this->parseFunctionDeclaration(isExposed));
  }
  return std::move(this->parseGlobalStatement(isExposed));
}

std::unique_ptr<SyntaxToken<std::any>> Parser::parsePrimitiveType() {
  switch (this->getKind()) {
  case SyntaxKindUtils::SyntaxKind::Int32Keyword: {
    return std::move(this->match(SyntaxKindUtils::SyntaxKind::Int32Keyword));
  }

  case SyntaxKindUtils::SyntaxKind::Int64Keyword: {
    return std::move(this->match(SyntaxKindUtils::SyntaxKind::Int64Keyword));
  }

  case SyntaxKindUtils::SyntaxKind::Deci32Keyword: {
    return std::move(this->match(SyntaxKindUtils::SyntaxKind::Deci32Keyword));
  }

  case SyntaxKindUtils::SyntaxKind::Int8Keyword: {
    return std::move(this->match(SyntaxKindUtils::SyntaxKind::Int8Keyword));
  }

  case SyntaxKindUtils::SyntaxKind::DeciKeyword: {
    return std::move(this->match(SyntaxKindUtils::SyntaxKind::DeciKeyword));
  }

  case SyntaxKindUtils::SyntaxKind::StrKeyword: {
    return std::move(this->match(SyntaxKindUtils::SyntaxKind::StrKeyword));
  }

  case SyntaxKindUtils::SyntaxKind::BoolKeyword: {
    return std::move(this->match(SyntaxKindUtils::SyntaxKind::BoolKeyword));
  }

  case SyntaxKindUtils::SyntaxKind::NthgKeyword: {
    return std::move(this->match(SyntaxKindUtils::SyntaxKind::NthgKeyword));
  }

  default:
    break;
  }

  this->_diagnosticHandler->addDiagnostic(Diagnostic(
      "Unexpected Token <" + SyntaxKindUtils::to_string(this->getKind()) +
          ">, Expected <" +
          SyntaxKindUtils::to_string(
              SyntaxKindUtils::SyntaxKind::Int32Keyword) +
          "> or <" +
          SyntaxKindUtils::to_string(SyntaxKindUtils::SyntaxKind::DeciKeyword) +
          "> or <" +
          SyntaxKindUtils::to_string(
              SyntaxKindUtils::SyntaxKind::Deci32Keyword) +
          "> or <" +
          SyntaxKindUtils::to_string(
              SyntaxKindUtils::SyntaxKind::Int64Keyword) +
          "> or <" +
          SyntaxKindUtils::to_string(SyntaxKindUtils::SyntaxKind::StrKeyword) +
          "> or <" +
          SyntaxKindUtils::to_string(SyntaxKindUtils::SyntaxKind::BoolKeyword) +
          "> or <" +
          SyntaxKindUtils::to_string(SyntaxKindUtils::SyntaxKind::NthgKeyword) +
          "> or <" +
          SyntaxKindUtils::to_string(SyntaxKindUtils::SyntaxKind::Int8Keyword) +
          ">",
      DiagnosticUtils::DiagnosticLevel::Error,
      DiagnosticUtils::DiagnosticType::Syntactic,
      Utils::getSourceLocation(this->getCurrent())));

  return nullptr;
}

std::unique_ptr<FunctionDeclarationSyntax>
Parser::parseFunctionDeclaration(const bool &isExposed, bool isMemberFunction) {
  std::unique_ptr<FunctionDeclarationSyntax> functionDeclaration =
      std::make_unique<FunctionDeclarationSyntax>();

  if (!isMemberFunction &&
      this->getKind() == SyntaxKindUtils::SyntaxKind::ExposeKeyword) {
    functionDeclaration->setExposedKeyword(
        std::move(this->match(SyntaxKindUtils::SyntaxKind::ExposeKeyword)));
    appendWithSpace();
  }
  if (!isMemberFunction) {
    functionDeclaration->setFunctionKeyword(
        std::move(this->match(SyntaxKindUtils::SyntaxKind::FunctionKeyword)));
    appendWithSpace();
  }
  functionDeclaration->setIsMemberFunction(isMemberFunction);

  functionDeclaration->setIdentifierToken(
      std::move(this->match(SyntaxKindUtils::SyntaxKind::IdentifierToken)));

  functionDeclaration->setOpenParenthesisToken(std::move(
      this->match(SyntaxKindUtils::SyntaxKind::OpenParenthesisToken)));

  bool isOptionalParameterType = false;

  while (this->getKind() !=
             SyntaxKindUtils::SyntaxKind::CloseParenthesisToken &&
         this->getKind() != SyntaxKindUtils::SyntaxKind::EndOfFileToken) {

    std::unique_ptr<VariableDeclarationSyntax> parameter =
        std::move(this->parseVariableDeclaration(true));

    functionDeclaration->addParameter(std::move(parameter));
    if (this->getKind() == SyntaxKindUtils::SyntaxKind::CommaToken) {
      functionDeclaration->addSeparator(
          std::move(this->match(SyntaxKindUtils::SyntaxKind::CommaToken)));
      appendWithSpace();
    }
  }

  functionDeclaration->setCloseParenthesisToken(std::move(
      this->match(SyntaxKindUtils::SyntaxKind::CloseParenthesisToken)));
  appendWithSpace();

  this->match(SyntaxKindUtils::SyntaxKind::MinusToken);
  this->match(SyntaxKindUtils::SyntaxKind::GreaterToken);
  appendWithSpace();

  functionDeclaration->setReturnType(this->parseTypeExpression());
  appendWithSpace();

  if (this->getKind() == SyntaxKindUtils::SyntaxKind::DeclKeyword)
    functionDeclaration->setDeclKeyword(
        std::move(this->match(SyntaxKindUtils::SyntaxKind::DeclKeyword)));
  else
    functionDeclaration->setBody(std::move(this->parseBlockStatement()));

  appendNewLine();
  return std::move(functionDeclaration);
}

std::unique_ptr<ArrayTypeExpressionSyntax> Parser::parseArrayTypeExpression() {
  std::unique_ptr<ArrayTypeExpressionSyntax> arrayTypeExpression =
      std::make_unique<ArrayTypeExpressionSyntax>(
          std::make_unique<SyntaxToken<std::any>>(
              this->_diagnosticHandler->getAbsoluteFilePath(), 0,
              SyntaxKindUtils::SyntaxKind::NBU_ARRAY_TYPE, 0, "NBU_ARRAY_TYPE",
              "NBU_ARRAY_TYPE"));

  if (this->getKind() == SyntaxKindUtils::SyntaxKind::IdentifierToken) {
    arrayTypeExpression->setNonTrivialElementType(
        std::move(this->parseObjectTypeExpression()));

  } else {
    arrayTypeExpression->setElementType(std::move(this->parsePrimitiveType()));
  }

  while (this->getKind() == SyntaxKindUtils::SyntaxKind::OpenBracketToken) {
    this->match(SyntaxKindUtils::SyntaxKind::OpenBracketToken);

    std::unique_ptr<SyntaxToken<std::any>> numToken =
        std::move(this->match(SyntaxKindUtils::SyntaxKind::NumberToken));

    std::any value = numToken->getValue();

    arrayTypeExpression->addDimension(
        std::make_unique<LiteralExpressionSyntax<std::any>>(std::move(numToken),
                                                            value));

    this->match(SyntaxKindUtils::SyntaxKind::CloseBracketToken);
  }

  return std::move(arrayTypeExpression);
}

std::unique_ptr<TypeExpressionSyntax> Parser::parseTypeExpression() {
  if (this->peek(1)->getKind() ==
      SyntaxKindUtils::SyntaxKind::OpenBracketToken) {
    return std::move(this->parseArrayTypeExpression());
  }

  if (this->getKind() == SyntaxKindUtils::SyntaxKind::IdentifierToken) {
    return std::move(this->parseObjectTypeExpression());
  }

  return std::make_unique<TypeExpressionSyntax>(this->parsePrimitiveType());
}

std::unique_ptr<ObjectTypeExpressionSyntax>
Parser::parseObjectTypeExpression() {
  std::unique_ptr<ObjectTypeExpressionSyntax> objectTypeExpression =
      std::make_unique<ObjectTypeExpressionSyntax>(
          std::make_unique<SyntaxToken<std::any>>(
              this->_diagnosticHandler->getAbsoluteFilePath(), 0,
              SyntaxKindUtils::SyntaxKind::NBU_OBJECT_TYPE, 0,
              "NBU_OBJECT_TYPE", "NBU_OBJECT_TYPE"));

  std::unique_ptr<SyntaxToken<std::any>> iden =
      std::move(this->match(SyntaxKindUtils::SyntaxKind::IdentifierToken));

  std::any value = iden->getValue();

  std::unique_ptr<LiteralExpressionSyntax<std::any>> literalExp =
      std::make_unique<LiteralExpressionSyntax<std::any>>(std::move(iden),
                                                          value);

  objectTypeExpression->setObjectTypeIdentifier(std::move(literalExp));

  return std::move(objectTypeExpression);
}

std::unique_ptr<FunctionDeclarationSyntax> Parser::handleOptionalType(
    std::unique_ptr<FunctionDeclarationSyntax> &functionDeclaration) {
  this->_diagnosticHandler->addDiagnostic(Diagnostic(
      "Unexpected Token <" + SyntaxKindUtils::to_string(this->getKind()) +
          ">, Expected <" +
          SyntaxKindUtils::to_string(SyntaxKindUtils::SyntaxKind::ColonToken) +
          ">",
      DiagnosticUtils::DiagnosticLevel::Error,
      DiagnosticUtils::DiagnosticType::Syntactic,
      Utils::getSourceLocation(this->getCurrent())));
  return std::move(functionDeclaration);
}

std::unique_ptr<GlobalStatementSyntax>
Parser::parseGlobalStatement(const bool &isExposed) {
  std::unique_ptr<StatementSyntax> statement =
      std::move(this->parseStatement());
  appendNewLine();
  return std::make_unique<GlobalStatementSyntax>(isExposed,
                                                 std::move(statement));
}

std::unique_ptr<BlockStatementSyntax> Parser::parseBlockStatement() {
  std::unique_ptr<BlockStatementSyntax> blockStatement =
      std::make_unique<BlockStatementSyntax>();

  std::unique_ptr<SyntaxToken<std::any>> openBraceToken =
      std::move(this->match(SyntaxKindUtils::SyntaxKind::OpenBraceToken));
  appendNewLine();

  blockStatement->setOpenBraceToken(std::move(openBraceToken));

  std::vector<std::unique_ptr<StatementSyntax>> statements;

  INDENT += TAB_SPACE;

  while (this->getKind() != SyntaxKindUtils::SyntaxKind::CloseBraceToken &&
         this->getKind() != SyntaxKindUtils::SyntaxKind::EndOfFileToken) {
    _formattedSourceCode += INDENT;
    blockStatement->addStatement(std::move(this->parseStatement()));
    appendNewLine();
  }
  INDENT = INDENT.substr(0, INDENT.length() - (sizeof(TAB_SPACE) - 1));
  _formattedSourceCode += INDENT;
  std::unique_ptr<SyntaxToken<std::any>> closeBraceToken =
      std::move(this->match(SyntaxKindUtils::SyntaxKind::CloseBraceToken));

  blockStatement->setCloseBraceToken(std::move(closeBraceToken));

  return std::move(blockStatement);
}

std::unique_ptr<ExpressionStatementSyntax> Parser::parseExpressionStatement() {
  std::unique_ptr<ExpressionSyntax> expression =
      std::move(this->parseExpression());
  return std::make_unique<ExpressionStatementSyntax>(std::move(expression));
}

std::unique_ptr<StatementSyntax> Parser::parseStatement() {

  SyntaxKindUtils::SyntaxKind currentKind = this->getKind();

  if (currentKind == SyntaxKindUtils::SyntaxKind::ExposeKeyword) {
    currentKind = this->peek(1)->getKind();
  }

  switch (currentKind) {
  case SyntaxKindUtils::SyntaxKind::OpenBraceToken:
    return std::move(this->parseBlockStatement());
  case SyntaxKindUtils::SyntaxKind::VarKeyword:
  case SyntaxKindUtils::SyntaxKind::ConstKeyword:
    return std::move(this->parseVariableDeclaration());
  case SyntaxKindUtils::SyntaxKind::IfKeyword:
    return std::move(this->parseIfStatement());
  case SyntaxKindUtils::SyntaxKind::WhileKeyword:
    return std::move(this->parseWhileStatement());
  case SyntaxKindUtils::SyntaxKind::ForKeyword:
    return std::move(this->parseForStatement());
  case SyntaxKindUtils::SyntaxKind::BreakKeyword:
    return std::move(this->parseBreakStatement());
  case SyntaxKindUtils::SyntaxKind::ContinueKeyword:
    return std::move(this->parseContinueStatement());
  case SyntaxKindUtils::SyntaxKind::ReturnKeyword:
    return std::move(this->parseReturnStatement());
  case SyntaxKindUtils::SyntaxKind::BringKeyword:
    return std::move(this->parseBringStatement());
  case SyntaxKindUtils::SyntaxKind::TypeKeyword:
    return std::move(this->parseCustomTypeStatement());
  case SyntaxKindUtils::SyntaxKind::ClassKeyword:
    return std::move(this->parseClassStatement());
  default:
    return std::move(this->parseExpressionStatement());
  }
}

std::unique_ptr<StatementSyntax> Parser::parseClassStatement() {

  std::unique_ptr<ClassStatementSyntax> classSyn =
      std::make_unique<ClassStatementSyntax>();

  if (this->getKind() == SyntaxKindUtils::SyntaxKind::ExposeKeyword) {
    this->match(SyntaxKindUtils::SyntaxKind::ExposeKeyword);
    classSyn->setIsExposed(true);
  }

  classSyn->setClassKeyword(
      std::move(this->match(SyntaxKindUtils::SyntaxKind::ClassKeyword)));
  appendWithSpace();

  classSyn->setClassNameIdentifier(
      std::move(this->match(SyntaxKindUtils::SyntaxKind::IdentifierToken)));
  appendWithSpace();

  if (this->getKind() == SyntaxKindUtils::SyntaxKind::ExtendsKeyword) {
    classSyn->setExtendsKeyword(
        std::move(this->match(SyntaxKindUtils::SyntaxKind::ExtendsKeyword)));
    appendWithSpace();
    classSyn->setParentClassNameIdentifier(
        std::move(this->match(SyntaxKindUtils::SyntaxKind::IdentifierToken)));
    appendWithSpace();
  }

  this->match(SyntaxKindUtils::SyntaxKind::OpenBraceToken);

  INDENT += TAB_SPACE;
  appendNewLine();
  while (this->getKind() != SyntaxKindUtils::SyntaxKind::CloseBraceToken &&
         this->getKind() != SyntaxKindUtils::SyntaxKind::EndOfFileToken) {
    _formattedSourceCode += INDENT;
    SyntaxKindUtils::SyntaxKind kind = this->getKind();

    switch (kind) {
    case SyntaxKindUtils::SyntaxKind::VarKeyword:
    case SyntaxKindUtils::SyntaxKind::ConstKeyword: {
      classSyn->addClassDataMember(std::move(this->parseVariableDeclaration()));

      break;
    }
    case SyntaxKindUtils::SyntaxKind::TypeKeyword: {
      classSyn->addCustomTypeStatement(
          std::move(this->parseCustomTypeStatement()));

      break;
    }

    default:
      classSyn->addClassMemberFunction(std::move(
          this->parseFunctionDeclaration(classSyn->isExposed(), true)));

      break;
    }
    appendNewLine();
  }
  INDENT = INDENT.substr(0, INDENT.length() - (sizeof(TAB_SPACE) - 1));
  _formattedSourceCode += INDENT;
  this->match(SyntaxKindUtils::SyntaxKind::CloseBraceToken);

  return std::move(classSyn);
}

std::unique_ptr<ExpressionSyntax> Parser::parseBracketedExpression() {
  std::unique_ptr<BracketedExpressionSyntax> bracketedExpression =
      std::make_unique<BracketedExpressionSyntax>();

  if (this->peek(1)->getKind() == SyntaxKindUtils::SyntaxKind::FillKeyword

      || this->peek(2)->getKind() == SyntaxKindUtils::SyntaxKind::FillKeyword) {
    bracketedExpression->setExpression(std::move(this->parseFillExpression()));
  } else {
    bracketedExpression->setExpression(
        std::move(this->parseContainerExpression()));
  }
  return std::move(bracketedExpression);
}

std::unique_ptr<CustomTypeStatementSyntax> Parser::parseCustomTypeStatement() {
  std::unique_ptr<CustomTypeStatementSyntax> customTypeStatement =
      std::make_unique<CustomTypeStatementSyntax>();

  if (this->getKind() == SyntaxKindUtils::SyntaxKind::ExposeKeyword) {
    customTypeStatement->setExposeKeyword(
        std::move(this->match(SyntaxKindUtils::SyntaxKind::ExposeKeyword)));
    appendWithSpace();
  }
  this->match(SyntaxKindUtils::SyntaxKind::TypeKeyword);
  appendWithSpace();

  std::unique_ptr<SyntaxToken<std::any>> typeToken =
      std::move(this->match(SyntaxKindUtils::SyntaxKind::IdentifierToken));
  appendWithSpace();

  std::any val = std::any_cast<std::string>(typeToken->getValue()) +
                 FLOWWING::UTILS::CONSTANTS::MEMBER_FUN_PREFIX +
                 IDGenerator::CustomTypeIDGenerator::instance()->nextString();

  std::unique_ptr<LiteralExpressionSyntax<std::any>> typeNameExp =
      std::make_unique<LiteralExpressionSyntax<std::any>>(std::move(typeToken),
                                                          val);

  customTypeStatement->setTypeName(std::move(typeNameExp));

  this->match(SyntaxKindUtils::SyntaxKind::EqualsToken);
  appendWithSpace();
  this->match(SyntaxKindUtils::SyntaxKind::OpenBraceToken);
  appendNewLine();
  INDENT += TAB_SPACE;
  while (this->getKind() != SyntaxKindUtils::SyntaxKind::CloseBraceToken &&
         this->getKind() != SyntaxKindUtils::SyntaxKind::EndOfFileToken) {
    _formattedSourceCode += INDENT;
    std::unique_ptr<SyntaxToken<std::any>> idenfierToken =
        std::move(this->match(SyntaxKindUtils::SyntaxKind::IdentifierToken));

    std::any val = idenfierToken->getValue();

    std::unique_ptr<LiteralExpressionSyntax<std::any>> idenfierExp =
        std::make_unique<LiteralExpressionSyntax<std::any>>(
            std::move(idenfierToken), val);

    this->match(SyntaxKindUtils::SyntaxKind::ColonToken);
    appendWithSpace();

    std::unique_ptr<TypeExpressionSyntax> typeExpression =
        std::move(this->parseTypeExpression());

    customTypeStatement->addKeyTypePair(std::move(idenfierExp),
                                        std::move(typeExpression));

    if (this->getKind() != SyntaxKindUtils::SyntaxKind::CloseBraceToken) {
      this->match(SyntaxKindUtils::SyntaxKind::CommaToken);
    }
    appendNewLine();
  }
  INDENT = INDENT.substr(0, INDENT.length() - (sizeof(TAB_SPACE) - 1));
  _formattedSourceCode += INDENT;
  this->match(SyntaxKindUtils::SyntaxKind::CloseBraceToken);
  return std::move(customTypeStatement);
}

std::unique_ptr<ContainerExpressionSyntax> Parser::parseContainerExpression() {
  std::unique_ptr<ContainerExpressionSyntax> containerExpression =
      std::make_unique<ContainerExpressionSyntax>();

  this->match(SyntaxKindUtils::SyntaxKind::OpenBracketToken);
  while (this->getKind() != SyntaxKindUtils::SyntaxKind::CloseBracketToken &&
         this->getKind() != SyntaxKindUtils::SyntaxKind::EndOfFileToken) {
    std::unique_ptr<ExpressionSyntax> expression = nullptr;

    if (this->getKind() == SyntaxKindUtils::SyntaxKind::OpenBracketToken) {
      expression = std::move(this->parseContainerExpression());
    } else {
      expression = std::move(this->parseExpression());
    }

    containerExpression->setElement(std::move(expression));

    if (this->getKind() != SyntaxKindUtils::SyntaxKind::CloseBracketToken) {
      this->match(SyntaxKindUtils::SyntaxKind::CommaToken);
      appendWithSpace();
    }
  }

  this->match(SyntaxKindUtils::SyntaxKind::CloseBracketToken);
  return std::move(containerExpression);
}

std::unique_ptr<StatementSyntax> Parser::parseBringStatement() {
  std::unique_ptr<SyntaxToken<std::any>> bringKeyword =
      std::move(this->match(SyntaxKindUtils::SyntaxKind::BringKeyword));
  appendWithSpace();
  std::unique_ptr<BringStatementSyntax> bringStatement =
      std::make_unique<BringStatementSyntax>();

  bringStatement->addBringKeyword(std::move(bringKeyword));

  if (this->getKind() == SyntaxKindUtils::SyntaxKind::OpenBraceToken) {
    this->match(SyntaxKindUtils::SyntaxKind::OpenBraceToken);
    while (this->getKind() != SyntaxKindUtils::SyntaxKind::CloseBraceToken) {
      std::unique_ptr<SyntaxToken<std::any>> identifier =
          std::move(this->match(SyntaxKindUtils::SyntaxKind::IdentifierToken));
      bringStatement->addExpression(std::move(identifier));
      if (this->getKind() == SyntaxKindUtils::SyntaxKind::CommaToken) {
        this->match(SyntaxKindUtils::SyntaxKind::CommaToken);
        appendWithSpace();
      }

      if (this->getKind() == SyntaxKindUtils::SyntaxKind::EndOfFileToken) {
        this->_diagnosticHandler->addDiagnostic(Diagnostic(
            "Unexpected Token <" + SyntaxKindUtils::to_string(this->getKind()) +
                ">, Expected <" +
                SyntaxKindUtils::to_string(
                    SyntaxKindUtils::SyntaxKind::CloseBraceToken) +
                ">",
            DiagnosticUtils::DiagnosticLevel::Error,
            DiagnosticUtils::DiagnosticType::Syntactic,
            Utils::getSourceLocation(this->getCurrent())));
        return std::move(bringStatement);
      }
    }
    this->match(SyntaxKindUtils::SyntaxKind::CloseBraceToken);
    appendWithSpace();
  }

  if (bringStatement->getIsChoosyImportPtr()) {
    this->match(SyntaxKindUtils::SyntaxKind::FromKeyword);
    appendWithSpace();
  }

  if (this->getKind() != SyntaxKindUtils::SyntaxKind::StringToken) {
    this->_diagnosticHandler->addDiagnostic(Diagnostic(
        "Unexpected Token <" + SyntaxKindUtils::to_string(this->getKind()) +
            ">, Expected <" +
            SyntaxKindUtils::to_string(
                SyntaxKindUtils::SyntaxKind::StringToken) +
            ">",
        DiagnosticUtils::DiagnosticLevel::Error,
        DiagnosticUtils::DiagnosticType::Syntactic,
        Utils::getSourceLocation(this->getCurrent())));
    return std::move(bringStatement);
  }

  std::unique_ptr<SyntaxToken<std::any>> stringToken =
      std::move(this->match(SyntaxKindUtils::SyntaxKind::StringToken));
  appendNewLine();
  const std::string relativeFilePath =
      std::any_cast<std::string>(stringToken->getValue());

  bringStatement->setRelativeFilePath(relativeFilePath);

  std::string absoluteFilePath =
      std::filesystem::path(this->_diagnosticHandler->getAbsoluteFilePath())
          .parent_path()
          .string() +
      "/" + relativeFilePath;

  std::unique_ptr<FLowWing::DiagnosticHandler> diagnosticHandler =
      std::make_unique<FLowWing::DiagnosticHandler>(absoluteFilePath);

  if (_bringStatementsPathsMap[absoluteFilePath] == 1) {
    this->_diagnosticHandler->addDiagnostic(
        Diagnostic("Found Circular Reference <" + absoluteFilePath + ">",
                   DiagnosticUtils::DiagnosticLevel::Warning,
                   DiagnosticUtils::DiagnosticType::Syntactic,
                   Utils::getSourceLocation(this->getCurrent())));

    return std::move(this->parseStatement());
  }

  _bringStatementsPathsMap[absoluteFilePath] += 1;

  bringStatement->setAbsoluteFilePath(absoluteFilePath);

  this->_diagnosticHandler->addParentDiagnostics(diagnosticHandler.get());
  bringStatement->setDiagnosticHandler(std::move(diagnosticHandler));

  std::unique_ptr<Parser> parser =
      std::make_unique<Parser>(Utils::readLines(absoluteFilePath),
                               bringStatement->getDiagnosticHandlerPtr().get(),
                               _bringStatementsPathsMap);

  std::unique_ptr<CompilationUnitSyntax> compilationUnit =
      std::move(parser->parseCompilationUnit());

  bringStatement->setCompilationUnit(std::move(compilationUnit));

  _bringStatementsPathsMap[absoluteFilePath] -= 1;
  return std::move(bringStatement);
}

std::unique_ptr<ReturnStatementSyntax> Parser::parseReturnStatement() {
  std::unique_ptr<SyntaxToken<std::any>> returnKeyword =
      std::move(this->match(SyntaxKindUtils::SyntaxKind::ReturnKeyword));
  appendWithSpace();
  if (this->getKind() == SyntaxKindUtils::SyntaxKind::OpenParenthesisToken) {
    this->match(SyntaxKindUtils::SyntaxKind::OpenParenthesisToken);

    std::unique_ptr<ExpressionSyntax> expression =
        std::move(this->parseExpression());
    this->match(SyntaxKindUtils::SyntaxKind::CloseParenthesisToken);
    return std::make_unique<ReturnStatementSyntax>(std::move(returnKeyword),
                                                   std::move(expression));
  } else if (this->getKind() != SyntaxKindUtils::SyntaxKind::ColonToken) {
    std::unique_ptr<ExpressionSyntax> expression =
        std::move(this->parseExpression());
    return std::make_unique<ReturnStatementSyntax>(std::move(returnKeyword),
                                                   std::move(expression));
  } else {
    this->match(SyntaxKindUtils::SyntaxKind::ColonToken);
  }
  return std::make_unique<ReturnStatementSyntax>(std::move(returnKeyword),
                                                 nullptr);
}

std::unique_ptr<BreakStatementSyntax> Parser::parseBreakStatement() {
  std::unique_ptr<SyntaxToken<std::any>> breakKeyword =
      std::move(this->match(SyntaxKindUtils::SyntaxKind::BreakKeyword));
  return std::make_unique<BreakStatementSyntax>(std::move(breakKeyword));
}

std::unique_ptr<ContinueStatementSyntax> Parser::parseContinueStatement() {
  std::unique_ptr<SyntaxToken<std::any>> continueKeyword =
      std::move(this->match(SyntaxKindUtils::SyntaxKind::ContinueKeyword));
  return std::make_unique<ContinueStatementSyntax>(std::move(continueKeyword));
}

std::unique_ptr<ForStatementSyntax> Parser::parseForStatement() {
  std::unique_ptr<SyntaxToken<std::any>> keyword =
      std::move(this->match(SyntaxKindUtils::SyntaxKind::ForKeyword));
  appendWithSpace();
  bool hadOpenParenthesis = false;
  if (this->getKind() == SyntaxKindUtils::SyntaxKind::OpenParenthesisToken) {
    this->match(SyntaxKindUtils::SyntaxKind::OpenParenthesisToken);
    hadOpenParenthesis = true;
  }

  std::unique_ptr<StatementSyntax> statementSyntax = nullptr;

  if (this->getKind() == SyntaxKindUtils::SyntaxKind::VarKeyword) {
    statementSyntax = std::move(this->parseVariableDeclaration());
  } else {
    statementSyntax = std::move(this->parseExpressionStatement());
  }
  appendWithSpace();

  std::unique_ptr<SyntaxToken<std::any>> toKeyword =
      std::move(this->match(SyntaxKindUtils::SyntaxKind::ToKeyword));
  appendWithSpace();

  std::unique_ptr<ExpressionSyntax> upperBound =
      std::move(this->parseExpression());
  std::unique_ptr<ExpressionSyntax> step = nullptr;
  if (this->getKind() == SyntaxKindUtils::SyntaxKind::ColonToken) {
    appendWithSpace();
    this->match(SyntaxKindUtils::SyntaxKind::ColonToken);
    appendWithSpace();
    step = std::move(this->parseExpression());
  }

  if (hadOpenParenthesis) {
    this->match(SyntaxKindUtils::SyntaxKind::CloseParenthesisToken);
  }
  appendWithSpace();

  std::unique_ptr<BlockStatementSyntax> statement =
      std::move(this->parseBlockStatement());

  return std::make_unique<ForStatementSyntax>(
      std::move(statementSyntax), std::move(upperBound), std::move(statement),
      std::move(step));
}

std::unique_ptr<ElseClauseSyntax> Parser::parseElseStatement() {
  std::unique_ptr<SyntaxToken<std::any>> elseKeyword =
      std::move(this->match(SyntaxKindUtils::SyntaxKind::ElseKeyword));
  appendWithSpace();
  std::unique_ptr<BlockStatementSyntax> elseStatement =
      std::move(this->parseBlockStatement());
  return std::make_unique<ElseClauseSyntax>(std::move(elseKeyword),
                                            std::move(elseStatement));
}

std::unique_ptr<IfStatementSyntax> Parser::parseIfStatement() {
  std::unique_ptr<IfStatementSyntax> ifStatement =
      std::make_unique<IfStatementSyntax>();
  std::unique_ptr<SyntaxToken<std::any>> keyword =
      std::move(this->match(SyntaxKindUtils::SyntaxKind::IfKeyword));
  appendWithSpace();

  std::unique_ptr<ExpressionSyntax> condition =
      std::move(this->parseExpression());
  appendWithSpace();

  std::unique_ptr<BlockStatementSyntax> statement =
      std::move(this->parseBlockStatement());
  appendNewLine();
  ifStatement->addIfKeyword(std::move(keyword));
  ifStatement->addCondition(std::move(condition));
  ifStatement->addStatement(std::move(statement));

  while (this->getKind() == SyntaxKindUtils::SyntaxKind::OrKeyword) {
    _formattedSourceCode += INDENT;
    std::unique_ptr<SyntaxToken<std::any>> orKeyword =
        std::move(this->match(SyntaxKindUtils::SyntaxKind::OrKeyword));
    appendWithSpace();

    std::unique_ptr<SyntaxToken<std::any>> ifKeyword =
        std::move(this->match(SyntaxKindUtils::SyntaxKind::IfKeyword));
    appendWithSpace();

    std::unique_ptr<ExpressionSyntax> condition =
        std::move(this->parseExpression());
    appendWithSpace();

    std::unique_ptr<BlockStatementSyntax> statement =
        std::move(this->parseBlockStatement());
    appendNewLine();

    ifStatement->addOrIfStatement(std::make_unique<OrIfStatementSyntax>(
        std::move(orKeyword), std::move(ifKeyword), std::move(condition),
        std::move(statement)));
  }
  std::unique_ptr<ElseClauseSyntax> elseClause = nullptr;

  if (this->getKind() == SyntaxKindUtils::SyntaxKind::ElseKeyword) {
    _formattedSourceCode += INDENT;
    elseClause = std::move(this->parseElseStatement());
  }

  ifStatement->addElseClause(std::move(elseClause));

  return std::move(ifStatement);
}

std::unique_ptr<WhileStatementSyntax> Parser::parseWhileStatement() {
  std::unique_ptr<SyntaxToken<std::any>> keyword =
      std::move(this->match(SyntaxKindUtils::SyntaxKind::WhileKeyword));
  appendWithSpace();

  std::unique_ptr<ExpressionSyntax> condition =
      std::move(this->parseExpression());
  appendWithSpace();

  std::unique_ptr<BlockStatementSyntax> statement =
      std::move(this->parseBlockStatement());
  return std::make_unique<WhileStatementSyntax>(
      std::move(keyword), std::move(condition), std::move(statement));
}

std::unique_ptr<VariableDeclarationSyntax>
Parser::parseVariableDeclaration(bool isFuncDec) {
  std::unique_ptr<VariableDeclarationSyntax> varDec =
      std::make_unique<VariableDeclarationSyntax>();

  if (this->getKind() == SyntaxKindUtils::SyntaxKind::ExposeKeyword) {
    varDec->setExposeKeyword(
        std::move(this->match(SyntaxKindUtils::SyntaxKind::ExposeKeyword)));
    appendWithSpace();
  }

  if (isFuncDec &&
      SyntaxKindUtils::SyntaxKind::INOUTKeyword == this->getKind()) {
    varDec->setInoutKeyword(
        std::move(this->match(SyntaxKindUtils::SyntaxKind::INOUTKeyword)));
    appendWithSpace();
  }

  if (isFuncDec &&
      SyntaxKindUtils::SyntaxKind::ConstKeyword == this->getKind()) {
    varDec->setKeyword(
        std::move(this->match(SyntaxKindUtils::SyntaxKind::ConstKeyword)));
    appendWithSpace();
  }
  if (!isFuncDec) {
    varDec->setKeyword(std::move(
        this->match(SyntaxKindUtils::SyntaxKind::VarKeyword == this->getKind()
                        ? SyntaxKindUtils::SyntaxKind::VarKeyword
                        : SyntaxKindUtils::SyntaxKind::ConstKeyword)));
    appendWithSpace();
  }

  std::unique_ptr<SyntaxToken<std::any>> identifier =
      std::move(this->match(SyntaxKindUtils::SyntaxKind::IdentifierToken));

  varDec->setIdentifier(std::move(identifier));

  std::unique_ptr<TypeExpressionSyntax> typeExpr =
      std::make_unique<TypeExpressionSyntax>(
          std::make_unique<SyntaxToken<std::any>>(
              this->_diagnosticHandler->getAbsoluteFilePath(), 0,
              SyntaxKindUtils::SyntaxKind::NBU_UNKNOWN_TYPE, 0,
              "NBU_UNKNOWN_TYPE", "NBU_UNKNOWN_TYPE"));

  if (this->getKind() == SyntaxKindUtils::SyntaxKind::ColonToken) {
    this->match(SyntaxKindUtils::SyntaxKind::ColonToken);
    appendWithSpace();
    typeExpr = std::move(this->parseTypeExpression());
  }
  varDec->setTypeExpr(std::move(typeExpr));

  if (this->getKind() == SyntaxKindUtils::SyntaxKind::EqualsToken) {
    appendWithSpace();
    std::unique_ptr<SyntaxToken<std::any>> equalsToken =
        std::move(this->match(SyntaxKindUtils::SyntaxKind::EqualsToken));
    appendWithSpace();

    if (this->getKind() == SyntaxKindUtils::SyntaxKind::NewKeyword) {
      varDec->setNewKeyword(
          std::move(this->match(SyntaxKindUtils::SyntaxKind::NewKeyword)));
      appendWithSpace();
    }

    std::unique_ptr<ExpressionSyntax> initializer =
        std::move(this->parseExpression());
    varDec->setInitializer(std::move(initializer));
  }

  return std::move(varDec);
}

std::unique_ptr<ExpressionSyntax>
Parser::parseExpression(int parentPrecedence) {

  std::unique_ptr<ExpressionSyntax> left = nullptr;
  int unaryOperatorPrecedence =
      this->getCurrent()->getUnaryOperatorPrecedence();

  if (unaryOperatorPrecedence != 0 &&
      unaryOperatorPrecedence >= parentPrecedence) {
    std::unique_ptr<SyntaxToken<std::any>> operatorToken =
        std::move(this->match(this->getKind()));
    std::unique_ptr<ExpressionSyntax> operand =
        std::move(this->parseExpression(unaryOperatorPrecedence));
    left = std::make_unique<UnaryExpressionSyntax>(std::move(operatorToken),
                                                   std::move(operand));

  } else {
    left = std::move(this->parsePrimaryExpression());
  }

  while (true) {
    int precedence = this->getCurrent()->getBinaryOperatorPrecedence();
    if (precedence == 0 || precedence <= parentPrecedence) {
      break;
    }
    appendWithSpace();
    std::unique_ptr<SyntaxToken<std::any>> operatorToken =
        std::move(this->match(this->getKind()));
    appendWithSpace();

    std::unique_ptr<ExpressionSyntax> right =
        std::move(this->parseExpression(precedence));

    left = std::make_unique<BinaryExpressionSyntax>(
        std::move(left), std::move(operatorToken), std::move(right));
  }

  return std::move(left);
}

std::unique_ptr<FillExpressionSyntax> Parser::parseFillExpression() {
  std::unique_ptr<FillExpressionSyntax> fillExpression =
      std::make_unique<FillExpressionSyntax>();

  this->match(SyntaxKindUtils::SyntaxKind::OpenBracketToken);

  std::unique_ptr<ExpressionSyntax> sizeToFillExpression = nullptr;

  auto numToken =
      std::move(this->match(SyntaxKindUtils::SyntaxKind::NumberToken));
  appendWithSpace();
  std::any sizeVAL = numToken->getValue();

  sizeToFillExpression = std::make_unique<LiteralExpressionSyntax<std::any>>(
      std::move(numToken), sizeVAL);

  this->match(SyntaxKindUtils::SyntaxKind::FillKeyword);
  appendWithSpace();
  std::unique_ptr<ExpressionSyntax> elementExpression =
      std::move(this->parseExpression());

  this->match(SyntaxKindUtils::SyntaxKind::CloseBracketToken);

  fillExpression->setSizeToFillExpression(std::move(sizeToFillExpression));
  fillExpression->setElementExpression(std::move(elementExpression));

  return std::move(fillExpression);
}

std::unique_ptr<ExpressionSyntax> Parser::parsePrimaryExpression() {
  switch (this->getKind()) {
  case SyntaxKindUtils::SyntaxKind::OpenParenthesisToken: {
    std::unique_ptr<SyntaxToken<std::any>> left = std::move(
        this->match(SyntaxKindUtils::SyntaxKind::OpenParenthesisToken));

    std::unique_ptr<ExpressionSyntax> expression =
        std::move(this->parseExpression());

    std::unique_ptr<SyntaxToken<std::any>> right = std::move(
        this->match(SyntaxKindUtils::SyntaxKind::CloseParenthesisToken));

    return std::make_unique<ParenthesizedExpressionSyntax>(
        std::move(left), std::move(expression), std::move(right));
  }
  case SyntaxKindUtils::SyntaxKind::NumberToken: {
    std::unique_ptr<SyntaxToken<std::any>> numberToken =
        std::move(this->match(SyntaxKindUtils::SyntaxKind::NumberToken));

    std::any value = numberToken->getValue();

    return std::make_unique<LiteralExpressionSyntax<std::any>>(
        std::move(numberToken), value);
  }

  case SyntaxKindUtils::SyntaxKind::StringToken: {
    std::unique_ptr<SyntaxToken<std::any>> stringToken =
        std::move(this->match(SyntaxKindUtils::SyntaxKind::StringToken));

    std::any value = stringToken->getValue();
    return std::make_unique<LiteralExpressionSyntax<std::any>>(
        std::move(stringToken), value);
  }
  case SyntaxKindUtils::SyntaxKind::TrueKeyword: {
    std::unique_ptr<SyntaxToken<std::any>> trueKeywordToken =
        std::move(this->match(SyntaxKindUtils::SyntaxKind::TrueKeyword));

    return std::make_unique<LiteralExpressionSyntax<std::any>>(
        std::move(trueKeywordToken), true);
  }
  case SyntaxKindUtils::SyntaxKind::NewKeyword: {
    return std::move(this->parseCallExpression());
  }
  case SyntaxKindUtils::SyntaxKind::FalseKeyword: {
    std::unique_ptr<SyntaxToken<std::any>> falseKeywordToken =
        std::move(this->match(SyntaxKindUtils::SyntaxKind::FalseKeyword));

    return std::make_unique<LiteralExpressionSyntax<std::any>>(
        std::move(falseKeywordToken), false);
  }
  case SyntaxKindUtils::SyntaxKind::CommaToken: {
    std::unique_ptr<SyntaxToken<std::any>> commaToken =
        std::move(this->match(SyntaxKindUtils::SyntaxKind::CommaToken));

    return std::make_unique<LiteralExpressionSyntax<std::any>>(
        std::move(commaToken), ",");
  }
  case SyntaxKindUtils::SyntaxKind::IdentifierToken: {
    return std::move(this->parseNameorCallExpression());
  }
  case SyntaxKindUtils::SyntaxKind::OpenBracketToken: {
    return std::move(this->parseBracketedExpression());
  }
  case SyntaxKindUtils::SyntaxKind::OpenBraceToken: {
    return std::move(this->parseObjectExpression());
  }
  default:
    break;
  }

  std::unique_ptr<SyntaxToken<std::any>> expressionToken =
      std::move(this->match(SyntaxKindUtils::SyntaxKind::ExpressionStatement));

  return std::make_unique<LiteralExpressionSyntax<std::any>>(
      std::move(expressionToken), nullptr);
}

std::unique_ptr<StatementSyntax> Parser::parseCommentStatement() {

  (this->match(SyntaxKindUtils::SyntaxKind::CommentStatement));
  std::unique_ptr<StatementSyntax> stat = std::move(this->parseStatement());
  appendNewLine();
  return std::move(stat);
}

std::unique_ptr<ObjectExpressionSyntax> Parser::parseObjectExpression() {
  std::unique_ptr<ObjectExpressionSyntax> objES =
      std::make_unique<ObjectExpressionSyntax>();

  this->match(SyntaxKindUtils::SyntaxKind::OpenBraceToken);
  appendNewLine();
  INDENT += TAB_SPACE;
  while (this->getKind() != SyntaxKindUtils::SyntaxKind::CloseBraceToken &&
         this->getKind() != SyntaxKindUtils::SyntaxKind::EndOfFileToken) {
    _formattedSourceCode += INDENT;
    std::unique_ptr<SyntaxToken<std::any>> idenfierToken =
        std::move(this->match(SyntaxKindUtils::SyntaxKind::IdentifierToken));

    std::any val = idenfierToken->getValue();

    std::unique_ptr<LiteralExpressionSyntax<std::any>> idenfierExp =
        std::make_unique<LiteralExpressionSyntax<std::any>>(
            std::move(idenfierToken), val);

    this->match(SyntaxKindUtils::SyntaxKind::ColonToken);
    appendWithSpace();

    std::unique_ptr<ExpressionSyntax> expression =
        std::move(this->parseExpression());

    objES->addAttribute(std::move(idenfierExp), std::move(expression));

    if (this->getKind() != SyntaxKindUtils::SyntaxKind::CloseBraceToken) {
      this->match(SyntaxKindUtils::SyntaxKind::CommaToken);
      appendNewLine();
    }
  }
  appendNewLine();
  INDENT = INDENT.substr(0, INDENT.length() - (sizeof(TAB_SPACE) - 1));
  _formattedSourceCode += INDENT;
  this->match(SyntaxKindUtils::SyntaxKind::CloseBraceToken);

  return std::move(objES);
}

std::unique_ptr<ExpressionSyntax> Parser::parseVariableExpression(bool isSelf) {
  std::unique_ptr<SyntaxToken<std::any>> identifierToken =
      std::move(this->match(SyntaxKindUtils::SyntaxKind::IdentifierToken));

  if (std::any_cast<std::string>(identifierToken->getValue()) == "self") {
    identifierToken.reset();
    this->match(SyntaxKindUtils::SyntaxKind::DotToken);
    return std::move(this->parseNameorCallExpression(true));
  }

  std::any value = identifierToken->getValue();

  std::unique_ptr<TypeExpressionSyntax> typeExpression =
      std::make_unique<TypeExpressionSyntax>(
          std::make_unique<SyntaxToken<std::any>>(
              this->_diagnosticHandler->getAbsoluteFilePath(), 0,
              SyntaxKindUtils::SyntaxKind::NBU_UNKNOWN_TYPE, 0,
              "NBU_UNKNOWN_TYPE", "NBU_UNKNOWN_TYPE"));

  std::unique_ptr<VariableExpressionSyntax> variExp =
      std::make_unique<VariableExpressionSyntax>(
          std::make_unique<LiteralExpressionSyntax<std::any>>(
              std::move(identifierToken), value),
          false, std::move(typeExpression));

  variExp->setIsSelf(isSelf);

  while (this->getKind() == SyntaxKindUtils::SyntaxKind::DotToken) {
    this->match(SyntaxKindUtils::SyntaxKind::DotToken);

    if (this->getKind() == SyntaxKindUtils::SyntaxKind::IdentifierToken &&
        this->peek(1)->getKind() ==
            SyntaxKindUtils::SyntaxKind::OpenBracketToken) {

      std::unique_ptr<SyntaxToken<std::any>> localIdentifierToken =
          std::move(this->match(SyntaxKindUtils::SyntaxKind::IdentifierToken));

      std::any value = localIdentifierToken->getValue();
      std::unique_ptr<IndexExpressionSyntax> localIndexExpression =
          std::make_unique<IndexExpressionSyntax>(
              std::make_unique<LiteralExpressionSyntax<std::any>>(
                  std::move(localIdentifierToken), value));

      while (this->getKind() == SyntaxKindUtils::SyntaxKind::OpenBracketToken) {

        this->match(SyntaxKindUtils::SyntaxKind::OpenBracketToken);

        localIndexExpression->addIndexExpression(
            std::move(this->parseExpression()));

        this->match(SyntaxKindUtils::SyntaxKind::CloseBracketToken);
      }

      variExp->addDotExpression(std::move(localIndexExpression));
    } else {

      if (this->getKind() == SyntaxKindUtils::SyntaxKind::IdentifierToken &&
          this->peek(1)->getKind() ==
              SyntaxKindUtils::SyntaxKind::OpenParenthesisToken) {
        variExp->addDotExpression(std::move(this->parseNameorCallExpression()));
      } else {

        std::unique_ptr<SyntaxToken<std::any>> localIdentifierToken = std::move(
            this->match(SyntaxKindUtils::SyntaxKind::IdentifierToken));
        std::any value = localIdentifierToken->getValue();

        variExp->addDotExpression(
            std::make_unique<LiteralExpressionSyntax<std::any>>(
                std::move(localIdentifierToken), value));
      }
    }
  }

  return std::move(variExp);
}
std::unique_ptr<ExpressionSyntax> Parser::parseIndexExpression(bool isSelf) {
  std::unique_ptr<SyntaxToken<std::any>> identifierToken =
      std::move(this->match(SyntaxKindUtils::SyntaxKind::IdentifierToken));

  std::any value = identifierToken->getValue();
  std::unique_ptr<IndexExpressionSyntax> indexExpression =
      std::make_unique<IndexExpressionSyntax>(
          std::make_unique<LiteralExpressionSyntax<std::any>>(
              std::move(identifierToken), value));

  while (this->getKind() == SyntaxKindUtils::SyntaxKind::OpenBracketToken) {
    this->match(SyntaxKindUtils::SyntaxKind::OpenBracketToken);

    indexExpression->addIndexExpression(std::move(this->parseExpression()));

    this->match(SyntaxKindUtils::SyntaxKind::CloseBracketToken);
  }

  if (this->getKind() == SyntaxKindUtils::SyntaxKind::DotToken) {
    std::unique_ptr<TypeExpressionSyntax> typeExpression =
        std::make_unique<TypeExpressionSyntax>(
            std::make_unique<SyntaxToken<std::any>>(
                this->_diagnosticHandler->getAbsoluteFilePath(), 0,
                SyntaxKindUtils::SyntaxKind::NBU_UNKNOWN_TYPE, 0,
                "NBU_UNKNOWN_TYPE", "NBU_UNKNOWN_TYPE"));

    std::unique_ptr<VariableExpressionSyntax> variExp =
        std::make_unique<VariableExpressionSyntax>(
            std::make_unique<LiteralExpressionSyntax<std::any>>(nullptr, value),
            false, std::move(typeExpression));

    while (this->getKind() == SyntaxKindUtils::SyntaxKind::DotToken) {
      this->match(SyntaxKindUtils::SyntaxKind::DotToken);

      if (this->getKind() == SyntaxKindUtils::SyntaxKind::IdentifierToken &&
          this->peek(1)->getKind() ==
              SyntaxKindUtils::SyntaxKind::OpenBracketToken) {

        std::unique_ptr<SyntaxToken<std::any>> localIdentifierToken = std::move(
            this->match(SyntaxKindUtils::SyntaxKind::IdentifierToken));

        std::any value = localIdentifierToken->getValue();
        std::unique_ptr<IndexExpressionSyntax> localIndexExpression =
            std::make_unique<IndexExpressionSyntax>(
                std::make_unique<LiteralExpressionSyntax<std::any>>(
                    std::move(localIdentifierToken), value));

        while (this->getKind() ==
               SyntaxKindUtils::SyntaxKind::OpenBracketToken) {

          this->match(SyntaxKindUtils::SyntaxKind::OpenBracketToken);

          localIndexExpression->addIndexExpression(
              std::move(this->parseExpression()));

          this->match(SyntaxKindUtils::SyntaxKind::CloseBracketToken);
        }

        variExp->addDotExpression(std::move(localIndexExpression));
      } else {
        std::unique_ptr<SyntaxToken<std::any>> localIdentifierToken = std::move(
            this->match(SyntaxKindUtils::SyntaxKind::IdentifierToken));
        std::any value = localIdentifierToken->getValue();

        variExp->addDotExpression(
            std::make_unique<LiteralExpressionSyntax<std::any>>(
                std::move(localIdentifierToken), value));
      }
    }
    indexExpression->addVariableExpression(std::move(variExp));
  }

  if (this->getKind() == SyntaxKindUtils::SyntaxKind::EqualsToken) {
    std::unique_ptr<SyntaxToken<std::any>> operatorToken =
        std::move(this->match(SyntaxKindUtils::SyntaxKind::EqualsToken));
    appendWithSpace();

    std::unique_ptr<ExpressionSyntax> right =
        std::move(this->parseExpression());

    return std::make_unique<AssignmentExpressionSyntax>(
        std::move(indexExpression), std::move(operatorToken), std::move(right));
  }

  return std::move(indexExpression);
}

std::unique_ptr<ExpressionSyntax>
Parser::parseNameorCallExpression(bool isSelf) {

  if (this->peek(1)->getKind() == SyntaxKindUtils::SyntaxKind::EqualsToken ||
      this->peek(1)->getKind() ==
          SyntaxKindUtils::SyntaxKind::AssignmentToken ||
      this->peek(1)->getKind() == SyntaxKindUtils::SyntaxKind::DotToken) {
    std::unique_ptr<VariableExpressionSyntax> variableExpression(
        static_cast<VariableExpressionSyntax *>(
            this->parseVariableExpression(isSelf).release()));

    bool needDefaultInitialize = false;

    std::unique_ptr<SyntaxToken<std::any>> operatorToken = nullptr;
    if (this->getKind() == SyntaxKindUtils::SyntaxKind::EqualsToken) {
      appendWithSpace();

      operatorToken =
          std::move(this->match(SyntaxKindUtils::SyntaxKind::EqualsToken));
    } else if (this->getKind() ==
               SyntaxKindUtils::SyntaxKind::AssignmentToken) {
      appendWithSpace();

      operatorToken =
          std::move(this->match(SyntaxKindUtils::SyntaxKind::AssignmentToken));
      needDefaultInitialize = true;
    } else {
      return std::move(variableExpression);
    }

    appendWithSpace();

    if (this->getKind() == SyntaxKindUtils::SyntaxKind::NewKeyword) {
      variableExpression->setNewKeyword(
          std::move(this->match(SyntaxKindUtils::SyntaxKind::NewKeyword)));
      appendWithSpace();
    }

    std::unique_ptr<ExpressionSyntax> right =
        std::move(this->parseExpression());
    appendWithSpace();

    return std::make_unique<AssignmentExpressionSyntax>(
        std::move(variableExpression), std::move(operatorToken),
        std::move(right), needDefaultInitialize);

  } else if (this->peek(1)->getKind() ==
             SyntaxKindUtils::SyntaxKind::OpenBracketToken) {
    return std::move(this->parseIndexExpression(isSelf));
  } else if (this->peek(1)->getKind() ==
             SyntaxKindUtils::SyntaxKind::OpenParenthesisToken) {
    return std::move(parseCallExpression());
  } else {
    return std::move(parseVariableExpression(isSelf));
  }
}

std::unique_ptr<ExpressionSyntax> Parser::parseCallExpression() {

  std::unique_ptr<SyntaxToken<std::any>> newKeywordToken = nullptr;

  if (this->getKind() == SyntaxKindUtils::SyntaxKind::NewKeyword) {
    newKeywordToken =
        std::move(this->match(SyntaxKindUtils::SyntaxKind::NewKeyword));
  }

  std::unique_ptr<SyntaxToken<std::any>> identifierToken =
      std::move(this->match(SyntaxKindUtils::SyntaxKind::IdentifierToken));

  std::any val = identifierToken->getValue();

  std::unique_ptr<CallExpressionSyntax> callExpression =
      std::make_unique<CallExpressionSyntax>(
          std::make_unique<LiteralExpressionSyntax<std::any>>(
              std::move(identifierToken), val));

  if (newKeywordToken) {
    callExpression->setNewKeyword(std::move(newKeywordToken));
  }

  std::unique_ptr<SyntaxToken<std::any>> openParenthesisToken =
      std::move(this->match(SyntaxKindUtils::SyntaxKind::OpenParenthesisToken));

  callExpression->setOpenParenthesisToken(std::move(openParenthesisToken));

  while (this->getKind() !=
             SyntaxKindUtils::SyntaxKind::CloseParenthesisToken &&
         this->getKind() != SyntaxKindUtils::SyntaxKind::EndOfFileToken) {
    std::unique_ptr<ExpressionSyntax> expression =
        std::move(this->parseExpression());
    callExpression->addArgument(std::move(expression));
    if (this->getKind() != SyntaxKindUtils::SyntaxKind::CloseParenthesisToken) {
      callExpression->addSeparator(
          std::move(this->match(SyntaxKindUtils::SyntaxKind::CommaToken)));
      appendWithSpace();
    }
  }
  std::unique_ptr<SyntaxToken<std::any>> closeParenthesisToken = std::move(
      this->match(SyntaxKindUtils::SyntaxKind::CloseParenthesisToken));

  callExpression->setCloseParenthesisToken(std::move(closeParenthesisToken));

  return std::move(callExpression);
}
