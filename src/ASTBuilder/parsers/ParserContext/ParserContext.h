#pragma once

#include "../../../SourceTokenizer/SourceTokenizer.h"
#include "../../../diagnostics/DiagnosticHandler/DiagnosticHandler.h"
#include "../../../syntax/SyntaxToken.h"
#include "../../CodeFormatter/CodeFormatter.h"
#include <cstdint>
#include <memory>
#include <vector>

class ParserContext {

public:
  ParserContext(
      FlowWing::DiagnosticHandler *diagnosticHandler,
      const std::unordered_map<std::string, int8_t> &dependencyPathsMap =
          std::unordered_map<std::string, int8_t>());

  ~ParserContext();

  //? Syntax Token Methods

  std::unique_ptr<SyntaxToken<std::any>>
  match(const SyntaxKindUtils::SyntaxKind &kind);
  SyntaxToken<std::any> *peek(const int &offset);
  SyntaxToken<std::any> *getCurrent();
  std::unique_ptr<SyntaxToken<std::any>> nextToken();
  SyntaxKindUtils::SyntaxKind getKind();
  //? Build Token List
  void buildTokenList(SourceTokenizer *lexer);

  //? Code Formatter Methods

  const std::unique_ptr<CodeFormatter> &getCodeFormatterRef();

  //? Parser Methods

  //? Getters
  const std::string &getCurrentModuleName();
  FlowWing::DiagnosticHandler *getDiagnosticHandler();
  const bool getIsInsideCallExpression() const;
  const bool getIsInsideIndexExpression() const;
  const bool getIsInsideContainerExpression() const;
  const bool getIsInsideReturnStatement() const;
  const int8_t getDependencyFileCount(const std::string &path);
  const std::vector<std::unique_ptr<SyntaxToken<std::any>>> &getTokenListRef();

  //? Setters

  void setCurrentModuleName(const std::string &name);
  void setIsInsideCallExpression(const bool value);
  void setIsInsideIndexExpression(const bool value);
  void setIsInsideContainerExpression(const bool value);
  void setIsInsideReturnStatement(const bool value);
  void updateDependencyCount(const std::string &path, const int8_t count);

private:
  void handleDiagnosticsForBadToken(SyntaxToken<std::any> *token);
  void handleFormatCommentToken(SyntaxToken<std::any> *token,
                                bool &isEncounteredEndOfLineBefore);

  FlowWing::DiagnosticHandler *_diagnosticHandler = nullptr;
  std::vector<std::unique_ptr<SyntaxToken<std::any>>> _tokens = {};
  std::unique_ptr<CodeFormatter> _codeFormatter = nullptr;
  std::unordered_map<std::string, int8_t> _dependencyPathsMap =
      std::unordered_map<std::string, int8_t>();
  size_t _position = 0;
  std::string _currentModuleName = "";
  bool _isInsideCallExpression = false;
  bool _isInsideIndexExpression = false;
  bool _isInsideContainerExpression = false;
  bool _isInsideReturnStatement = false;
};
