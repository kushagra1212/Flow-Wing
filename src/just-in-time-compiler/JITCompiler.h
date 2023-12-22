#ifndef JITCOMPILER_H
#define JITCOMPILER_H

#include "../IR/IRGenerator.h"
#include "../IR/utils/fileSaver/ll-file/LLFileSaveStrategy.h"
#include "../compiler/Compiler.h"
#include "../parser/Parser.h"
#include "../utils/Utils.h"
#include <fstream>
#include <gtest/gtest.h>
#include <iostream>

class JITCompiler : public Compiler {

public:
  JITCompiler(std::string filePath = "");

  void execute() override;
};

#endif // JITCOMPILER_H