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
  /// Ensure a directory exists (and parents). Does not remove existing
  /// directories — shared output dirs (e.g. build/objects/.../same_folder) must
  /// keep sibling .o files when emitting multiple TUs.
  static int8_t createDirectories(const std::string &path) {
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