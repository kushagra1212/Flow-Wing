#ifndef __FLOW__WING__AOT__COMPILER__H__
#define __FLOW__WING__AOT__COMPILER__H__

#include <gtest/gtest.h>

#include <cstdlib>
#include <fstream>
#include <iostream>

#include "../IR/IRGenerator.h"
#include "../IR/utils/fileSaver/ll-file/LLFileSaveStrategy.h"
#include "../common/managers/CommandManager.h"
#include "../common/managers/PathManager.h"
#include "../compiler/Compiler.h"
#include "../parser/Parser.h"
#include "../utils/Utils.h"
#include "ObjectFile/ObjectFile.h"

class AOTCompiler : public Compiler {
  argh::parser *_cmdl;

public:
  AOTCompiler(std::string filePath = "", argh::parser *cmdl = nullptr,
              const bool &isFormattedCodeRequired = false);

  auto inline deleteObjectFiles() -> void {
    std::vector<std::string> objectFiles =
        Utils::getAllFilesInDirectoryWithExtension(
            FLOWWING::IR::CONSTANTS::TEMP_OBJECT_FILES_DIR, ".o", false);
    for (const auto &objectFile : objectFiles) {
      std::filesystem::remove(objectFile);
    }
  }

  auto inline getFileNameWithoutExtension() -> std::string {

#if defined(AOT_TEST_MODE)
    return FLOWWING::IR::CONSTANTS::FLOWWING_GLOBAL_ENTRY_POINT;
#endif

    return Utils::removeExtensionFromString(
        Utils::getFileName(_currentDiagnosticHandler->getAbsoluteFilePath()));
  }
  void link();
  void execute();

  // LOGS

  inline auto LINKING_FAIL_ERROR(int status,
                                 std::string &fileNameWithOutExtension,
                                 std::string version) {
    Utils::printErrors(
        {(std::string)YELLOW_TEXT + "FlowWing " + (version) + ": " +
         std::string(RED_TEXT) +
         " failed with non zero status: " + std::to_string(status)},
        std::cerr, false);
    Utils::printErrors({"Failed to link: " + fileNameWithOutExtension},
                       std::cerr, false);
  }

  inline auto DEBUG_LOG_LL_FILES_INFO() {
#if (defined(DEBUG) && defined(JIT_MODE)) ||                                   \
    (defined(DEBUG) && defined(AOT_MODE))
    std::vector<std::string> llFiles =
        Utils::getAllFilesInDirectoryWithExtension(
            std::filesystem::current_path(), ".ll", false);

    for (auto llFile : llFiles) {
      std::string cmd = PathManager::getClangPath().string() + " " + llFile +
                        " -emit-llvm -c " + " -o " +
                        llFile.substr(0, llFile.length() - 3) + ".bc";
      std::cout << BLUE_TEXT << "Compiling: " << GREEN << llFile << RESET
                << std::endl;
      const int status = std::system(cmd.c_str());

      if (status != 0) {

        std::cerr << Utils::CE("Failed to compile: ") << llFile << std::endl;
        return;
      }
    }

#endif
  }

  inline auto DEBUG_LOG_LINKING_INFO(std::string &cmd) {

#if (defined(DEBUG) && defined(JIT_MODE)) ||                                   \
    (defined(DEBUG) && defined(AOT_MODE))

    std::cout << YELLOW_TEXT << "[Linking]: " << GREEN << cmd << RESET
              << std::endl;
#endif
  }
};

#endif // __FLOW__WING__AOT__COMPILER__H__