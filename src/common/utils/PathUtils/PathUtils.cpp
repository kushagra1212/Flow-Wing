/*
 * FlowWing Compiler
 * Copyright (C) 2023-2026 Kushagra Rathore
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
#include <cstdint>
#include <filesystem>
#include <iomanip>
#include <sstream>
#include <string_view>

namespace flow_wing {
namespace utils {

namespace {

std::string canonicalPathKeyForArtifacts(const std::string &file_path) {
  std::error_code ec;
  std::filesystem::path abs = std::filesystem::absolute(file_path, ec);
  if (ec) {
    return file_path;
  }
  return abs.lexically_normal().generic_string();
}

uint64_t fnv1a64(std::string_view s) {
  uint64_t h = 14695981039346656037ULL;
  constexpr uint64_t kPrime = 1099511628211ULL;
  for (char c : s) {
    h ^= static_cast<unsigned char>(c);
    h *= kPrime;
  }
  return h;
}

} // namespace

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

std::string PathUtils::shortHashedHex16ForPath(const std::string &file_path) {
  const std::string key = canonicalPathKeyForArtifacts(file_path);
  const uint64_t h = fnv1a64(key);
  std::ostringstream oss;
  oss << std::hex << std::setfill('0') << std::setw(16) << h;
  return oss.str();
}

std::string PathUtils::getDirectoryPath(const std::string &path) {
  return std::filesystem::path(path).parent_path().string();
}
} // namespace utils
} // namespace flow_wing
