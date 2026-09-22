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

#include "process.h"

#include <cerrno>
#include <chrono>
#include <cstring>
#include <poll.h>
#include <spawn.h>
#include <sys/wait.h>
#include <unistd.h>
#include <vector>

extern char **environ;

namespace fwbench {

namespace {

// Drains both pipes concurrently.
//
// Reading stdout to EOF before touching stderr would deadlock the moment a
// child writes more than one pipe buffer of diagnostics, which the
// FlowWing compiler does on any error, since it echoes the offending source
// lines. poll() on both descriptors avoids that.
void drainPipes(int out_fd, int err_fd, std::string &out, std::string &err) {
  struct pollfd fds[2];
  fds[0] = {out_fd, POLLIN, 0};
  fds[1] = {err_fd, POLLIN, 0};

  char buffer[8192];
  int open_count = 2;

  while (open_count > 0) {
    if (::poll(fds, 2, -1) < 0) {
      if (errno == EINTR) {
        continue;
      }
      break;
    }

    for (int i = 0; i < 2; ++i) {
      if (fds[i].fd < 0 || !(fds[i].revents & (POLLIN | POLLHUP | POLLERR))) {
        continue;
      }

      const ssize_t n = ::read(fds[i].fd, buffer, sizeof(buffer));
      if (n > 0) {
        (i == 0 ? out : err).append(buffer, static_cast<size_t>(n));
        continue;
      }
      if (n < 0 && errno == EINTR) {
        continue;
      }

      // EOF or a hard read error: retire this descriptor.
      fds[i].fd = -1;
      --open_count;
    }
  }
}

} // namespace

ProcResult runProcess(const std::vector<std::string> &argv) {
  ProcResult result;
  if (argv.empty()) {
    return result;
  }

  int out_pipe[2];
  int err_pipe[2];
  if (::pipe(out_pipe) != 0) {
    result.err = "pipe() failed: " + std::string(std::strerror(errno));
    return result;
  }
  if (::pipe(err_pipe) != 0) {
    result.err = "pipe() failed: " + std::string(std::strerror(errno));
    ::close(out_pipe[0]);
    ::close(out_pipe[1]);
    return result;
  }

  posix_spawn_file_actions_t actions;
  posix_spawn_file_actions_init(&actions);
  posix_spawn_file_actions_addclose(&actions, out_pipe[0]);
  posix_spawn_file_actions_addclose(&actions, err_pipe[0]);
  posix_spawn_file_actions_adddup2(&actions, out_pipe[1], STDOUT_FILENO);
  posix_spawn_file_actions_adddup2(&actions, err_pipe[1], STDERR_FILENO);
  posix_spawn_file_actions_addclose(&actions, out_pipe[1]);
  posix_spawn_file_actions_addclose(&actions, err_pipe[1]);

  std::vector<char *> raw_argv;
  raw_argv.reserve(argv.size() + 1);
  for (const std::string &arg : argv) {
    raw_argv.push_back(const_cast<char *>(arg.c_str()));
  }
  raw_argv.push_back(nullptr);

  const auto started = std::chrono::steady_clock::now();

  pid_t pid = 0;
  const int spawn_rc = ::posix_spawn(&pid, raw_argv[0], &actions, nullptr,
                                     raw_argv.data(), environ);

  posix_spawn_file_actions_destroy(&actions);
  ::close(out_pipe[1]);
  ::close(err_pipe[1]);

  if (spawn_rc != 0) {
    result.err = "posix_spawn(" + argv[0] +
                 ") failed: " + std::string(std::strerror(spawn_rc));
    ::close(out_pipe[0]);
    ::close(err_pipe[0]);
    return result;
  }

  result.spawned = true;
  drainPipes(out_pipe[0], err_pipe[0], result.out, result.err);
  ::close(out_pipe[0]);
  ::close(err_pipe[0]);

  int status = 0;
  while (::waitpid(pid, &status, 0) < 0 && errno == EINTR) {
    // Retry.
  }

  const auto finished = std::chrono::steady_clock::now();
  result.wall_seconds =
      std::chrono::duration<double>(finished - started).count();

  if (WIFEXITED(status)) {
    result.exit_code = WEXITSTATUS(status);
  } else if (WIFSIGNALED(status)) {
    // Mirror the shell convention so a SIGSEGV in the compiler reads as the
    // familiar 139 rather than as an opaque negative number.
    result.exit_code = 128 + WTERMSIG(status);
  }

  return result;
}

} // namespace fwbench
