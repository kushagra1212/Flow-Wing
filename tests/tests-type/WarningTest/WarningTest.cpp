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


#include "WarningTest.h"
#include "../../../src/diagnostics/Diagnostic/DiagnosticCodeData.h"

void WarningTest::SetUp() { _test->SetUp(true); }

void WarningTest::TearDown() { _test->TearDown(); }

TEST_F(WarningTest, MultipleClassDeclarationImportModuleWithErrorsWarning) {
  writeFile("test1-module.fg", R"(
module [test1]
class A {
  type T = {
    a: int
  }
  var x: T
  var u: int
  init() -> nthg {
  }


  printX() -> nthg {
    print(self.x)
  }


}



class A {
  type T = {
    a: int
  }
  var x: T
  var u: int
  init() -> nthg {
  }


  printX() -> nthg {
    print(self.x)
  }


}

  )");

  writeFile("test2.fg", R"(
bring test1
  )");

  std::system(createBuildAndRunCmd("test2.fg").c_str());

  EXPECT_ERROR_CODE(
      FLOW_WING::DIAGNOSTIC::DiagnosticCode::ImportModuleWithErrorsWarning);
}

TEST_F(WarningTest, MultipleVariableDeclarationImportModuleWithErrorsWarning) {
  writeFile("test1-module.fg", R"(
module [local]
var x: int = 2
var x ="Hello"

  )");

  writeFile("test2.fg", R"(
bring test1
  )");

  std::system(createBuildAndRunCmd("test2.fg").c_str());

  EXPECT_ERROR_CODE(
      FLOW_WING::DIAGNOSTIC::DiagnosticCode::ImportModuleWithErrorsWarning);
}

TEST_F(WarningTest, MultipleFunctionImportModuleWithErrorsWarning) {
  writeFile("test1-module.fg", R"(
module [local]
fun test2() -> nthg {
}

fun test2() -> nthg {
}
  )");

  writeFile("test2.fg", R"(
bring test1
  )");

  std::system(createBuildAndRunCmd("test2.fg").c_str());

  EXPECT_ERROR_CODE(
      FLOW_WING::DIAGNOSTIC::DiagnosticCode::ImportModuleWithErrorsWarning);
}

TEST_F(WarningTest, MultipleTypeImportModuleWithErrorsWarning) {
  writeFile("test1-module.fg", R"(
module [local]
type T = {
  a: int,
  b: deci
}
type T = {
  a: int,
  b: deci
}
  )");

  writeFile("test2.fg", R"(
bring test1
  )");

  std::system(createBuildAndRunCmd("test2.fg").c_str());

  EXPECT_ERROR_CODE(
      FLOW_WING::DIAGNOSTIC::DiagnosticCode::ImportModuleWithErrorsWarning);
}