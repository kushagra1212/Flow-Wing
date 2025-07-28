/*
 * FlowWing Compiler
 * Copyright (C) 2023-2025 Kushagra Rathore
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include "BCFileSaveStrategy.h"
#include "src/IR/logger/LLVMLogger.h"
#include "src/utils/Utils.h"
#include <iostream>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-parameter"
#include <llvm/Bitcode/BitcodeWriter.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Transforms/Utils/Cloning.h>
#pragma clang diagnostic pop

BCFileSaveStrategy::BCFileSaveStrategy(LLVMLogger *llvmLogger) {
  logger = llvmLogger;
}

bool BCFileSaveStrategy::saveToFile(const std::string &path,
                                    llvm::Module *module) const {

  // Create an output stream for the .bc file
  std::error_code EC;
  llvm::raw_fd_ostream OS(path, EC, llvm::sys::fs::OF_None);

  // llvm::legacy::PassManager pass = llvm::legacy::PassManager();
  // pass.add(llvm::createVerifierPass());
  // pass.add(llvm::createCFGSimplificationPass());
  // pass.add(llvm::createDeadCodeEliminationPass());
  // pass.run(*module);

  if (!EC) {
    // Write the LLVM module to the .bc file
    llvm::WriteBitcodeToFile(*module, OS);
    OS.flush();
    return true;
  } else {

    const std::string errorString = "Error opening " +
                                    Utils::getFileName(path) +
                                    " for writing: " + EC.message();
    if (logger == nullptr) {
      std::cerr << errorString;
    } else {
      logger->LogError(errorString);
    }

    return false;
  }
}