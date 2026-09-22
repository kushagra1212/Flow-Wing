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

// Newton's method rather than std::sqrt: Flow-Wing has no math module, and
// rolling it by hand keeps both sides running the identical algorithm instead
// of comparing against whatever libm ships on the host.
static double mysqrt(double x) {
  if (x <= 0.0) {
    return 0.0;
  }
  double g = x;
  for (int i = 0; i < 20; ++i) {
    g = (g + (x / g)) * 0.5;
  }
  return g;
}

int main(int argc, char **argv) {
  const int steps = std::atoi(argv[1]);
  const int N = 5;
  double px[5];
  double py[5];
  double vx[5];
  double vy[5];
  double mass[5];

  for (int i = 0; i < N; ++i) {
    px[i] = (static_cast<double>(i) * 1.5) - 3.0;
    py[i] = (static_cast<double>(i) * 0.75) - 1.5;
    vx[i] = 0.0;
    vy[i] = 0.0;
    mass[i] = 1.0 + (static_cast<double>(i) * 0.25);
  }

  const double dt = 0.001;

  for (int s = 0; s < steps; ++s) {
    for (int a = 0; a < N; ++a) {
      double fx = 0.0;
      double fy = 0.0;
      for (int b = 0; b < N; ++b) {
        if (a != b) {
          const double dx = px[b] - px[a];
          const double dy = py[b] - py[a];
          const double d2 = (dx * dx) + (dy * dy) + 0.01;
          const double d = mysqrt(d2);
          const double f = mass[b] / (d2 * d);
          fx = fx + (dx * f);
          fy = fy + (dy * f);
        }
      }
      vx[a] = vx[a] + (fx * dt);
      vy[a] = vy[a] + (fy * dt);
    }

    for (int c = 0; c < N; ++c) {
      px[c] = px[c] + (vx[c] * dt);
      py[c] = py[c] + (vy[c] * dt);
    }
  }

  double energy = 0.0;
  for (int k = 0; k < N; ++k) {
    energy = energy + ((0.5 * mass[k]) * ((vx[k] * vx[k]) + (vy[k] * vy[k])));
  }

  std::printf("%lld\n", static_cast<long long>(energy * 1000000.0));
  return 0;
}
