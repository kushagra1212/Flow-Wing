#ifndef __FLOW__WING__AOT__COMPILER__H__
#define __FLOW__WING__AOT__COMPILER__H__

#include <gtest/gtest.h>

#include <cstdlib>
#include <fstream>
#include <iostream>

#include "../IR/IRGenerator.h"
#include "../IR/utils/fileSaver/ll-file/LLFileSaveStrategy.h"
#include "../compiler/Compiler.h"
#include "../parser/Parser.h"
#include "../utils/Utils.h"

class AOTCompiler : public Compiler {
 public:
  AOTCompiler(std::string filePath = "");

  void execute();
};

#endif  // __FLOW__WING__AOT__COMPILER__H__