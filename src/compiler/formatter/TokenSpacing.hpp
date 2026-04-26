/*
 * Flow-Wing Compiler
 * Copyright (C) 2023-2026 Kushagra Rathore
 *
 * Declarative (left, right) token spacing overrides for the imperative formatter.
 * `std::nullopt` means: fall back to the rest of `SourceFormatter::spaceBefore`.
 * `true` / `false` means: require or forbid a space before `right` (after `left`
 * is already emitted).
 */
 #pragma once

 #include "src/SourceTokenizer/TokenKind/TokenKind.h"
 #include <optional>
 
 namespace flow_wing {
 namespace compiler {
 namespace format {
 
 inline std::optional<bool>
 getSpacingOverride(lexer::TokenKind left, lexer::TokenKind right) {
   using TK = lexer::TokenKind;
 
   // Group by `right` token first to create a fast jump table
   switch (right) {
   case TK::kOpenParenthesisToken:
     switch (left) {
     case TK::kIfKeyword:
     case TK::kWhileKeyword:
     case TK::kForKeyword:
     case TK::kSwitchKeyword:
     case TK::kReturnKeyword:
       return true; // Space before '(' for control flow
     case TK::kIdentifierToken:
       return false; // No space for function calls: `foo(`
     default:
       return std::nullopt;
     }
 
   case TK::kIdentifierToken:
     switch (left) {
     case TK::kVarKeyword:
     case TK::kConstKeyword:
     case TK::kFunctionKeyword:
       return true; // Space between decl keyword and identifier
     default:
       return std::nullopt;
     }
 
   default:
     // All other combinations (including punctuation, closing braces, 
     // and relational operators) implicitly fall through to nullopt.
     return std::nullopt;
   }
 }
 
 } // namespace format
 } // namespace compiler
 } // namespace flow_wing