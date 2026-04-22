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

# Get the Windows download URL
WINDOWS_URL="$(curl -s "https://api.github.com/repos/kushagra1212/Flow-Wing/releases/tags/${RAW_VERSION}" | jq -r '.assets[] | select(.name | test("windows")) | .browser_download_url')"

if [ -z "$WINDOWS_URL" ]; then
  echo "Warning: Could not find Windows artifact for Chocolatey package."
  exit 0
fi

# Get the SHA256 hash
WINDOWS_SHA256="$(curl -s "$WINDOWS_URL" | sha256sum | cut -d' ' -f1)"

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
choco push flowwing.$VERSION.nupkg --source https://push.chocolatey.org/ --api-key "$API_KEY"

echo "=== Chocolatey package published ==="