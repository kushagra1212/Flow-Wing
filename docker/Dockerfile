# ---- Base Stage ----
# Use the pre-built dependency image, which already contains Ubuntu,
# all required packages, and CMake.
FROM kushagra711/flow-wing-compiler-deps:latest AS base


# Copy the remaining source files
# Note: .dockerignore excludes folders like build, fw_dependencies
COPY . .

# Set compiler environment variables
ENV CC=/usr/bin/clang-17
ENV CXX=/usr/bin/clang++-17

# ---- Builder Stage ----
# This stage compiles the source code
FROM base AS builder

# Clean any existing build artifacts
RUN make clean

# ---- Test Stage (JIT) ----
# This stage runs the just-in-time (JIT) tests
FROM builder AS test-jit
RUN make test-jit

# ---- Test Stage (AOT) ----
# This stage runs the ahead-of-time (AOT) tests
FROM builder AS test-aot
RUN make test-aot
