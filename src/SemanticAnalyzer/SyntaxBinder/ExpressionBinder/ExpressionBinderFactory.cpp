

#include "ExpressionBinderFactory.h"
#include "AssignmentExpressionBinder/AssignmentExpressionBinder.h"
#include "BinaryExpressionBinder/BinaryExpressionBinder.h"
#include "BracketedExpressionBinder/BracketedExpressionBinder.h"
#include "CallExpressionBinder/CallExpressionBinder.h"
#include "ContainerExpressionBinder/ContainerExpressionBinder.h"
#include "DefaultExpressionBinder/DefaultExpressionBinder.h"
#include "FillExpressionBinder/FillExpressionBinder.h"
#include "IndexExpressionBinder/IndexExpressionBinder.h"
#include "LiteralExpressionBinder/LiteralExpressionBinder.h"
#include "MultipleAssignmentExpressionBinder/MultipleAssignmentExpressionBinder.h"
#include "NirastExpressionBinder/NirastExpressionBinder.h"
#include "ObjectExpressionBinder/ObjectExpressionBinder.h"
#include "ParenthesizedExpressionBinder/ParenthesizedExpressionBinder.h"
#include "TernaryExpressionBinder/TernaryExpressionBinder.h"
#include "UnaryExpressionBinder/UnaryExpressionBinder.h"
#include "VariableExpressionBinder/VariableExpressionBinder.h"

#include "TypeExpressionBinder/ArrayTypeExpressionBinder/ArrayTypeExpressionBinder.h"
#include "TypeExpressionBinder/FunctionTypeExpressionBinder/FunctionTypeExpressionBinder.h"
#include "TypeExpressionBinder/ObjectTypeExpressionBinder/ObjectTypeExpressionBinder.h"
#include "TypeExpressionBinder/PrimitiveTypeExpressionBinder/PrimitiveTypeExpressionBinder.h"

std::unique_ptr<ExpressionBinder>
ExpressionBinderFactory::create(const SyntaxKindUtils::SyntaxKind &kind) {
  switch (kind) {
  case SyntaxKindUtils::SyntaxKind::AssignmentExpression: {
    return std::make_unique<AssignmentExpressionBinder>();
  }
  case SyntaxKindUtils::SyntaxKind::BinaryExpression: {
    return std::make_unique<BinaryExpressionBinder>();
  }
  case SyntaxKindUtils::SyntaxKind::BracketedExpression: {
    return std::make_unique<BracketedExpressionBinder>();
  }
  case SyntaxKindUtils::SyntaxKind::CallExpression: {
    return std::make_unique<CallExpressionBinder>();
  }
  case SyntaxKindUtils::SyntaxKind::ContainerExpression: {
    return std::make_unique<ContainerExpressionBinder>();
  }
  case SyntaxKindUtils::SyntaxKind::FillExpression: {
    return std::make_unique<FillExpressionBinder>();
  }
  case SyntaxKindUtils::SyntaxKind::IndexExpression: {
    return std::make_unique<IndexExpressionBinder>();
  }
  case SyntaxKindUtils::SyntaxKind::LiteralExpression: {
    return std::make_unique<LiteralExpressionBinder>();
  }
  case SyntaxKindUtils::SyntaxKind::MultipleAssignmentExpression: {
    return std::make_unique<MultipleAssignmentExpressionBinder>();
  }
  case SyntaxKindUtils::SyntaxKind::NirastExpression: {
    return std::make_unique<NirastExpressionBinder>();
  }
  case SyntaxKindUtils::SyntaxKind::ObjectExpression: {
    return std::make_unique<ObjectExpressionBinder>();
  }
  case SyntaxKindUtils::SyntaxKind::ParenthesizedExpression: {
    return std::make_unique<ParenthesizedExpressionBinder>();
  }
  case SyntaxKindUtils::SyntaxKind::TernaryExpression: {
    return std::make_unique<TernaryExpressionBinder>();
  }
  case SyntaxKindUtils::SyntaxKind::UnaryExpression: {
    return std::make_unique<UnaryExpressionBinder>();
  }
  case SyntaxKindUtils::SyntaxKind::VariableExpressionSyntax: {
    return std::make_unique<VariableExpressionBinder>();
  }
  case SyntaxKindUtils::SyntaxKind::ArrayTypeExpression: {
    return std::make_unique<ArrayTypeExpressionBinder>();
  }
  case SyntaxKindUtils::SyntaxKind::FunctionTypeExpression: {
    return std::make_unique<FunctionTypeExpressionBinder>();
  }
  case SyntaxKindUtils::SyntaxKind::ObjectTypeExpression: {
    return std::make_unique<ObjectTypeExpressionBinder>();
  }
  case SyntaxKindUtils::SyntaxKind::PrimitiveTypeExpression: {
    return std::make_unique<PrimitiveTypeExpressionBinder>();
  }

  default:
    return std::make_unique<DefaultExpressionBinder>();
  }
}