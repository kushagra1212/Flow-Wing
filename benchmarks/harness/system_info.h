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


//
// FlowWing Compiler
// Copyright (C) 2023-2026 Kushagra Rathore
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//

#pragma once

#include <string>

namespace fwbench {

// The machine a report was produced on.
//
// Absolute timings mean nothing without this. Two reports are only comparable
// when their fingerprints match; everything here is recorded so that a reader
// months later can tell whether a difference is a real regression or just a
// different laptop.
struct SystemInfo {
  std::string os;           // "Darwin 24.6.0"
  std::string arch;         // "arm64"
  std::string cpu_model;    // "Apple M4 Pro"
  int physical_cores = 0;
  int logical_cores = 0;
  double ram_gib = 0.0;

  // Mains or battery. Laptops throttle aggressively on battery, which can
  // move every figure in a report by tens of percent, so a run made on
  // battery is worth flagging rather than silently publishing.
  std::string power_source;

  // One-minute load average sampled as the suite starts. A busy machine
  // inflates wall-clock measurements.
  double load_average_1m = 0.0;
};

SystemInfo collectSystemInfo();

// Short stable hash over the fields that decide comparability: OS, arch, CPU
// model, core counts and RAM. Deliberately excludes load average and power
// source, which vary between runs on one machine.
std::string machineFingerprint(const SystemInfo &info);

} // namespace fwbench
