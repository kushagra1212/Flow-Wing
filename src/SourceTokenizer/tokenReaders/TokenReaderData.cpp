/*
 * FlowWing Compiler
 * Copyright (C) 2023-2025 Kushagra Rathore
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */


#include "TokenReaderData.h"

const TokenReaderState __gl_FLOW_WING_KEYWORDS[] = {
    {"true", SyntaxKindUtils::SyntaxKind::TrueKeyword},
    {"false", SyntaxKindUtils::SyntaxKind::FalseKeyword},
    {"var", SyntaxKindUtils::SyntaxKind::VarKeyword},
    {"if", SyntaxKindUtils::SyntaxKind::IfKeyword},
    {"or", SyntaxKindUtils::SyntaxKind::OrKeyword},
    {"else", SyntaxKindUtils::SyntaxKind::ElseKeyword},
    {"while", SyntaxKindUtils::SyntaxKind::WhileKeyword},
    {"for", SyntaxKindUtils::SyntaxKind::ForKeyword},
    {"fun", SyntaxKindUtils::SyntaxKind::FunctionKeyword},
    {"to", SyntaxKindUtils::SyntaxKind::ToKeyword},
    {"continue", SyntaxKindUtils::SyntaxKind::ContinueKeyword},
    {"break", SyntaxKindUtils::SyntaxKind::BreakKeyword},
    {"return", SyntaxKindUtils::SyntaxKind::ReturnKeyword},
    {"const", SyntaxKindUtils::SyntaxKind::ConstKeyword},
    {"nthg", SyntaxKindUtils::SyntaxKind::NthgKeyword},
    {"int", SyntaxKindUtils::SyntaxKind::Int32Keyword},
    {"char", SyntaxKindUtils::SyntaxKind::Int8Keyword},
    {"int64", SyntaxKindUtils::SyntaxKind::Int64Keyword},
    {"bool", SyntaxKindUtils::SyntaxKind::BoolKeyword},
    {"unknown", SyntaxKindUtils::SyntaxKind::NBU_UNKNOWN_TYPE},
    {"str", SyntaxKindUtils::SyntaxKind::StrKeyword},
    {"deci", SyntaxKindUtils::SyntaxKind::DeciKeyword},
    {"deci32", SyntaxKindUtils::SyntaxKind::Deci32Keyword},
    {"Nir", SyntaxKindUtils::SyntaxKind::NirastKeyword},
    {"bring", SyntaxKindUtils::SyntaxKind::BringKeyword},
    {"expose", SyntaxKindUtils::SyntaxKind::ExposeKeyword},
    {"from", SyntaxKindUtils::SyntaxKind::FromKeyword},
    {"fill", SyntaxKindUtils::SyntaxKind::FillKeyword},
    {"type", SyntaxKindUtils::SyntaxKind::TypeKeyword},
    {"decl", SyntaxKindUtils::SyntaxKind::DeclKeyword},
    {"new", SyntaxKindUtils::SyntaxKind::NewKeyword},
    {"class", SyntaxKindUtils::SyntaxKind::ClassKeyword},
    {"inout", SyntaxKindUtils::SyntaxKind::InOutKeyword},
    {"extends", SyntaxKindUtils::SyntaxKind::ExtendsKeyword},
    {"as", SyntaxKindUtils::SyntaxKind::AsKeyword},
    {"module", SyntaxKindUtils::SyntaxKind::ModuleKeyword},
    {"switch", SyntaxKindUtils::SyntaxKind::SwitchKeyword},
    {"case", SyntaxKindUtils::SyntaxKind::CaseKeyword},
    {"default", SyntaxKindUtils::SyntaxKind::DefaultKeyword},
};

const TokenReaderState __gl_FLOW_WING_SYMBOLS[] = {
    {"+", SyntaxKindUtils::SyntaxKind::PlusToken},
    {"-", SyntaxKindUtils::SyntaxKind::MinusToken},
    {"*", SyntaxKindUtils::SyntaxKind::StarToken},
    {";", SyntaxKindUtils::SyntaxKind::SemicolonToken},
    {",", SyntaxKindUtils::SyntaxKind::CommaToken},
    {"{", SyntaxKindUtils::SyntaxKind::OpenBraceToken},
    {"}", SyntaxKindUtils::SyntaxKind::CloseBraceToken},
    {"[", SyntaxKindUtils::SyntaxKind::OpenBracketToken},
    {"]", SyntaxKindUtils::SyntaxKind::CloseBracketToken},
    {"#", SyntaxKindUtils::SyntaxKind::HashToken},
    {"(", SyntaxKindUtils::SyntaxKind::OpenParenthesisToken},
    {")", SyntaxKindUtils::SyntaxKind::CloseParenthesisToken},
    {"^", SyntaxKindUtils::SyntaxKind::CaretToken},
    {"%", SyntaxKindUtils::SyntaxKind::PercentToken},
    {"~", SyntaxKindUtils::SyntaxKind::TildeToken},
    {":", SyntaxKindUtils::SyntaxKind::ColonToken},
    {".", SyntaxKindUtils::SyntaxKind::DotToken},
    {"&", SyntaxKindUtils::SyntaxKind::AmpersandToken},
    {"&&", SyntaxKindUtils::SyntaxKind::AmpersandAmpersandToken},
    {"//", SyntaxKindUtils::SyntaxKind::SlashSlashToken},
    {"/", SyntaxKindUtils::SyntaxKind::SlashToken},
    {"||", SyntaxKindUtils::SyntaxKind::PipePipeToken},
    {"|", SyntaxKindUtils::SyntaxKind::PipeToken},
    {"=", SyntaxKindUtils::SyntaxKind::EqualsToken},
    {"==", SyntaxKindUtils::SyntaxKind::EqualsEqualsToken},
    {"!", SyntaxKindUtils::SyntaxKind::BangToken},
    {"!=", SyntaxKindUtils::SyntaxKind::BangEqualsToken},
    {"<", SyntaxKindUtils::SyntaxKind::LessToken},
    {"<-", SyntaxKindUtils::SyntaxKind::AssignmentToken},
    {"<=", SyntaxKindUtils::SyntaxKind::LessOrEqualsToken},
    {">", SyntaxKindUtils::SyntaxKind::GreaterToken},
    {">=", SyntaxKindUtils::SyntaxKind::GreaterOrEqualsToken},
    {"?", SyntaxKindUtils::SyntaxKind::QuestionToken}};