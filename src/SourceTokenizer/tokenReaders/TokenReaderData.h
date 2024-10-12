#pragma once

#include "../../syntax/SyntaxKindUtils.h"

#define __gl_FLOW_WING_KEYWORDS_SIZE 39
#define __gl_FLOW_WING_SYMBOLS_SIZE 33

struct TokenReaderState {
  std::string _tokenName;
  SyntaxKindUtils::SyntaxKind _tokenType;
};

extern const TokenReaderState
    __gl_FLOW_WING_KEYWORDS[__gl_FLOW_WING_KEYWORDS_SIZE];
extern const TokenReaderState
    __gl_FLOW_WING_SYMBOLS[__gl_FLOW_WING_SYMBOLS_SIZE];