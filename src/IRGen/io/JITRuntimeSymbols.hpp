/*
 * FlowWing Compiler
 * Copyright (C) 2023-2026 Kushagra Rathore
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#pragma once

// clang-format off
#include "src/common/diagnostics/diagnostic_push.h"
#include <llvm/ExecutionEngine/Orc/LLJIT.h>
#include "src/common/diagnostics/diagnostic_pop.h"
// clang-format on

namespace flow_wing::ir_gen::jit_utils {

/**
 * @brief Install the FlowWing C runtime symbols (fg_*, dyn_list_*, dyn_map_*,
 *        file_*, io_*, vortex_*, str*) as absolute definitions inside the
 *        JIT's MainJITDylib.
 *
 * Why not just rely on LLJIT's default
 * `DynamicLibrarySearchGenerator::GetForCurrentProcess`?
 *
 *   The default generator ultimately calls
 *   `llvm::sys::DynamicLibrary::getAddressOfSymbol`, which on every platform
 *   goes through `dlsym(RTLD_DEFAULT, ...)` / `GetProcAddress(nullptr, ...)`
 *   and — per the header's own docs — does NOT consult symbols registered
 *   via `llvm::sys::DynamicLibrary::AddSymbol`.
 *
 *   * On macOS / Linux the compiler links with `-force_load` /
 *     `--whole-archive` + (on Linux) `--export-dynamic`, so the runtime
 *     functions end up in the dynamic symbol table and `dlsym` finds them.
 *
 *   * On Windows, symbols brought in via `/WHOLEARCHIVE` are NOT placed in
 *     the PE export directory, so `GetProcAddress(nullptr, "fg_pf")`
 *     returns NULL and ORC reports
 *     `Symbols not found: [ fg_pf, dyn_list_new, ... ]`.
 *
 * Defining the addresses as absolute symbols inside MainJITDylib bypasses
 * that whole path: ORC resolves them from the materialization unit we hand
 * it before it ever asks the process-wide dynamic library generator.  The
 * source of truth for the symbol list is `JITRuntimeSymbols.def`.
 *
 * In AOT builds this is a no-op — the runtime libs aren't linked into the
 * compiler binary, so taking `&fg_pf` would be an unresolved external.  The
 * `.cpp` guards all runtime references with `#ifdef JIT_MODE`.
 */
void registerRuntimeSymbols(llvm::orc::LLJIT &JIT);

} // namespace flow_wing::ir_gen::jit_utils
