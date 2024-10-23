#ifndef __FLOWWING_UTILS_CONSTANTS_H__
#define __FLOWWING_UTILS_CONSTANTS_H__

#include <string>

namespace FLOWWING::UTILS::CONSTANTS {
extern const std::string GLOBAL_VARIABLE_PREFIX;
extern const std::string MEMBER_FUN_PREFIX;
extern const std::string MODULE_PREFIX;
extern const std::string RETURN_VAR_NAME;

#ifdef _WIN32
extern const std::string NULL_DEVICE;
#else
extern const std::string NULL_DEVICE;
#endif

}; // namespace FLOWWING::UTILS::CONSTANTS

#endif // __FLOWWING_UTILS_CONSTANTS_H__