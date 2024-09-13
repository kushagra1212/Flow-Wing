#pragma once

#include "../TypeExpressionSyntax.h"

class FunctionTypeExpressionSyntax : public TypeExpressionSyntax {
 private:
  std::unique_ptr<SyntaxToken<std::any>> _type;
  std::vector<std::unique_ptr<TypeExpressionSyntax>> _parameterTypes;
  std::vector<std::unique_ptr<TypeExpressionSyntax>> _returnTypes;
  std::vector<std::unique_ptr<SyntaxToken<std::any>>> _asParametersKeywords;
  std::unique_ptr<SyntaxToken<std::any>> _asKeyword;

  std::vector<std::unique_ptr<SyntaxToken<std::any>>> _separators;
  std::unique_ptr<SyntaxToken<std::any>> _openParenthesisToken;
  std::unique_ptr<SyntaxToken<std::any>> _closeParenthesisToken;

 public:
  FunctionTypeExpressionSyntax(std::unique_ptr<SyntaxToken<std::any>> type);
  const virtual SyntaxKindUtils::SyntaxKind getKind() const override;
  const virtual std::vector<SyntaxNode *> &getChildren() override;
  const virtual DiagnosticUtils::SourceLocation getSourceLocation()
      const override;

  inline auto addParameterType(
      std::unique_ptr<TypeExpressionSyntax> parameterType) -> void {
    _parameterTypes.push_back(std::move(parameterType));
  }

  inline auto addReturnType(std::unique_ptr<TypeExpressionSyntax> returnType)
      -> void {
    _returnTypes.push_back(std::move(returnType));
  }

  inline auto addAsParameterKeyword(
      std::unique_ptr<SyntaxToken<std::any>> asParameterKeyword) -> void {
    _asParametersKeywords.push_back(std::move(asParameterKeyword));
  }

  inline auto setAsKeyword(std::unique_ptr<SyntaxToken<std::any>> asKeyword)
      -> void {
    _asKeyword = std::move(asKeyword);
  }

  inline auto setOpenParenthesisToken(
      std::unique_ptr<SyntaxToken<std::any>> openParenthesisToken) -> void {
    _openParenthesisToken = std::move(openParenthesisToken);
  }

  inline auto setCloseParenthesisToken(
      std::unique_ptr<SyntaxToken<std::any>> closeParenthesisToken) -> void {
    _closeParenthesisToken = std::move(closeParenthesisToken);
  }

  inline auto addSeparator(std::unique_ptr<SyntaxToken<std::any>> separator) {
    _separators.push_back(std::move(separator));
  }

  inline auto getTypeRef() const
      -> const std::unique_ptr<SyntaxToken<std::any>> & {
    return _type;
  }

  inline auto getReturnTypesRef() const
      -> const std::vector<std::unique_ptr<TypeExpressionSyntax>> & {
    return _returnTypes;
  }

  inline auto getParameterTypesRef() const
      -> const std::vector<std::unique_ptr<TypeExpressionSyntax>> & {
    return _parameterTypes;
  }

  inline auto getAsKeywordRef() const
      -> const std::unique_ptr<SyntaxToken<std::any>> & {
    return _asKeyword;
  }

  inline auto getAsParametersKeywordsRef() const
      -> const std::vector<std::unique_ptr<SyntaxToken<std::any>>> & {
    return _asParametersKeywords;
  }
};