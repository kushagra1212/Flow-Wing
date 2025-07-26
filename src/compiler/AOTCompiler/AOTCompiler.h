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

#pragma once

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

#include "AotCompilerUtils.h"
#include "ObjectFile/ObjectFile.h"
#include "src/ASTBuilder/ASTBuilder.h"
#include "src/IR/IRGenerator.h"
#include "src/IR/utils/fileSaver/ll-file/LLFileSaveStrategy.h"
#include "src/common/managers/CommandManager.h"
#include "src/compiler/Compiler.h"
#include "src/utils/Utils.h"

class AOTCompiler : public Compiler {

public:
  AOTCompiler(std::string filePath = "",
              const bool &isFormattedCodeRequired = false);

  void link();
  void execute();
};