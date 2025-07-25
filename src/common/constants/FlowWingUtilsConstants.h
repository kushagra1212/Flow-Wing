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