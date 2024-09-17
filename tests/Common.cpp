#include "Common.h"
namespace Tests {
namespace FlowWing {
std::unique_ptr<BaseTest> getTest() {
  std::unique_ptr<BaseTest> _test;
#ifdef JIT_TEST_MODE
  _test = std::make_unique<JITCompilerTest>();
#endif

#ifdef AOT_TEST_MODE
  _test = std::make_unique<AOTCompilerTest>();
#endif

#ifdef REPL_TEST_MODE
  _test = std::make_unique<ReplTest>();
#endif

  return std::move(_test);
}
} // namespace FlowWing
} // namespace Tests