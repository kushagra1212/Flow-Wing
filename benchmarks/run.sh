#!/usr/bin/env bash
#
# FlowWing Compiler
# Copyright (C) 2023-2026 Kushagra Rathore
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License along
# with this program; if not, write to the Free Software Foundation, Inc.,
# 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
#
# =============================================================================
# Builds the benchmark driver if needed, then measures every case and writes a
# timestamped report.
#
# All arguments are forwarded to the driver, so the sampling knobs are
# available without editing anything:
#
#   ./benchmarks/run.sh
#   ./benchmarks/run.sh --iterations=10 --repetitions=15
#   ./benchmarks/run.sh --opt=-O3
#   ./benchmarks/run.sh --benchmark_filter='run/0[12]'
# =============================================================================

set -euo pipefail

BENCH_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd "${BENCH_DIR}/.." && pwd)"
CMAKE_BUILD_DIR="${BENCH_DIR}/build/cmake"
DRIVER="${CMAKE_BUILD_DIR}/bench_driver"
FLOWWING="${REPO_ROOT}/build/sdk/bin/FlowWing"

if [[ ! -x "${FLOWWING}" ]]; then
    echo "error: FlowWing not found at ${FLOWWING}" >&2
    echo "       build it first:  make build-aot-release" >&2
    exit 1
fi

echo "==> Configuring benchmark driver"
cmake -S "${BENCH_DIR}" -B "${CMAKE_BUILD_DIR}" -DCMAKE_BUILD_TYPE=Release >/dev/null

echo "==> Building benchmark driver"
cmake --build "${CMAKE_BUILD_DIR}" -j"$(getconf _NPROCESSORS_ONLN 2>/dev/null || echo 4)" >/dev/null

STAMP="$(date -u +%Y-%m-%dT%H-%M-%SZ)"
RESULT_DIR="${BENCH_DIR}/results/${STAMP}"
mkdir -p "${RESULT_DIR}"

echo "==> Running benchmarks (results: ${RESULT_DIR})"
"${DRIVER}" --out="${RESULT_DIR}/report.md" "$@"

# A stable path for the most recent run, so tooling and docs can link one
# location instead of chasing timestamps.
ln -sfn "${STAMP}" "${BENCH_DIR}/results/latest"

echo
echo "==> Report: ${RESULT_DIR}/report.md"
echo "==> Latest: ${BENCH_DIR}/results/latest/report.md"
