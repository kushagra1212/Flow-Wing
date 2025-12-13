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

#include "PathUtils.h"
#include <filesystem>

namespace flow_wing {
namespace utils {

std::string
PathUtils::getAbsoluteFilePath(const std::string &relative_file_path) {
  return std::filesystem::absolute(relative_file_path).string();
}

std::string PathUtils::getFileName(const std::string &file_path) {
  return std::filesystem::path(file_path).filename().string();
}

std::string PathUtils::removeExtension(const std::string &file_path) {
  return std::filesystem::path(file_path).stem().string();
}

std::string PathUtils::getExtension(const std::string &file_path) {
  return std::filesystem::path(file_path).extension().string();
}

} // namespace utils
} // namespace flow_wing
