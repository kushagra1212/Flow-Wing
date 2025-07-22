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