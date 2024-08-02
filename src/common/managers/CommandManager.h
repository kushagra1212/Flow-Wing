#pragma once

#include "../../Common.h"
#include "../../IR/constants/FlowWingIRConstants.h"
#include "../../cli/argh.h"
#include "../../cli/commandLineOptions/commandLineOptions.h"
#include "../../utils/Utils.h"
#include "PathManager.h"

class CommandManager {

  argh::parser *_cmdl;
  std::string _outputFileNameWithoutExtension = "output";

public:
  CommandManager(argh::parser *cmdl,
                 const std::string &outputFileNameWithoutExtension)
      : _cmdl(cmdl),
        _outputFileNameWithoutExtension(outputFileNameWithoutExtension) {}

  auto inline create() -> std::string {
    std::string cmd = "";

    cmd += PathManager::getClangPath().string() + " ";

    cmd += this->getOptimizationLevel();

    cmd += this->getOutputArgument();

    cmd += this->getEntryPoint();

    cmd += this->getObjectFilesJoinedAsString();

    // Linking with BuiltIn Module
    cmd += this->getBuiltInModuleLinked();

    for (const auto &[key, value] : (*_cmdl).params()) {
      cmd += this->getOtherLibrariesPath(key, value);
      cmd += this->getLinkLibrary(key, value);
      cmd += this->getFramework(key, value);
    }

#if defined(AOT_TEST_MODE)
    cmd += " && ./" + FLOWWING::IR::CONSTANTS::TEMP_BIN_DIR +
           fileNameWithOutExtension;
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
    if ((*_cmdl)[{
            FlowWingCliOptions::OPTIONS::OptimizationLevel0.name.c_str()}])
      return " -O0 ";

    if ((*_cmdl)[{
            FlowWingCliOptions::OPTIONS::OptimizationLevel1.name.c_str()}])
      return " -O1 ";

    if ((*_cmdl)[{
            FlowWingCliOptions::OPTIONS::OptimizationLevel2.name.c_str()}])
      return " -O2 ";

    if ((*_cmdl)[{
            FlowWingCliOptions::OPTIONS::OptimizationLevel3.name.c_str()}])
      return " -O3 ";

    return "";
  }

  auto inline getEntryPoint() -> std::string {
    return " -e _" + FLOWWING::IR::CONSTANTS::FLOWWING_GLOBAL_ENTRY_POINT + " ";
  }

  auto inline getOutputArgument() -> std::string {
    return " -o " + FLOWWING::IR::CONSTANTS::TEMP_BIN_DIR +
           _outputFileNameWithoutExtension + " ";
  }

  auto inline getBuiltInModuleLinked() -> std::string {
    return " -L " + PathManager::getLibPath().string() + " -l built_in_module ";
  }

  auto inline getOtherLibrariesPath(const std::string &key,
                                    const std::string &value) -> std::string {

    if (FlowWingCliOptions::OPTIONS::LibraryPath.name == "-" + key)
      return " -L " + value + " ";

    return "";
  }

  auto inline getLinkLibrary(const std::string &key, const std::string &value)
      -> std::string {
    if (FlowWingCliOptions::OPTIONS::LinkLibrary.name == "-" + key)
      return " -l " + value + " ";

    return "";
  }

  auto inline getFramework(const std::string &key, const std::string &value)
      -> std::string {
    if (FlowWingCliOptions::OPTIONS::Framework.name == "-" + key)
      return " -framework " + value + " ";

    return "";
  }
};
