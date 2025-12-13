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
  static void createObjectFile(const llvm::Module *llvm_module,
                               const std::string &file_path);

  static std::string getObjectFilePath(const std::string &file_path);
};

} // namespace ir_gen
} // namespace flow_wing