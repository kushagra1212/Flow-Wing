#pragma once

// clang-format off
#include "src/compiler/diagnostics/DiagnosticPush.hpp"
#include <llvm/IR/Module.h>
#include "src/compiler/diagnostics/DiagnosticPop.hpp"
// clang-format on

namespace flow_wing {
namespace ir_gen {

class ObjectUtils {
public:
  /// Returns false if LLVM could not write the object file.
  /// \param output_dir \c --output-dir; objects go under \c {output_dir}/objects/.
  static bool createObjectFile(const llvm::Module *llvm_module,
                               const std::string &file_path,
                               const std::string &output_dir);

  static std::string getObjectFilePath(const std::string &file_path,
                                       const std::string &output_dir);
};

} // namespace ir_gen
} // namespace flow_wing