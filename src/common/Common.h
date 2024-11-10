#pragma once
#include "../IR/constants/FlowWingIRConstants.h"
#include "../common/CrossPlatformMacros.h"
#include "../common/constants/FlowWingUtilsConstants.h"
#include "../external/include/json.hpp"
#include "../utils/Colors.h"
#include "../utils/CustomTypeIDGenerator/CustomTypeIDGenerator.h"
#include "../utils/Macros.h"
#include <algorithm>
#include <any>
#include <chrono>
#include <csignal>
#include <cstdlib> // For malloc
#include <cstring> // For strlen and memcpy
#include <exception>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
#include <limits>
#include <map>
#include <memory>
#include <mutex>
#include <queue>
#include <random>
#include <sstream>
#include <stack>
#include <stdint.h>
#include <string>
#include <thread>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using JSON = nlohmann::json;

namespace COLORED_STRING {
inline std::string GET(std::string str, const char *color, const char *reset) {
  std::stringstream ss;
  ss << color << str << reset;
  return ss.str();
}
} // namespace COLORED_STRING
