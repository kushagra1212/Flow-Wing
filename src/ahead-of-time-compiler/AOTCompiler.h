#ifndef __FLOW__WING__AOT__COMPILER__H__
#define __FLOW__WING__AOT__COMPILER__H__

#include <gtest/gtest.h>

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

#include "../ASTBuilder/ASTBuilder.h"
#include "../IR/IRGenerator.h"
#include "../IR/utils/fileSaver/ll-file/LLFileSaveStrategy.h"
#include "../common/managers/CommandManager.h"
#include "../compiler/Compiler.h"
#include "../utils/Utils.h"
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