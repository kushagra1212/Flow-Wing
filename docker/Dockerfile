# ---- Base Stage ----
# Use a specific version of the base image for reproducible builds.
# Consider using a minimal base image to reduce the final image size.
FROM kushagra711/common-base-llvm:latest AS base
WORKDIR /compiler

# ---- Builder Stage ----
# This stage compiles the source code.
FROM base AS builder
# Copy only the necessary source files for building.
# Consider using a .dockerignore file to exclude unnecessary files.
COPY . .
# Add comments to explain complex or non-obvious commands.
RUN make clean

# ---- Test Stage ----
# This stage runs the tests.
FROM builder AS test-jit
# Run the just-in-time (JIT) tests.
RUN make build-test-jit


FROM builder AS test-aot
# Run the ahead-of-time (AOT) tests.
RUN make build-test-aot


FROM builder AS build-aot
# Release the image
RUN make build-aot



FROM builder AS build-jit
# Release the image
RUN make build-jit