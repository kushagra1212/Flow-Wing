#pragma once

#include <string_view>
namespace flow_wing {
namespace ir_gen {

namespace constants {

namespace paths {
#if defined(_WIN32)
const std::string_view kObject_files_dir = "build\\objects\\";
const std::string_view kBin_files_dir = "build\\bin\\";
const std::string_view kObject_file_extension = ".obj";
const std::string_view kFG_tmp_dir = "fg_temp\\";
#else
const std::string_view kObject_files_dir = "build/objects/";
const std::string_view kBin_files_dir = "build/bin/";
const std::string_view kObject_file_extension = ".o";
const std::string_view kFG_tmp_dir = "fg_tmp/";
#endif

#if defined(DEBUG)
const std::string_view kIR_files_extension = ".ll";
#else
const std::string_view kIR_files_extension = ".bc";
#endif
} // namespace paths

namespace types {
const std::string_view kDynamic_type_name = "fg_dyn_type";
}

namespace functions {
// Built-in Functions
const std::string_view kPrint_fn = "print";
const std::string_view kString_fn = "String";
const std::string_view kBool_fn = "Bool";
const std::string_view kDecimal_fn = "Decimal";
const std::string_view kDecimal32_fn = "Decimal32";
const std::string_view kInt8_fn = "Int8";
const std::string_view kChar_fn = "Char";
const std::string_view kInt32_fn = "Int32";
const std::string_view kInt64_fn = "Int64";

// FlowWing Internal Functions
const std::string_view kPrintf_fn = "fg_pf";
const std::string_view kConcat_strings_fn = "fg_cs";
const std::string_view kString_length_fn = "fg_sl";
const std::string_view kItos_fn = "fg_itos";
const std::string_view kI8tos_fn = "fg_i8tos";
const std::string_view kDtos_fn = "fg_dtos";
const std::string_view kFtos_fn = "fg_ftos";
const std::string_view kCtos_fn = "fg_ctos";
const std::string_view kLltos_fn = "fg_lltos";
const std::string_view kGet_malloc_ptr_of_string_constant_fn = "fg_gmosc";
const std::string_view kGet_malloc_ptr_of_int_constant_fn = "fg_gmoic";
const std::string_view kCompare_strings_fn = "fg_cmp";
const std::string_view kLess_than_strings_fn = "fg_lt";
const std::string_view kLess_than_or_equal_strings_fn = "fg_lte";
const std::string_view kGreater_than_strings_fn = "fg_gt";
const std::string_view kGreater_than_or_equal_strings_fn = "fg_gte";
const std::string_view kEqual_strings_fn = "fg_eq";
const std::string_view kGet_input_fn = "fg_gi";
const std::string_view kString_to_int_fn = "fg_sti";
const std::string_view kString_to_char_fn = "fg_stc";
const std::string_view kString_to_long_fn = "fg_stl";
const std::string_view kString_to_double_fn = "fg_std";
const std::string_view kString_to_float_fn = "fg_stf";
const std::string_view kRaise_exception_fn = "fg_re";

const std::string_view kMalloc_fn = "malloc";

#if defined(AOT_MODE) || defined(AOT_TEST_MODE)
const std::string_view kGC_malloc_fn = "GC_malloc";
#else
const std::string_view kGC_malloc_fn = "malloc";
#endif

// Entry Point

#if defined(__APPLE__)
const std::string_view kMain_fn = "main";
#else
const std::string_view kMain_fn = "main";
#endif
} // namespace functions
} // namespace constants
} // namespace ir_gen
} // namespace flow_wing