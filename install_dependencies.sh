#!/bin/bash

# Update package list and install required packages
sudo apt-get update
sudo apt-get install -y \
    cmake \
    libgtest-dev \
    llvm-dev \
    g++ \
    gdb \
    wget \
    lsb-release \
    software-properties-common \
    ninja-build \
    zlib1g-dev \
    libzstd-dev \
    libcurl4-openssl-dev \
    lld \
    ccache

# Clean up
sudo apt-get clean
sudo rm -rf /var/lib/apt/lists/*

# Install LLVM 17
wget https://apt.llvm.org/llvm.sh
chmod +x llvm.sh
./llvm.sh 17

# Clean up
rm llvm.sh
