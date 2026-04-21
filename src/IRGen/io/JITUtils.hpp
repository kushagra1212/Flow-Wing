#pragma once

#include "src/IRGen/FlowWingConstants/FlowWingConstants.hpp"
#include "src/IRGen/io/Utils.hpp"
#include <filesystem>
#include <fstream>
#include <string>
#if defined(_WIN32)
#include <algorithm> // std::replace — only used in the Windows colon-strip branch.
#endif

namespace flow_wing {
namespace ir_gen {

namespace jit_utils {

static inline std::string
getIRFilePath(const std::string &parent_directory_path,
              const std::string &file_path) {
  std::filesystem::path p(file_path);
  if (p.is_absolute()) {
    p = p.relative_path();
  }
  std::string rel = p.string();
#if defined(_WIN32)
  std::replace(rel.begin(), rel.end(), ':', '_');
#endif
  return std::string(parent_directory_path) + rel +
         std::string(constants::paths::kIR_files_extension);
}

static inline void saveIRToFile(const std::string &llvm_ir,
                                const std::string &parent_directory_path,
                                const std::string &file_path) {

  const std::string ir_file_path =
      getIRFilePath(parent_directory_path, file_path);
  std::filesystem::path ir_directory =
      std::filesystem::path(ir_file_path).parent_path();
  Utils::createDirectories(ir_directory.string());

  std::ofstream ir_file(ir_file_path);
  ir_file << llvm_ir;
  ir_file.close();
}
} // namespace jit_utils

} // namespace ir_gen
} // namespace flow_wing
