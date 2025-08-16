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

#include "FlowWingIRConstants.h"
#include <string>

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

#if defined(__linux__)
const std::string FLOWWING_GLOBAL_ENTRY_POINT = "main";
#elif defined(__APPLE__)
const std::string FLOWWING_GLOBAL_ENTRY_POINT = "flowmain";
#else
const std::string FLOWWING_GLOBAL_ENTRY_POINT = "main";
#endif

#if defined(_WIN32)
const std::string TEMP_BIN_DIR = "build\\bin\\";
const std::string TEMP_OBJECT_FILES_DIR = "build\\objects\\";
const std::string OBJECT_FILE_EXTENSION = ".obj";
const std::string TEMP_BC_FILES_DIR = "flowwing\\bc\\";
#else
const std::string TEMP_OBJECT_FILES_DIR = "build/objects/";
const std::string TEMP_BIN_DIR = "build/bin/";
const std::string OBJECT_FILE_EXTENSION = ".o";
const std::string TEMP_BC_FILES_DIR = "temp/bc/";
#endif

namespace DYNAMIC_VALUE {
namespace TYPE {

const std::string TYPE_INT8 = "FG_TYPE_INT8";
const std::string TYPE_INT32 = "FG_TYPE_INT32";
const std::string TYPE_INT64 = "FG_TYPE_INT64";
const std::string TYPE_FLOAT32 = "FG_TYPE_FLOAT32";
const std::string TYPE_FLOAT64 = "FG_TYPE_FLOAT64";
const std::string TYPE_STRING = "FG_TYPE_STRING";
const std::string TYPE_BOOLEAN = "FG_TYPE_BOOLEAN";
const std::string TYPE_NIRAST = "FG_TYPE_NIRAST";

const std::string DYNAMIC_VALUE_TYPE = "FG_DYNAMIC_VALUE_TYPE";

} // namespace TYPE
} // namespace DYNAMIC_VALUE
namespace INNERS {
namespace FUNCTIONS {

const std::string PRINT = "print";
const std::string PRINT_F = "printf";
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
const std::string MALLOC = "malloc";
const std::string PUT_CHAR = "putchar";
#if defined(AOT_MODE) || defined(AOT_TEST_MODE)
const std::string GC_MALLOC = "GC_malloc";
#else
const std::string GC_MALLOC = "malloc";
#endif
}; // namespace FUNCTIONS
}; // namespace INNERS

const std::string IS_EXISTS = "is_exists";

}; // namespace FLOWWING::IR::CONSTANTS