#include "BringTest.h"

BringTest::BringTest() { _test = std::move(Tests::FlowWing::getTest()); }

void BringTest::SetUp() {
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

void BringTest::TearDown() { _test->TearDown(); }

void BringTest::setInput(const std::string &input) { _test->setInput(input); }

std::string BringTest::getOutput() const { return _test->getOutput(); }

void BringTest::runEvaluator() { _test->runEvaluator(); }

void BringTest::writeFile(const std::string &filename,
                          const std::string &code) {
  std::string moduleFilePath = currentPath.string() + "/" + filename;

  std::ofstream exportFile(moduleFilePath);
  exportFile << code;
  exportFile.close();
}

std::string BringTest::createBuildAndRunCmd(const std::string &fileName) {
  return (currentPath.string() + "/../aot-compiler-build" +
          "/FlowWing -O0 --F=" + currentPath.string() + "/" + fileName +
          " && build/bin/" + fileName.substr(0, fileName.find_last_of('.')));
}
TEST_F(BringTest, BringTestBasicTestAll) {

  writeFile("file1.fg", R"(
var x:int = 2

type TB = {
    s:str 
  }

type T  ={
    a:int,
    b:TB[2]
}

var k:T = {}

var j:T[2] 

class  A {
  var x:int 
  var y:T  
  
  init(y:T ) -> nthg {
    self.y = y 
  }

  printY() -> nthg {
      print(self.y)
  }

}




fun callS(x:int ) -> nthg {
  var aF:A = new A({b:[{s:"Hello"}]})
  print("Printing af ",aF.y)

  print("Printing k ",k)

  print("Print local x",x)
}
  )");

  writeFile("task.fg", R"(
bring "file1.fg"


print(x)

print(k)

print(j)



callS(88)

var p:T  

p = {a:2 }
print("print p ",p )
  )");

  std::system(createBuildAndRunCmd("task.fg").c_str());

  O("\n2{ a : 0, b : [{ s : '' }, { s : '' }] }[{ a : 0, b : [{ s : '' }, { s "
    ": '' }] }, { a : 0, b : [{ s : '' }, { s : '' }] }]Printing af { a : 0, b "
    ": [{ s : 'Hello' }, { s : '' }] }Printing k { a : 0, b : [{ s : '' }, { s "
    ": '' }] }Print local x88print p { a : 2, b : [{ s : '' }, { s : '' }] }");
}

TEST_F(BringTest, BringTestBasicTestAllChoosy) {

  writeFile("file1.fg", R"(
expose var x:int = 2

expose type TB = {
    s:str 
  }

expose type T  ={
    a:int,
    b:TB[2]
}

expose var k:T = {}

expose var j:T[2] 

expose class  A {
  var x:int 
  var y:T  
  
  init(y:T ) -> nthg {
    self.y = y 
  }

  printY() -> nthg {
      print(self.y)
  }

}




expose fun callS(x:int ) -> nthg {
  var aF:A = new A({b:[{s:"Hello"}]})
  print("Printing af ",aF.y)

  print("Printing k ",k)

  print("Print local x",x)
}
  )");

  writeFile("task.fg", R"(
bring {x,k,j,callS} from "file1.fg"


print(x)

print(k)

print(j)



callS(88)

var p:T  

p = {a:2 }
print("print p ",p )

var g:A = new A({})

g.printY()
  )");

  std::system(createBuildAndRunCmd("task.fg").c_str());

  O("\n2{ a : 0, b : [{ s : '' }, { s : '' }] }[{ a : 0, b : [{ s : '' }, { s "
    ": '' }] }, { a : 0, b : [{ s : '' }, { s : '' }] }]Printing af { a : 0, b "
    ": [{ s : 'Hello' }, { s : '' }] }Printing k { a : 0, b : [{ s : '' }, { s "
    ": '' }] }Print local x88print p { a : 2, b : [{ s : '' }, { s : '' }] }{ "
    "a : 0, b : [{ s : '' }, { s : '' }] }");
}