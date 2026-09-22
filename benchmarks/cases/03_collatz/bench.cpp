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

int main(int argc, char **argv) {
  const int limit = std::atoi(argv[1]);
  int best = 0;
  int best_start = 0;

  for (int i = 1; i < limit; ++i) {
    std::int64_t cur = i;
    int steps = 0;

    while (cur != 1) {
      if (cur % 2 == 0) {
        cur = cur / 2;
      } else {
        cur = cur * 3 + 1;
      }
      ++steps;
    }

    if (steps > best) {
      best = steps;
      best_start = i;
    }
  }

  std::printf("%d\n%d\n", best_start, best);
  return 0;
}
