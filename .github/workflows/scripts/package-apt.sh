#!/bin/bash
set -e

# Arguments:
#   $1: version - Release version (e.g., 1.0.0)
#   $2: token - GitHub token for the apt repo
#   $3: username - Git username

VERSION="$1"
TOKEN="$2"
DEB_VERSION="${VERSION#v}"
USERNAME="$3"

echo "=== Publishing to apt ==="
echo "Version: $VERSION"

# Get the Linux download URL
LINUX_URL="$(curl -s -H "Authorization: token $TOKEN" "https://api.github.com/repos/kushagra1212/Flow-Wing/releases/tags/$VERSION" | jq -r '.assets[]? | select(.name | endswith(".deb")) | .browser_download_url' | head -n 1)"

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
Version: $DEB_VERSION
Section: devel
Priority: optional
Architecture: amd64
Depends: libllvm17, libc6, libgl1
Maintainer: FlowWing <kushagrarathore002@gmail.com>
Description: FlowWing Programming Language
 FlowWing is a fast, simple, and easy to use programming language with
 static and dynamic typing, object-oriented programming, and memory management.
DEB_EOF

# Download the original .deb and fully unpack it (data + control) so that
# the postinst/prerm scripts that create /usr/local/bin symlinks are
# preserved in the rebuilt package.
curl -L "$LINUX_URL" -o /tmp/flowwing.deb
dpkg-deb -x /tmp/flowwing.deb flowwing-deb-extracted
dpkg-deb -e /tmp/flowwing.deb flowwing-deb-control

# Copy payload (dest must exist — cp will not create the full path)
mkdir -p flowwing-deb/usr/local/flow-wing
cp -r flowwing-deb-extracted/usr/local/flow-wing/* flowwing-deb/usr/local/flow-wing/

# Carry over any maintainer scripts (postinst, prerm, postrm, preinst) that
# shipped with the upstream package so the repo-rebuilt .deb keeps the
# PATH symlink behaviour.
for script in postinst prerm postrm preinst; do
  if [ -f "flowwing-deb-control/${script}" ]; then
    cp "flowwing-deb-control/${script}" "flowwing-deb/DEBIAN/${script}"
    chmod 0755 "flowwing-deb/DEBIAN/${script}"
  fi
done

# Create the new .deb (brace-delimit VERSION to avoid Bash treating
# ${VERSION_amd64} as a single, undefined variable)
DEB_NAME="flowwing_${DEB_VERSION}_amd64.deb"
dpkg-deb -b flowwing-deb "${DEB_NAME}"

echo "=== Updating APT Repository Index ==="

# 1. Switch to a persistent gh-pages branch (create it if it doesn't exist)
# We stash any current changes just in case, fetch the remote, and checkout.
git fetch origin
git checkout gh-pages 2>/dev/null || git checkout -b gh-pages

# 2. Create the directory structure and move the new .deb into it
mkdir -p pool/main
mv "${DEB_NAME}" "pool/main/${DEB_NAME}"

# 3. Generate the Packages index
# This scans the pool/ directory and creates an index of all .deb files
echo "Scanning packages..."
dpkg-scanpackages --multiversion pool/ > Packages
gzip -k -f Packages

# 4. Generate the Release file
# This tells the apt client about the architectures and components supported
echo "Generating Release file..."
apt-ftparchive release . > Release

# 5. Commit and push to the gh-pages branch
echo "Committing to gh-pages..."
git add pool/ Packages Packages.gz Release
git commit -m "Add flowwing v$DEB_VERSION to APT repository"
git push -u origin gh-pages

echo "=== APT repository updated and pushed ==="