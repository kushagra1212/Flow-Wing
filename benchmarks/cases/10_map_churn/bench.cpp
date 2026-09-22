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


#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <unordered_map>

int main(int argc, char **argv) {
  const int n = std::atoi(argv[1]);
  std::unordered_map<std::string, int> m;

  for (int i = 0; i < n; ++i) {
    m[std::to_string(i % 10000)] = i % 10000;
  }

  std::int64_t total = 0;
  for (int j = 0; j < n; ++j) {
    const auto found = m.find(std::to_string(j % 10000));
    const int value = found == m.end() ? 0 : found->second;
    total = (total + static_cast<std::int64_t>(value)) % 1000000007;
  }

  std::printf("%d\n%lld\n", static_cast<int>(m.size()),
              static_cast<long long>(total));
  return 0;
}
