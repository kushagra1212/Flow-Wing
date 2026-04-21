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

// The FlowWing runtime (built_in_module, dynamic, flowwing_{vec,map,text,
// file,io,vortex}) is only /WHOLEARCHIVE'd into the compiler binary when
// building in JIT mode — see cmake/targets.cmake, the `if(NOT BUILD_AOT)`
// branch.  In AOT mode those static libs are not linked into the compiler
// (they're shipped separately and consumed by the bundled clang++ when
// compiling user code), so references like `&fg_pf` here would fail to
// resolve at link time.  Guard the whole body with JIT_MODE and keep the
// public `registerRuntimeSymbols()` entry point as a no-op stub in AOT so
// JITCompilerPass.cpp stays free of #ifdefs.
#ifdef JIT_MODE

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

#endif // JIT_MODE

namespace flow_wing::ir_gen::jit_utils {

void registerRuntimeSymbols() {
#ifdef JIT_MODE
  // `AddSymbol` stores into a global map inside LLVM, so repeated calls
  // just overwrite the same entries — idempotent by construction.
#  define FW_JIT_RUNTIME_SYMBOL(name)                                          \
    llvm::sys::DynamicLibrary::AddSymbol(                                      \
        #name, reinterpret_cast<void *>(&name));
#  include "JITRuntimeSymbols.def"
#  undef FW_JIT_RUNTIME_SYMBOL
#endif // JIT_MODE
}

} // namespace flow_wing::ir_gen::jit_utils
