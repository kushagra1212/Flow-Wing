#include "ModuleTest.h"

ModuleTest::ModuleTest() { _test = std::move(Tests::FlowWing::getTest()); }

void ModuleTest::SetUp() {
  _test->SetUp();
  namespace fs = std::filesystem;
  std::string buildDir = "../../aot-compiler/aot-compiler-build";

  if (!fs::exists(buildDir)) {
    if (!fs::create_directory(buildDir)) {
      std::cerr << "Failed to create directory: " << buildDir << std::endl;
      return;
    }
  }

  // Change to the build directory
  fs::current_path(buildDir);

  const std::string cmakeCommand =
      "cmake -G Ninja -DTESTS_ENABLED=OFF -DCMAKE_BUILD_TYPE=Release .. > " +
      FLOWWING::UTILS::CONSTANTS::NULL_DEVICE + " 2>&1";

  if (std::system(cmakeCommand.c_str()) != EXIT_SUCCESS) {
    std::cerr << "Failed to run cmake command" << std::endl;
    return;
  }

  std::string ninjaCommand =
      "ninja > " + FLOWWING::UTILS::CONSTANTS::NULL_DEVICE + " 2>&1";

  if (std::system(ninjaCommand.c_str()) != EXIT_SUCCESS) {
    std::cerr << "Failed to run ninja command" << std::endl;
    return;
  }
  return;
}

void ModuleTest::TearDown() { _test->TearDown(); }

void ModuleTest::setInput(const std::string &input) { _test->setInput(input); }

std::string ModuleTest::getOutput() const { return _test->getOutput(); }

void ModuleTest::runEvaluator() { _test->runEvaluator(); }

void ModuleTest::writeFile(const std::string &filename,
                           const std::string &code) {
  std::string moduleFilePath = currentPath.string() + "/" + filename;

  std::ofstream exportFile(moduleFilePath);
  exportFile << code;
  exportFile.close();
}

std::string ModuleTest::createBuildAndRunCmd(const std::string &fileName) {
  return (currentPath.string() + "/../aot-compiler-build" +
          "/FlowWing -O0 --F=" + currentPath.string() + "/" + fileName +
          " && build/bin/" + fileName.substr(0, fileName.find_last_of('.')));
}

TEST_F(ModuleTest, ModuleImportTest) {

  writeFile("test-module.fg", R"(module [test]
  
    var x:int = 2
  )");

  writeFile("temp.fg", R"(
    bring test
    print(test::x)
  )");

  std::system(createBuildAndRunCmd("temp.fg").c_str());

  O("\n0");
}

TEST_F(ModuleTest, ModuleImportTestFunction) {

  writeFile("test2-module.fg", R"(module [test2]
  
    var x:int = 2
 
 fun main2(x:int,s:str) -> nthg {
    print("Printing from Module Test "+x+s)
}
  )");

  writeFile("temp2.fg", R"(
bring test2

test2::main2(2,"s")
  )");

  std::system(createBuildAndRunCmd("temp2.fg").c_str());

  O("\nPrinting from Module Test 2s");
}

TEST_F(ModuleTest, ModuleImportTestCustomTypes) {

  writeFile("local-module.fg", R"(
module [local]


type T = {
    a:int
  }

  var x:local::T

fun main() -> nthg {
  print(local::x)
  }

  )");

  writeFile("temp.fg", R"(
bring local

local::main()
print(local::x)
  )");

  std::system(createBuildAndRunCmd("temp.fg").c_str());

  O("\n{ a : 0 }{ a : 0 }");
}
TEST_F(ModuleTest, ModuleImportTestCustomTypesAssignment) {

  writeFile("local-module.fg", R"(
module [local]


type T = {
    a:int
  }

  var x:local::T

fun main() -> nthg {
  local::x = {a:2}
print(local::x)
}

  )");

  writeFile("temp.fg", R"(
bring local


local::main()
  )");

  std::system(createBuildAndRunCmd("temp.fg").c_str());

  O("\n{ a : 2 }");
}
TEST_F(ModuleTest, ModuleImportTestCustomTypesAssignment2) {

  writeFile("local-module.fg", R"(
module [local]


type T = {
    a:int
  }

  var x:local::T

fun main() -> nthg {
  local::x = {a:2}
  var k:local::T
  print(k)
print(local::x)
}

  )");

  writeFile("temp.fg", R"(
bring local


local::main()
  )");

  std::system(createBuildAndRunCmd("temp.fg").c_str());

  O("\n{ a : 0 }{ a : 2 }");
}

TEST_F(ModuleTest, ModuleImportTestCustomTypesAssignment3) {

  writeFile("local-module.fg", R"(
module [local]


type T = {
    a:int
  }

  var x:local::T

fun main() -> nthg {
  local::x = {a:2}
  var k:local::T
  print(k)
print(local::x)
}

  )");

  writeFile("temp.fg", R"(
bring local



local::x = {a:3}
print(local::x)
local::main()

local::x = {a:3}
print(local::x)
  )");

  std::system(createBuildAndRunCmd("temp.fg").c_str());

  O("\n{ a : 3 }{ a : 0 }{ a : 2 }{ a : 3 }");
}
TEST_F(ModuleTest, ModuleImportTestCustomTypes2) {

  writeFile("local-module.fg", R"(
module [local]


type P ={
    a:int 
  }

type T = {
    a:int,
    b:str,
    c:deci,
    d:deci32,
    e:bool,
    f:local::P
  }

  var x:local::T

fun main() -> nthg {
  local::x = {a:2}
  var k:local::T
  print(k)
print(local::x)
}
  )");

  writeFile("temp.fg", R"(
bring local


var j:local::T = {a:5}


print(j)
  )");

  std::system(createBuildAndRunCmd("temp.fg").c_str());

  O("\n{ a : 5, b : '', c : 0.00000000000000, d : 0.0000000, e : false, f : { "
    "a : 0 } }");
}
TEST_F(ModuleTest, ModuleImportTestFunctionTest) {

  writeFile("local-module.fg", R"(
module [local]


type P ={
    a:int 
  }

type T = {
    a:int,
    b:str,
    c:deci,
    d:deci32,
    e:bool,
    f:local::P
  }

  var x:local::T


fun callMe(y:local::T) -> local::T {
  var p:local::T = y

  p.e = true

  return p

  
}

fun main() -> nthg {
  local::x = {a:2}
  var k:local::T
  print(k)
print(local::x)
}
  )");

  writeFile("temp.fg", R"(
bring local


print(local::callMe({a:10}))
  )");

  std::system(createBuildAndRunCmd("temp.fg").c_str());

  O("\n{ a : 10, b : '', c : 0.00000000000000, d : 0.0000000, e : true, f : { "
    "a : 0 } }");
}

TEST_F(ModuleTest, ModuleImportTestFunctionTest2) {

  writeFile("local-module.fg", R"(
module [local]


type P ={
    a:int 
  }

type T = {
    a:int,
    b:str,
    c:deci,
    d:deci32,
    e:bool,
    f:local::P
  }

  var x:local::T

fun main() -> nthg {
  local::x = {a:2}
  var k:local::T
  print(k)
print(local::x)
}
fun callMe(y:local::T) -> local::T {
  var p:local::T = y

  p.e = true
local::main()
  return p

  
}
  )");

  writeFile("temp.fg", R"(
bring local


print(local::callMe({a:10}))
  )");

  std::system(createBuildAndRunCmd("temp.fg").c_str());

  O("\n{ a : 0, b : '', c : 0.00000000000000, d : 0.0000000, e : false, f : { "
    "a : 0 } }{ a : 2, b : '', c : 0.00000000000000, d : 0.0000000, e : false, "
    "f : { a : 0 } }{ a : 10, b : '', c : 0.00000000000000, d : 0.0000000, e : "
    "true, f : { a : 0 } }");
}