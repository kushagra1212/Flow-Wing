#!/bin/bash
set -e

# Arguments:
#   $1: version - Release version (e.g., 1.0.0)
#   $2: token - GitHub token for the apt repo
#   $3: username - Git username

VERSION="$1"
TOKEN="$2"
USERNAME="$3"

echo "=== Publishing to apt ==="
echo "Version: $VERSION"

# Get the Linux download URL
LINUX_URL="$(curl -s "https://api.github.com/repos/kushagra1212/Flow-Wing/releases/tags/$VERSION" | jq -r '.assets[] | select(.name | test("linux")) | .browser_download_url')"

if [ -z "$LINUX_URL" ]; then
  echo "Warning: Could not find Linux artifact for apt repository."
  exit 0
fi

# Create a branch and PR for the apt repo
git config user.name "FlowWing Bot"
git config user.email "bot@flowwing.dev"
git checkout -b "add-flowwing-$VERSION"

# Create the .deb package structure
mkdir -p flowwing-deb/DEBIAN
cat > flowwing-deb/DEBIAN/control << DEB_EOF
Package: flowwing
Version: $VERSION
Section: devel
Priority: optional
Architecture: amd64
Maintainer: FlowWing <kushagrarathore002@gmail.com>
Description: FlowWing Programming Language
 FlowWing is a fast, simple, and easy to use programming language with
 static and dynamic typing, object-oriented programming, and memory management.
 DEB_EOF

# Download and extract the .deb from the release
curl -L "$LINUX_URL" -o /tmp/flowwing.deb
dpkg-deb -x /tmp/flowwing.deb flowwing-deb-extracted

# Copy the extracted files (dest must exist — cp will not create the full path)
mkdir -p flowwing-deb/usr/local/flow-wing
cp -r flowwing-deb-extracted/usr/local/flow-wing/* flowwing-deb/usr/local/flow-wing/

# Create the new .deb
dpkg-deb -b flowwing-deb flowwing_$VERSION_amd64.deb

# Upload to apt repository
curl -H "Authorization: token $TOKEN" \
  -H "Content-Type: application/octet-stream" \
  --upload-file flowwing_$VERSION_amd64.deb \
  "https://api.github.com/repos/$USERNAME/flowwing-apt/contents/pool/flowwing/flowwing_$VERSION_amd64.deb"

echo "=== apt package uploaded ==="
