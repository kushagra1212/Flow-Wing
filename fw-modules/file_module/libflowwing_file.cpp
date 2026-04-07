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
/*
 * FlowWing Compiler - File I/O FFI
 * Cross-Platform: Compiles on Windows, macOS, and Linux
 */

#include <cstdio>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <gc/gc.h>
#include <sstream>
#include <string>

namespace fs = std::filesystem;

extern "C" {
// Stores the last error code to avoid complex FFI pointer passing
// 0 = OK, 1 = NOT_FOUND, 2 = FAILED
static thread_local int32_t last_file_error = 0;

int32_t dyn_file_last_error() { return last_file_error; }

// Helper: Allocate a GC-tracked string to return to FlowWing
static const char *alloc_gc_string(const std::string &str) {
  char *cstr = (char *)GC_MALLOC_ATOMIC(str.length() + 1);
  if (cstr) {
    std::memcpy(cstr, str.c_str(), str.length());
    cstr[str.length()] = '\0';
  }
  return cstr;
}

// --- Path Helpers (NEW) ---

const char *dyn_file_cwd() {
  std::error_code ec;
  fs::path cwd = fs::current_path(ec);
  return alloc_gc_string(cwd.string());
}

const char *dyn_file_absolute_path(const char *path) {
  std::error_code ec;
  fs::path abs_path = fs::absolute(fs::path(path), ec);
  return alloc_gc_string(abs_path.string());
}

// --- Static One-Shot Operations ---

const char *dyn_file_read_all(const char *path) {
  // fs::path automatically normalizes slashes for the host OS
  std::ifstream file(fs::path(path), std::ios::in | std::ios::binary);
  if (!file) {
    last_file_error = 1; // NOT_FOUND
    return alloc_gc_string("");
  }
  std::ostringstream contents;
  contents << file.rdbuf();
  last_file_error = 0; // OK
  return alloc_gc_string(contents.str());
}

void dyn_file_write_all(const char *path, const char *content) {
  std::ofstream file(fs::path(path), std::ios::out | std::ios::binary);
  if (!file) {
    last_file_error = 2; // FAILED
    return;
  }
  file << content;
  last_file_error = 0;
}

void dyn_file_append_all(const char *path, const char *content) {
  std::ofstream file(fs::path(path),
                     std::ios::out | std::ios::app | std::ios::binary);
  if (!file) {
    last_file_error = 2; // FAILED
    return;
  }
  file << content;
  last_file_error = 0;
}

bool dyn_file_exists(const char *path) {
  std::error_code ec;
  return fs::exists(fs::path(path), ec);
}

void dyn_file_delete(const char *path) {
  std::error_code ec;
  if (!fs::remove(fs::path(path), ec)) {
    last_file_error = 2; // FAILED
  } else {
    last_file_error = 0; // OK
  }
}

// --- Stateful File Operations (For Streaming/Line-by-Line) ---

struct FileHandle {
  std::fstream stream;
};

void finalizeFileHandle(void *raw_handle, void *) {
  auto *handle = static_cast<FileHandle *>(raw_handle);
  if (handle->stream.is_open()) {
    handle->stream.close();
  }
  using fstream_t = decltype(handle->stream);
  handle->stream.~fstream_t(); // Explicit destructor call using decltype
}

int64_t dyn_file_open(const char *path, const char *mode) {
  auto *handle = static_cast<FileHandle *>(GC_MALLOC(sizeof(FileHandle)));
  if (!handle)
    return 0;

  new (&handle->stream) std::fstream(); // Placement new
  GC_register_finalizer(handle, finalizeFileHandle, nullptr, nullptr, nullptr);

  std::ios_base::openmode std_mode = std::ios::binary;
  if (std::strcmp(mode, "r") == 0)
    std_mode |= std::ios::in;
  else if (std::strcmp(mode, "w") == 0)
    std_mode |= std::ios::out;
  else if (std::strcmp(mode, "a") == 0)
    std_mode |= (std::ios::out | std::ios::app);

  handle->stream.open(fs::path(path), std_mode);
  if (!handle->stream.is_open()) {
    last_file_error = 1; // NOT_FOUND
    return 0;            // Return null handle
  }

  last_file_error = 0;
  return reinterpret_cast<int64_t>(handle);
}

void dyn_file_close(int64_t raw_handle) {
  if (!raw_handle)
    return;
  auto *handle = reinterpret_cast<FileHandle *>(raw_handle);
  if (handle->stream.is_open()) {
    handle->stream.close();
  }
}

const char *dyn_file_read_line(int64_t raw_handle) {
  if (!raw_handle)
    return alloc_gc_string("");
  auto *handle = reinterpret_cast<FileHandle *>(raw_handle);

  std::string line;
  if (std::getline(handle->stream, line)) {
    last_file_error = 0;
    // Handle cross-platform CRLF by stripping trailing '\r'
    if (!line.empty() && line.back() == '\r') {
      line.pop_back();
    }
    return alloc_gc_string(line);
  }

  last_file_error = 1; // EOF or Failed
  return alloc_gc_string("");
}
}