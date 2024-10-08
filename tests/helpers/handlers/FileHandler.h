#pragma once

#include "../../Common.h"

class FileHandler {

public:
  FileHandler() {

#if defined(AOT_TEST_MODE)
    buildFolder = "aot-compiler-build-for-test";
#elif defined(JIT_TEST_MODE)
    buildFolder = "jit-compiler-build-for-test";
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

    std::string buildDir = "";
#if defined(AOT_TEST_MODE)
    buildDir = "../../aot-compiler/" + buildFolder;
#elif defined(JIT_TEST_MODE)
    buildDir = "../../jit-compiler/" + buildFolder;
#endif

    createDirectory(buildDir);

    // Change to the build directory
    std::filesystem::current_path(buildDir);

    const std::string cmakeCommand = "cmake -G Ninja -DTESTS_ENABLED=OFF "
                                     "-DCMAKE_BUILD_TYPE=Release .. > " +
                                     FLOWWING::UTILS::CONSTANTS::NULL_DEVICE +
                                     " 2>&1";

    if (std::system(cmakeCommand.c_str()) != EXIT_SUCCESS) {
      removeDirectory(buildDir);
      createDirectory(buildDir);

      // Change to the build directory
      std::filesystem::current_path(buildDir);
      if (std::system(cmakeCommand.c_str()) != EXIT_SUCCESS) {
        std::cerr << "Failed to run cmake command" << std::endl;
        return;
      }
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
    return (currentPath.string() + "/../" + buildFolder +
            "/FlowWing -O0 --F=" + currentPath.string() + "/" + fileName +
            " && build/bin/" + fileName.substr(0, fileName.find_last_of('.')));
  }

private:
  std::string buildFolder = "";
  std::filesystem::path currentPath = std::filesystem::current_path();
};