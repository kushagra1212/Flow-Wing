#!/bin/bash
set -e

# Arguments:
#   $1: version - Release version (e.g., 1.0.0)
#   $2: release_url - GitHub release HTML URL
#   $3: api_key - Chocolatey API key

VERSION="$1"
RELEASE_URL="$2"
API_KEY="$3"

echo "=== Publishing to Chocolatey ==="
echo "Version: $VERSION"
echo "Release URL: $RELEASE_URL"

# Get the Windows download URL
WINDOWS_URL="$(curl -s "https://api.github.com/repos/kushagra1212/Flow-Wing/releases/tags/v$VERSION" | jq -r '.assets[] | select(.name | test("windows")) | .browser_download_url')"

if [ -z "$WINDOWS_URL" ]; then
  echo "Warning: Could not find Windows artifact for Chocolatey package."
  exit 0
fi

# Get the SHA256 hash
WINDOWS_SHA256="$(curl -s "$WINDOWS_URL" | sha256sum | cut -d' ' -f1)"

# Create the Chocolatey package
mkdir -p flowwing.nuspec flowwing/tools

cat > flowwing.nuspec << NUSPEC_EOF
<?xml version="1.0" encoding="utf-8"?>
<package xmlns="http://schemas.microsoft.com/packaging/2015/06/nuspec.xsd">
  <metadata>
    <id>flowwing</id>
    <version>$VERSION</version>
    <title>FlowWing</title>
    <authors>Kushagra Rathore</authors>
    <projectUrl>https://github.com/kushagra1212/Flow-Wing</projectUrl>
    <iconUrl>https://raw.githubusercontent.com/kushagra1212/Flow-Wing/main/src/lsp/client/src/resources/icon.png</iconUrl>
    <licenseUrl>https://raw.githubusercontent.com/kushagra1212/Flow-Wing/main/LICENSE.txt</licenseUrl>
    <license>GPL-2.0-only</license>
    <projectSourceUrl>https://github.com/kushagra1212/Flow-Wing</projectSourceUrl>
    <docsUrl>https://github.com/kushagra1212/Flow-Wing</docsUrl>
    <bugTrackerUrl>https://github.com/kushagra1212/Flow-Wing/issues</bugTrackerUrl>
    <tags>flowwing programming language compiler jit aot</tags>
    <summary>A fast, simple, and easy to use programming language</summary>
    <description>A fast, simple, and easy to use programming language with static and dynamic typing, object-oriented programming, and memory management.</description>
  </metadata>
</package>
NUSPEC_EOF

cat > flowwing/tools/chocolateyinstall.ps1 << 'PS1_EOF'
$package = 'flowwing'
$version = '$VERSION'
$url = 'WINDOWS_URL_PLACEHOLDER'
$checksum = 'WINDOWS_SHA256_PLACEHOLDER'
$checksumType = 'sha256'
$installDir = Join-Path $env:ProgramFiles "FlowWing\$version"

Install-ChocolateyZipPackage -PackageName "$package" `
  -Url "$url" `
  -UnzipLocation "$installDir" `
  -Checksum "$checksum" `
  -ChecksumType "$checksumType"

# Add to PATH
$binPath = Join-Path $installDir 'bin'
$null = [System.Environment]::SetEnvironmentVariable('PATH', "$env:PATH;$binPath", 'Machine')

# Create start menu shortcut
$shortcutPath = Join-Path $env:ProgramData 'Microsoft\Windows\Start Menu\Programs\FlowWing.lnk'
Install-ChocolateyShortcut -ShortcutFilePath $shortcutPath `
  -TargetPath (Join-Path $installDir 'bin\FlowWing.exe') `
  -WorkDir $installDir
PS1_EOF

# Replace placeholders
sed -i "s/WINDOWS_URL_PLACEHOLDER/$WINDOWS_URL/g" flowwing/tools/chocolateyinstall.ps1
sed -i "s/WINDOWS_SHA256_PLACEHOLDER/$WINDOWS_SHA256/g" flowwing/tools/chocolateyinstall.ps1

cat > flowwing/tools/chocolateyuninstall.ps1 << 'UNINSTALL_EOF'
$installDir = Join-Path $env:ProgramFiles "FlowWing"

# Remove all FlowWing versions
Get-ChildItem $installDir -Directory | ForEach-Object {
  if ($_.Name -match '^\d+\.\d+\.\d+$') {
    Remove-Item $_.FullName -Recurse -Force
  }
}

# Remove from PATH
$path = [System.Environment]::GetEnvironmentVariable('PATH', 'Machine')
$path = $path -replace ';[;]*[^\;]*FlowWing[^;]*', ''
[System.Environment]::SetEnvironmentVariable('PATH', $path, 'Machine')

# Remove start menu shortcut
$shortcutPath = Join-Path $env:ProgramData 'Microsoft\Windows\Start Menu\Programs\FlowWing.lnk'
if (Test-Path $shortcutPath) {
  Remove-Item $shortcutPath -Force
}
UNINSTALL_EOF

# Package and push
choco pack flowwing.nuspec
choco push flowwing.$VERSION.nupkg --source https://push.chocolatey.org/ --api-key "$API_KEY"

echo "=== Chocolatey package published ==="
