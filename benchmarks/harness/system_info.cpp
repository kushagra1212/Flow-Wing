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

#include "system_info.h"

#include "process.h"

#include <cstdint>
#include <cstdlib>
#include <iomanip>
#include <sstream>
#include <sys/utsname.h>

namespace fwbench {

namespace {

std::string trim(const std::string &text) {
  const auto first = text.find_first_not_of(" \t\r\n");
  if (first == std::string::npos) {
    return "";
  }
  const auto last = text.find_last_not_of(" \t\r\n");
  return text.substr(first, last - first + 1);
}

// Every probe here is best-effort. A missing CPU string degrades the report
// header; it never invalidates a measurement, so nothing below is fatal.
std::string shellCapture(const std::vector<std::string> &argv) {
  const ProcResult result = runProcess(argv);
  if (result.exit_code != 0) {
    return "";
  }
  return trim(result.out);
}

long long parseLongLong(const std::string &text, long long fallback = 0) {
  if (text.empty()) {
    return fallback;
  }
  try {
    return std::stoll(text);
  } catch (const std::exception &) {
    return fallback;
  }
}

} // namespace

SystemInfo collectSystemInfo() {
  SystemInfo info;

  struct utsname uts {};
  if (::uname(&uts) == 0) {
    info.os = std::string(uts.sysname) + " " + uts.release;
    info.arch = uts.machine;
  } else {
    info.os = "unknown";
    info.arch = "unknown";
  }

#if defined(__APPLE__)
  info.cpu_model =
      shellCapture({"/usr/sbin/sysctl", "-n", "machdep.cpu.brand_string"});
  info.physical_cores = static_cast<int>(
      parseLongLong(shellCapture({"/usr/sbin/sysctl", "-n", "hw.physicalcpu"})));
  info.logical_cores = static_cast<int>(
      parseLongLong(shellCapture({"/usr/sbin/sysctl", "-n", "hw.logicalcpu"})));
  info.ram_gib =
      static_cast<double>(
          parseLongLong(shellCapture({"/usr/sbin/sysctl", "-n", "hw.memsize"}))) /
      (1024.0 * 1024.0 * 1024.0);

  // `pmset -g batt` prints "Now drawing from 'AC Power'" on mains.
  const std::string battery = shellCapture({"/usr/bin/pmset", "-g", "batt"});
  if (battery.find("AC Power") != std::string::npos) {
    info.power_source = "AC Power";
  } else if (battery.find("Battery Power") != std::string::npos) {
    info.power_source = "Battery Power";
  }
#else
  info.cpu_model = shellCapture(
      {"/bin/sh", "-c", "grep -m1 'model name' /proc/cpuinfo | cut -d: -f2"});
  info.physical_cores = static_cast<int>(parseLongLong(shellCapture(
      {"/bin/sh", "-c",
       "grep -m1 'cpu cores' /proc/cpuinfo | cut -d: -f2 | tr -d ' '"})));
  info.logical_cores =
      static_cast<int>(parseLongLong(shellCapture({"/bin/sh", "-c", "nproc"})));
  info.ram_gib =
      static_cast<double>(parseLongLong(shellCapture(
          {"/bin/sh", "-c",
           "grep -m1 MemTotal /proc/meminfo | tr -dc '0-9'"}))) /
      (1024.0 * 1024.0);

  // Present on laptops, absent on most servers and in containers.
  const std::string online = shellCapture(
      {"/bin/sh", "-c", "cat /sys/class/power_supply/AC*/online 2>/dev/null"});
  if (online == "1") {
    info.power_source = "AC Power";
  } else if (online == "0") {
    info.power_source = "Battery Power";
  }
#endif

  if (info.cpu_model.empty()) {
    info.cpu_model = "unknown";
  }
  if (info.power_source.empty()) {
    info.power_source = "unknown";
  }

  double loads[3] = {0.0, 0.0, 0.0};
  if (::getloadavg(loads, 3) > 0) {
    info.load_average_1m = loads[0];
  }

  return info;
}

std::string machineFingerprint(const SystemInfo &info) {
  std::ostringstream stable;
  stable << info.os << '|' << info.arch << '|' << info.cpu_model << '|'
         << info.physical_cores << '|' << info.logical_cores << '|'
         << static_cast<long long>(info.ram_gib * 1024.0);

  // FNV-1a. Not cryptographic. It only needs to answer "same machine
  // configuration or not" at a glance.
  const std::string text = stable.str();
  std::uint64_t hash = 1469598103934665603ULL;
  for (const unsigned char byte : text) {
    hash ^= byte;
    hash *= 1099511628211ULL;
  }

  std::ostringstream out;
  out << std::hex << std::setw(12) << std::setfill('0') << (hash >> 16);
  return out.str();
}

} // namespace fwbench
