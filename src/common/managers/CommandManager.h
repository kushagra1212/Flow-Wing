#pragma once

#include "../../IR/constants/FlowWingIRConstants.h"
#include "../../common/Common.h"
#include "../../common/commandLineOptions/commandLineOptions.h"
#include "../../external/include/argh.h"
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

    cmd += std::string(FLOWWING_LINKER_PATH) + " ";

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
    cmd += this->getBuiltInModuleLinked();

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

  auto getBuiltInModuleLinked() -> std::string {

    std::string linkLibs = "";
    auto absPath =
        std::filesystem::absolute(std::filesystem::path(FLOWWING_LIB_PATH));

    linkLibs += createLibPathArg(absPath.string());

    for (const auto lib : DYNAMIC_LINKING_LIBRARIES) {

      linkLibs += createLibArgs(lib);
    }

    for (const auto lib : STATIC_LINKING_LIBRARIES) {

      linkLibs += createLibArgs(lib);
    }

    return linkLibs;
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
    return " /LIBPATH:" + value + " ";
#else
    return " -L " + value + " ";
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
      cmd += " " + createLibPathArg(std::string(FLOWWING_LIB_PATH)) +
             createLibArgs("flowwing_vortex") + " ";
    }
  }
};
