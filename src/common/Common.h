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


#pragma once
#include "../IR/constants/FlowWingIRConstants.h"
#include "../common/constants/FlowWingUtilsConstants.h"
#include "../external/include/json.hpp"
#include "../utils/CustomTypeIDGenerator/CustomTypeIDGenerator.h"
#include <algorithm>
#include <any>
#include <chrono>
#include <csignal>
#include <cstdint>
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
#include <string>
#include <thread>
#include <unordered_map>
#include <unordered_set>
#include <vector>
// TODO: Add support for Windows
// #include <windows.h>
#include "../utils/Colors.h"
#include "../utils/Macros.h"
#include <stdint.h>
#include <unistd.h>

using JSON = nlohmann::json;

namespace COLORED_STRING {
inline std::string GET(std::string str, const char *color, const char *reset) {
  std::stringstream ss;
  ss << color << str << reset;
  return ss.str();
}
} // namespace COLORED_STRING
