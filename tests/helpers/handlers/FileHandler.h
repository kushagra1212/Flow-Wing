#pragma once

#include "../../Common.h"

class FileHandler {

public:
  FileHandler() {

#if defined(AOT_TEST_MODE)
    compilerType = "aot";
#endif
  }

  void createDirectory(const std::string &path) {

    if (!std::filesystem::exists(path)) {
      if (!std::filesystem::create_directory(path)) {
        std::cerr << "Failed to create directory: " << path << std::endl;
        return;
      }
    }
  }

  void removeDirectory(const std::string &path) {

    // Check if directory exists and remove it
    if (std::filesystem::exists(path)) {
      if (!std::filesystem::remove_all(path)) {
        std::cerr << "Failed to delete directory: " << path << std::endl;
        return; // Return an error code
      }
    }
  }

  void initialize() {

    std::string makeCommand =
        "make build-" + compilerType + "-release SILENT=1";

    std::string ninjaCommand =
        ("cd " + currentPath.string() + "/../../ && " + makeCommand + " ") +
        " > " + FLOWWING::UTILS::CONSTANTS::NULL_DEVICE + " 2>&1";

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

    const std::string buildFolder = compilerType + "-release-dev";
    std::string runCMD =
        ("cd " + currentPath.string() + "/../" + buildFolder + " && " +
         "./FlowWing " + currentPath.string() + "/" + fileName + " ");

#if AOT_TEST_MODE
    runCMD += " && " + currentPath.string() + "/../" + buildFolder +
              "/build/bin/" + fileName.substr(0, fileName.find_last_of('.'));
#endif

    return runCMD;
  }

private:
  std::string compilerType = "jit";
  std::filesystem::path currentPath = std::filesystem::current_path();
};