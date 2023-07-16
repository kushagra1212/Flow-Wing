#ifndef UTILS_H
#define UTILS_H
#include "../syntax/SyntaxNode.h"
#include "../syntax/expression/LiteralExpressionSyntax.h"
#include "Common.h"
namespace Utils {
void prettyPrint(SyntaxNode *node, std::string indent = "", bool isLast = true);
std::string getLineNumberAndPosition(SyntaxToken<std::any> *token);
} // namespace Utils

#endif // UTILS_H