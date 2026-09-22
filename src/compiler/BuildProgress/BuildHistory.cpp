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

#include "BuildHistory.hpp"

#include <charconv>
#include <fstream>
#include <system_error>
#include <utility>

namespace flow_wing {
namespace compiler {

BuildHistory::BuildHistory(std::filesystem::path file)
    : m_file(std::move(file)) {}

std::map<std::string, long long> BuildHistory::load() const {
  std::map<std::string, long long> entries;
  std::ifstream in(m_file);
  std::string line;
  while (std::getline(in, line)) {
    const size_t tab = line.find('\t');
    if (tab == std::string::npos || tab == 0) {
      continue;
    }
    long long milliseconds = 0;
    const char *first = line.data() + tab + 1;
    const char *last = line.data() + line.size();
    const auto [end, error] = std::from_chars(first, last, milliseconds);
    // Any line that is not exactly "<key>\t<non-negative integer>" is skipped
    // rather than trusted.
    if (error != std::errc() || end != last || milliseconds < 0) {
      continue;
    }
    entries[line.substr(0, tab)] = milliseconds;
  }
  return entries;
}

std::optional<long long> BuildHistory::last(const std::string &key) const {
  const auto entries = load();
  const auto found = entries.find(key);
  if (found == entries.end()) {
    return std::nullopt;
  }
  return found->second;
}

void BuildHistory::record(const std::string &key,
                          long long milliseconds) const {
  auto entries = load();
  entries[key] = milliseconds;

  std::error_code error;
  std::filesystem::create_directories(m_file.parent_path(), error);
  if (error) {
    return;
  }

  // Written beside the real file and then renamed over it, so a reader sees
  // either the old file or the new one, never half of one.
  std::filesystem::path temp = m_file;
  temp += ".tmp";
  {
    std::ofstream out(temp, std::ios::trunc);
    for (const auto &[entry_key, entry_ms] : entries) {
      out << entry_key << '\t' << entry_ms << '\n';
    }
    if (!out) {
      std::filesystem::remove(temp, error);
      return;
    }
  }
  std::filesystem::rename(temp, m_file, error);
  if (error) {
    std::filesystem::remove(temp, error);
  }
}

} // namespace compiler
} // namespace flow_wing
