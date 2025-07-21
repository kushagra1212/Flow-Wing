#pragma once

#include "../../diagnostics/DiagnosticHandler/DiagnosticHandler.h"
#include "../../utils/PathUtils.h"
#include "../../utils/Utils.h"

namespace FlowWing {

namespace AOT {

void LINKING_FAIL_ERROR(int status, std::string &fileNameWithOutExtension,
                        std::string version);

void RUN_ON_DEBUG_GENERATE_BC_FROM_LL();

auto getFileNameWithoutExtension(FlowWing::DiagnosticHandler *diagHandler)
    -> std::string;

// CLEAN UP
auto deleteObjectFiles() -> void;

} // namespace AOT

} // namespace FlowWing