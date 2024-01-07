#include "Parser.h"
Parser::Parser(std::vector<std::string> souceCode,
               DiagnosticHandler *diagnosticHandler) {
  this->tokens = std::vector<std::unique_ptr<SyntaxToken<std::any>>>();
  this->_diagnosticHandler = diagnosticHandler;

  lexer = std::make_unique<Lexer>(souceCode, diagnosticHandler);

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
        _kind != SyntaxKindUtils::SyntaxKind::EndOfLineToken &&
        _kind != SyntaxKindUtils::SyntaxKind::CommentStatement) {
      this->tokens.push_back(std::move(token));
    } else {
      token.reset();
    }

  } while (_kind != SyntaxKindUtils::SyntaxKind::EndOfFileToken);
  compilationUnit = std::make_unique<CompilationUnitSyntax>();
}

Parser::~Parser() {
  for (auto &token : this->tokens) {
    token.reset();
  }
  lexer.reset();

  this->tokens.clear();
}

SyntaxToken<std::any> *Parser::peek(int offset) {
  int index = this->position + offset;
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

std::unique_ptr<SyntaxToken<std::any>> Parser::match(
    SyntaxKindUtils::SyntaxKind kind) {
  if (this->getCurrent()->getKind() == kind) {
    return std::move(this->nextToken());
  }

  this->_diagnosticHandler->addDiagnostic(
      Diagnostic("Unexpected Token <" +
                     SyntaxKindUtils::to_string(this->getCurrent()->getKind()) +
                     ">, Expected <" + SyntaxKindUtils::to_string(kind) + ">",
                 DiagnosticUtils::DiagnosticLevel::Error,
                 DiagnosticUtils::DiagnosticType::Syntactic,
                 Utils::getSourceLocation(this->getCurrent())));

  if (this->getCurrent()->getKind() !=
      SyntaxKindUtils::SyntaxKind::EndOfFileToken) {
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

bool Parser::matchKind(SyntaxKindUtils::SyntaxKind kind) {
  return this->getCurrent()->getKind() == kind;
}
std::unique_ptr<CompilationUnitSyntax> Parser::parseCompilationUnit() {
  this->position = 0;

  while (this->getCurrent()->getKind() !=
         SyntaxKindUtils::SyntaxKind::EndOfFileToken) {
    this->compilationUnit->addMember(std::move(this->parseMember()));
  }

  std::unique_ptr<SyntaxToken<std::any>> endOfFileToken =
      std::move(this->match(SyntaxKindUtils::SyntaxKind::EndOfFileToken));

  this->compilationUnit->setEndOfFileToken(std::move(endOfFileToken));

  return std::move(this->compilationUnit);
}

std::unique_ptr<MemberSyntax> Parser::parseMember() {
  bool isExposed = false;

  if (this->getCurrent()->getKind() ==
      SyntaxKindUtils::SyntaxKind::ExposeKeyword) {
    this->match(SyntaxKindUtils::SyntaxKind::ExposeKeyword);
    isExposed = true;
  }

  if (isExposed) {
    SyntaxKindUtils::SyntaxKind kind = this->getCurrent()->getKind();

    if (!(kind == SyntaxKindUtils::SyntaxKind::FunctionKeyword ||
          kind == SyntaxKindUtils::SyntaxKind::VarKeyword ||
          kind == SyntaxKindUtils::SyntaxKind::ConstKeyword)) {
      this->_diagnosticHandler->addDiagnostic(Diagnostic(
          "Unexpected Token <" +
              SyntaxKindUtils::to_string(this->getCurrent()->getKind()) +
              ">, Expected <" +
              SyntaxKindUtils::to_string(
                  SyntaxKindUtils::SyntaxKind::FunctionKeyword) +
              "> or <" +
              SyntaxKindUtils::to_string(
                  SyntaxKindUtils::SyntaxKind::VarKeyword) +
              "> or <" +
              SyntaxKindUtils::to_string(
                  SyntaxKindUtils::SyntaxKind::ConstKeyword) +
              ">",
          DiagnosticUtils::DiagnosticLevel::Error,
          DiagnosticUtils::DiagnosticType::Syntactic,
          Utils::getSourceLocation(this->getCurrent())));
    }
  }

  if (this->getCurrent()->getKind() ==
      SyntaxKindUtils::SyntaxKind::FunctionKeyword) {
    return std::move(this->parseFunctionDeclaration(isExposed));
  }
  return std::move(this->parseGlobalStatement(isExposed));
}

std::unique_ptr<SyntaxToken<std::any>> Parser::parsePrimitiveType() {
  switch (this->getCurrent()->getKind()) {
    case SyntaxKindUtils::SyntaxKind::Int32Keyword: {
      return std::move(this->match(SyntaxKindUtils::SyntaxKind::Int32Keyword));
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
      "Unexpected Token <" +
          SyntaxKindUtils::to_string(this->getCurrent()->getKind()) +
          ">, Expected <" +
          SyntaxKindUtils::to_string(
              SyntaxKindUtils::SyntaxKind::Int32Keyword) +
          "> or <" +
          SyntaxKindUtils::to_string(SyntaxKindUtils::SyntaxKind::DeciKeyword) +
          "> or <" +
          SyntaxKindUtils::to_string(SyntaxKindUtils::SyntaxKind::StrKeyword) +
          "> or <" +
          SyntaxKindUtils::to_string(SyntaxKindUtils::SyntaxKind::BoolKeyword) +
          "> or <" +
          SyntaxKindUtils::to_string(SyntaxKindUtils::SyntaxKind::NthgKeyword) +
          ">",
      DiagnosticUtils::DiagnosticLevel::Error,
      DiagnosticUtils::DiagnosticType::Syntactic,
      Utils::getSourceLocation(this->getCurrent())));

  return nullptr;
}

std::unique_ptr<FunctionDeclarationSyntax> Parser::parseFunctionDeclaration(
    const bool &isExposed) {
  std::unique_ptr<FunctionDeclarationSyntax> functionDeclaration =
      std::make_unique<FunctionDeclarationSyntax>(isExposed);

  functionDeclaration->setFunctionKeyword(
      std::move(this->match(SyntaxKindUtils::SyntaxKind::FunctionKeyword)));

  functionDeclaration->setIdentifierToken(
      std::move(this->match(SyntaxKindUtils::SyntaxKind::IdentifierToken)));

  functionDeclaration->setOpenParenthesisToken(std::move(
      this->match(SyntaxKindUtils::SyntaxKind::OpenParenthesisToken)));

  bool isOptionalParameterType = false;

  while (this->getCurrent()->getKind() !=
             SyntaxKindUtils::SyntaxKind::CloseParenthesisToken &&
         this->getCurrent()->getKind() !=
             SyntaxKindUtils::SyntaxKind::EndOfFileToken) {
    if (functionDeclaration->getParametersPtr().size() > 0) {
      functionDeclaration->addSeparator(
          std::move(this->match(SyntaxKindUtils::SyntaxKind::CommaToken)));
    }

    std::unique_ptr<VariableDeclarationSyntax> parameter =
        std::move(this->parseVariableDeclaration());

    functionDeclaration->addParameter(std::move(parameter));
  }

  functionDeclaration->setCloseParenthesisToken(std::move(
      this->match(SyntaxKindUtils::SyntaxKind::CloseParenthesisToken)));

  this->match(SyntaxKindUtils::SyntaxKind::MinusToken);
  this->match(SyntaxKindUtils::SyntaxKind::GreaterToken);

  functionDeclaration->setReturnType(this->parseTypeExpression());

  functionDeclaration->setBody(std::move(this->parseBlockStatement()));

  return std::move(functionDeclaration);
}

std::unique_ptr<ArrayTypeExpressionSyntax> Parser::parseArrayTypeExpression() {
  std::unique_ptr<ArrayTypeExpressionSyntax> arrayTypeExpression =
      std::make_unique<ArrayTypeExpressionSyntax>(
          std::make_unique<SyntaxToken<std::any>>(
              this->_diagnosticHandler->getAbsoluteFilePath(), 0,
              SyntaxKindUtils::SyntaxKind::NBU_ARRAY_TYPE, 0, "NBU_ARRAY_TYPE",
              "NBU_ARRAY_TYPE"));

  arrayTypeExpression->setElementType(std::move(this->parsePrimitiveType()));

  while (this->getCurrent()->getKind() ==
         SyntaxKindUtils::SyntaxKind::OpenBracketToken) {
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

  if (this->getCurrent()->getKind() ==
      SyntaxKindUtils::SyntaxKind::IdentifierToken) {
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
      "Unexpected Token <" +
          SyntaxKindUtils::to_string(this->getCurrent()->getKind()) +
          ">, Expected <" +
          SyntaxKindUtils::to_string(SyntaxKindUtils::SyntaxKind::ColonToken) +
          ">",
      DiagnosticUtils::DiagnosticLevel::Error,
      DiagnosticUtils::DiagnosticType::Syntactic,
      Utils::getSourceLocation(this->getCurrent())));
  return std::move(functionDeclaration);
}

std::unique_ptr<GlobalStatementSyntax> Parser::parseGlobalStatement(
    const bool &isExposed) {
  std::unique_ptr<StatementSyntax> statement =
      std::move(this->parseStatement());
  return std::make_unique<GlobalStatementSyntax>(isExposed,
                                                 std::move(statement));
}

std::unique_ptr<BlockStatementSyntax> Parser::parseBlockStatement() {
  std::unique_ptr<BlockStatementSyntax> blockStatement =
      std::make_unique<BlockStatementSyntax>();

  std::unique_ptr<SyntaxToken<std::any>> openBraceToken =
      std::move(this->match(SyntaxKindUtils::SyntaxKind::OpenBraceToken));

  blockStatement->setOpenBraceToken(std::move(openBraceToken));

  std::vector<std::unique_ptr<StatementSyntax>> statements;
  while (this->getCurrent()->getKind() !=
             SyntaxKindUtils::SyntaxKind::CloseBraceToken &&
         this->getCurrent()->getKind() !=
             SyntaxKindUtils::SyntaxKind::EndOfFileToken) {
    blockStatement->addStatement(std::move(this->parseStatement()));
  }

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
  switch (this->getCurrent()->getKind()) {
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
    default:
      return std::move(this->parseExpressionStatement());
  }
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

  this->match(SyntaxKindUtils::SyntaxKind::TypeKeyword);

  std::unique_ptr<SyntaxToken<std::any>> typeToken =
      std::move(this->match(SyntaxKindUtils::SyntaxKind::IdentifierToken));

  std::any val = typeToken->getValue();

  std::unique_ptr<LiteralExpressionSyntax<std::any>> typeNameExp =
      std::make_unique<LiteralExpressionSyntax<std::any>>(std::move(typeToken),
                                                          val);

  customTypeStatement->setTypeName(std::move(typeNameExp));

  this->match(SyntaxKindUtils::SyntaxKind::EqualsToken);
  this->match(SyntaxKindUtils::SyntaxKind::OpenBraceToken);

  while (this->getCurrent()->getKind() !=
             SyntaxKindUtils::SyntaxKind::CloseBraceToken &&
         this->getCurrent()->getKind() !=
             SyntaxKindUtils::SyntaxKind::EndOfFileToken) {
    std::unique_ptr<SyntaxToken<std::any>> idenfierToken =
        std::move(this->match(SyntaxKindUtils::SyntaxKind::IdentifierToken));

    std::any val = idenfierToken->getValue();

    std::unique_ptr<LiteralExpressionSyntax<std::any>> idenfierExp =
        std::make_unique<LiteralExpressionSyntax<std::any>>(
            std::move(idenfierToken), val);

    this->match(SyntaxKindUtils::SyntaxKind::ColonToken);

    std::unique_ptr<TypeExpressionSyntax> typeExpression =
        std::move(this->parseTypeExpression());

    customTypeStatement->addKeyTypePair(std::move(idenfierExp),
                                        std::move(typeExpression));

    if (this->getCurrent()->getKind() !=
        SyntaxKindUtils::SyntaxKind::CloseBraceToken) {
      this->match(SyntaxKindUtils::SyntaxKind::CommaToken);
    }
  }

  this->match(SyntaxKindUtils::SyntaxKind::CloseBraceToken);
  return std::move(customTypeStatement);
}

std::unique_ptr<ContainerExpressionSyntax> Parser::parseContainerExpression() {
  std::unique_ptr<ContainerExpressionSyntax> containerExpression =
      std::make_unique<ContainerExpressionSyntax>();

  this->match(SyntaxKindUtils::SyntaxKind::OpenBracketToken);
  while (this->getCurrent()->getKind() !=
             SyntaxKindUtils::SyntaxKind::CloseBracketToken &&
         this->getCurrent()->getKind() !=
             SyntaxKindUtils::SyntaxKind::EndOfFileToken) {
    std::unique_ptr<ExpressionSyntax> expression = nullptr;

    if (this->getCurrent()->getKind() ==
        SyntaxKindUtils::SyntaxKind::OpenBracketToken) {
      expression = std::move(this->parseContainerExpression());
    } else {
      expression = std::move(this->parseExpression());
    }

    containerExpression->setElement(std::move(expression));

    if (this->getCurrent()->getKind() !=
        SyntaxKindUtils::SyntaxKind::CloseBracketToken) {
      this->match(SyntaxKindUtils::SyntaxKind::CommaToken);
    }
  }

  this->match(SyntaxKindUtils::SyntaxKind::CloseBracketToken);

  return std::move(containerExpression);
}

std::unique_ptr<StatementSyntax> Parser::parseBringStatement() {
  std::unique_ptr<SyntaxToken<std::any>> bringKeyword =
      std::move(this->match(SyntaxKindUtils::SyntaxKind::BringKeyword));

  std::unique_ptr<BringStatementSyntax> bringStatement =
      std::make_unique<BringStatementSyntax>();

  bringStatement->addBringKeyword(std::move(bringKeyword));

  if (this->getCurrent()->getKind() ==
      SyntaxKindUtils::SyntaxKind::OpenBraceToken) {
    this->match(SyntaxKindUtils::SyntaxKind::OpenBraceToken);
    while (this->getCurrent()->getKind() !=
           SyntaxKindUtils::SyntaxKind::CloseBraceToken) {
      std::unique_ptr<SyntaxToken<std::any>> identifier =
          std::move(this->match(SyntaxKindUtils::SyntaxKind::IdentifierToken));
      bringStatement->addExpression(std::move(identifier));
      if (this->getCurrent()->getKind() ==
          SyntaxKindUtils::SyntaxKind::CommaToken) {
        this->match(SyntaxKindUtils::SyntaxKind::CommaToken);
      }

      if (this->getCurrent()->getKind() ==
          SyntaxKindUtils::SyntaxKind::EndOfFileToken) {
        this->_diagnosticHandler->addDiagnostic(Diagnostic(
            "Unexpected Token <" +
                SyntaxKindUtils::to_string(this->getCurrent()->getKind()) +
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
  }

  if (bringStatement->getIsChoosyImportPtr()) {
    this->match(SyntaxKindUtils::SyntaxKind::FromKeyword);
  }

  if (this->getCurrent()->getKind() !=
      SyntaxKindUtils::SyntaxKind::StringToken) {
    this->_diagnosticHandler->addDiagnostic(Diagnostic(
        "Unexpected Token <" +
            SyntaxKindUtils::to_string(this->getCurrent()->getKind()) +
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

  const std::string relativeFilePath =
      std::any_cast<std::string>(stringToken->getValue());

  bringStatement->setRelativeFilePath(relativeFilePath);

  std::unique_ptr<DiagnosticHandler> diagnosticHandler =
      std::make_unique<DiagnosticHandler>(relativeFilePath);

  bringStatement->setAbsoluteFilePath(
      Utils::getAbsoluteFilePath(relativeFilePath));

  this->_diagnosticHandler->addParentDiagnostics(diagnosticHandler.get());
  bringStatement->setDiagnosticHandler(std::move(diagnosticHandler));

  std::unique_ptr<Parser> parser = std::make_unique<Parser>(
      Utils::readLines(Utils::getAbsoluteFilePath(relativeFilePath)),
      bringStatement->getDiagnosticHandlerPtr().get());

  std::unique_ptr<CompilationUnitSyntax> compilationUnit =
      std::move(parser->parseCompilationUnit());

  bringStatement->setCompilationUnit(std::move(compilationUnit));

  return std::move(bringStatement);
}

std::unique_ptr<ReturnStatementSyntax> Parser::parseReturnStatement() {
  std::unique_ptr<SyntaxToken<std::any>> returnKeyword =
      std::move(this->match(SyntaxKindUtils::SyntaxKind::ReturnKeyword));

  if (this->getCurrent()->getKind() ==
      SyntaxKindUtils::SyntaxKind::OpenParenthesisToken) {
    this->match(SyntaxKindUtils::SyntaxKind::OpenParenthesisToken);

    std::unique_ptr<ExpressionSyntax> expression =
        std::move(this->parseExpression());
    this->match(SyntaxKindUtils::SyntaxKind::CloseParenthesisToken);
    return std::make_unique<ReturnStatementSyntax>(std::move(returnKeyword),
                                                   std::move(expression));
  } else if (this->getCurrent()->getKind() !=
             SyntaxKindUtils::SyntaxKind::ColonToken) {
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
  bool hadOpenParenthesis = false;
  if (this->getCurrent()->getKind() ==
      SyntaxKindUtils::SyntaxKind::OpenParenthesisToken) {
    this->nextToken();
    hadOpenParenthesis = true;
  }

  std::unique_ptr<StatementSyntax> statementSyntax = nullptr;

  if (this->getCurrent()->getKind() ==
      SyntaxKindUtils::SyntaxKind::VarKeyword) {
    statementSyntax = std::move(this->parseVariableDeclaration());
  } else {
    statementSyntax = std::move(this->parseExpressionStatement());
  }

  std::unique_ptr<SyntaxToken<std::any>> toKeyword =
      std::move(this->match(SyntaxKindUtils::SyntaxKind::ToKeyword));

  std::unique_ptr<ExpressionSyntax> upperBound =
      std::move(this->parseExpression());
  std::unique_ptr<ExpressionSyntax> step = nullptr;
  if (this->getCurrent()->getKind() ==
      SyntaxKindUtils::SyntaxKind::ColonToken) {
    this->match(SyntaxKindUtils::SyntaxKind::ColonToken);

    step = std::move(this->parseExpression());
  }

  if (hadOpenParenthesis) {
    this->match(SyntaxKindUtils::SyntaxKind::CloseParenthesisToken);
  }

  std::unique_ptr<BlockStatementSyntax> statement =
      std::move(this->parseBlockStatement());
  return std::make_unique<ForStatementSyntax>(
      std::move(statementSyntax), std::move(upperBound), std::move(statement),
      std::move(step));
}

std::unique_ptr<ElseClauseSyntax> Parser::parseElseStatement() {
  std::unique_ptr<SyntaxToken<std::any>> elseKeyword =
      std::move(this->match(SyntaxKindUtils::SyntaxKind::ElseKeyword));
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

  std::unique_ptr<ExpressionSyntax> condition =
      std::move(this->parseExpression());

  std::unique_ptr<BlockStatementSyntax> statement =
      std::move(this->parseBlockStatement());

  ifStatement->addIfKeyword(std::move(keyword));
  ifStatement->addCondition(std::move(condition));
  ifStatement->addStatement(std::move(statement));

  while (this->getCurrent()->getKind() ==
         SyntaxKindUtils::SyntaxKind::OrKeyword) {
    std::unique_ptr<SyntaxToken<std::any>> orKeyword =
        std::move(this->match(SyntaxKindUtils::SyntaxKind::OrKeyword));
    std::unique_ptr<SyntaxToken<std::any>> ifKeyword =
        std::move(this->match(SyntaxKindUtils::SyntaxKind::IfKeyword));
    std::unique_ptr<ExpressionSyntax> condition =
        std::move(this->parseExpression());
    std::unique_ptr<BlockStatementSyntax> statement =
        std::move(this->parseBlockStatement());

    ifStatement->addOrIfStatement(std::make_unique<OrIfStatementSyntax>(
        std::move(orKeyword), std::move(ifKeyword), std::move(condition),
        std::move(statement)));
  }
  std::unique_ptr<ElseClauseSyntax> elseClause = nullptr;

  if (this->getCurrent()->getKind() ==
      SyntaxKindUtils::SyntaxKind::ElseKeyword) {
    elseClause = std::move(this->parseElseStatement());
  }

  ifStatement->addElseClause(std::move(elseClause));

  return std::move(ifStatement);
}

std::unique_ptr<WhileStatementSyntax> Parser::parseWhileStatement() {
  std::unique_ptr<SyntaxToken<std::any>> keyword =
      std::move(this->match(SyntaxKindUtils::SyntaxKind::WhileKeyword));
  std::unique_ptr<ExpressionSyntax> condition =
      std::move(this->parseExpression());
  std::unique_ptr<BlockStatementSyntax> statement =
      std::move(this->parseBlockStatement());
  return std::make_unique<WhileStatementSyntax>(
      std::move(keyword), std::move(condition), std::move(statement));
}

std::unique_ptr<VariableDeclarationSyntax> Parser::parseVariableDeclaration(
    bool isFuncDec) {
  std::unique_ptr<VariableDeclarationSyntax> varDec =
      std::make_unique<VariableDeclarationSyntax>();

  std::unique_ptr<SyntaxToken<std::any>> keyword = nullptr;

  if (isFuncDec && SyntaxKindUtils::SyntaxKind::ConstKeyword ==
                       this->getCurrent()->getKind()) {
    keyword = std::move(this->match(SyntaxKindUtils::SyntaxKind::ConstKeyword));
    varDec->setKeyword(std::move(keyword));
  } else if (!isFuncDec) {
    keyword = std::move(this->match(
        SyntaxKindUtils::SyntaxKind::VarKeyword == this->getCurrent()->getKind()
            ? SyntaxKindUtils::SyntaxKind::VarKeyword
            : SyntaxKindUtils::SyntaxKind::ConstKeyword));
    varDec->setKeyword(std::move(keyword));
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

  if (this->getCurrent()->getKind() ==
      SyntaxKindUtils::SyntaxKind::ColonToken) {
    this->match(SyntaxKindUtils::SyntaxKind::ColonToken);
    typeExpr = std::move(this->parseTypeExpression());
  }
  varDec->setTypeExpr(std::move(typeExpr));

  if (this->getCurrent()->getKind() ==
      SyntaxKindUtils::SyntaxKind::EqualsToken) {
    std::unique_ptr<SyntaxToken<std::any>> equalsToken =
        std::move(this->match(SyntaxKindUtils::SyntaxKind::EqualsToken));

    std::unique_ptr<ExpressionSyntax> initializer =
        std::move(this->parseExpression());
    varDec->setInitializer(std::move(initializer));
  }

  return std::move(varDec);
}

std::unique_ptr<ExpressionSyntax> Parser::parseExpression(
    int parentPrecedence) {
  std::unique_ptr<ExpressionSyntax> left = nullptr;
  int unaryOperatorPrecedence =
      this->getCurrent()->getUnaryOperatorPrecedence();

  if (unaryOperatorPrecedence != 0 &&
      unaryOperatorPrecedence >= parentPrecedence) {
    std::unique_ptr<SyntaxToken<std::any>> operatorToken =
        std::move(this->match(this->getCurrent()->getKind()));
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

    std::unique_ptr<SyntaxToken<std::any>> operatorToken =
        std::move(this->match(this->getCurrent()->getKind()));

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

  std::any sizeVAL = numToken->getValue();

  sizeToFillExpression = std::make_unique<LiteralExpressionSyntax<std::any>>(
      std::move(numToken), sizeVAL);

  this->match(SyntaxKindUtils::SyntaxKind::FillKeyword);

  std::unique_ptr<ExpressionSyntax> elementExpression =
      std::move(this->parseExpression());

  this->match(SyntaxKindUtils::SyntaxKind::CloseBracketToken);

  fillExpression->setSizeToFillExpression(std::move(sizeToFillExpression));
  fillExpression->setElementExpression(std::move(elementExpression));

  return std::move(fillExpression);
}

std::unique_ptr<ExpressionSyntax> Parser::parsePrimaryExpression() {
  switch (this->getCurrent()->getKind()) {
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
    default:
      break;
  }

  std::unique_ptr<SyntaxToken<std::any>> expressionToken =
      std::move(this->match(SyntaxKindUtils::SyntaxKind::ExpressionStatement));

  return std::make_unique<LiteralExpressionSyntax<std::any>>(
      std::move(expressionToken), nullptr);
}
std::unique_ptr<VariableExpressionSyntax> Parser::parseVariableExpression() {
  std::unique_ptr<SyntaxToken<std::any>> identifierToken =
      std::move(this->match(SyntaxKindUtils::SyntaxKind::IdentifierToken));

  std::any value = identifierToken->getValue();

  std::unique_ptr<TypeExpressionSyntax> typeExpression =
      std::make_unique<TypeExpressionSyntax>(
          std::make_unique<SyntaxToken<std::any>>(
              this->_diagnosticHandler->getAbsoluteFilePath(), 0,
              SyntaxKindUtils::SyntaxKind::NBU_UNKNOWN_TYPE, 0,
              "NBU_UNKNOWN_TYPE", "NBU_UNKNOWN_TYPE"));

  return std::make_unique<VariableExpressionSyntax>(
      std::make_unique<LiteralExpressionSyntax<std::any>>(
          std::move(identifierToken), value),
      false, std::move(typeExpression));
}
std::unique_ptr<ExpressionSyntax> Parser::parseIndexExpression() {
  std::unique_ptr<SyntaxToken<std::any>> identifierToken =
      std::move(this->match(SyntaxKindUtils::SyntaxKind::IdentifierToken));

  std::any value = identifierToken->getValue();
  std::unique_ptr<IndexExpressionSyntax> indexExpression =
      std::make_unique<IndexExpressionSyntax>(
          std::make_unique<LiteralExpressionSyntax<std::any>>(
              std::move(identifierToken), value));

  while (this->getCurrent()->getKind() ==
         SyntaxKindUtils::SyntaxKind::OpenBracketToken) {
    this->match(SyntaxKindUtils::SyntaxKind::OpenBracketToken);

    indexExpression->addIndexExpression(std::move(this->parseExpression()));

    this->match(SyntaxKindUtils::SyntaxKind::CloseBracketToken);
  }

  if (this->getCurrent()->getKind() ==
      SyntaxKindUtils::SyntaxKind::EqualsToken) {
    std::unique_ptr<SyntaxToken<std::any>> operatorToken =
        std::move(this->match(SyntaxKindUtils::SyntaxKind::EqualsToken));

    std::unique_ptr<ExpressionSyntax> right =
        std::move(this->parseExpression());

    return std::make_unique<AssignmentExpressionSyntax>(
        std::move(indexExpression), std::move(operatorToken), std::move(right));
  }

  return std::move(indexExpression);
}

std::unique_ptr<ExpressionSyntax> Parser::parseNameorCallExpression() {
  if (this->peek(1)->getKind() == SyntaxKindUtils::SyntaxKind::EqualsToken) {
    std::unique_ptr<SyntaxToken<std::any>> identifierToken =
        std::move(this->match(SyntaxKindUtils::SyntaxKind::IdentifierToken));
    std::unique_ptr<SyntaxToken<std::any>> operatorToken =
        std::move(this->match(SyntaxKindUtils::SyntaxKind::EqualsToken));
    std::unique_ptr<ExpressionSyntax> right =
        std::move(this->parseExpression());

    std::any value = identifierToken->getValue();
    return std::make_unique<AssignmentExpressionSyntax>(
        std::make_unique<LiteralExpressionSyntax<std::any>>(
            std::move(identifierToken), value),
        std::move(operatorToken), std::move(right));
  } else if (this->peek(1)->getKind() ==
             SyntaxKindUtils::SyntaxKind::OpenBracketToken) {
    return std::move(this->parseIndexExpression());
  } else if (this->peek(1)->getKind() ==
             SyntaxKindUtils::SyntaxKind::OpenParenthesisToken) {
    std::unique_ptr<SyntaxToken<std::any>> identifierToken =
        std::move(this->match(SyntaxKindUtils::SyntaxKind::IdentifierToken));
    std::any val = identifierToken->getValue();

    std::unique_ptr<CallExpressionSyntax> callExpression =
        std::make_unique<CallExpressionSyntax>(
            std::make_unique<LiteralExpressionSyntax<std::any>>(
                std::move(identifierToken), val));

    std::unique_ptr<SyntaxToken<std::any>> openParenthesisToken = std::move(
        this->match(SyntaxKindUtils::SyntaxKind::OpenParenthesisToken));

    callExpression->setOpenParenthesisToken(std::move(openParenthesisToken));

    while (this->getCurrent()->getKind() !=
               SyntaxKindUtils::SyntaxKind::CloseParenthesisToken &&
           this->getCurrent()->getKind() !=
               SyntaxKindUtils::SyntaxKind::EndOfFileToken) {
      std::unique_ptr<ExpressionSyntax> expression =
          std::move(this->parseExpression());
      callExpression->addArgument(std::move(expression));
      if (this->getCurrent()->getKind() !=
          SyntaxKindUtils::SyntaxKind::CloseParenthesisToken) {
        callExpression->addSeparator(
            std::move(this->match(SyntaxKindUtils::SyntaxKind::CommaToken)));
      }
    }
    std::unique_ptr<SyntaxToken<std::any>> closeParenthesisToken = std::move(
        this->match(SyntaxKindUtils::SyntaxKind::CloseParenthesisToken));

    callExpression->setCloseParenthesisToken(std::move(closeParenthesisToken));

    return std::move(callExpression);
  } else {
    return std::move(parseVariableExpression());
  }
}
