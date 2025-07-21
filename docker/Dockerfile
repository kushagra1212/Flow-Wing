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
FROM builder AS test
# Run the just-in-time (JIT) and ahead-of-time (AOT) tests.
RUN make build-test-jit
RUN make build-test-aot
# ---- Final Stage ----
# This is the final, lean image for production.
# It only contains the compiled application, not the build tools or source code.
FROM base
# Release the image
