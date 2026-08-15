#!/bin/bash
set -e

# Arguments:
#   $1: version - Release version (e.g., 1.0.0)
#   $2: release_url - GitHub release HTML URL
#   $3: api_key - Chocolatey API key

RAW_VERSION="$1"
VERSION="${RAW_VERSION#v}"  # strip leading 'v' for Chocolatey semver compatibility
RELEASE_URL="$2"
API_KEY="$3"

echo "=== Publishing to Chocolatey ==="
echo "Raw version: $RAW_VERSION"
echo "Version (for package): $VERSION"
echo "Release URL: $RELEASE_URL"

# Get the Windows download URL.
#
# SDK zip only. The release publishes BOTH `-windows-x86_64.zip` and
# `-windows-x86_64.exe`, so a loose `test("windows")` matched both and jq
# emitted two lines into this one variable — the v1.0.7 package shipped a `url`
# field containing two newline-separated URLs, which 404s and failed Chocolatey
# verification. Match the zip exactly (Install-ChocolateyZipPackage needs the
# zip) and take a single line. Same guard as package-homebrew.sh.
WINDOWS_URL="$(curl -fsSL "https://api.github.com/repos/kushagra1212/Flow-Wing/releases/tags/${RAW_VERSION}" \
  | jq -r '.assets[]? | select(.name | endswith("-windows-x86_64.zip")) | .browser_download_url' \
  | head -n1)"

if [ -z "$WINDOWS_URL" ]; then
  echo "Warning: Could not find Windows artifact for Chocolatey package."
  exit 0
fi

# A URL that still contains whitespace means the selector matched more than one
# asset; publishing that would repeat the v1.0.7 failure silently.
case "$WINDOWS_URL" in
  *[[:space:]]*)
    echo "Error: resolved more than one Windows asset URL:" >&2
    printf '%s\n' "$WINDOWS_URL" >&2
    exit 1
    ;;
esac
echo "Windows asset: $WINDOWS_URL"

# Get the SHA256 hash.
#
# Download to a file and hash the file. `curl -s | sha256sum` silently hashes an
# empty stream when the request fails, which would publish a package whose
# checksum never matches and break `choco install` for everyone. The releases
# download host can also answer 503 for a while after the upload job finishes,
# so retry over several minutes (same reasoning as package-homebrew.sh).
WINDOWS_ZIP="$(mktemp)"
if ! curl -fSL \
    --connect-timeout 20 \
    --retry 8 --retry-delay 15 --retry-max-time 300 --retry-all-errors \
    -o "$WINDOWS_ZIP" "$WINDOWS_URL"; then
  rm -f "$WINDOWS_ZIP"
  echo "Error: failed to download Windows release asset: ${WINDOWS_URL}" >&2
  exit 1
fi
if [ ! -s "$WINDOWS_ZIP" ]; then
  rm -f "$WINDOWS_ZIP"
  echo "Error: downloaded Windows release asset is 0 bytes: ${WINDOWS_URL}" >&2
  exit 1
fi
WINDOWS_SHA256="$(sha256sum "$WINDOWS_ZIP" | cut -d' ' -f1)"
rm -f "$WINDOWS_ZIP"

if [ -z "$API_KEY" ]; then
  echo "Warning: CHOCOLATEY_API_KEY is not set; skipping Chocolatey pack and push."
  exit 0
fi

# -----------------------------------------------------------------------------
# FIX: Use a relative directory. Native Windows Python does not understand
# Git Bash's virtual "/tmp" directory path.
# -----------------------------------------------------------------------------
BUILD_DIR="choco-build"
rm -rf "$BUILD_DIR"
mkdir -p "$BUILD_DIR/tools"

# Create the Chocolatey package metadata
cat > "$BUILD_DIR/flowwing.nuspec" << NUSPEC_EOF
<?xml version="1.0" encoding="utf-8"?>
<package xmlns="http://schemas.microsoft.com/packaging/2015/06/nuspec.xsd">
  <metadata>
    <id>flowwing</id>
    <version>$VERSION</version>
    <title>FlowWing</title>
    <authors>Kushagra Rathore</authors>
    <owners>Kushagra Rathore</owners>
    <projectUrl>https://github.com/kushagra1212/Flow-Wing</projectUrl>
    <iconUrl>https://raw.githubusercontent.com/kushagra1212/Flow-Wing/main/src/lsp/client/src/resources/icon.png</iconUrl>
    <licenseUrl>https://raw.githubusercontent.com/kushagra1212/Flow-Wing/main/LICENSE.txt</licenseUrl>
    <projectSourceUrl>https://github.com/kushagra1212/Flow-Wing</projectSourceUrl>
    <packageSourceUrl>https://github.com/kushagra1212/Flow-Wing</packageSourceUrl>
    <docsUrl>https://github.com/kushagra1212/Flow-Wing</docsUrl>
    <bugTrackerUrl>https://github.com/kushagra1212/Flow-Wing/issues</bugTrackerUrl>
    <releaseNotes>$RELEASE_URL</releaseNotes>
    <tags>flowwing programming language compiler jit aot</tags>
    <summary>A fast, simple, and easy to use programming language</summary>
    <description>A fast, simple, and easy to use programming language with static and dynamic typing, object-oriented programming, and memory management.</description>
  </metadata>
  <files>
    <file src="tools\**" target="tools" />
  </files>
</package>
NUSPEC_EOF

cat > "$BUILD_DIR/tools/chocolateyinstall.ps1" << 'PS1_EOF'
$ErrorActionPreference = 'Stop'
# Installed next to this script: tools/bin, tools/lib/... (release zip layout)
$toolsDir = Split-Path -Parent $MyInvocation.MyCommand.Definition
$packageArgs = @{
  packageName    = 'flowwing'
  unzipLocation  = $toolsDir
  url            = 'WINDOWS_URL_PLACEHOLDER'
  checksum       = 'WINDOWS_SHA256_PLACEHOLDER'
  checksumType   = 'sha256'
}
Install-ChocolateyZipPackage @packageArgs
$binDir = Join-Path $toolsDir 'bin'
Install-ChocolateyPath -PathToInstall $binDir -PathType 'Machine'
PS1_EOF

# FIX: Pass the relative BUILD_DIR into Python to ensure paths match
WU="$WINDOWS_URL" WS="$WINDOWS_SHA256" BDIR="$BUILD_DIR" python3 << 'PY'
from pathlib import Path
import os
p = Path(os.environ["BDIR"]) / "tools" / "chocolateyinstall.ps1"
t = p.read_text()
t = t.replace("WINDOWS_URL_PLACEHOLDER", os.environ["WU"])
t = t.replace("WINDOWS_SHA256_PLACEHOLDER", os.environ["WS"])
p.write_text(t)
PY

cat > "$BUILD_DIR/tools/chocolateyuninstall.ps1" << 'UNINSTALL_EOF'
$ErrorActionPreference = 'Stop'
$toolsDir = Split-Path -Parent $MyInvocation.MyCommand.Definition
$binDir = Join-Path $toolsDir 'bin'
$machinePath = [Environment]::GetEnvironmentVariable('Path', 'Machine')
$newPath = ($machinePath -split ';' | Where-Object { $_ -and ($_ -ne $binDir) }) -join ';'
[Environment]::SetEnvironmentVariable('Path', $newPath, 'Machine')
UNINSTALL_EOF

# Move into the clean staging directory to build and push
cd "$BUILD_DIR"
choco pack flowwing.nuspec

# `choco push` reports only "Response status code does not indicate success:
# 403 (Forbidden)", which does not say which of several unrelated causes it hit.
# Translate the common ones so the log is actionable.
if ! choco push "flowwing.$VERSION.nupkg" \
      --source https://push.chocolatey.org/ --api-key "$API_KEY"; then
  echo "" >&2
  echo "Error: 'choco push' was rejected for flowwing $VERSION." >&2
  echo "The package built fine, so this is a publishing/credential problem:" >&2
  echo "  403 Forbidden - the CHOCOLATEY_API_KEY secret is invalid, expired or" >&2
  echo "                  regenerated, or its account does not have push rights" >&2
  echo "                  for the 'flowwing' package id." >&2
  echo "                  Fix: regenerate the key at" >&2
  echo "                  https://community.chocolatey.org/account and update the" >&2
  echo "                  CHOCOLATEY_API_KEY repository secret." >&2
  echo "  409 Conflict  - version $VERSION is already published; bump the tag." >&2
  exit 1
fi

echo "=== Chocolatey package published ==="