#ifndef ELANG_IR_CONSTANTS_H
#define ELANG_IR_CONSTANTS_H

#include <string>

namespace ELANG::EVALUATOR::CONSTANTS {

// Elang Global Strings

extern const std::string ELANG_CONTINUE_COUNT;
extern const std::string ELANG_BREAK_COUNT;
extern const std::string ELANG_GLOBAL_ZERO;
extern const std::string ELANG_GLOBAL_RETURN_COUNT;

// For Error

extern const std::string ELANG_GLOBAL_ERROR;

// NULL

extern const std::string ELANG_GLOBAL_NULL;

// TRUE AND FALSE KEYWORDS
extern const std::string ELANG_GLOBAL_TRUE;
extern const std::string ELANG_GLOBAL_FALSE;

enum ENVIRONMENT { REPL, SOURCE_FILE };

}; // namespace ELANG::EVALUATOR::CONSTANTS

#endif // ELANG_IR_CONSTANTS_H