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

# Create the new .deb 
DEB_NAME="flowwing_${DEB_VERSION}_amd64.deb"
dpkg-deb -b flowwing-deb "${DEB_NAME}"

echo "=== Updating APT Repository Index ==="

# 1. Cleanup temporary build folders so apt-ftparchive doesn't scan them
rm -rf flowwing-deb flowwing-deb-extracted flowwing-deb-control /tmp/flowwing.deb

# 2. Smart checkout: Fetch existing gh-pages, OR create a clean empty branch
if git ls-remote --heads origin gh-pages | grep -q gh-pages; then
  echo "Fetching existing gh-pages branch..."
  git fetch origin gh-pages
  git checkout -f gh-pages      # <--- ADD -f HERE
else
  echo "Creating clean gh-pages branch..."
  git checkout --orphan gh-pages
  git rm -rf .  # Delete all source code files from this branch
fi

# 3. Create the directory structure and move the new .deb into it
mkdir -p pool/main
mv "${DEB_NAME}" "pool/main/${DEB_NAME}"

# 4. Import the GPG Private Key
echo "Importing GPG Key..."
echo "$GPG_PRIVATE_KEY" | gpg --import

# Ensure the public key is hosted on the gh-pages branch for users to download
gpg --export --armor "bot@flowwing.dev" > flowwing.gpg.key
git add flowwing.gpg.key

# 5. Generate the Packages index
echo "Scanning packages..."
dpkg-scanpackages --multiversion pool/ > Packages
gzip -k -f Packages

# 6. Generate the Release file
echo "Generating Release file..."
apt-ftparchive release . > Release

# 7. Sign the Release file (This is the magic step!)
echo "Signing the repository..."
# Create Release.gpg (detached signature)
gpg --batch --yes --no-tty --default-key "bot@flowwing.dev" -abs -o Release.gpg Release
# Create InRelease (inline signature)
gpg --batch --yes --no-tty --default-key "bot@flowwing.dev" --clearsign -o InRelease Release

# 8. Landing page for the branch root.
#
# gh-pages is served by GitHub Pages as https://kushagra1212.github.io/Flow-Wing/.
# Without an index.html, Jekyll renders this branch's README.md instead — a copy
# of the source tree frozen whenever the branch was created — so the URL served
# stale content that was never the documentation. Redirect it to the docs site.
#
# Written *after* the Release file is generated and signed, so these files are
# not part of the signed APT index. .nojekyll stops Pages from running Jekyll,
# which both fixes the README fallback and keeps it away from the repo metadata.
echo "Writing docs redirect and .nojekyll..."
DOCS_URL="https://flow-wing-docs.vercel.app/"
cat > index.html <<EOF
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Flow-Wing Documentation</title>
    <meta http-equiv="refresh" content="0; url=${DOCS_URL}">
    <link rel="canonical" href="${DOCS_URL}">
    <meta name="robots" content="noindex">
  </head>
  <body>
    <p>
      The Flow-Wing documentation has moved to
      <a href="${DOCS_URL}">${DOCS_URL}</a>.
    </p>
    <p>
      This host also serves the signed APT repository; see the
      <a href="https://github.com/kushagra1212/Flow-Wing">project README</a>
      for installation instructions.
    </p>
  </body>
</html>
EOF
touch .nojekyll

# 9. Commit and push to the gh-pages branch
echo "Committing to gh-pages..."
git add pool/ Packages Packages.gz Release Release.gpg InRelease index.html .nojekyll
git commit -m "Add flowwing v$DEB_VERSION to signed APT repository"
git push origin gh-pages

echo "=== Signed APT repository updated and pushed ==="