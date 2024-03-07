#include "FlowWingIRConstants.h"

namespace FLOWWING::IR::CONSTANTS {

const std::string FLOWWING_CONTINUE_COUNT = "FLOWWING_CONTINUE_COUNT";
const std::string FLOWWING_BREAK_COUNT = "FLOWWING_BREAK_COUNT";
const std::string FLOWWING_GLOBAL_RETURN_COUNT = "FLOWWING_GLOBAL_RETURN_COUNT";

// For Error

const std::string FLOWWING_GLOBAL_ERROR_COUNT = "FLOWWING_GLOBAL_ERROR_COUNT";

// NULL

const std::string FLOWWING_GLOBAL_NULL = "FLOWWING_GLOBAL_NULL";

// TRUE AND FALSE KEYWORDS
const std::string FLOWWING_GLOBAL_TRUE = "FLOWWING_GLOBAL_TRUE";
const std::string FLOWWING_GLOBAL_FALSE = "FLOWWING_GLOBAL_FALSE";

// Entry Point
const std::string FLOWWING_GLOBAL_ENTRY_POINT = "main";

namespace INNERS {
namespace FUNCTIONS {

const std::string PRINT = "print";
const std::string CONCAT_STRINGS = "concat_strings";
const std::string STRING_LENGTH = "string_length";
const std::string ITOS = "itos";
const std::string DTOS = "dtos";
const std::string GET_MALLOC_PTR_OF_STRING_CONSTANT =
    "get_malloc_ptr_of_string_constant";
const std::string GET_MALLOC_PTR_OF_INT_CONSTANT =
    "get_malloc_ptr_of_int_constant";
const std::string COMPARE_STRINGS = "compare_strings";
const std::string LESS_THAN_STRINGS = "less_than_strings";
const std::string LESS_THAN_OR_EQUAL_STRINGS = "less_than_or_equal_strings";
const std::string GREATER_THAN_STRINGS = "greater_than_strings";
const std::string GREATER_THAN_OR_EQUAL_STRINGS =
    "greater_than_or_equal_strings";
const std::string EQUAL_STRINGS = "equal_strings";
const std::string GET_INPUT = "get_input";
const std::string STRING_TO_INT = "string_to_int";
const std::string STRING_TO_LONG = "string_to_long";
const std::string STRING_TO_DOUBLE = "string_to_double";
const std::string RAISE_EXCEPTION = "raise_exception";

}; // namespace FUNCTIONS
}; // namespace INNERS

const std::string IS_EXISTS = "is_exists";

}; // namespace FLOWWING::IR::CONSTANTS