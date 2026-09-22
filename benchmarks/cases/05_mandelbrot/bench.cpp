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

int main(int argc, char **argv) {
  const int size = std::atoi(argv[1]);
  int inside = 0;

  for (int y = 0; y < size; ++y) {
    for (int x = 0; x < size; ++x) {
      const double cr =
          ((static_cast<double>(x) * 3.0) / static_cast<double>(size)) - 2.0;
      const double ci =
          ((static_cast<double>(y) * 3.0) / static_cast<double>(size)) - 1.5;
      double zr = 0.0;
      double zi = 0.0;
      int it = 0;
      int escaped = 0;

      while (it < 50) {
        const double zr2 = zr * zr;
        const double zi2 = zi * zi;
        if ((zr2 + zi2) > 4.0) {
          escaped = 1;
          it = 50;
        } else {
          zi = ((2.0 * zr) * zi) + ci;
          zr = (zr2 - zi2) + cr;
          it = it + 1;
        }
      }

      if (escaped == 0) {
        ++inside;
      }
    }
  }

  std::printf("%d\n", inside);
  return 0;
}
