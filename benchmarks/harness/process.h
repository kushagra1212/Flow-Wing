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
#include <vector>

namespace fwbench {

// Result of running a child process to completion.
//
// `wall_seconds` is measured around the whole spawn/wait cycle, so it
// includes process creation. That is deliberate: the `run/` benchmarks are
// end-to-end measurements and the `00_startup` case exists to quantify the
// floor that creation contributes.
struct ProcResult {
  bool spawned = false;
  int exit_code = -1;
  std::string out;
  std::string err;
  double wall_seconds = 0.0;
};

// Spawns argv[0] with the given arguments, captures stdout and stderr, and
// waits for it to exit.
//
// All paths must be absolute. The child inherits this process's working
// directory and no chdir is performed. `posix_spawn_file_actions_addchdir_np`
// is not portable across the platforms this suite targets, so the driver
// resolves every path up front instead.
ProcResult runProcess(const std::vector<std::string> &argv);

} // namespace fwbench
