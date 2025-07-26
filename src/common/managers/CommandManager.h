/*
 * FlowWing Compiler
 * Copyright (C) 2023-2025 Kushagra Rathore
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

#pragma once

#include <string>

class CommandManager {
  std::string _outputFileName = "output";
  bool hasEntryPoint = false;

public:
  CommandManager(const std::string &outputFileNameWithoutExtension);

  auto create() -> std::string;

private:
  auto getObjectFilesJoinedAsString() -> std::string;

  auto getDefaultEntryPoint() -> std::string;

  auto getEntryPoint(const std::string &key, const std::string &value)
      -> std::string;

  auto getOutputArgument() -> std::string;

  auto getRuntimeLibrariesLinked() -> std::string;

  auto createLibArgs(const std::string &libName) -> std::string;

  auto getOptimizationLevel() -> std::string;

  auto getOtherLibrariesPath(const std::string &key, const std::string &value)
      -> std::string;

  auto createLibPathArg(const std::string &value) -> std::string;

  auto getLinkLibrary(const std::string &key, const std::string &value)
      -> std::string;

  auto getFramework(const std::string &key, const std::string &value)
      -> std::string;

  auto checkForRestOfFlags(std::string &cmd) -> void;
};