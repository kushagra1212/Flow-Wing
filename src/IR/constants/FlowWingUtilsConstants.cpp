#include "FlowWingUtilsConstants.h"

namespace FLOWWING::UTILS::CONSTANTS {
const std::string GLOBAL_VARIABLE_PREFIX = "[:global:]";
const std::string MEMBER_FUN_PREFIX = ".";
const std::string MODULE_PREFIX = "::";
const std::string RETURN_VAR_NAME = "r::v";

#ifdef _WIN32
const std::string NULL_DEVICE = "NUL";
#else
const std::string NULL_DEVICE = "/dev/null";
#endif
}; // namespace FLOWWING::UTILS::CONSTANTS
