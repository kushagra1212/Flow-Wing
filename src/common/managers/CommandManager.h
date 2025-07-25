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

#include "../../IR/constants/FlowWingIRConstants.h"
#include "../../common/Common.h"
#include "../../common/commandLineOptions/commandLineOptions.h"
#include "../../external/include/argh.h"
#include "../../utils/PathUtils.h"
#include "../../utils/Utils.h"
#include "../LibUtils/LibUtils.h"
#include "llvm/Support/FileSystem.h"
#include <filesystem>
#include <string>

class CommandManager {
  std::string _outputFileName = "output";
  bool hasEntryPoint = false;

public:
  CommandManager(const std::string &outputFileNameWithoutExtension)
      : _outputFileName(outputFileNameWithoutExtension) {
#if defined(_WIN32)
    _outputFileName += ".exe";
#endif
  }

  auto create() -> std::string {
    std::string cmd = "";

    cmd += FlowWing::PathUtils::getAOTLinkerPath() + " ";

    cmd += this->getOptimizationLevel();

    cmd += this->getOutputArgument();

    cmd += this->getObjectFilesJoinedAsString();

    if (FlowWing::Cli::cmdl) {
      for (const auto &[key, value] : (*FlowWing::Cli::cmdl).params()) {
        cmd += this->getOtherLibrariesPath(key, value);
        cmd += this->getLinkLibrary(key, value);
        cmd += this->getFramework(key, value);
        cmd += this->getEntryPoint(key, value);
      }

      checkForRestOfFlags(cmd);
    }

    if (!hasEntryPoint) {

      cmd += this->getDefaultEntryPoint();
    }
#if defined(__APPLE__)
    if (FlowWing::Cli::cmdl && !FlowWing::Cli::isFlag::linkerWarnings()) {
      cmd += "  -Wl,-w ";
    } else {
      cmd += "  -Wl,-w ";
    }
#endif

    // Linking with BuiltIn Module
    cmd += this->getRuntimeLibrariesLinked();

#if defined(AOT_TEST_MODE)
    cmd += " && ./" + FLOWWING::IR::CONSTANTS::TEMP_BIN_DIR + _outputFileName;
#endif

#if defined(__linux__)
    cmd += " -lstdc++ ";
#endif

#if defined(_WIN32)
    cmd += " ucrt.lib legacy_stdio_definitions.lib vcruntime.lib msvcrt.lib ";
    cmd += " /SUBSYSTEM:CONSOLE /IGNORE:4210 ";
#endif
    return cmd;
  }

private:
  auto getObjectFilesJoinedAsString() -> std::string {
    std::vector<std::string> objectFiles =
        Utils::getAllFilesInDirectoryWithExtension(
            FLOWWING::IR::CONSTANTS::TEMP_OBJECT_FILES_DIR,
            FLOWWING::IR::CONSTANTS::OBJECT_FILE_EXTENSION, false);

    std::string joined = "";
    for (const auto &objectFile : objectFiles) {
      joined += objectFile + " ";
    }
    return joined;
  }

  auto getOptimizationLevel() -> std::string {
    if (!FlowWing::Cli::cmdl) {
      return " -O3 ";
    }

    if (FlowWing::Cli::isFlag::OptimizationLevel0())
      return " -O0 ";

    if (FlowWing::Cli::isFlag::OptimizationLevel1())
      return " -O1 ";

    if (FlowWing::Cli::isFlag::OptimizationLevel2())
      return " -O2 ";

    if (FlowWing::Cli::isFlag::OptimizationLevel3())
      return " -O3 ";

    return " -O3 ";
  }

  auto getDefaultEntryPoint() -> std::string {

#if defined(_WIN32)
    return " /ENTRY:" + FLOWWING::IR::CONSTANTS::FLOWWING_GLOBAL_ENTRY_POINT +
           " ";
#endif

#if defined(__linux__)
    return "";
#endif

    return " -e _" + FLOWWING::IR::CONSTANTS::FLOWWING_GLOBAL_ENTRY_POINT + " ";
  }

  auto getEntryPoint(const std::string &key, const std::string &value)
      -> std::string {

#if defined(_WIN32)
    return "";
#elif defined(__linux__)
    return "";
#endif

    if (!hasEntryPoint &&
        FlowWing::Cli::OPTIONS::EntryPoint.name.c_str() == "-" + key) {
      hasEntryPoint = true;
      return " -e _" + value + " ";
    }

    return "";
  }

  auto getOutputArgument() -> std::string {

#if defined(_WIN32)
    return " /OUT:" + FLOWWING::IR::CONSTANTS::TEMP_BIN_DIR + _outputFileName +
           " ";
#endif

    return " -o " + FLOWWING::IR::CONSTANTS::TEMP_BIN_DIR + _outputFileName +
           " ";
  }

  auto getRuntimeLibrariesLinked() -> std::string {
    // A. Discover the location of our installed libraries at runtime.
    //    getAppResourcesPath() points to '.../share/FlowWing'
    //    So we navigate to '../lib/FlowWing' from there.
    std::filesystem::path runtimeLibPath =
        FlowWing::PathUtils::getLibrariesPath();

    std::string linkCmd = "";

    CODEGEN_DEBUG_LOG("runtimeLibPath", runtimeLibPath.string());

    // B. Add the "-L" flag to tell the linker where to search.
    linkCmd += createLibPathArg(runtimeLibPath.string());

    // C. Add the "-l" flags for each of your static libraries.
    for (const auto &lib :
         STATIC_LINKING_LIBRARIES) { // Assuming you have this list
      linkCmd += createLibArgs(lib);
    }
    return linkCmd;
  }

  auto createLibArgs(const std::string &libName) -> std::string {

#if defined(_WIN32)
    return " " + libName + ".lib ";
#endif

    return " -l" + libName + " ";
  }

  auto getOtherLibrariesPath(const std::string &key, const std::string &value)
      -> std::string {
    if (FlowWing::Cli::OPTIONS::LibraryPath.name == "-" + key) {
      return createLibPathArg(value);
    }

    return "";
  }

  auto createLibPathArg(const std::string &value) -> std::string {
#if defined(_WIN32)
    return " /LIBPATH:\"" + value + "\" ";
#else
    return " -L\"" + value + "\" ";
#endif
  }

  auto getLinkLibrary(const std::string &key, const std::string &value)
      -> std::string {
    if (FlowWing::Cli::OPTIONS::LinkLibrary.name == "-" + key) {
      return createLibArgs(value);
    }

    return "";
  }

  auto getFramework(const std::string &key, const std::string &value)
      -> std::string {
    if (FlowWing::Cli::OPTIONS::Framework.name == "-" + key)
      return " -framework " + value + " ";

    return "";
  }

  auto checkForRestOfFlags(std::string &cmd) -> void {
    if (FlowWing::Cli::isFlag::server() ||
        FlowWing::Cli::isFlag::shortServer()) {
      cmd += " " + createLibPathArg(FlowWing::PathUtils::getLibrariesPath()) +
             createLibArgs("flowwing_vortex") + " ";
    }
  }
};