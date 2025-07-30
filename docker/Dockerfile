# ---- Base Stage ----
# Use Ubuntu as the base image for a reproducible environment
FROM ubuntu:latest AS base

# Set environment variables to avoid interactive prompts during package installation
ENV DEBIAN_FRONTEND=noninteractive

# Install required packages for the compiler environment, including libssl-dev for CMake
RUN apt-get update && apt-get install -y \
    clang-17 \
    clang++-17 \
    libgtest-dev \
    g++ \
    gdb \
    wget \
    lsb-release \
    software-properties-common \
    ninja-build \
    zlib1g-dev \
    libzstd-dev \
    libcurl4-openssl-dev \
    libssl-dev \
    lld \
    ccache \
    build-essential \
    python3 \
    && apt-get clean && rm -rf /var/lib/apt/lists/*

# Build and install CMake 3.29.6 from source to ensure compatibility with x86_64 and ARM64
RUN wget https://github.com/Kitware/CMake/releases/download/v3.29.6/cmake-3.29.6.tar.gz && \
    tar -xzf cmake-3.29.6.tar.gz && \
    cd cmake-3.29.6 && \
    ./bootstrap && \
    make -j$(nproc) && \
    make install && \
    cd .. && \
    rm -rf cmake-3.29.6 cmake-3.29.6.tar.gz



# Set the working directory for the compiler project
WORKDIR /compiler



    # Copy the remaining source files
# Note: .dockerignore excludes folders like build, docs, tests/data, .fw_dependencies
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
RUN make build-test-jit

# ---- Test Stage (AOT) ----
# This stage runs the ahead-of-time (AOT) tests
FROM builder AS test-aot
RUN make build-test-aot

# ---- Build Stage (AOT) ----
# This stage creates the AOT release
FROM builder AS build-aot
RUN make build-aot

# ---- Build Stage (JIT) ----
# This stage creates the JIT release
FROM builder AS build-jit
RUN make build-jit