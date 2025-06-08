#ifndef FLOWWING_IR_CONSTANTS_H
#define FLOWWING_IR_CONSTANTS_H

#include "../../utils/FlowWingConfig.h"
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
extern const std::string TEMP_OBJECT_FILES_DIR;
extern const std::string TEMP_BC_FILES_DIR;
extern const std::string TEMP_BIN_DIR;
extern const std::string OBJECT_FILE_EXTENSION;
enum ENVIRONMENT { REPL, SOURCE_FILE };

namespace DYNAMIC_VALUE {
namespace TYPE {
extern const std::string TYPE_INT32;
extern const std::string TYPE_INT64;
extern const std::string TYPE_FLOAT32;
extern const std::string TYPE_FLOAT64;
extern const std::string TYPE_STRING;
extern const std::string TYPE_BOOLEAN;

// Dynamic Value Initial Values

enum VALUE_TYPE { INT8, INT32, INT64, FLOAT32, FLOAT64, STRING, BOOLEAN };

// Dynamic Value Type Name
extern const std::string DYNAMIC_VALUE_TYPE;
} // namespace TYPE
} // namespace DYNAMIC_VALUE

namespace INNERS {
namespace FUNCTIONS {

extern const std::string PRINT;
extern const std::string PRINT_F;
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
extern const std::string RAISE_EXCEPTION;
extern const std::string MALLOC;
extern const std::string PUT_CHAR;
extern const std::string GC_MALLOC;

}; // namespace FUNCTIONS
}; // namespace INNERS

extern const std::string IS_EXISTS;

}; // namespace FLOWWING::IR::CONSTANTS

#endif // FLOWWING_IR_CONSTANTS_H