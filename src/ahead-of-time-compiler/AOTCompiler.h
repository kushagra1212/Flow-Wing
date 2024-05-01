#ifndef __FLOW__WING__AOT__COMPILER__H__
#define __FLOW__WING__AOT__COMPILER__H__

#include <gtest/gtest.h>

#include <cstdlib>
#include <fstream>
#include <iostream>

#include "../IR/IRGenerator.h"
#include "../IR/utils/fileSaver/ll-file/LLFileSaveStrategy.h"
#include "../compiler/Compiler.h"
#include "../parser/Parser.h"
#include "../utils/Utils.h"
#include "ObjectFile/ObjectFile.h"

class AOTCompiler : public Compiler {
public:
  AOTCompiler(std::string filePath = "",
              const bool &isFormattedCodeRequired = false);

  auto inline getClangFilePath() -> std::filesystem::path {
    std::filesystem::path CLANG_PATH = "";

#if defined(__linux__)
    CLANG_PATH = "/usr/bin/clang-17";
#elif defined(__APPLE__)
    CLANG_PATH = "/usr/bin/clang";
#endif

    return CLANG_PATH;
  }

  auto inline getLibPath() -> std::filesystem::path {
    std::filesystem::path LIB_PATH = "";

#if defined(__linux__)
    LIB_PATH = "/usr/local/lib/FlowWing";
#elif defined(__APPLE__)
    LIB_PATH = "/Users/apple/code/per/Flow-Wing/lib/mac-silicon/lib";
#endif

    return LIB_PATH;
  }

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

  auto inline deleteObjectFiles() -> void {
    std::vector<std::string> objectFiles =
        Utils::getAllFilesInDirectoryWithExtension(
            FLOWWING::IR::CONSTANTS::TEMP_OBJECT_FILES_DIR, ".o", false);
    for (const auto &objectFile : objectFiles) {
      std::filesystem::remove(objectFile);
    }
  }

  void link();
  void execute();
};

#endif // __FLOW__WING__AOT__COMPILER__H__