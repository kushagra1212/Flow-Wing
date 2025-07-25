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


#ifndef __FLOW__WING__AOT__COMPILER__H__
#define __FLOW__WING__AOT__COMPILER__H__

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

#include "../../ASTBuilder/ASTBuilder.h"
#include "../../IR/IRGenerator.h"
#include "../../IR/utils/fileSaver/ll-file/LLFileSaveStrategy.h"
#include "../../common/managers/CommandManager.h"
#include "../../compiler/Compiler.h"
#include "../../utils/Utils.h"
#include "AotCompilerUtils.h"
#include "ObjectFile/ObjectFile.h"

class AOTCompiler : public Compiler {

public:
  AOTCompiler(std::string filePath = "",
              const bool &isFormattedCodeRequired = false);

  void link();
  void execute();
};

#endif // __FLOW__WING__AOT__COMPILER__H__