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
#include <vector>

int main(int argc, char **argv) {
  const int n = std::atoi(argv[1]);
  std::vector<int> flags;

  for (int i = 0; i < n; ++i) {
    flags.push_back(1);
  }

  for (int p = 2; (p * p) < n; ++p) {
    if (flags[p] == 1) {
      for (int k = p * p; k < n; k += p) {
        flags[k] = 0;
      }
    }
  }

  int count = 0;
  for (int j = 2; j < n; ++j) {
    if (flags[j] == 1) {
      ++count;
    }
  }

  std::printf("%d\n", count);
  return 0;
}
