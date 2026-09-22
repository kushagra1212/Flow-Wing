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
#include <vector>

static void quicksort(std::vector<int> &v, int lo, int hi) {
  if (lo < hi) {
    const int pivot = v[hi];
    int i = lo - 1;

    for (int j = lo; j < hi; ++j) {
      if (v[j] <= pivot) {
        i = i + 1;
        const int tmp = v[i];
        v[i] = v[j];
        v[j] = tmp;
      }
    }

    const int tmp2 = v[i + 1];
    v[i + 1] = v[hi];
    v[hi] = tmp2;

    quicksort(v, lo, i);
    quicksort(v, i + 2, hi);
  }
}

int main(int argc, char **argv) {
  const int n = std::atoi(argv[1]);
  std::vector<int> data;

  // MINSTD generator: the product stays well inside int64, so both languages
  // produce the identical sequence without relying on a shared library RNG.
  std::int64_t seed = 42;
  for (int i = 0; i < n; ++i) {
    seed = (seed * 48271) % 2147483647;
    data.push_back(static_cast<int>(seed % 100000));
  }

  quicksort(data, 0, n - 1);

  std::int64_t checksum = 0;
  for (int k = 0; k < n; ++k) {
    checksum = (checksum + (static_cast<std::int64_t>(k) *
                            static_cast<std::int64_t>(data[k]))) %
               1000000007;
  }

  std::printf("%d\n%d\n%lld\n", data[0], data[n - 1],
              static_cast<long long>(checksum));
  return 0;
}
