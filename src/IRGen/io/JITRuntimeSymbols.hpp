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

namespace flow_wing::ir_gen::jit_utils {

/**
 * @brief Make the FlowWing C runtime symbols (fg_*, dyn_list_*, dyn_map_*,
 *        file_*, io_*, sys_*, vortex_*, str*) findable by LLJIT's default
 *        DynamicLibrarySearchGenerator.
 *
 * On Linux the compiler build links FlowWing-jit with
 * `-Wl,--export-dynamic`, on macOS `dlsym(RTLD_DEFAULT)` is already able to
 * see all whole-archive'd symbols, so those platforms work out of the box.
 *
 * On Windows (MSVC) however, symbols from a `/WHOLEARCHIVE`'d static lib
 * are *not* placed into the .exe's export directory, so
 * `GetProcAddress(nullptr, "fg_pf")` returns NULL and the JIT fails at
 * link time with `Symbols not found: [ fg_pf, dyn_list_new, ... ]`.
 *
 * To sidestep that, this function pushes every known runtime symbol into
 * `llvm::sys::DynamicLibrary::AddSymbol`, which LLVM's
 * `DynamicLibrarySearchGenerator::GetForCurrentProcess` consults *before*
 * falling back to `GetProcAddress`.  The call is idempotent and safe to
 * invoke on every JIT entry.  The source of truth for the symbol list is
 * `JITRuntimeSymbols.def`.
 */
void registerRuntimeSymbols();

} // namespace flow_wing::ir_gen::jit_utils
