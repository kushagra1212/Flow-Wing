/*
 * FlowWing Compiler
 * Copyright (C) 2023-2026 Kushagra Rathore
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#include "JITRuntimeSymbols.hpp"

// clang-format off
#include "src/common/diagnostics/diagnostic_push.h"
#include <llvm/ADT/StringRef.h>
#include <llvm/Support/DynamicLibrary.h>
#include "src/common/diagnostics/diagnostic_pop.h"
// clang-format on

// Opaque forward declarations of every runtime entry point.  We only ever
// take the address of these functions and pass it to
// `DynamicLibrary::AddSymbol` as a `void*`, so the signature we pick here
// does not have to match the real definition in the runtime .c/.cpp — the
// linker resolves by name alone.  Using `void(void)` keeps the TU
// header-free so we don't have to drag in runtime-internal types
// (DynamicValue, FileHandle, …) from every module.
extern "C" {
#define FW_JIT_RUNTIME_SYMBOL(name) void name(void);
#include "JITRuntimeSymbols.def"
#undef FW_JIT_RUNTIME_SYMBOL
} // extern "C"

namespace flow_wing::ir_gen::jit_utils {

void registerRuntimeSymbols() {
  // `AddSymbol` stores into a global map inside LLVM, so repeated calls
  // just overwrite the same entries — idempotent by construction.
#define FW_JIT_RUNTIME_SYMBOL(name)                                            \
  llvm::sys::DynamicLibrary::AddSymbol(                                        \
      #name, reinterpret_cast<void *>(&name));
#include "JITRuntimeSymbols.def"
#undef FW_JIT_RUNTIME_SYMBOL
}

} // namespace flow_wing::ir_gen::jit_utils
