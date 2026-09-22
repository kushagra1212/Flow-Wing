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

static const int N = 64;

static int a[N][N];
static int b[N][N];
static int c[N][N];

int main(int argc, char **argv) {
  const int reps = std::atoi(argv[1]);
  std::int64_t checksum = 0;

  for (int r = 0; r < reps; ++r) {
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) {
        a[i][j] = ((i * 3) + (j * 7) + r) % 100;
        b[i][j] = ((i * 5) + (j * 11) + r) % 100;
      }
    }

    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) {
        int sum = 0;
        for (int k = 0; k < N; ++k) {
          sum = sum + (a[i][k] * b[k][j]);
        }
        c[i][j] = sum;
      }
    }

    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) {
        checksum = (checksum + static_cast<std::int64_t>(c[i][j])) % 1000000007;
      }
    }
  }

  std::printf("%lld\n", static_cast<long long>(checksum));
  return 0;
}
