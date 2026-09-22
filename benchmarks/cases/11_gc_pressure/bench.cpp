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
#include <memory>

class Node {
public:
  explicit Node(int v) : m_value(v) {}
  int get() const { return m_value; }

private:
  int m_value;
};

int main(int argc, char **argv) {
  const int n = std::atoi(argv[1]);
  std::int64_t total = 0;

  for (int i = 0; i < n; ++i) {
    const auto node = std::make_unique<Node>(i % 1000);
    total = (total + static_cast<std::int64_t>(node->get())) % 1000000007;
  }

  std::printf("%lld\n", static_cast<long long>(total));
  return 0;
}
