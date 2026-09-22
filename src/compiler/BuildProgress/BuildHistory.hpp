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

#pragma once

#include <filesystem>
#include <map>
#include <optional>
#include <string>

namespace flow_wing {
namespace compiler {

// How long the last successful build took, per build key, kept in one small
// text file with one "<key>\t<milliseconds>" line per key.
//
// Advisory only. A missing, unreadable or corrupt file reads as "no earlier
// build", and a failed write is ignored: the build-time delta must never be
// the reason a build fails.
class BuildHistory {
public:
  explicit BuildHistory(std::filesystem::path file);

  std::optional<long long> last(const std::string &key) const;
  void record(const std::string &key, long long milliseconds) const;

private:
  std::map<std::string, long long> load() const;

  std::filesystem::path m_file;
};

} // namespace compiler
} // namespace flow_wing
