#pragma once

#include "src/common/cli/CliReporter.h"
#include <string>

// clang-format off
#include "src/compiler/diagnostics/DiagnosticPush.hpp"
#include <llvm/Support/FileSystem.h>
#include "src/compiler/diagnostics/DiagnosticPop.hpp"
// clang-format on

namespace flow_wing {
namespace ir_gen {

class Utils {
public:
  static int8_t createDirectories(const std::string &path) {
    std::error_code rm_ec = llvm::sys::fs::remove_directories(path);

    if (rm_ec && rm_ec != std::errc::no_such_file_or_directory) {

      cli::Reporter::error("Failed to remove directory '" + path +
                           "': " + rm_ec.message());

      return EXIT_FAILURE;
    }

    std::error_code create_ec = llvm::sys::fs::create_directories(path);

    if (create_ec) {
      cli::Reporter::error("Failed to create directory '" + path +
                           "': " + create_ec.message());

      return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
  }
};

} // namespace ir_gen
} // namespace flow_wing