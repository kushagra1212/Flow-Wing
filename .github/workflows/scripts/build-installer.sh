#!/bin/bash
set -e

# Arguments:
#   $1: install_prefix - The installation directory (e.g., /usr/local/flow-wing/1.0.0/)
#   $2: installer_name - The output installer filename (e.g., FlowWing-1.0.0-macos-arm64.dmg)
#   $3: os - Platform (macOS, Windows, Linux)
#   $4: arch - Architecture (arm64, x86_64)

INSTALL_PREFIX="$1"
INSTALLER_NAME="$2"
OS="$3"
ARCH="$4"

echo "=== Building installer $INSTALLER_NAME ($OS $ARCH) ==="
echo "Install prefix: $INSTALL_PREFIX"
echo "Installer name: $INSTALLER_NAME"

case "$OS" in
  macOS)
    # Create .dmg using create-dmg
    echo "Creating macOS .dmg installer..."
    
    # Create the app directory structure
    mkdir -p /tmp/FlowWing\ Installer.app/Contents/Resources
    mkdir -p /tmp/FlowWing\ Installer.app/Contents/MacOS
    
    # Copy the FlowWing binary and SDK to the app bundle
    cp -r "$INSTALL_PREFIX" /tmp/FlowWing\ Installer.app/Contents/Resources/
    
    # Create a simple shell script wrapper in the app bundle
    cat > /tmp/FlowWing\ Installer.app/Contents/MacOS/FlowWing << 'WRAPPER'
#!/bin/bash
SCRIPT_DIR="$(cd "$(dirname "$0")"/../Resources/lib/modules/../../.." 2>/dev/null || pwd)"
export PATH="$SCRIPT_DIR/bin:$PATH"
export FLOWWING_MODULES_PATH="$SCRIPT_DIR/lib/modules"
export FLOWWING_LIB_PATH="$SCRIPT_DIR/lib"
exec "$SCRIPT_DIR/bin/FlowWing" "$@"
WRAPPER
    chmod +x /tmp/FlowWing\ Installer.app/Contents/MacOS/FlowWing
    
    # Create the .dmg
    create-dmg \
      --volname "FlowWing $FLOWWING_VERSION" \
      --window-size 600 400 \
      --icon-size 128 \
      --icon "FlowWing Installer.app" 150 200 \
      --app-drop-link 450 200 \
      "/tmp/$INSTALLER_NAME" \
      "/tmp/FlowWing Installer.app"
    
    echo "macOS .dmg created: /tmp/$INSTALLER_NAME"
    mv /tmp/$INSTALLER_NAME "$INSTALLER_NAME"
    ;;
    
  Windows)
    # Create NSIS installer
    echo "Creating Windows NSIS installer..."
    
    # Create NSIS script
    cat > installer.nsi << NSIS_EOF
!include MUI.nsh
!include LogicLib.nsh

Name "FlowWing $FLOWWING_VERSION"
OutFile "$INSTALLER_NAME"

RequestExecutionLevel admin
SetOverwrite on

!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_INSTFILES

!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES

!insertmacro MUI_LANGUAGE English

; Default install directory
InstallDir "C:\Program Files\FlowWing\\$FLOWWING_VERSION"

Section "Install"
  SetOutPath \$INSTDIR
  
  ; Copy all files from the install prefix
  File /r "$INSTALL_PREFIX\*"
  
  ; Create Start Menu shortcut
  CreateShortCut "\$SMPROGRAMS\FlowWing.lnk" "\$INSTDIR\bin\FlowWing.exe" ""
  
  ; Write Registry keys for uninstaller
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\FlowWing" "DisplayVersion" "$FLOWWING_VERSION"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\FlowWing" "InstallLocation" "\$INSTDIR"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\FlowWing" "UninstallString" "\$INSTDIR\uninstall.exe"
  
  ; Add bin to System PATH using PowerShell (Bypasses NSIS 1024-char limit)
  DetailPrint "Adding FlowWing to System PATH..."
  nsExec::ExecToLog 'powershell.exe -NoProfile -ExecutionPolicy Bypass -Command "\$target = ''\$INSTDIR\bin''; \$path = [Environment]::GetEnvironmentVariable(''PATH'', ''Machine''); if (\$path -notmatch [regex]::Escape(\$target)) { [Environment]::SetEnvironmentVariable(''PATH'', \$path + '';'' + \$target, ''Machine'') }"'
  
  ; Create uninstaller
  WriteUninstaller "\$INSTDIR\uninstall.exe"
SectionEnd

Section "Uninstall"
  ; Remove from System PATH using PowerShell
  DetailPrint "Removing FlowWing from System PATH..."
  nsExec::ExecToLog 'powershell.exe -NoProfile -ExecutionPolicy Bypass -Command "\$target = ''\$INSTDIR\bin''; \$path = [Environment]::GetEnvironmentVariable(''PATH'', ''Machine''); \$newPath = (\$path -split '';'' | Where-Object { \$_ -and \$_ -ne \$target }) -join '';''; [Environment]::SetEnvironmentVariable(''PATH'', \$newPath, ''Machine'')"'
  
  ; Remove registry entries
  DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\FlowWing"
  
  ; Remove start menu shortcut
  Delete "\$SMPROGRAMS\FlowWing.lnk"
  
  ; Remove installed files
  RMDir /r "\$INSTDIR"
SectionEnd
NSIS_EOF
    
    # Build the installer
    makensis installer.nsi
    
    echo "Windows NSIS installer created: $INSTALLER_NAME"
    ;;
    
  Linux)
    # Create .deb using fpm
    echo "Creating Linux .deb installer..."

    DEB_ARCH=$ARCH
    if [ "$ARCH" = "x86_64" ]; then
      DEB_ARCH="amd64"
    fi
    
    # Create control file
    mkdir -p /tmp/flowwing-deb/DEBIAN
    cat > /tmp/flowwing-deb/DEBIAN/control << DEB_EOF
Package: flowwing
Version: $FLOWWING_VERSION
Section: devel
Priority: optional
Architecture: $DEB_ARCH
Maintainer: FlowWing <kushagrarathore002@gmail.com>
Description: FlowWing Programming Language
 FlowWing is a fast, simple, and easy to use programming language with
 static and dynamic typing, object-oriented programming, and memory management.
DEB_EOF

    # Package using fpm (DEB_ARCH is e.g. amd64 for x86_64)
    # Note: fpm has no --deb-repo; use --deb-field for custom control stanzas if needed.
    fpm -f \
      -s dir \
      -t deb \
      -n flowwing \
      -v "$FLOWWING_VERSION" \
      -a "$DEB_ARCH" \
      --after-install .github/workflows/scripts/post-install.sh \
      --before-remove .github/workflows/scripts/pre-remove.sh \
      --package "$INSTALLER_NAME" \
      "$INSTALL_PREFIX"
    
    echo "Linux .deb installer created: $INSTALLER_NAME"
    ;;
esac

echo "=== Installer build complete ==="
