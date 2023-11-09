#ifndef FLOWWING_IR_CONSTANTS_H
#define FLOWWING_IR_CONSTANTS_H

#include <string>

namespace FLOWWING::IR::CONSTANTS {

// FlowWing Global Strings

extern const std::string FLOWWING_CONTINUE_COUNT;
extern const std::string FLOWWING_BREAK_COUNT;
extern const std::string FLOWWING_GLOBAL_RETURN_COUNT;

// For Error

extern const std::string FLOWWING_GLOBAL_ERROR_COUNT;

// NULL

extern const std::string FLOWWING_GLOBAL_NULL;

// TRUE AND FALSE KEYWORDS
extern const std::string FLOWWING_GLOBAL_TRUE;
extern const std::string FLOWWING_GLOBAL_FALSE;

// Entry Point

extern const std::string FLOWWING_GLOBAL_ENTRY_POINT;

enum ENVIRONMENT { REPL, SOURCE_FILE };

namespace INNERS {
namespace FUNCTIONS {

extern const std::string PRINT;
extern const std::string CONCAT_STRINGS;
extern const std::string STRING_LENGTH;
extern const std::string ITOS;
extern const std::string DTOS;
extern const std::string GET_MALLOC_PTR_OF_STRING_CONSTANT;
extern const std::string GET_MALLOC_PTR_OF_INT_CONSTANT;
extern const std::string COMPARE_STRINGS;
extern const std::string LESS_THAN_STRINGS;
extern const std::string LESS_THAN_OR_EQUAL_STRINGS;
extern const std::string GREATER_THAN_STRINGS;
extern const std::string GREATER_THAN_OR_EQUAL_STRINGS;
extern const std::string EQUAL_STRINGS;
extern const std::string GET_INPUT;
extern const std::string STRING_TO_INT;
extern const std::string STRING_TO_LONG;
extern const std::string STRING_TO_DOUBLE;
}; // namespace FUNCTIONS
}; // namespace INNERS

enum class CustomLLVMType {
  Int8,
  Int16,
  Int32,
  Int64,
  Float,
  Double,
  Bool,
  String,
  Void,
  Unknown
};

}; // namespace FLOWWING::IR::CONSTANTS

#endif // FLOWWING_IR_CONSTANTS_H