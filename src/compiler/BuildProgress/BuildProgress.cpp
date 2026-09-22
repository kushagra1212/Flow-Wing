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

#include "BuildProgress.hpp"

#include "src/common/cli/CliColors.h"
#include "src/common/io/PathUtils.hpp"
#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <system_error>

#if defined(_WIN32)
#include <io.h>
#else
#include <unistd.h>
#endif

namespace flow_wing {
namespace compiler {

namespace {

namespace fs = std::filesystem;

// Cargo's layout: every verb right-aligned in a 12-column gutter.
constexpr size_t kVerbWidth = 12;

bool stderrIsTerminal() {
#if defined(_WIN32)
  return _isatty(_fileno(stderr)) != 0;
#else
  return isatty(fileno(stderr)) != 0;
#endif
}

// Only builds show progress. --emit=ir|tokens|ast|sem already print their one
// "dumped to" line.
bool isBuild(CompilerOptions::OutputType type) {
  return type == CompilerOptions::OutputType::kObj ||
         type == CompilerOptions::OutputType::kExe ||
         type == CompilerOptions::OutputType::kJIT;
}

std::string seconds(long long milliseconds) {
  std::ostringstream out;
  out << std::fixed << std::setprecision(2)
      << static_cast<double>(milliseconds) / 1000.0 << "s";
  return out.str();
}

// A module that `bring <name>` found in one of the two places it looks: the
// SDK modules directory, or a fw-modules tree when working inside the repo.
bool isStandardModule(const fs::path &path) {
  for (const auto &part : path.parent_path()) {
    if (part == "fw-modules") {
      return true;
    }
  }
  std::error_code error;
  const fs::path modules = io::PathUtils::getModulesPath();
  return !modules.empty() && fs::equivalent(path.parent_path(), modules, error);
}

// 64-bit FNV-1a: stable across runs and compiler builds, unlike std::hash,
// and fixed-width, so any key is safe in the tab-separated history file.
std::string fnv1a64Hex(const std::string &text) {
  uint64_t hash = 14695981039346656037ULL;
  for (const char c : text) {
    hash ^= static_cast<unsigned char>(c);
    hash *= 1099511628211ULL;
  }
  std::ostringstream out;
  out << std::hex << std::setfill('0') << std::setw(16) << hash;
  return out.str();
}

} // namespace

BuildProgress::BuildProgress(const CompilerOptions &options,
                             const std::string &absolute_entry_path)
    : m_options(options), m_entry(absolute_entry_path),
      m_history(fs::path(options.output_dir) / ".flowwing" / "build-times"),
      m_start(std::chrono::steady_clock::now()) {
  const bool terminal = stderrIsTerminal();
  switch (options.progress) {
  case ProgressMode::kNever:
    m_shown = false;
    break;
  case ProgressMode::kAlways:
    m_shown = isBuild(options.output_type);
    break;
  case ProgressMode::kAuto:
    m_shown = isBuild(options.output_type) && terminal;
    break;
  }
  // Colour only on a terminal: --progress=always into a CI log stays plain.
  m_colour = m_shown && terminal;
}

void BuildProgress::unit(const std::string &absolute_path) {
  if (!m_shown) {
    return;
  }
  ++m_units;
  line("Compiling", display(absolute_path));
}

void BuildProgress::linking(const std::string &binary_path) {
  if (!m_shown) {
    return;
  }
  line("Linking", fs::path(binary_path).generic_string());
}

void BuildProgress::finished() {
  if (!m_shown || m_finished) {
    return;
  }
  m_finished = true;

  const long long elapsed_ms =
      std::chrono::duration_cast<std::chrono::milliseconds>(
          std::chrono::steady_clock::now() - m_start)
          .count();

  std::ostringstream text;
  text << m_entry.stem().string() << " in " << seconds(elapsed_ms) << " ("
       << m_units << (m_units == 1 ? " file, " : " files, ")
       << delta(elapsed_ms) << ")";
  line("Finished", text.str());

  // After the delta was read, so this build is compared with the previous
  // one rather than with itself.
  m_history.record(historyKey(), elapsed_ms);
}

void BuildProgress::running() {
  if (!m_shown) {
    return;
  }
  line("Running", display(m_entry));
}

void BuildProgress::failed() {
  if (!m_shown || m_units > 0 || m_finished) {
    return;
  }
  line("Compiling", display(m_entry));
}

void BuildProgress::line(std::string_view verb, const std::string &text) const {
  const std::string gutter(
      verb.size() < kVerbWidth ? kVerbWidth - verb.size() : 0, ' ');
  if (m_colour) {
    std::cerr << gutter << GREEN_TEXT << verb << RESET;
  } else {
    std::cerr << gutter << verb;
  }
  std::cerr << ' ' << text << '\n';
}

std::string BuildProgress::display(const fs::path &absolute_path) const {
  if (isStandardModule(absolute_path)) {
    std::string name = absolute_path.stem().string();
    const std::string suffix = "-module";
    if (name.size() > suffix.size() &&
        name.compare(name.size() - suffix.size(), suffix.size(), suffix) ==
            0) {
      name.resize(name.size() - suffix.size());
    }
    return name + " (std)";
  }
  std::error_code error;
  const fs::path relative =
      fs::relative(absolute_path, m_entry.parent_path(), error);
  if (error || relative.empty()) {
    return absolute_path.generic_string();
  }
  return relative.generic_string();
}

// Builds are only comparable when they compile the same entry the same way:
// a -O3 build compared with a -O0 one would report a meaningless change.
std::string BuildProgress::historyKey() const {
  std::ostringstream key;
  key << m_entry.generic_string() << '|'
      << static_cast<int>(m_options.optimization_level) << '|'
      << static_cast<int>(m_options.target_platform) << '|'
      << static_cast<int>(m_options.output_type);
  return fnv1a64Hex(key.str());
}

std::string BuildProgress::delta(long long now_ms) const {
  const auto previous_ms = m_history.last(historyKey());
  if (!previous_ms) {
    return "first build";
  }

  // Below max(50 ms, 5% of the last build) the difference is run-to-run
  // noise, and reporting it would make every build look like a regression.
  const long long change_ms = now_ms - *previous_ms;
  const long long noise_ms = std::max<long long>(50, *previous_ms / 20);
  if (std::llabs(change_ms) < noise_ms) {
    return "same as last build";
  }

  const bool slower = change_ms > 0;
  std::string text = std::string(slower ? "+" : "-") +
                     seconds(std::llabs(change_ms)) + " vs last build";
#if !defined(_WIN32)
  // Windows consoles default to a code page that mangles these; the sign
  // already says which way it went.
  text += slower ? " ▲" : " ▼";
#endif
  if (m_colour) {
    return std::string(slower ? RED_TEXT : GREEN_TEXT) + text + RESET;
  }
  return text;
}

} // namespace compiler
} // namespace flow_wing
