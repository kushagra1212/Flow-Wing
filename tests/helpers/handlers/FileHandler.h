#pragma once

#include "../../Common.h"

class FileHandler {

public:
  void initialize() {
    namespace fs = std::filesystem;
    std::string buildDir = "../../aot-compiler/aot-compiler-build";

    if (!fs::exists(buildDir)) {
      if (!fs::create_directory(buildDir)) {
        std::cerr << "Failed to create directory: " << buildDir << std::endl;
        return;
      }
    }

    // Change to the build directory
    fs::current_path(buildDir);

    const std::string cmakeCommand =
        "cmake -G Ninja -DTESTS_ENABLED=OFF -DCMAKE_BUILD_TYPE=Release .. > " +
        FLOWWING::UTILS::CONSTANTS::NULL_DEVICE + " 2>&1";

    if (std::system(cmakeCommand.c_str()) != EXIT_SUCCESS) {
      std::cerr << "Failed to run cmake command" << std::endl;
      return;
    }

    std::string ninjaCommand =
        "ninja > " + FLOWWING::UTILS::CONSTANTS::NULL_DEVICE + " 2>&1";

    if (std::system(ninjaCommand.c_str()) != EXIT_SUCCESS) {
      std::cerr << "Failed to run ninja command" << std::endl;
      return;
    }
    return;
  }

  void writeFile(const std::string &filename, const std::string &code) {
    std::string moduleFilePath = currentPath.string() + "/" + filename;

    std::ofstream exportFile(moduleFilePath);
    exportFile << code;
    exportFile.close();
  }

  std::string createBuildAndRunCmd(const std::string &fileName) {
    return (currentPath.string() + "/../aot-compiler-build" +
            "/FlowWing -O0 --F=" + currentPath.string() + "/" + fileName +
            " && build/bin/" + fileName.substr(0, fileName.find_last_of('.')));
  }

  std::filesystem::path currentPath = std::filesystem::current_path();
};