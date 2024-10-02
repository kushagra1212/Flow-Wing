#pragma once

#include "../../Common.h"
#include "../../IR/constants/FlowWingIRConstants.h"
#include "../../cli/argh.h"
#include "../../cli/commandLineOptions/commandLineOptions.h"
#include "../../utils/Utils.h"
#include <string>

class CommandManager {
  std::string _outputFileNameWithoutExtension = "output";
  bool hasEntryPoint = false;

public:
  CommandManager(const std::string &outputFileNameWithoutExtension)
      : _outputFileNameWithoutExtension(outputFileNameWithoutExtension) {}

  auto inline create() -> std::string {
    std::string cmd = "";

    cmd += std::string(FLOWWING_CLANG_PATH) + " ";

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

    // Linking with BuiltIn Module
    cmd += this->getBuiltInModuleLinked();

#if defined(AOT_TEST_MODE)
    cmd += " && ./" + FLOWWING::IR::CONSTANTS::TEMP_BIN_DIR +
           _outputFileNameWithoutExtension;
#endif

#if defined(__linux__)
    cmd += " -lstdc++ ";
#endif

    return cmd;
  }

private:
  auto inline getObjectFilesJoinedAsString() -> std::string {
    std::vector<std::string> objectFiles =
        Utils::getAllFilesInDirectoryWithExtension(
            FLOWWING::IR::CONSTANTS::TEMP_OBJECT_FILES_DIR, ".o", false);
    std::string joined = "";
    for (const auto &objectFile : objectFiles) {
      joined += objectFile + " ";
    }
    return joined;
  }

  auto inline getOptimizationLevel() -> std::string {
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

  auto inline getDefaultEntryPoint() -> std::string {

#if defined(__linux__)
    return "";
#endif

    return " -e _" + FLOWWING::IR::CONSTANTS::FLOWWING_GLOBAL_ENTRY_POINT + " ";
  }

  auto inline getEntryPoint(const std::string &key, const std::string &value)
      -> std::string {

#if defined(__linux__)
    return "";
#endif

    if (!hasEntryPoint &&
        FlowWing::Cli::OPTIONS::EntryPoint.name.c_str() == "-" + key) {
      hasEntryPoint = true;
      return " -e _" + value + " ";
    }

    return "";
  }

  auto inline getOutputArgument() -> std::string {
    return " -o " + FLOWWING::IR::CONSTANTS::TEMP_BIN_DIR +
           _outputFileNameWithoutExtension + " ";
  }

  auto inline getBuiltInModuleLinked() -> std::string {

    // #if defined(AOT_TEST_MODE) || defined(AOT_MODE)
    //     return " -L" + std::string(FLOWWING_LIB_PATH) + " " +
    //            getDynamicLibraryPath("built_in_module") + " " +
    //            getDynamicLibraryPath("flowwing_string") + " ";
    // #else
    return " -L" + std::string(FLOWWING_LIB_PATH) + " " +
           getDynamicLibraryPath("built_in_module") + " " +
           getDynamicLibraryPath("flowwing_string") + " " +
           getDynamicLibraryPath("flowwing_vector") + " " +
           getDynamicLibraryPath("flowwing_map") + " ";

    // #endif
  }

  auto inline getDynamicLibraryPath(const std::string &libName) -> std::string {
    return " -l" + libName;
  }

  auto inline getOtherLibrariesPath(const std::string &key,
                                    const std::string &value) -> std::string {
    if (FlowWing::Cli::OPTIONS::LibraryPath.name == "-" + key)
      return " -L " + value + " ";

    return "";
  }

  auto inline getLinkLibrary(const std::string &key, const std::string &value)
      -> std::string {
    if (FlowWing::Cli::OPTIONS::LinkLibrary.name == "-" + key)
      return " -l " + value + " ";

    return "";
  }

  auto inline getFramework(const std::string &key, const std::string &value)
      -> std::string {
    if (FlowWing::Cli::OPTIONS::Framework.name == "-" + key)
      return " -framework " + value + " ";

    return "";
  }

  auto inline checkForRestOfFlags(std::string &cmd) -> void {
    if (FlowWing::Cli::isFlag::server() ||
        FlowWing::Cli::isFlag::shortServer()) {
      cmd += " -L" + std::string(FLOWWING_LIB_PATH) + " " +
             getDynamicLibraryPath("flowwing_vortex") + " ";
    }
  }
};
