/*
 * Flow-Wing Compiler
 * Copyright (C) 2023-2026 Kushagra Rathore
 */

#include "SourceFormatter.hpp"
#include "src/compiler/formatter/TokenSpacing.hpp"
#include "src/SourceTokenizer/TokenKind/TokenKind.h"
#include "src/syntax/CompilationUnitSyntax.h"
#include "src/syntax/NodeKind/NodeKind.h"
#include "src/syntax/SyntaxToken.h"
#include "src/syntax/expression/AssignmentExpressionSyntax/AssignmentExpressionSyntax.h"
#include "src/syntax/expression/BinaryExpressionSyntax/BinaryExpressionSyntax.h"
#include "src/syntax/expression/BooleanLiteralExpressionSyntax/BooleanLiteralExpressionSyntax.h"
#include "src/syntax/expression/BracketedExpressionSyntax/BracketedExpressionSyntax.h"
#include "src/syntax/expression/CallExpressionSyntax/CallExpressionSyntax.h"
#include "src/syntax/expression/CharacterLiteralExpressionSyntax/CharacterLiteralExpressionSyntax.h"
#include "src/syntax/expression/ColonExpressionSyntax/ColonExpressionSyntax.h"
#include "src/syntax/expression/ContainerExpressionSyntax/ContainerExpressionSyntax.h"
#include "src/syntax/expression/DeclaratorExpressionSyntax/DeclaratorExpressionSyntax.h"
#include "src/syntax/expression/DimensionClauseExpressionSyntax/DimensionClauseExpressionSyntax.h"
#include "src/syntax/expression/DoubleLiteralExpressionSyntax/DoubleLiteralExpressionSyntax.h"
#include "src/syntax/expression/ExpressionSyntax.h"
#include "src/syntax/expression/FieldDeclarationSyntax/FieldDeclarationSyntax.h"
#include "src/syntax/expression/FillExpressionSyntax/FillExpressionSyntax.h"
#include "src/syntax/expression/FloatLiteralExpressionSyntax/FloatLiteralExpressionSyntax.h"
#include "src/syntax/expression/FunctionReturnTypeExpressionSyntax/FunctionReturnTypeExpressionSyntax.h"
#include "src/syntax/expression/IdentifierExpressionSyntax/IdentifierExpressionSyntax.h"
#include "src/syntax/expression/IndexExpressionSyntax/IndexExpressionSyntax.h"
#include "src/syntax/expression/Int64LiteralExpressionSyntax/Int64LiteralExpressionSyntax.h"
#include "src/syntax/expression/IntegerLiteralExpressionSyntax/IntegerLiteralExpressionSyntax.h"
#include "src/syntax/expression/MemberAccessExpressionSyntax/MemberAccessExpressionSyntax.h"
#include "src/syntax/expression/ModuleAccessExpressionSyntax/ModuleAccessExpressionSyntax.h"
#include "src/syntax/expression/NewExpressionSyntax/NewExpressionSyntax.h"
#include "src/syntax/expression/NirastExpressionSyntax/NirastExpressionSyntax.h"
#include "src/syntax/expression/ObjectExpressionSyntax/ObjectExpressionSyntax.h"
#include "src/syntax/expression/ParenthesizedExpressionSyntax/ParenthesizedExpressionSyntax.h"
#include "src/syntax/expression/StringLiteralExpressionSyntax/StringLiteralExpressionSyntax.h"
#include "src/syntax/expression/TemplateStringLiteralExpressionSyntax/TemplateStringLiteralExpressionSyntax.h"
#include "src/syntax/expression/TernaryExpressionSyntax/TernaryExpressionSyntax.h"
#include "src/syntax/expression/TypeExpressionSyntax/ArrayTypeExpressionSyntax/ArrayTypeExpressionSyntax.h"
#include "src/syntax/expression/TypeExpressionSyntax/BoolTypeExpressionSyntax/BoolTypeExpressionSyntax.h"
#include "src/syntax/expression/TypeExpressionSyntax/CharTypeExpressionSyntax/CharTypeExpressionSyntax.h"
#include "src/syntax/expression/TypeExpressionSyntax/Deci32TypeExpressionSyntax/Deci32TypeExpressionSyntax.h"
#include "src/syntax/expression/TypeExpressionSyntax/DeciTypeExpressionSyntax/DeciTypeExpressionSyntax.h"
#include "src/syntax/expression/TypeExpressionSyntax/DynTypeExpressionSyntax/DynTypeExpressionSyntax.h"
#include "src/syntax/expression/TypeExpressionSyntax/FunctionTypeExpressionSyntax/FunctionTypeExpressionSyntax.h"
#include "src/syntax/expression/TypeExpressionSyntax/Int32TypeExpressionSyntax/Int32TypeExpressionSyntax.h"
#include "src/syntax/expression/TypeExpressionSyntax/Int64TypeExpressionSyntax/Int64TypeExpressionSyntax.h"
#include "src/syntax/expression/TypeExpressionSyntax/Int8TypeExpressionSyntax/Int8TypeExpressionSyntax.h"
#include "src/syntax/expression/TypeExpressionSyntax/ModuleAccessTypeExpressionSyntax/ModuleAccessTypeExpressionSyntax.h"
#include "src/syntax/expression/TypeExpressionSyntax/NthgTypeExpressionSyntax/NthgTypeExpressionSyntax.h"
#include "src/syntax/expression/TypeExpressionSyntax/ObjectTypeExpressionSyntax/ObjectTypeExpressionSyntax.h"
#include "src/syntax/expression/TypeExpressionSyntax/StrTypeExpressionSyntax/StrTypeExpressionSyntax.h"
#include "src/syntax/expression/UnaryExpressionSyntax/UnaryExpressionSyntax.h"
#include "src/syntax/statements/BlockStatementSyntax/BlockStatementSyntax.h"
#include "src/syntax/statements/BreakStatementSyntax/BreakStatementSyntax.h"
#include "src/syntax/statements/BringStatementSyntax/BringStatementSyntax.h"
#include "src/syntax/statements/CaseStatementSyntax/CaseStatementSyntax.h"
#include "src/syntax/statements/ClassStatementSyntax/ClassStatementSyntax.h"
#include "src/syntax/statements/ContinueStatementSyntax/ContinueStatementSyntax.h"
#include "src/syntax/statements/CustomTypeStatementSyntax/CustomTypeStatementSyntax.h"
#include "src/syntax/statements/DefaultCaseStatementSyntax/DefaultCaseStatementSyntax.h"
#include "src/syntax/statements/ElseClauseSyntax/ElseClauseSyntax.h"
#include "src/syntax/statements/ExposeStatementSyntax/ExposeStatementSyntax.h"
#include "src/syntax/statements/ExpressionStatementSyntax/ExpressionStatementSyntax.hpp"
#include "src/syntax/statements/ForStatementSyntax/ForStatementSyntax.h"
#include "src/syntax/statements/FunctionStatementSyntax/FunctionStatementSyntax.h"
#include "src/syntax/statements/IfStatementSyntax/IfStatementSyntax.h"
#include "src/syntax/statements/ModuleStatementSyntax/ModuleStatementSyntax.h"
#include "src/syntax/statements/OrIfStatementSyntax/OrIfStatementSyntax.h"
#include "src/syntax/statements/ParameterExpressionSyntax/ParameterExpressionSyntax.h"
#include "src/syntax/statements/ReturnStatementSyntax/ReturnStatementSyntax.h"
#include "src/syntax/statements/SwitchStatementSyntax/SwitchStatementSyntax.h"
#include "src/syntax/statements/VariableDeclarationSyntax/VariableDeclarationSyntax.h"
#include "src/syntax/statements/WhileStatementSyntax/WhileStatementSyntax.h"
#include "src/syntax/expression/SuperExpressionSyntax/SuperExpressionSyntax.h"
#include <cctype>
#include <cstddef>
#include <cstring>
#include <optional>

namespace flow_wing {
namespace compiler {
namespace format {

namespace {

struct DepthPush {
  int &ref;
  explicit DepthPush(int &r) : ref(r) { ++ref; }
  ~DepthPush() { --ref; }
  DepthPush(const DepthPush &) = delete;
  DepthPush &operator=(const DepthPush &) = delete;
};

/// Object/array literal bodies are parsed as left-associative `((a, b), c)`.
void collectCommaListParts(const syntax::ExpressionSyntax *root,
                           std::vector<const syntax::ExpressionSyntax *> *out) {
  if (root == nullptr) {
    return;
  }
  if (root->getKind() == syntax::NodeKind::kBinaryExpression) {
    const auto *b = static_cast<const syntax::BinaryExpressionSyntax *>(root);
    if (b->getOperatorToken() != nullptr &&
        b->getOperatorToken()->getTokenKind() == lexer::TokenKind::kCommaToken) {
      collectCommaListParts(b->getLeft().get(), out);
      collectCommaListParts(b->getRight().get(), out);
      return;
    }
  }
  out->push_back(root);
}

static bool
commaListAnyPartIsContainer(
    const std::vector<const syntax::ExpressionSyntax *> &parts) {
  for (const syntax::ExpressionSyntax *p : parts) {
    if (p && p->getKind() == syntax::NodeKind::kContainerExpression) {
      return true;
    }
  }
  return false;
}

static bool
commaListAnyPartIsObject(
    const std::vector<const syntax::ExpressionSyntax *> &parts) {
  for (const syntax::ExpressionSyntax *p : parts) {
    if (p && p->getKind() == syntax::NodeKind::kObjectExpression) {
      return true;
    }
  }
  return false;
}

/// True if this container literal would use multi-line (compact block) layout
/// when it is the outermost `[` in its initializer (ignores "extra" depth from a
/// wrapping `var arr = [ { ...` — see `ObjectExpression` reset).
static bool
arrayLiteralValueWouldUseBlockLayoutIfAtOuterDepth1(
    const syntax::ExpressionSyntax *e) {
  if (!e || e->getKind() != syntax::NodeKind::kContainerExpression) {
    return false;
  }
  const auto *ce = static_cast<const syntax::ContainerExpressionSyntax *>(e);
  const auto &ch = ce->getChildren();
  if (ch.size() < 2U || ch[1] == nullptr) {
    return false;
  }
  std::vector<const syntax::ExpressionSyntax *> cParts;
  collectCommaListParts(static_cast<const syntax::ExpressionSyntax *>(ch[1]),
                        &cParts);
  if (cParts.size() <= 1U) {
    return false;
  }
  return commaListAnyPartIsContainer(cParts) ||
         commaListAnyPartIsObject(cParts);
}

/// Object elements of `[ { ... } ]` that contain a 2D+ array in a field must
/// not use the one-line object form, or the expanded array breaks mid-line.
/// Object fields parse as `ColonExpression` (`a: value`); `FieldDeclaration` is
/// a separate construct for typed fields.
static bool
objectFieldListNeedsMultilineObjectLayout(
    const std::vector<const syntax::ExpressionSyntax *> &fieldParts) {
  for (const syntax::ExpressionSyntax *p : fieldParts) {
    if (!p) {
      continue;
    }
    const syntax::ExpressionSyntax *value = nullptr;
    if (p->getKind() == syntax::NodeKind::kColonExpression) {
      const auto *ce = static_cast<const syntax::ColonExpressionSyntax *>(p);
      const auto &v = ce->getRightExpression();
      value = v.get();
    } else if (p->getKind() ==
               syntax::NodeKind::kFieldDeclarationExpression) {
      const auto *fd =
          static_cast<const syntax::FieldDeclarationSyntax *>(p);
      const auto &v = fd->getValue();
      value = v.get();
    } else {
      continue;
    }
    if (value && arrayLiteralValueWouldUseBlockLayoutIfAtOuterDepth1(value)) {
      return true;
    }
  }
  return false;
}

} // namespace

static bool isIdChar(char c) {
  return (std::isalnum(static_cast<unsigned char>(c)) != 0) || c == '_';
}

static char outLastNonSpaceChar(const std::string &s) {
  size_t j = s.size();
  while (j > 0U) {
    const unsigned char c = static_cast<unsigned char>(s[j - 1U]);
    if (std::isspace(c) == 0) {
      return static_cast<char>(c);
    }
    --j;
  }
  return '\0';
}

// True when `n` is `}` and its leading trivia has a one-line // /; (or
// single-line /* */) comment that appears in source *before* the first newline
// in that trivia — i.e. it belongs on the same line as the last statement, not
// on its own line. Used to avoid inserting an extra `\\n` in visit(Block) which
// would break end-of-line comments stored as leading trivia of `}`.
static bool
closeBraceHasSameLineLineCommentInLeadingTrivia(const syntax::SyntaxNode *n) {
  if (!n || n->getKind() != syntax::NodeKind::kTokenNode)
    return false;
  const auto *tok = static_cast<const syntax::SyntaxToken *>(n);
  if (tok->getTokenKind() != lexer::TokenKind::kCloseBraceToken)
    return false;
  constexpr size_t kNo = static_cast<size_t>(-1);
  size_t firstEol = kNo;
  size_t firstLineC = kNo;
  const auto &lt = tok->getLeadingTrivia();
  for (size_t i = 0; i < lt.size(); ++i) {
    const auto *tr = lt[i].get();
    if (!tr)
      continue;
    const auto kk = tr->getTokenKind();
    if (kk == lexer::TokenKind::kEndOfLineToken && firstEol == kNo)
      firstEol = i;
    if (firstLineC == kNo) {
      if (kk == lexer::TokenKind::kSingleLineCommentToken)
        firstLineC = i;
      else if (kk == lexer::TokenKind::kMultiLineCommentToken &&
               tr->getText().find('\n') == std::string::npos)
        firstLineC = i;
    }
  }
  if (firstLineC == kNo)
    return false;
  if (firstEol == kNo)
    return true;
  return firstLineC < firstEol;
}

void SourceFormatter::appendBlockIndent() {
  m_buf.clearInterTokenSpace();
  m_buf.text.append(static_cast<size_t>(m_blockDepth) * kIndentSize, ' ');
}

bool SourceFormatter::controlKeywordWantsSpaceBeforeOpenParen() const {
  if (!m_lastEmittedToken)
    return false;
  switch (m_lastEmittedToken->getTokenKind()) {
  case lexer::TokenKind::kIfKeyword:
  case lexer::TokenKind::kWhileKeyword:
  case lexer::TokenKind::kForKeyword:
  case lexer::TokenKind::kSwitchKeyword:
  case lexer::TokenKind::kReturnKeyword:
    return true;
  default:
    return false;
  }
}

void SourceFormatter::spaceBefore(const syntax::SyntaxToken *t) {
  if (m_buf.text.empty() || m_buf.text.back() == '\n' || m_buf.text.back() == ' ')
    return;
  if (!t)
    return;
  if (t->getText().empty())
    return;
  const lexer::TokenKind k = t->getTokenKind();
  if (k == lexer::TokenKind::kCloseParenthesisToken ||
      k == lexer::TokenKind::kCloseBracketToken ||
      k == lexer::TokenKind::kCloseBraceToken)
    return;
  if (k == lexer::TokenKind::kDotToken)
    return;
  if (k == lexer::TokenKind::kCommaToken)
    return;
  if (k == lexer::TokenKind::kSemicolonToken)
    return;
  if (k == lexer::TokenKind::kColonColonToken)
    return;
  if (k == lexer::TokenKind::kColonToken) {
    if (m_lastEmittedToken &&
        m_lastEmittedToken->getTokenKind() == lexer::TokenKind::kReturnKeyword)
      return; // "return" + ":"  =>  return:
  }

  if (m_lastEmittedToken) {
    const std::optional<bool> o =
        getSpacingOverride(m_lastEmittedToken->getTokenKind(), k);
    if (o.has_value()) {
      if (o.value()) {
        m_buf.requestInterTokenSpace();
      }
      return;
    }
  }

  char f = t->getText().front();
  const char L = m_buf.text.back();
  if (k == lexer::TokenKind::kLeftArrowToken) {
    if (isIdChar(L) || L == ')' || L == ']' || L == '}' || L == '.' ||
        (L >= '0' && L <= '9') || L == '"')
      m_buf.requestInterTokenSpace();
    return;
  }
  if (L == '=' && m_lastEmittedToken) {
    const auto lk = m_lastEmittedToken->getTokenKind();
    if (lk == lexer::TokenKind::kEqualsToken ||
        lk == lexer::TokenKind::kEqualsEqualsToken ||
        lk == lexer::TokenKind::kBangEqualsToken ||
        lk == lexer::TokenKind::kLessOrEqualsToken ||
        lk == lexer::TokenKind::kGreaterOrEqualsToken) {
      if (isIdChar(f) || f == '"' || f == '\'' || f == '(' || f == '{' ||
          f == '[' || f == '-' || f == '!' || (f >= '0' && f <= '9'))
        m_buf.requestInterTokenSpace();
      return;
    }
  }
  if (L == '<') {
    if (isIdChar(f) || (f >= '0' && f <= '9') || f == '"' || f == '\'' ||
        f == '(')
      m_buf.requestInterTokenSpace();
    return;
  }
  if (L == '>') {
    if (m_lastEmittedToken &&
        m_lastEmittedToken->getTokenKind() == lexer::TokenKind::kRightArrowToken) {
      if (m_prevEmittedToken &&
          m_prevEmittedToken->getTokenKind() ==
              lexer::TokenKind::kCloseParenthesisToken) {
        if (isIdChar(f) || f == '(' || (f >= '0' && f <= '9') || f == '"' ||
            f == '\'')
          m_buf.requestInterTokenSpace();
        return; // `) ->` return type, space after `->`
      }
      return; // `a->` member, no space before field
    }
    if (isIdChar(f) || (f >= '0' && f <= '9') || f == '"' || f == '\'' ||
        f == '(')
      m_buf.requestInterTokenSpace();
    return;
  }
  // Space before `=`, `==`, `!=`, `<`, `>`, `<=`, `>=`
  if (k == lexer::TokenKind::kEqualsToken ||
      k == lexer::TokenKind::kEqualsEqualsToken ||
      k == lexer::TokenKind::kBangEqualsToken ||
      k == lexer::TokenKind::kLessToken ||
      k == lexer::TokenKind::kLessOrEqualsToken ||
      k == lexer::TokenKind::kGreaterToken ||
      k == lexer::TokenKind::kGreaterOrEqualsToken) {
    if (isIdChar(L) || L == ')' || L == ']' || L == '.')
      m_buf.requestInterTokenSpace();
    return;
  }
  // `&&` / `||` — first char is `&` or `|` so `isIdChar(f)` paths do not apply
  if (k == lexer::TokenKind::kAmpersandAmpersandToken ||
      k == lexer::TokenKind::kPipePipeToken) {
    if (isIdChar(L) || L == ')' || L == ']' || L == '>' || L == '<' ||
        (L >= '0' && L <= '9'))
      m_buf.requestInterTokenSpace();
    return;
  }
  if (k == lexer::TokenKind::kPlusToken || k == lexer::TokenKind::kMinusToken ||
      k == lexer::TokenKind::kStarToken || k == lexer::TokenKind::kSlashToken ||
      k == lexer::TokenKind::kPercentToken) {
    if (isIdChar(L) || L == ')' || L == ']' || L == '}' ||
        (L >= '0' && L <= '9'))
      m_buf.requestInterTokenSpace();
    return;
  }

  if (L == '(') {
    if (k == lexer::TokenKind::kOpenParenthesisToken)
      m_buf.requestInterTokenSpace();
    return;
  }
  if (L == '[') {
    // `[[1,2],[3,4]]` — no space between consecutive `[` (messy `a [0]` uses
    // trivia paths in emitLeadingTrivia).
    return;
  }
  if (L == '{') {
    if (k == lexer::TokenKind::kOpenBraceToken)
      m_buf.requestInterTokenSpace();
    return;
  }
  if (L == ',') {
    m_buf.requestInterTokenSpace();
    return;
  }
  if (L == '.')
    return;
  if (L == ':') {
    if (f == ':')
      return;
    // `raylib::Window` / `M::N` — do not add space after `::` (m_buf.text already
    // contains both `:` from kColonColonToken, so the last char is `:` and
    // the one before is also `:`).
    if (m_buf.text.size() >= 2 && m_buf.text[m_buf.text.size() - 2] == ':')
      return;
    m_buf.requestInterTokenSpace();
    return;
  }
  if (k == lexer::TokenKind::kRightArrowToken && m_lastEmittedToken &&
      m_lastEmittedToken->getTokenKind() ==
          lexer::TokenKind::kCloseParenthesisToken) {
    m_buf.requestInterTokenSpace();
    return; // ) ->
  }
  if (L == '>' && t->getTokenKind() == lexer::TokenKind::kOpenParenthesisToken)
    return;

  // `while!x` / `if!x` (no `(` after keyword) and `a!` after identifier — needs
  // a space (unary `!` is still the next token; operand spacing uses suppress).
  if (k == lexer::TokenKind::kBangToken) {
    if (isIdChar(L))
      m_buf.requestInterTokenSpace();
    return;
  }
  if (L == '}' && (k == lexer::TokenKind::kElseKeyword ||
                   k == lexer::TokenKind::kOrKeyword ||
                   k == lexer::TokenKind::kFromKeyword)) {
    m_buf.requestInterTokenSpace();
    return;
  }

  // K&R: `) {`, `] {`, `-> int {` — a single space before `{` when the header
  // and `{` are not already separated (leading trivia after `) -> int` may
  // be empty; after Allman EOL in trivia we may need this).
  if (t->getTokenKind() == lexer::TokenKind::kOpenBraceToken) {
    if (m_buf.text.empty() || m_buf.text.back() == ' ' || m_buf.text.back() == '\n' ||
        m_buf.text.back() == '\r' || m_buf.text.back() == '\t')
      return;
    m_buf.requestInterTokenSpace();
    return;
  }

  if (t->getTokenKind() == lexer::TokenKind::kOpenParenthesisToken) {
    if (controlKeywordWantsSpaceBeforeOpenParen()) {
      m_buf.requestInterTokenSpace();
      return;
    }
    if (isIdChar(L) || L == ')' || L == ']') {
      return; // f(
    }
  }

  if (isIdChar(L) && t->getTokenKind() == lexer::TokenKind::kOpenParenthesisToken)
    return; // f(

  if (isIdChar(L) && (isIdChar(f) || f == '"' || f == '\'')) {
    m_buf.requestInterTokenSpace();
    return;
  }
  if (L == ')' && (isIdChar(f) || f == '"'))
    m_buf.requestInterTokenSpace();

  if (strchr("+-*/%&|!><", L) != nullptr && (isIdChar(f) || f == '(')) {
    m_buf.requestInterTokenSpace();
  }
}

void SourceFormatter::emitLeadingTrivia(const syntax::SyntaxToken *t) {
  for (const auto &tr : t->getLeadingTrivia()) {
    if (!tr)
      continue;
    const lexer::TokenKind k = tr->getTokenKind();
    if (k == lexer::TokenKind::kWhitespaceToken) {
      if (t->getTokenKind() == lexer::TokenKind::kCommaToken) {
        while (!m_buf.text.empty() && m_buf.text.back() == ' ') {
          m_buf.text.pop_back();
        }
        continue; // `Type ,` / `, x` with stray space in trivia → `Type,`
      }
      if (t->getTokenKind() == lexer::TokenKind::kCloseParenthesisToken ||
          t->getTokenKind() == lexer::TokenKind::kCloseBracketToken) {
        while (!m_buf.text.empty() && m_buf.text.back() == ' ') {
          m_buf.text.pop_back();
        }
        continue; // `2 )` / `0 ]` from source trivia → `2)` / `0]`
      }
      if (t->getTokenKind() == lexer::TokenKind::kDotToken) {
        while (!m_buf.text.empty() && m_buf.text.back() == ' ') {
          m_buf.text.pop_back();
        }
        continue; // `self . n` in source trivia → `self.n` (tight member access)
      }
      if (t->getTokenKind() == lexer::TokenKind::kOpenParenthesisToken) {
        // `f ( x )` / `main (` → `f(x)`; keep `if (` / `for (`.
        const char Lb = outLastNonSpaceChar(m_buf.text);
        if (Lb != '\0' && isIdChar(Lb) &&
            !controlKeywordWantsSpaceBeforeOpenParen()) {
          while (!m_buf.text.empty() && m_buf.text.back() == ' ') {
            m_buf.text.pop_back();
          }
        }
        continue;
      }
      if (t->getTokenKind() == lexer::TokenKind::kOpenBracketToken) {
        // `= [1,2]` / array literal: keep the space the formatter (or `spaceBefore`)
        // put after `=`. Only tighten `a [0]` / `int [3]`-style spacing.
        if (!m_lastEmittedToken || m_lastEmittedToken->getTokenKind() !=
                                  lexer::TokenKind::kEqualsToken) {
          while (!m_buf.text.empty() && m_buf.text.back() == ' ') {
            m_buf.text.pop_back();
          }
        } else {
          // Trivia for `[` can skip the generic kWhitespace path below; ensure
          // `= [` (not `=[`) when `=` and `[` are separate tokens.
          m_buf.ensureSpaceIfNeeded();
        }
        continue; // `arr [0]` in source trivia → `arr[0]`
      }
      if (t->getTokenKind() == lexer::TokenKind::kColonToken &&
          m_tightTypeColonDepth > 0) {
        while (!m_buf.text.empty() && m_buf.text.back() == ' ') {
          m_buf.text.pop_back();
        }
        continue; // `a : int` in decl / param / field → `a: int`
      }
      if (!m_buf.text.empty() && m_buf.text.back() != '\n' && m_buf.text.back() != ' ') {
        const char b = m_buf.text.back();
        if (b == '(' || b == '[' || b == '{' || b == '.')
          continue; // no space after `.` for `a.b` (drop trivia before `b`)
        m_buf.text += ' ';
      }
      continue;
    }
    if (k == lexer::TokenKind::kEndOfLineToken) {
      // Allman "header\n{" — do not print the newline; K&R is `header {` on
      // the same line (space is added in spaceBefore for `{`).
      if (t->getTokenKind() == lexer::TokenKind::kOpenBraceToken)
        continue;
      // Closing `}`: the only line break before the brace is emitted by
      // visit(BlockStatement) after the last body statement. Leading EOLs on
      // `}` are source/layout trivia; if we also emit them, we get a blank
      // line between the last statement and `}`.
      if (t->getTokenKind() == lexer::TokenKind::kCloseBraceToken)
        continue;
      // `(expr\n` before `)` in source — do not end the line before `)`.
      if (t->getTokenKind() == lexer::TokenKind::kCloseParenthesisToken)
        continue;
      // K&R: `} else {`, `} or if` — source often has `else` / `or` on the
      // next line; drop that EOL so the chain stays on one line.
      if (t->getTokenKind() == lexer::TokenKind::kElseKeyword) {
        size_t j = m_buf.text.size();
        while (j > 0U && (m_buf.text[j - 1U] == ' ' || m_buf.text[j - 1U] == '\t')) {
          --j;
        }
        if (j > 0U && m_buf.text[j - 1U] == '}') {
          continue;
        }
      }
      if (t->getTokenKind() == lexer::TokenKind::kOrKeyword) {
        size_t j = m_buf.text.size();
        while (j > 0U && (m_buf.text[j - 1U] == ' ' || m_buf.text[j - 1U] == '\t')) {
          --j;
        }
        if (j > 0U && m_buf.text[j - 1U] == '}') {
          continue;
        }
      }
      if (t->getTokenKind() == lexer::TokenKind::kIfKeyword &&
          m_lastEmittedToken &&
          m_lastEmittedToken->getTokenKind() == lexer::TokenKind::kOrKeyword) {
        continue; // `or \n if` → `or if`
      }
      // Trivia EOLs after `expose` or `fun` would split a header across lines
      // (e.g. `expose` / `fun` / `name(`) — keep the signature on one line.
      if (t->getTokenKind() == lexer::TokenKind::kFunctionKeyword &&
          m_lastEmittedToken &&
          m_lastEmittedToken->getTokenKind() == lexer::TokenKind::kExposeKeyword) {
        continue;
      }
      if (t->getTokenKind() == lexer::TokenKind::kIdentifierToken &&
          m_lastEmittedToken &&
          m_lastEmittedToken->getTokenKind() ==
              lexer::TokenKind::kFunctionKeyword) {
        continue;
      }
      // `name\n(` / `call\n(` — keep identifier and `(` on one line (like
      // `fun name(` and `sumArray(`).
      if (t->getTokenKind() == lexer::TokenKind::kOpenParenthesisToken) {
        const char Lb = outLastNonSpaceChar(m_buf.text);
        if (Lb != '\0' && isIdChar(Lb)) {
          continue;
        }
      }
      if (t->getTokenKind() == lexer::TokenKind::kOpenBracketToken) {
        const char Lb = outLastNonSpaceChar(m_buf.text);
        if (Lb != '\0' && isIdChar(Lb)) {
          continue; // `arr\n[0]` → `arr[0]`
        }
      }
      // `)\n->` — one line before return type.
      if (t->getTokenKind() == lexer::TokenKind::kRightArrowToken &&
          outLastNonSpaceChar(m_buf.text) == ')') {
        continue;
      }
      // `->\ntype` after `) ->` — the `->` is one token; last emitted is that.
      if (m_lastEmittedToken &&
          m_lastEmittedToken->getTokenKind() == lexer::TokenKind::kRightArrowToken) {
        continue;
      }
      const int collapseDepth =
          m_collapseEolParenListDepth + m_collapseEolExpressionDepth;
      if (collapseDepth > 0) {
        // Skipped EOL; line breaks in trivia skip spaceBefore, so re-insert
        // the usual break between tokens.
        if (!m_buf.text.empty() && m_buf.text.back() == ',') {
          m_buf.text += ' ';
        } else if (m_buf.text.size() >= 2U && m_buf.text.back() == ':' &&
                   m_buf.text[m_buf.text.size() - 2U] != ':') {
          m_buf.text += ' '; // `r:\n type` in params → `r: type` (not `M::\nN`)
        } else if (m_lastEmittedToken &&
                   (m_lastEmittedToken->getTokenKind() ==
                        lexer::TokenKind::kVarKeyword ||
                    m_lastEmittedToken->getTokenKind() ==
                        lexer::TokenKind::kConstKeyword)) {
          // One space after `var` / `const` (multiple EOLs in trivia must not
          // stack spaces — `ensureSpaceIfNeeded` is idempotent).
          m_buf.ensureSpaceIfNeeded();
        }
        continue; // e.g. `f(\n  a, \n  b\n)` / `f(a,\n b)` from source
      }
      // Avoid `\\n\\n` when this EOL is redundant with a line break already
      // output (e.g. previous token’s trivia ended the line).
      if (m_buf.text.empty() || m_buf.text.back() != '\n')
        m_buf.text += '\n';
      continue;
    }
    if (k == lexer::TokenKind::kSingleLineCommentToken ||
        k == lexer::TokenKind::kMultiLineCommentToken) {
      const std::string &cText = tr->getText();
      const bool cOnePhysicalLine = cText.find('\n') == std::string::npos;
      // Standalone "full line" comment: m_buf.text is empty or last char is \n, then
      // block indent + comment + \n. End-of-line ("trailing") comment: lexer
      // attaches the comment as leading trivia to the *next* token, but it
      // belongs on the same line as the previous statement — m_buf.text has code and
      // does not end with \n. Emit space + comment + \n, no leading indent
      // before the comment.
      if (cOnePhysicalLine && !m_buf.text.empty() && m_buf.text.back() != '\n') {
        // Trivia can contribute multiple kWhitespaceToken runs; we normalize
        // them to a single space before the `/;` or // comment.
        while (!m_buf.text.empty() && m_buf.text.back() == ' ')
          m_buf.text.pop_back();
        if (!m_buf.text.empty() && m_buf.text.back() != '\n')
          m_buf.text += ' ';
        m_buf.text += cText;
        m_buf.text += '\n';
        continue;
      } else {
        if (!m_buf.text.empty() && m_buf.text.back() != '\n')
          m_buf.text += '\n';
        appendBlockIndent();
        m_buf.text += cText;
        m_buf.text += '\n';
        continue;
      }
    } else
      m_buf.text += tr->getText();
  }
}

void SourceFormatter::visitTokenCore(syntax::SyntaxToken *t) {
  if (!t)
    return;
  if (t->getTokenKind() == lexer::TokenKind::kEndOfFileToken)
    return;
  const bool skipInterTokenSpace = m_suppressSpaceBeforeNextToken;
  if (skipInterTokenSpace) {
    m_suppressSpaceBeforeNextToken = false;
    m_buf.clearInterTokenSpace();
  }
  if (t->getLeadingTrivia().empty()) {
    if (!skipInterTokenSpace) {
      spaceBefore(t);
    }
  } else {
    emitLeadingTrivia(t);
    if (!skipInterTokenSpace &&
        (t->getTokenKind() == lexer::TokenKind::kOpenBraceToken ||
         t->getTokenKind() == lexer::TokenKind::kOpenParenthesisToken ||
         t->getTokenKind() == lexer::TokenKind::kElseKeyword ||
         t->getTokenKind() == lexer::TokenKind::kOrKeyword ||
         t->getTokenKind() == lexer::TokenKind::kEqualsToken ||
         t->getTokenKind() == lexer::TokenKind::kLeftArrowToken ||
         t->getTokenKind() == lexer::TokenKind::kOpenBracketToken ||
         t->getTokenKind() == lexer::TokenKind::kIdentifierToken)) {
      // Leading trivia path skips spaceBefore; Allman EOL / `} \n else` EOL
      // (and dropped EOL before `(`) is handled in emitLeadingTrivia, so
      // insert the usual ` spaceBefore` for `{` and control-keyword `if (`;
      // decl `=` / `<-` with messy leading EOL/whitespace must still get spacing
      // around the operator.
      spaceBefore(t);
    }
  }
  if (m_buf.text.empty() || m_buf.text.back() == '\n')
    appendBlockIndent();
  m_buf.appendTokenLexeme(t->getText());
  m_prevEmittedToken = m_lastEmittedToken;
  m_lastEmittedToken = t;
}

void SourceFormatter::visit(syntax::SyntaxToken *node) { visitTokenCore(node); }

void SourceFormatter::visitChild(const syntax::SyntaxNode *node) {
  if (!node)
    return;
  if (node->getKind() == syntax::NodeKind::kTokenNode) {
    auto *tok = const_cast<syntax::SyntaxToken *>(
        static_cast<const syntax::SyntaxToken *>(node));
    if (tok->getTokenKind() == lexer::TokenKind::kEndOfFileToken)
      return;
    visitTokenCore(tok);
  } else
    const_cast<syntax::SyntaxNode *>(node)->accept(this);
}

void SourceFormatter::emitDefault(const syntax::SyntaxNode *node) {
  for (const auto *c : node->getChildren())
    visitChild(c);
}

void SourceFormatter::trimTrailingLineSpacesInPlace() {
  if (m_buf.text.find('\n') == std::string::npos) {
    while (!m_buf.text.empty() && (m_buf.text.back() == ' ' || m_buf.text.back() == '\t'))
      m_buf.text.pop_back();
    return;
  }
  size_t w = 0;
  size_t i = 0;
  const size_t n = m_buf.text.size();
  while (i < n) {
    const size_t lineStart = i;
    const size_t nl = m_buf.text.find('\n', i);
    if (nl == std::string::npos) {
      size_t e = n;
      while (e > lineStart && (m_buf.text[e - 1] == ' ' || m_buf.text[e - 1] == '\t'))
        --e;
      for (size_t j = lineStart; j < e; ++j)
        m_buf.text[w++] = m_buf.text[j];
      break;
    }
    size_t e = nl;
    while (e > lineStart && (m_buf.text[e - 1] == ' ' || m_buf.text[e - 1] == '\t'))
      --e;
    for (size_t j = lineStart; j < e; ++j)
      m_buf.text[w++] = m_buf.text[j];
    m_buf.text[w++] = '\n';
    i = nl + 1;
  }
  m_buf.text.resize(w);
}

void SourceFormatter::finishOutput() {
  if (m_buf.text.empty()) {
    m_buf.text = "\n";
    return;
  }
  if (m_buf.text.find('\n') == std::string::npos) {
    while (!m_buf.text.empty() &&
           (m_buf.text.back() == ' ' || m_buf.text.back() == '\t' || m_buf.text.back() == '\r'))
      m_buf.text.pop_back();
  } else
    trimTrailingLineSpacesInPlace();
  if (m_buf.text.empty() || m_buf.text.back() != '\n')
    m_buf.text += '\n';
}

std::string SourceFormatter::format(
    const std::unique_ptr<syntax::CompilationUnitSyntax> &root,
    std::size_t sourceLengthHint) {
  if (!root)
    return "\n";
  SourceFormatter f;
  if (sourceLengthHint)
    f.m_buf.text.reserve(sourceLengthHint);
  root->accept(&f);
  f.finishOutput();
  return std::move(f.m_buf.text);
}

void SourceFormatter::visit(syntax::CompilationUnitSyntax *node) {
  const auto &stmts = node->getStatements();
  for (size_t i = 0; i < stmts.size(); ++i) {
    if (stmts[i]) {
      stmts[i]->accept(this);
    }
    // When the next top-level item starts on the same line as the previous
    // one ended (e.g. `} start_game()` with no EOL in trivia), ensure a
    // break before the next statement. If the output already ends with `\\n`
    // (from trivia or prior formatting), skip — leading EOL on the next
    // token also skips adding a duplicate (emitLeadingTrivia).
    if (i + 1 < stmts.size() && stmts[i + 1]) {
      if (m_buf.text.empty() || m_buf.text.back() != '\n')
        m_buf.text += '\n';
    }
  }
}

void SourceFormatter::visit(syntax::BlockStatementSyntax *node) {
  const auto &ch = node->getChildren();
  if (ch.size() < 2) {
    emitDefault(node);
    return;
  }
  if (ch.size() == 2) {
    visitChild(ch[0]);
    // Empty `{}`: put `{` and `}` on separate lines; leading EOL on `}` is
    // skipped in emitLeadingTrivia, so we supply the break here.
    if (m_buf.text.empty() || m_buf.text.back() != '\n')
      m_buf.text += "\n";
    visitChild(ch[1]);
    return;
  }
  visitChild(ch[0]);
  m_buf.text += "\n";
  {
    DepthPush block(m_blockDepth);
    for (size_t i = 1; i + 1 < ch.size(); ++i) {
      visitChild(ch[i]);
      // A statement’s last token can already end the line (EOL in its trivia,
      // or a comment line); avoid a second `\\n` or we get a blank line before
      // the closing `}`.
      if (m_buf.text.empty() || m_buf.text.back() != '\n') {
        const bool nextIsCloseBrace = (i + 1 == ch.size() - 1);
        if (!nextIsCloseBrace ||
            !closeBraceHasSameLineLineCommentInLeadingTrivia(ch[i + 1]))
          m_buf.text += "\n";
      }
    }
  }
  appendBlockIndent();
  visitChild(ch.back());
}

void SourceFormatter::visit(syntax::ErrorExpressionSyntax *node) {
  for (const auto *s : node->getSkippedTokens()) {
    if (s)
      visitTokenCore(const_cast<syntax::SyntaxToken *>(s));
  }
}

void SourceFormatter::visit(syntax::IdentifierExpressionSyntax *node) {
  emitDefault(node);
}
void SourceFormatter::visit(syntax::ParameterExpressionSyntax *node) {
  for (const auto *c : node->getChildren()) {
    if (!c)
      continue;
    if (c->getKind() == syntax::NodeKind::kTokenNode) {
      const auto *tok = static_cast<const syntax::SyntaxToken *>(c);
      if (tok->getTokenKind() == lexer::TokenKind::kColonToken) {
        DepthPush tight(m_tightTypeColonDepth);
        visitChild(c);
        continue;
      }
    }
    visitChild(c);
  }
}
void SourceFormatter::visit(syntax::DimensionClauseExpressionSyntax *node) {
  emitDefault(node);
}
void SourceFormatter::visit(syntax::IntegerLiteralExpressionSyntax *node) {
  emitDefault(node);
}
void SourceFormatter::visit(syntax::Int64LiteralExpressionSyntax *node) {
  emitDefault(node);
}
void SourceFormatter::visit(syntax::AssignmentExpressionSyntax *node) {
  const auto &ch = node->getChildren();
  if (ch.empty()) {
    return;
  }
  // Join `lhs` / `=` / `rhs` that messy source split across lines (`t\n= {}`).
  DepthPush collapse(m_collapseEolExpressionDepth);
  for (const auto *c : ch) {
    if (c) {
      visitChild(c);
    }
  }
}
void SourceFormatter::visit(syntax::BooleanLiteralExpressionSyntax *node) {
  emitDefault(node);
}
void SourceFormatter::visit(syntax::BracketedExpressionSyntax *node) {
  emitDefault(node);
}
void SourceFormatter::visit(syntax::CallExpressionSyntax *node) {
  const auto &ch = node->getChildren();
  if (ch.size() < 3) {
    emitDefault(node);
    return;
  }
  if (ch[0])
    visitChild(ch[0]);
  // `callee\n(` in messy source can leave a newline in m_buf.text before `(`; join
  // `callee(` on one line.
  while (!m_buf.text.empty() &&
         (m_buf.text.back() == '\n' || m_buf.text.back() == '\r' || m_buf.text.back() == ' ' ||
          m_buf.text.back() == '\t')) {
    m_buf.text.pop_back();
  }
  if (ch[1])
    visitChild(ch[1]);
  {
    DepthPush args(m_collapseEolParenListDepth);
    for (size_t j = 2; j + 1 < ch.size(); ++j) {
      if (ch[j])
        visitChild(ch[j]);
    }
  }
  if (!ch.empty())
    visitChild(ch.back());
}
void SourceFormatter::visit(syntax::CharacterLiteralExpressionSyntax *node) {
  emitDefault(node);
}
void SourceFormatter::visit(syntax::ContainerExpressionSyntax *node) {
  const auto &ch = node->getChildren();
  if (ch.size() < 2) {
    emitDefault(node);
    return;
  }
  DepthPush nest(m_bracketArrayLiteralNesting);
  if (ch.size() == 2) {
    visitChild(ch[0]);
    visitChild(ch[1]);
    return;
  }
  if (ch[1] == nullptr) {
    visitChild(ch[0]);
    if (ch.size() > 1) {
      visitChild(ch.back());
    }
    return;
  }
  std::vector<const syntax::ExpressionSyntax *> parts;
  collectCommaListParts(static_cast<const syntax::ExpressionSyntax *>(ch[1]),
                          &parts);
  if (parts.size() <= 1) {
    visitChild(ch[0]);
    visitChild(ch[1]);
    visitChild(ch.back());
    return;
  }
  // Compact block: only the outermost array with nested `[` or array of
  // objects — keep inner rows / small object literals on one line when
  // `Container` / `Object` elements are compact.
  const bool useBlockStyle =
      m_bracketArrayLiteralNesting == 1 &&
      (commaListAnyPartIsContainer(parts) || commaListAnyPartIsObject(parts));
  if (!useBlockStyle) {
    visitChild(ch[0]);
    visitChild(ch[1]);
    visitChild(ch.back());
    return;
  }
  visitChild(ch[0]);
  m_buf.text += "\n";
  {
    DepthPush block(m_blockDepth);
    for (size_t i = 0; i < parts.size(); ++i) {
      if (i) {
        m_buf.text += ",\n";
      }
      visitChild(static_cast<const syntax::SyntaxNode *>(parts[i]));
    }
  }
  if (m_buf.text.empty() || m_buf.text.back() != '\n') {
    m_buf.text += "\n";
  }
  appendBlockIndent();
  visitChild(ch.back());
}
void SourceFormatter::visit(syntax::DeclaratorExpressionSyntax *node) {
  const auto &ch = node->getChildren();
  if (ch.size() < 2) {
    emitDefault(node);
    return;
  }
  visitChild(ch[0]);
  {
    DepthPush tight(m_tightTypeColonDepth);
    visitChild(ch[1]);
  }
  for (size_t i = 2; i < ch.size(); ++i) {
    if (ch[i])
      visitChild(ch[i]);
  }
}
void SourceFormatter::visit(syntax::DoubleLiteralExpressionSyntax *node) {
  emitDefault(node);
}
void SourceFormatter::visit(syntax::FieldDeclarationSyntax *node) {
  const auto &ch = node->getChildren();
  if (ch.size() < 2) {
    emitDefault(node);
    return;
  }
  // Join `a:` and `int` when source puts the type on the next line.
  DepthPush collapse(m_collapseEolExpressionDepth);
  visitChild(ch[0]);
  {
    DepthPush tight(m_tightTypeColonDepth);
    visitChild(ch[1]);
  }
  for (size_t i = 2; i < ch.size(); ++i) {
    if (ch[i])
      visitChild(ch[i]);
  }
}
void SourceFormatter::visit(syntax::FillExpressionSyntax *node) {
  emitDefault(node);
}
void SourceFormatter::visit(syntax::FloatLiteralExpressionSyntax *node) {
  emitDefault(node);
}
void SourceFormatter::visit(syntax::FunctionReturnTypeExpressionSyntax *node) {
  emitDefault(node);
}
void SourceFormatter::visit(syntax::IndexExpressionSyntax *node) {
  emitDefault(node);
}
void SourceFormatter::visit(syntax::MemberAccessExpressionSyntax *node) {
  emitDefault(node);
}
void SourceFormatter::visit(syntax::ModuleAccessExpressionSyntax *node) {
  emitDefault(node);
}
void SourceFormatter::visit(syntax::NewExpressionSyntax *node) {
  emitDefault(node);
}
void SourceFormatter::visit(syntax::NirastExpressionSyntax *node) {
  emitDefault(node);
}
void SourceFormatter::visit(syntax::SuperExpressionSyntax *node) {
  emitDefault(node);
}
void SourceFormatter::visit(syntax::ObjectExpressionSyntax *node) {
  const auto &ch = node->getChildren();
  if (ch.size() < 3) {
    emitDefault(node);
    return;
  }
  visitChild(ch[0]);
  if (ch[1] == nullptr) {
    visitChild(ch[2]);
    return;
  }
  std::vector<const syntax::ExpressionSyntax *> parts;
  collectCommaListParts(static_cast<const syntax::ExpressionSyntax *>(ch[1]),
                          &parts);
  if (parts.size() <= 1) {
    const int saveB = m_bracketArrayLiteralNesting;
    if (m_bracketArrayLiteralNesting == 1) {
      m_bracketArrayLiteralNesting = 0;
    }
    if (ch[1]) {
      visitChild(ch[1]);
    }
    m_bracketArrayLiteralNesting = saveB;
    visitChild(ch[2]);
    return;
  }
  // Direct elements of a block-style `[` … `]` (see `m_bracketArrayLiteralNesting`):
  // small struct literals on one line; otherwise multiline with field bodies
  // un-indented for array layout (reset depth so `b: [[…],[…]]` is not forced
  // to stay one long line because of the wrapping `var arr = [` depth).
  const bool inBlockStyleArray = (m_bracketArrayLiteralNesting == 1);
  const bool oneLineObjectInArray =
      inBlockStyleArray && !objectFieldListNeedsMultilineObjectLayout(parts);
  if (oneLineObjectInArray) {
    const int saveB = m_bracketArrayLiteralNesting;
    m_bracketArrayLiteralNesting = 0;
    m_buf.requestInterTokenSpace();
    for (size_t i = 0; i < parts.size(); ++i) {
      if (i) {
        m_buf.text += ", ";
        m_buf.clearInterTokenSpace();
      }
      visitChild(static_cast<const syntax::SyntaxNode *>(parts[i]));
    }
    m_bracketArrayLiteralNesting = saveB;
    m_buf.ensureSpaceIfNeeded();
    visitChild(ch[2]);
    return;
  }
  const int saveB = m_bracketArrayLiteralNesting;
  if (m_bracketArrayLiteralNesting == 1) {
    m_bracketArrayLiteralNesting = 0;
  }
  m_buf.text += "\n";
  {
    DepthPush block(m_blockDepth);
    for (size_t i = 0; i < parts.size(); ++i) {
      if (i) {
        m_buf.text += ",\n";
      }
      visitChild(static_cast<const syntax::SyntaxNode *>(parts[i]));
    }
  }
  m_bracketArrayLiteralNesting = saveB;
  if (m_buf.text.empty() || m_buf.text.back() != '\n') {
    m_buf.text += "\n";
  }
  appendBlockIndent();
  visitChild(ch[2]);
}
void SourceFormatter::visit(syntax::ColonExpressionSyntax *node) {
  emitDefault(node);
}
void SourceFormatter::visit(syntax::ParenthesizedExpressionSyntax *node) {
  emitDefault(node);
}
void SourceFormatter::visit(syntax::StringLiteralExpressionSyntax *node) {
  emitDefault(node);
}
void SourceFormatter::visit(syntax::TemplateStringLiteralExpressionSyntax *node) {
  emitDefault(node);
}
void SourceFormatter::visit(syntax::TernaryExpressionSyntax *node) {
  // Document order: condition, `?`, then-branch, `:`, else-branch. emitDefault
  // would glue `1?1:0` because `?` / ternary `:` are not special-cased in
  // spaceBefore; normalize to `a ? b : c`.
  const auto &ch = node->getChildren();
  if (ch.size() != 5) {
    emitDefault(node);
    return;
  }
  visitChild(ch[0]);
  m_buf.ensureSpaceIfNeeded();
  visitChild(ch[1]);
  m_buf.ensureSpaceIfNeeded();
  visitChild(ch[2]);
  m_buf.ensureSpaceIfNeeded();
  visitChild(ch[3]);
  visitChild(ch[4]);
}
void SourceFormatter::visit(syntax::BinaryExpressionSyntax *node) {
  emitDefault(node);
}
void SourceFormatter::visit(syntax::ArrayTypeExpressionSyntax *node) {
  emitDefault(node);
}
void SourceFormatter::visit(syntax::BoolTypeExpressionSyntax *node) {
  emitDefault(node);
}
void SourceFormatter::visit(syntax::CharTypeExpressionSyntax *node) {
  emitDefault(node);
}
void SourceFormatter::visit(syntax::Deci32TypeExpressionSyntax *node) {
  emitDefault(node);
}
void SourceFormatter::visit(syntax::DeciTypeExpressionSyntax *node) {
  emitDefault(node);
}
void SourceFormatter::visit(syntax::FunctionTypeExpressionSyntax *node) {
  emitDefault(node);
}
void SourceFormatter::visit(syntax::Int8TypeExpressionSyntax *node) {
  emitDefault(node);
}
void SourceFormatter::visit(syntax::DynTypeExpressionSyntax *node) {
  emitDefault(node);
}
void SourceFormatter::visit(syntax::Int32TypeExpressionSyntax *node) {
  emitDefault(node);
}
void SourceFormatter::visit(syntax::Int64TypeExpressionSyntax *node) {
  emitDefault(node);
}
void SourceFormatter::visit(syntax::ModuleAccessTypeExpressionSyntax *node) {
  emitDefault(node);
}
void SourceFormatter::visit(syntax::NthgTypeExpressionSyntax *node) {
  emitDefault(node);
}
void SourceFormatter::visit(syntax::ObjectTypeExpressionSyntax *node) {
  emitDefault(node);
}
void SourceFormatter::visit(syntax::StrTypeExpressionSyntax *node) {
  emitDefault(node);
}
void SourceFormatter::visit(syntax::UnaryExpressionSyntax *node) {
  if (const auto *op = node->getOperatorToken()) {
    visitChild(op);
  }
  const auto ok = node->getOperatorTokenKind();
  if (ok == lexer::TokenKind::kMinusToken ||
      ok == lexer::TokenKind::kPlusToken ||
      ok == lexer::TokenKind::kBangToken) {
    m_suppressSpaceBeforeNextToken = true;
  }
  if (node->getExpression()) {
    node->getExpression()->accept(this);
  }
}
void SourceFormatter::visit(syntax::ExposeStatementSyntax *node) {
  emitDefault(node);
}
void SourceFormatter::visit(syntax::ExpressionStatementSyntax *node) {
  emitDefault(node);
}
void SourceFormatter::visit(syntax::FunctionStatementSyntax *node) {
  const auto &ch = node->getChildren();
  if (ch.size() < 3) {
    emitDefault(node);
    return;
  }
  for (size_t i = 0; i < 3; ++i) {
    if (ch[i])
      visitChild(ch[i]);
  }
  size_t i = 3;
  {
    DepthPush params(m_collapseEolParenListDepth);
    for (; i < ch.size(); ++i) {
      const auto *c = ch[i];
      if (!c)
        continue;
      if (c->getKind() == syntax::NodeKind::kTokenNode) {
        const auto *tok = static_cast<const syntax::SyntaxToken *>(c);
        if (tok->getTokenKind() == lexer::TokenKind::kCloseParenthesisToken) {
          visitChild(c);
          ++i;
          break;
        }
      }
      visitChild(c);
    }
  }
  for (; i < ch.size(); ++i) {
    if (ch[i])
      visitChild(ch[i]);
  }
}
void SourceFormatter::visit(syntax::BreakStatementSyntax *node) {
  emitDefault(node);
}
void SourceFormatter::visit(syntax::BringStatementSyntax *node) {
  // getChildren() omits `,` between braced names; insert them explicitly.
  const auto &ch = node->getChildren();
  const size_t nId = node->getIdentifierExpressions().size();
  size_t idx = 0;
  for (const auto *c : ch) {
    if (idx > 2 && idx < 2 + nId)
      m_buf.text += ", ";
    if (c)
      visitChild(c);
    ++idx;
  }
}
void SourceFormatter::visit(syntax::CaseStatementSyntax *node) {
  emitDefault(node);
}
void SourceFormatter::visit(syntax::ClassStatementSyntax *node) {
  const auto &ch = node->getChildren();
  if (ch.size() < 2) {
    emitDefault(node);
    return;
  }
  size_t openI = 0, closeI = 0;
  bool foundOpen = false, foundClose = false;
  for (size_t i = 0; i < ch.size(); ++i) {
    if (!ch[i] || ch[i]->getKind() != syntax::NodeKind::kTokenNode)
      continue;
    const auto *tok = static_cast<const syntax::SyntaxToken *>(ch[i]);
    if (tok->getTokenKind() == lexer::TokenKind::kOpenBraceToken) {
      openI = i;
      foundOpen = true;
    }
    if (tok->getTokenKind() == lexer::TokenKind::kCloseBraceToken) {
      closeI = i;
      foundClose = true;
    }
  }
  if (!foundOpen || !foundClose || openI + 1 > closeI) {
    emitDefault(node);
    return;
  }
  for (size_t i = 0; i <= openI; ++i) {
    if (ch[i])
      visitChild(ch[i]);
  }
  m_buf.text += "\n";
  {
    DepthPush block(m_blockDepth);
    for (size_t i = openI + 1; i < closeI; ++i) {
      if (ch[i]) {
        visitChild(ch[i]);
      }
      if (m_buf.text.empty() || m_buf.text.back() != '\n')
        m_buf.text += "\n";
    }
  }
  appendBlockIndent();
  if (ch[closeI])
    visitChild(ch[closeI]);
}
void SourceFormatter::visit(syntax::ContinueStatementSyntax *node) {
  emitDefault(node);
}
void SourceFormatter::visit(syntax::CustomTypeStatementSyntax *node) {
  const auto &ch = node->getChildren();
  if (ch.size() < 2) {
    emitDefault(node);
    return;
  }
  size_t openI = 0, closeI = 0;
  bool foundOpen = false, foundClose = false;
  for (size_t i = 0; i < ch.size(); ++i) {
    if (!ch[i] || ch[i]->getKind() != syntax::NodeKind::kTokenNode) {
      continue;
    }
    const auto *tok = static_cast<const syntax::SyntaxToken *>(ch[i]);
    if (tok->getTokenKind() == lexer::TokenKind::kOpenBraceToken) {
      openI = i;
      foundOpen = true;
    }
    if (tok->getTokenKind() == lexer::TokenKind::kCloseBraceToken) {
      closeI = i;
      foundClose = true;
    }
  }
  if (!foundOpen || !foundClose || openI + 1 > closeI) {
    emitDefault(node);
    return;
  }
  for (size_t i = 0; i <= openI; ++i) {
    if (ch[i]) {
      visitChild(ch[i]);
    }
  }
  m_buf.text += "\n";
  {
    DepthPush block(m_blockDepth);
    for (size_t i = openI + 1; i < closeI; ++i) {
      if (ch[i]) {
        visitChild(ch[i]);
      }
      if (m_buf.text.empty() || m_buf.text.back() != '\n') {
        m_buf.text += "\n";
      }
    }
  }
  appendBlockIndent();
  if (ch[closeI]) {
    visitChild(ch[closeI]);
  }
}
void SourceFormatter::visit(syntax::DefaultCaseStatementSyntax *node) {
  emitDefault(node);
}
void SourceFormatter::visit(syntax::ElseClauseSyntax *node) {
  emitDefault(node);
}
void SourceFormatter::visit(syntax::ForStatementSyntax *node) {
  emitDefault(node);
}
void SourceFormatter::visit(syntax::IfStatementSyntax *node) {
  emitDefault(node);
}
void SourceFormatter::visit(syntax::ModuleStatementSyntax *node) {
  const auto &ch = node->getChildren();
  for (size_t i = 0; i < ch.size(); ++i) {
    const auto *c = ch[i];
    if (!c) {
      continue;
    }
    if (c->getKind() == syntax::NodeKind::kTokenNode) {
      const auto *tok = static_cast<const syntax::SyntaxToken *>(c);
      if (tok->getTokenKind() == lexer::TokenKind::kEndOfFileToken) {
        continue;
      }
    }
    visitChild(c);
  }
}
void SourceFormatter::visit(syntax::OrIfStatementSyntax *node) {
  emitDefault(node);
}
void SourceFormatter::visit(syntax::ReturnStatementSyntax *node) {
  const auto &ch = node->getChildren();
  const auto *expr = static_cast<const syntax::SyntaxNode *>(
      node->getReturnExpression().get());
  for (const auto *c : ch) {
    if (!c)
      continue;
    if (c == expr) {
      DepthPush retExpr(m_collapseEolExpressionDepth);
      visitChild(c);
    } else {
      visitChild(c);
    }
  }
}
void SourceFormatter::visit(syntax::SwitchStatementSyntax *node) {
  const auto &ch = node->getChildren();
  if (ch.size() < 3) {
    emitDefault(node);
    return;
  }
  // `switch` … `{`  —  cases are *not* wrapped in a BlockStatementSyntax, so
  // emitDefault would never bump m_blockDepth; case lines align with `switch`.
  for (size_t i = 0; i < 3; ++i) {
    if (ch[i])
      visitChild(ch[i]);
  }
  if (m_buf.text.empty() || m_buf.text.back() != '\n')
    m_buf.text += "\n";
  {
    DepthPush cases(m_blockDepth);
    for (size_t i = 3; i + 1 < ch.size(); ++i) {
      if (ch[i])
        visitChild(ch[i]);
      if (m_buf.text.empty() || m_buf.text.back() != '\n') {
        const bool lastCase = (i + 1 == ch.size() - 1);
        if (!lastCase ||
            !closeBraceHasSameLineLineCommentInLeadingTrivia(ch[i + 1]))
          m_buf.text += "\n";
      }
    }
  }
  appendBlockIndent();
  if (ch.size() > 3)
    visitChild(ch.back());
}
void SourceFormatter::visit(syntax::VariableDeclarationSyntax *node) {
  const auto &ch = node->getChildren();
  // Bump collapse depth *after* emitting const/var so leading trivia of that
  // token (e.g. newlines after `module[m]` before a top-level `var`) is not
  // collapsed. EOLs *after* the keyword attach to the next token and collapse.
  std::optional<DepthPush> afterConstOrVar;
  for (const auto *c : ch) {
    if (!c)
      continue;
    if (c->getKind() == syntax::NodeKind::kTokenNode) {
      const auto *t = static_cast<const syntax::SyntaxToken *>(c);
      if (t->getTokenKind() == lexer::TokenKind::kConstKeyword) {
        visitChild(c);
        if (!afterConstOrVar.has_value())
          afterConstOrVar.emplace(m_collapseEolExpressionDepth);
        continue;
      }
      if (t->getTokenKind() == lexer::TokenKind::kVarKeyword) {
        visitChild(c);
        if (!afterConstOrVar.has_value())
          afterConstOrVar.emplace(m_collapseEolExpressionDepth);
        continue;
      }
    }
    visitChild(c);
  }
}
void SourceFormatter::visit(syntax::WhileStatementSyntax *node) {
  emitDefault(node);
}

} // namespace format
} // namespace compiler
} // namespace flow_wing
