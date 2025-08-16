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

#include "CommandManager.h"
#include "src/IR/constants/FlowWingIRConstants.h"
#include "src/common/LibUtils/LibUtils.h"
#include "src/common/commandLineOptions/commandLineOptions.h"
#include "src/utils/LogConfig.h"
#include "src/utils/PathUtils.h"
#include "src/utils/Utils.h"

CommandManager::CommandManager(
    const std::string &outputFileNameWithoutExtension)
    : _outputFileName(outputFileNameWithoutExtension) {

#if defined(_WIN32)
  _outputFileName += ".exe";
#endif
}

auto CommandManager::create() -> std::string {
  std::string cmd = "";

  cmd += FlowWing::PathUtils::getAOTLinkerPath() + " ";

#if defined(__APPLE__)
  cmd += std::string(MACOS_SDK_SYSROOT_FLAG) + " ";
#endif

#if defined(__linux__)
  cmd += " -fuse-ld=lld ";
#endif
#if defined(_WIN32)
  cmd += " /nologo "; 
#endif

  // cmd += this->getOptimizationLevel();

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


#if defined(__linux__)
  cmd += " -lstdc++ ";
#endif

#if defined(_WIN32)
  cmd += "  ucrt.lib vcruntime.lib kernel32.lib user32.lib advapi32.lib msvcrt.lib legacy_stdio_definitions.lib ";
  cmd += " /SUBSYSTEM:CONSOLE /IGNORE:4210 ";
#endif


#if defined(AOT_TEST_MODE) && defined(_unix_) 
  cmd += " && ./" + FLOWWING::IR::CONSTANTS::TEMP_BIN_DIR + _outputFileName +" ";
#elif defined(AOT_TEST_MODE) && defined(_WIN32)
  cmd += " && " + FLOWWING::IR::CONSTANTS::TEMP_BIN_DIR + _outputFileName +" ";
#endif

  return cmd;
}

auto CommandManager::getObjectFilesJoinedAsString() -> std::string {
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

auto CommandManager::getOptimizationLevel() -> std::string {
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

auto CommandManager::getDefaultEntryPoint() -> std::string {

#if defined(_WIN32)
  return " ";
#elif defined(__linux__)
  return "";

#elif defined(__APPLE__)
  return " -e _" + FLOWWING::IR::CONSTANTS::FLOWWING_GLOBAL_ENTRY_POINT + " ";

  #endif
}

auto CommandManager::getEntryPoint([[maybe_unused]] const std::string &key,
                                   [[maybe_unused]] const std::string &value)
    -> std::string {

#if defined(_WIN32)
  return "";
#elif defined(__linux__)
  return "";
#elif defined(__APPLE__)
  if (!hasEntryPoint &&
      FlowWing::Cli::OPTIONS::EntryPoint.name.c_str() == "-" + key) {
    hasEntryPoint = true;
    return " -e _" + value + " ";
  }

  return "";
#endif
}

auto CommandManager::getOutputArgument() -> std::string {

#if defined(_WIN32)
  return " /OUT:" + FLOWWING::IR::CONSTANTS::TEMP_BIN_DIR + _outputFileName +
         " ";
#else
  return " -o " + FLOWWING::IR::CONSTANTS::TEMP_BIN_DIR + _outputFileName + " ";
  #endif
}

auto CommandManager::getRuntimeLibrariesLinked() -> std::string {
  // A. Discover the location of our installed libraries at runtime.
  //    getAppResourcesPath() points to '.../share/FlowWing'
  //    So we navigate to '../lib/FlowWing' from there.
  std::string runtimeLibPath = FlowWing::PathUtils::getLibrariesPath().string();

  std::string linkCmd = "";

  LINKING_DEBUG_LOG("runtimeLibPath ", runtimeLibPath);

  const std::string &libPath = createLibPathArg(runtimeLibPath);

  // B. Add the "-L" flag to tell the linker where to search.
  linkCmd += libPath;

  // C. Add the "-l" flags for each of your static libraries.
  for (const auto &lib :
       STATIC_LINKING_LIBRARIES) { // Assuming you have this list
    linkCmd += createLibArgs(lib);
  }

  LINKING_DEBUG_LOG("FlowWing Lib  ", linkCmd);
  return linkCmd;
}

auto CommandManager::createLibArgs(const std::string &libName) -> std::string {

#if defined(_WIN32)
  return " " + libName + ".lib ";
#else
  return " -l" + libName + " ";
  #endif

}

auto CommandManager::getOtherLibrariesPath(const std::string &key,
                                           const std::string &value)
    -> std::string {
  if (FlowWing::Cli::OPTIONS::LibraryPath.name == "-" + key) {
    return createLibPathArg(value);
  }

  return "";
}

auto CommandManager::createLibPathArg(const std::string &value) -> std::string {
#if defined(_WIN32)
  return " /LIBPATH:\"" + value + "\" ";
#else
  return " -L\"" + value + "\" ";
#endif
}

auto CommandManager::getLinkLibrary(const std::string &key,
                                    const std::string &value) -> std::string {
  if (FlowWing::Cli::OPTIONS::LinkLibrary.name == "-" + key) {
    return createLibArgs(value);
  }

  return "";
}

auto CommandManager::getFramework(const std::string &key,
                                  const std::string &value) -> std::string {
  if (FlowWing::Cli::OPTIONS::Framework.name == "-" + key)
    return " -framework " + value + " ";

  return "";
}

auto CommandManager::checkForRestOfFlags(std::string &cmd) -> void {
  if (FlowWing::Cli::isFlag::server() || FlowWing::Cli::isFlag::shortServer()) {
    cmd += " " +
           createLibPathArg(FlowWing::PathUtils::getLibrariesPath().string()) +
           createLibArgs("flowwing_vortex") + " ";
  }
}