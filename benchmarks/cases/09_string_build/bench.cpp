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


#include <cstdio>
#include <cstdlib>
#include <string>

int main(int argc, char **argv) {
  const int n = std::atoi(argv[1]);
  std::string s;

  for (int i = 0; i < n; ++i) {
    // Deliberately `s = s + "x"` and not `s += "x"`. Flow-Wing's concat
    // produces a new string every step; using append here would compare an
    // amortised O(n) algorithm against an O(n^2) one.
    s = s + "x";
  }

  std::printf("%d\n", static_cast<int>(s.size()));
  return 0;
}
