#!/bin/bash

# Define the URL of the Debian package to download
PACKAGE_URL="https://github.com/kushagra1212/Flow-Wing/releases/download/v0.0.1-alpha/FlowWing-0.0.1-Linux.deb"

# Define the name of the downloaded Debian package
PACKAGE_FILE="FlowWing-0.0.1-Linux.deb"

# Define the path to the clang-17 binary
CLANG_BINARY="/usr/local/lib/FlowWing/dependencies/llvm-17/bin/clang-17"

# Download the Debian package
echo "Downloading $PACKAGE_FILE..."
wget "$PACKAGE_URL"

# Install the Debian package
echo "Installing $PACKAGE_FILE..."
sudo dpkg -i "$PACKAGE_FILE"

# Indicate that we're getting things ready
echo "Getting things ready.."

# Grant permission to the clang-17 binary
sudo chmod +x "$CLANG_BINARY"

echo "Installation complete."