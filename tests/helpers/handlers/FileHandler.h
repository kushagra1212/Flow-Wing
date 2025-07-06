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

  void redirectOutputToCout(const std::string &cmd) {

    // 2. Append the shell redirection to capture stderr.
    //    " 2>&1" redirects stream 2 (stderr) to stream 1 (stdout).
    std::string cmd_with_redirect = cmd + " 2>&1";

    std::cout << "--- Executing command: " << cmd_with_redirect << std::endl;
    std::cout << "--- Capturing output and piping to std::cout:" << std::endl;

    // 3. Use popen to execute the command and open a pipe for reading.
    //    The "r" means we are opening the pipe in "read" mode.
    FILE *pipe = popen(cmd_with_redirect.c_str(), "r");
    if (!pipe) {
      std::cout << "popen() failed!" << std::endl;
    }

    // 4. Read the output from the pipe line by line and write it to std::cerr.
    std::array<char, 256> buffer;
    while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
      std::cout << buffer.data();
    }

    // 5. Close the pipe and get the command's exit status.
    //    This is a crucial step! It waits for the command to finish.
    int exit_status = pclose(pipe);
  }

  std::string createBuildAndRunCmd(const std::string &fileName) {
    std::string runCMD =
        (currentPath.string() + "/../" + buildFolder +
         "/FlowWing -O0 --F=" + currentPath.string() + "/" + fileName);

#if defined(AOT_MODE) || defined(AOT_TEST_MODE)
    runCMD += " && build/bin/" + fileName.substr(0, fileName.find_last_of('.'));
#endif

    return runCMD;
  }

private:
  std::string buildFolder = "";
  std::filesystem::path currentPath = std::filesystem::current_path();
};