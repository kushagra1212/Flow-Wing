#ifndef _TESTS_COMMON_H
#define _TESTS_COMMON_H

#include "AOTCompilerTest/AOTCompilerTest.h"
#include "JITCompilerTest/JITCompilerTest.h"
#include "ReplTest/ReplTest.h"

namespace Tests {
namespace FlowWing {

std::unique_ptr<BaseTest> getTest();

}
} // namespace Tests

#endif // _TESTS_COMMON_H